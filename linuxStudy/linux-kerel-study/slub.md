
##  kmem_cache_open 

```c
/*
 * Slab cache management.
 */
struct kmem_cache {
	struct kmem_cache_cpu __percpu *cpu_slab;
	/* Used for retriving partial slabs etc */
	unsigned long flags;
	unsigned long min_partial;
	int size;		/* The size of an object including meta data */
	int objsize;		/* The size of an object without meta data */
	int offset;		/* Free pointer offset. */
	int cpu_partial;	/* Number of per cpu partial objects to keep around */
	struct kmem_cache_order_objects oo;

	/* Allocation and freeing of slabs */
	struct kmem_cache_order_objects max;
	struct kmem_cache_order_objects min;
	gfp_t allocflags;	/* gfp flags to use on each alloc */
	int refcount;		/* Refcount for slab cache destroy */
	void (*ctor)(void *);
	int inuse;		/* Offset to metadata */
	int align;		/* Alignment */
	int reserved;		/* Reserved bytes at the end of slabs */
	const char *name;	/* Name (only for display!) */
	struct list_head list;	/* List of slab caches */
#ifdef CONFIG_SYSFS
	struct kobject kobj;	/* For sysfs */
#endif

#ifdef CONFIG_NUMA
	/*
	 * Defragmentation by allocating from a remote node.
	 */
	int remote_node_defrag_ratio;
#endif
	struct kmem_cache_node *node[MAX_NUMNODES];
};



struct kmem_cache_node {
	spinlock_t list_lock;	/* Protect partial list and nr_partial */
	unsigned long nr_partial;
	struct list_head partial;
#ifdef CONFIG_SLUB_DEBUG
	atomic_long_t nr_slabs;
	atomic_long_t total_objects;
	struct list_head full;
#endif
};
```

static int kmem_cache_open(struct kmem_cache *s,
		const char *name, size_t size,
		size_t align, unsigned long flags,
		void (*ctor)(void *))
		
首先对s的成员 name size align flags reserved进行初始化，

set_min_partial(s, ilog2(s->size) / 2);	
设置 min_partial 最小为5 最大为 10

if (slab_state == DOWN)
			early_kmem_cache_node_alloc(node);
第一次时进入这个函数。 里面调用 new_slab 分配一个slab page。
并初始化 freelist inuse frozen   
init_kmem_cache_node(n, kmem_cache_node); 将n->partial 初始化为链表头。
freelist 使用下面的函数进行初始化。
```c
static inline void *get_freepointer(struct kmem_cache *s, void *object)
{
	return *(void **)(object + s->offset);
}
```  

和下面这个函数一起为 struct kmem_cache 类型的结构体分配了一个
kmem_cache_nodes 和 这个类型的  kmem_cache_cpus 的结构。  
`alloc_kmem_cache_cpus(s)`


/* Able to allocate the per node structures */
slab_state = PARTIAL;

申请一个 叫做 kmem_cache 的结构体
temp_kmem_cache = kmem_cache;
kmem_cache_open(kmem_cache, "kmem_cache", kmem_size,
		0, SLAB_HWCACHE_ALIGN | SLAB_PANIC, NULL);

但是在open之后就立马alloc了一下。还把temp_kmem_cache拷贝了回去？
kmem_cache = kmem_cache_alloc(kmem_cache, GFP_NOWAIT);
memcpy(kmem_cache, temp_kmem_cache, kmem_size);

## slab_alloc
/*
* Inlined fastpath so that allocation functions (kmalloc, kmem_cache_alloc)
* have the fastpath folded into their functions. So no function call
* overhead for requests that can be satisfied on the fastpath.
*
* The fastpath works by first checking if the lockless freelist can be used.
* If not then __slab_alloc is called for slow processing.
*
* Otherwise we can simply pick the next object from the lockless free list.
*/

slab_alloc(s, gfpflags, NUMA_NO_NODE, _RET_IP_);


## 关于谁初始化的 size-x 破案了

```c
static struct cache_names __initdata cache_names[] = {
#define CACHE(x) { .name = "size-" #x, .name_dma = "size-" #x "(DMA)" },
#include <linux/kmalloc_sizes.h>
	{NULL,}
#undef CACHE
};
```c

直接就蒙了，后来才明白。

这种初始化在声明的时候才会调用到里面的`#include`中的头文件，而头文件中就是一大堆关于
`CHANE`的声明。  
```c
........

#if L1_CACHE_BYTES < 64
	CACHE(96)
#endif
	CACHE(128)
#if L1_CACHE_BYTES < 128
	CACHE(192)
#endif
	CACHE(256)
	CACHE(512)
	CACHE(1024)
	CACHE(2048)
	CACHE(4096)

.........

```












/*
 * This function must be completely optimized away if a constant is passed to
 * it.  Mostly the same as what is in linux/slab.h except it returns an index.
 */
static __always_inline int index_of(const size_t size)
{
	extern void __bad_size(void);

	if (__builtin_constant_p(size)) {
		int i = 0;

#define CACHE(x) \
	if (size <=x) \
		return i; \
	else \
		i++;
#include <linux/kmalloc_sizes.h>
#undef CACHE
		__bad_size();
	} else
		__bad_size();
	return 0;
}


#define INDEX_AC index_of(sizeof(struct arraycache_init))
#define INDEX_L3 index_of(sizeof(struct kmem_list3))

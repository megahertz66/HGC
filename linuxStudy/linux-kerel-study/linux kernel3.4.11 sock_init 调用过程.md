# Linux kernel do_initcalls() function

## sock_init

该函数在3.4.11版本的内核中没有直接调用。而是通过  
`core_initcall(sock_init);	/* early initcall */`	core_initcalls定义如下：
```c
/*In include\linux\init.h */

#define core_initcall(fn)		__define_initcall("1",fn,1)

#define __define_initcall(level,fn,id) \
	static initcall_t __initcall_##fn##id __used \
	__attribute__((__section__(".initcall" level ".init"))) = fn
```


.
## __attribute__

[attribute](https://gcc.gnu.org/onlinedocs/gcc-4.7.1/gcc/Attribute-Syntax.html)是一种GNU的机制。\_\_attribute\_\_ 可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。    

这个链接是 stackoverflow 中的一个关于此问题比较好的回答[链接](https://stackoverflow.com/questions/11505681/good-explanation-of-read-mostly-init-exit-macros) 。    

此处使用section 是要把这个函数指定放到某个段中。sock_init 被放在 `.initcall1.init`这个段上.

.  
## __used 

定义：
`# define __used			__attribute__((__unused__))`      


在gcc中对 unused 的描述：
>**unused**       When attached to a type (including a union or a struct), this attribute means that variables of that type are meant to appear possibly unused. GCC will not
produce a warning for any variables of that type, even if the variable appears to
do nothing. This is often the case with lock or thread classes, which are usually
defined and then not referenced, but contain constructors and destructors that
have nontrivial bookkeeping functions.

意思是,就算不使用这个变量,或者这个变量什么都不干.gcc也不会报错.

.
## do_initcalls
```c
static void __init do_initcalls(void)
{
	int level;

	for (level = 0; level < ARRAY_SIZE(initcall_levels) - 1; level++)
		do_initcall_level(level);
}
```
其中ARRAY定义：
`#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])`  

### do_initcall_level

在 initcall_levels 数组中的内容都是段的值,这样就相当于将函数指针赋值给fn, 并调用执行.

```c
static void __init do_initcall_level(int level)
{
	extern const struct kernel_param __start___param[], __stop___param[];
	initcall_t *fn;

	strcpy(static_command_line, saved_command_line);
	parse_args(initcall_level_names[level],
		   static_command_line, __start___param,
		   __stop___param - __start___param,
		   level, level,
		   repair_env_string);

	for (fn = initcall_levels[level]; fn < initcall_levels[level+1]; fn++)
		do_one_initcall(*fn);
}

int __init_or_module do_one_initcall(initcall_t fn)
{
	int count = preempt_count();
	int ret;

	if (initcall_debug)
		ret = do_one_initcall_debug(fn);
	else
		ret = fn();

	msgbuf[0] = 0;

	if (ret && ret != -ENODEV && initcall_debug)
		sprintf(msgbuf, "error code %d ", ret);

	if (preempt_count() != count) {
		strlcat(msgbuf, "preemption imbalance ", sizeof(msgbuf));
		preempt_count() = count;
	}
	if (irqs_disabled()) {
		strlcat(msgbuf, "disabled interrupts ", sizeof(msgbuf));
		local_irq_enable();
	}
	if (msgbuf[0]) {
		printk("initcall %pF returned with %s\n", fn, msgbuf);
	}

	return ret;
}
```
上面一些段在下面目录中定义:
`include\asm-generic\vmlinux.lds.h` 
```c
extern initcall_t __initcall_start[];
extern initcall_t __initcall0_start[];
extern initcall_t __initcall1_start[];
extern initcall_t __initcall2_start[];
extern initcall_t __initcall3_start[];
extern initcall_t __initcall4_start[];
extern initcall_t __initcall5_start[];
extern initcall_t __initcall6_start[];
extern initcall_t __initcall7_start[];
extern initcall_t __initcall_end[];

static initcall_t *initcall_levels[] __initdata = {
	__initcall0_start,
	__initcall1_start,
	__initcall2_start,
	__initcall3_start,
	__initcall4_start,
	__initcall5_start,
	__initcall6_start,
	__initcall7_start,
	__initcall_end,
};
```
这些知识被记录在GNU 的linker 文档.  [CSDN博客](https://blog.csdn.net/ooonebook/article/details/52690132)  

这些东西是由Kconfig指定的,[关于Kconfig的CSDN博客](https://blog.csdn.net/jianwen_hi/article/details/53398141) \ [Kconfig文档](https://www.kernel.org/doc/html/latest/kbuild/kconfig-language.html)

没有直接引用他们的文章，只放了链接，侵删。


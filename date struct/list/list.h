#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>

enum
{
	RET_FAILED		= -1,
	RET_OK			= 0,
	RET_NOTFIND		= 1
};

typedef struct tag_node{
	void * data;
	struct tag_node * next;
}node_t;

typedef struct mylist{
	node_t * pHead;
	node_t * pTail;
}list_t;

// 初始化, 认为应该返回一个指针供后面使用
extern list_t * initList(void);
// 删除链表
extern node_t * deleteList(list_t * pList);
// 插入节点
extern node_t * insertNode(list_t * pList, void * Data);
// 查找结点
extern node_t * findNode(void *pKey, int (*finder)(void *pKey, void *pData));
// 删除节点
extern node_t * freeNode(list_t * pList);
// 反转链表
extern list_t * reversList(list_t * pList);
// 链表pop
extern node_t * poplist(list_t * pList);
// 链表top
extern node_t * toplist(list_t * pList);
// 节点排序，使用何算法排序
//extern void sortList( int (*compare)(void *element1, void *element2) );
// 合并链表
//extern void mergeList(list_t* firstList, list_t* secondList);


#endif /* __LIST_H__ */
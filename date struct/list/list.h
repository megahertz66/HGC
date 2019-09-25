#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>

typedef struct tag_node{
	void * data;
	struct tag_node * next;
}node_t;

typedef struct mylist{
	node_t * pHead;
	node_t * pTail;
	int count;
}list_t;

// 初始化链表
extern list_t * initList();
// 删除链表
extern list_t * deleteList(list_t * pList);
// 插入节点
extern node_t * insertNode(list_t * pList, void * pData);
// 查找结点/修改节点
extern node_t * findNode(list_t * pList, void *pKey, int (*finder)(void *pKey, void *pData));
// 删除节点
extern node_t * freeNode(list_t * pList, void *pKey, int (*compare)(void *pKey, void *pData));
// 反转链表
extern list_t * reversList(list_t * pList);
// 链表top
extern node_t * toplist(list_t * pList);
/*
// 节点排序，使用何算法排序
extern void sortList(int (*compare)(void *element1, void *element2) );
// 合并链表
extern void mergeList(list_t* firstList, list_t* secondList);
*/
#endif /* __LIST_H__ */
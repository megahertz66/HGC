#include <stdio.h>
#include <malloc.h>
#include "list.h"

// 初始化链表
list_t * initList()
{
	list_t * pList;
	pList = (list_t *)malloc(sizeof(list_t));
	memset(pList, 0, sizeof(list_t));
	return pList;
}

// 删除链表
list_t * deleteList(list_t * pList)
{
	node_t * delNode = NULL;
	node_t * tmpNode = NULL;

	if(NULL == pList)
	{
		return NULL;
	}
	delNode = pList->pHead;
	while(delNode)
	{
		tmpNode = delNode->next;
		if(NULL != delNode->data)
		{
			free(delNode->data);
		}
		free(delNode);
		delNode = tmpNode;
	}
	free(pList);
	return NULL;
}

// 插入节点
node_t * insertNode(list_t * pList, void * pData)
{	
	node_t * node;
	
	if(NULL == pList)
	{
		return NULL;
	}
	node = (node_t *)malloc(sizeof(node_t));
	node->data = pData;
	node->next = NULL;
	if (NULL == pList->pHead)
	{
		pList->pHead = node;
		pList->pTail = node;
	}
	else
	{
		pList->pTail->next = node;
		pList->pTail = node;
	}
	pList->count++;

	return node;
}

// 查找结点/修改结点
node_t * findNode(list_t * pList, void *pKey, int (*finder)(void *pKey, void *pData))
{
	node_t * pTmp = NULL;

	if(NULL == pList)
	{
		return NULL;
	}
	pTmp = pList->pHead;
	while(pTmp)
	{
		if(0 == finder(pKey, pTmp->data))
		{
			break;
		}
		pTmp = pTmp->next;
	}
	
	return pTmp;
}

// 删除节点
node_t * freeNode(list_t * pList, void *pKey, int (*compare)(void *pKey, void *pData))
{
	node_t * delNode = NULL;
	node_t * tmpNode = NULL;
	node_t * result = NULL;

	if(NULL == pList)
	{
		goto err;
	}
	delNode = pList->pHead;
	if(0 == compare(pKey, delNode->data))
	{
		pList->pHead = delNode->next;
		free(delNode->data);
		free(delNode);
		goto err;
	}

	delNode = pList->pHead->next;
	tmpNode = pList->pHead;
	while(delNode)
	{
		if(0 == compare(pKey, delNode->data))
		{
			tmpNode->next = delNode->next;
			free(delNode->data);
			free(delNode);
			goto err;
		}
		tmpNode = delNode;
		delNode = tmpNode->next;
	}
err:
	return result;
}

// 链表top
node_t * toplist(list_t * pList)
{
	return pList->pTail;
}

// 反转链表
list_t * reversList(list_t * pList)
{
	list_t * reList = pList;
	node_t * newHead = NULL;
	node_t * newTail = pList->pHead;
	node_t * head = pList->pHead;
	if(head == NULL) return NULL;
	while(head != NULL){
		node_t * tmp = head->next;
		head->next = newHead;
		newHead = head;
		head = tmp;
	}
	reList->pHead = newHead;
	reList->pTail = newTail;
	return reList;
}

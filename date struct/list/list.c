#include <stdio.h>
#include <malloc.h>
#include "list.h"

list_t  pList;

int initList() 
{
	pList.pHead = NULL;
	pList.pTail = NULL;
	return RET_OK;
}

int freeList()
{
	node_t * delNode = pList.pHead;
	node_t * tmpNode = NULL;

	while(delNode)
	{
		tmpNode = delNode->next;
		free(delNode->data);
		free(delNode);
		delNode = tmpNode;
	}

	pList.pHead = NULL;
	pList.pTail = NULL;	
}

int insertNode(void * Data)
{	
	node_t * node;
	
	node = (node_t *)malloc(sizeof(node_t));
	node->data = Data;
	if (NULL == pList.pHead)
	{
		pList.pHead = node;
		pList.pTail = node;
	}
	else
	{
		pList.pTail->next = node;
		pList.pTail = node;
	}
	return;
}

int findNode(void *pKey, int (*finder)(void *pKey, void *pData))
{
	node_t * pTmp = pList.pHead;

	if(NULL == pTmp)
	{
		return RET_NOTFIND;
	}

	while(pTmp)
	{
		if(0 == finder(pKey, pTmp->data))
		{
			break;
		}
		pTmp = pTmp->next;
	}
	
	return RET_OK;
}

int deleteNode()
{

	return ;
}

void listSort()
{
	
}

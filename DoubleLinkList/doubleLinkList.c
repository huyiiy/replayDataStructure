#include "doubleLinkList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,

};
/* 静态函数只在本源文件（.c）使用*/
/* 静态前置声明 */
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList * pList, ELEMENTTYPE val , int * pPos, int(*compareFunc )(ELEMENTTYPE , ELEMENTTYPE));
/* 新建新结点封装成函数 */
static  DoubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val);


/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList ** pList)
{
    int ret = 0;

    DoubleLinkList *list = (DoubleLinkList *)malloc(sizeof(DoubleLinkList) * 1);
    if ( list == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list, 0 , sizeof(DoubleLinkList) * 1);

    list->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list->head, 0, sizeof(DoubleLinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;
    /* 虚拟头结点的prev指针置为NULL */
    list->head->prev = NULL;
    /* 初始化的时候，尾指针 = 头指针 */
    list->tail = list->head;


    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 */
    * pList = list;

    return ret;
}

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
 
    return DoubleLinkListAppointPosInsert(pList, 0, val);

}

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, pList->len, val);
}

static  DoubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val)
{
    /* 封装结点 */
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (newNode == NULL)
    {
        return NULL;
    }
    /* 清除脏数据 */
    memset(newNode, 0 , sizeof(DoubleLinkNode) * 1);

    /* 赋值 */
    newNode->data = val;
    newNode->next = NULL;
    /* 新结点的*/
    newNode->prev = NULL;
}
/* 链表指定位置插入 */
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    if (pList == NULL)
    {
        return MALLOC_ERROR;       
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    /* 新建新结点封装成函数 */
    DoubleLinkNode * newNode = createDoubleLinkNode(val);
    if (newNode == NULL)
    {
        return NULL_PTR;
    }
#else
    /* 封装结点 */
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(newNode, 0 , sizeof(DoubleLinkNode) * 1);

    /* 赋值 */
    newNode->data = val;
#endif

#if 1
    /* 从虚拟头结点开始遍历 */
    DoubleLinkNode * travelNode = pList->head;
#else
    DoubleLinkNode * travelNode = pList->head->next;
#endif

    int flag = 0;
    /* 这种情况下需要更改尾指针 */
    if (pos == pList->len)
    {
        /* 修改结点指向 */
        travelNode = pList->tail;
#if 0
        // newNode->next = travelNode->next;
        // travelNode->next = newNode;
#endif
        flag = 1;
    }
    else
    {
        while (pos)
        {      
            travelNode = travelNode->next;
            pos--;
        }
        
        travelNode->next->prev = newNode;  //3:     空链表/ 尾插
        
    }
    newNode->next = travelNode->next;   //1
    newNode->prev = travelNode;         //2
    travelNode->next = newNode;         //4
 
    if(flag)
    {
        /* 尾指针更新位置 */
        pList->tail = newNode;
    } 

    /* 更新链表的长度 */
    (pList->len)++;
    return ret;   
}

/* 链表头删 */
int DoubleLinkListHeadDel(DoubleLinkList * pList)
{
    return DoubleLinkListDelAppointPos(pList, 1);

}

/* 链表尾删 */
int DoubleLinkListTaiDel(DoubleLinkList * pList)
{
    return DoubleLinkListDelAppointPos(pList, pList->len);
}

/* 链表指定位置删 */
int DoubleLinkListDelAppointPos(DoubleLinkList * pList, int pos)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    /* */
    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    DoubleLinkNode * travelNode = pList->head;
#else
    DoubleLinkNode * travelNode = pList->head->next;
#endif
    DoubleLinkNode * needDelNode = NULL;
    /* 需要修改尾指针 */
    if (pos == pList->len)
    {
        /* 需要修改尾指针 */
        
        DoubleLinkNode * tmpNode = pList->tail;
        /* 移动尾指针 */
        pList->tail = pList->tail->prev;
        needDelNode = tmpNode;
    }
    
    while (--pos)
    {
        /* 向后移动位置 */
        travelNode = travelNode->next;
    }
    // 跳出循环找到的是哪一个结点 
    needDelNode = travelNode->next;
    travelNode->next = needDelNode->next;
    needDelNode->next->prev = travelNode;


    /* 释放内存 */
    if (needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }
    /* 链表结点 */
    (pList->len)--;
    return ret;
    
}

/* 根据指定的元素得到在链表中所在的位置 */
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList * pList, ELEMENTTYPE val, int *pPos , int(*compareFunc )(ELEMENTTYPE , ELEMENTTYPE))
{
    /* 静态函数只给本源文件的函数使用 ， 不需要判断合法性 */
    int ret;

#if 0
    int pos = 0;
    DoubleLinkNode * travelNode = pList->head;
#else
    int pos = 1;
    DoubleLinkNode * travelNode = pList->head->next;
#endif
    int cmp = 0;
    while (travelNode != NULL)
    {
#if 0 
        if (travelNode->data == val)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }

#else 
        cmp = compareFunc(val , travelNode->data);
        if (cmp == 0)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }

#endif
        travelNode = travelNode->next;
        pos++;
    }  
    /* 解引用 */
    *pPos = NOT_FIND; 
    return NOT_FIND;
}

/* 链表删除指定的数据 */
int DoubleLinkListDelAppointData(DoubleLinkList * pList, ELEMENTTYPE val, int(*compareFunc )(ELEMENTTYPE , ELEMENTTYPE))
{
    int ret = 0;

    /* 元素在链表中的位置 */
    int pos = 0;

    /* 链表的长度 */
    int size = 0;
    while (DoubleLinkListGetLength(pList, &size) && NOT_FIND)
    {
        /* 根据指定的元素得到在链表中所在的位置 */  
        DoubleLinkListAccordAppointValGetPos(pList, val, &pos, compareFunc);
        DoubleLinkListDelAppointPos(pList, pos);   
    } 
    return ret;
}

/* 获取链表的长度 */
int DoubleLinkListGetLength(DoubleLinkList * pList, int * pSize)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pSize)
    {
        * pSize = pList->len;
    }
    /* 返回链表的长度 */
    return pList->len;
    
}

/* 链表的销毁 */
int DoubleLinkListDestroy(DoubleLinkList * pList)
{
    int ret = 0;
    /* 我们使用头删释放链表*/
    int size = 0;
    while (DoubleLinkListGetLength(pList, &size))
    {
        DoubleLinkListHeadDel(pList);
    }
    if (pList->head != NULL)
    {
        free(pList->head);
        /* 指针置为NULL */
        pList->head = NULL;
        pList->tail = NULL; 
    }
    return ret;

}

/* 链表顺序遍历接口 */
int DoubleLinkListForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }
#if 0
    /* travelNode为虚拟头结点 */
    DoubleLinkNode * travelNode = pList->head;
      while (travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        printf("travelNode->data:%d\n", travelNode->data);
    }
#else
    /* travelNode 指向链表第一个元素 */
    DoubleLinkNode * travelNode = pList->head->next;
   
      while (travelNode != NULL)
    {    
#if 0
        printf("travelNode->data:%d\n", travelNode->data);
#else
        /* 包装器 . 钩子 . 回调函数 */
        printFunc(travelNode->data);
#endif
        travelNode = travelNode->next;
    }
#endif
    return ret;    
}

/* 链表逆序遍历 */
int DoubleLinkListReverseForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    DoubleLinkNode * travelNode = pList->tail;
    while (travelNode != pList->head)
    {
         /* 包装器 . 钩子 . 回调函数 */
        printFunc(travelNode->data);
        /* 移动前指针 */
        travelNode = travelNode->prev;
    } 

    return ret;
}
 
    
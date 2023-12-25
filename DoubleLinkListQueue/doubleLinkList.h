#ifndef __GOUBLELINKLIST_H_
#define __DOUBLELINKLIST_H_


#define ELEMENTTYPE void*

/* 取别名 */
typedef struct DoubleLinkNode
{
    ELEMENTTYPE data;
    
    struct  DoubleLinkNode * prev;

    /* 指向下一个结点的指针 */
    struct DoubleLinkNode *next;      /* 指针的类型为什么是结点*/
} DoubleLinkNode;

typedef struct DoubleLinkList
{
    DoubleLinkNode node;
}DoubleLinkList;

/* 链表 */
typedef struct DoubleLinkList
{
    /* 链表的虚拟头结点 */
    DoubleLinkNode * head;
    DoubleLinkNode * tail;        /* 为什么尾指针不需要分配空间*/
    /* 链表的长度 */
    int len;
} DoubleLinkList;

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList ** pList);

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表指定位置插入 */
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList, int pos, ELEMENTTYPE val);

/* 链表头删 */
int DoubleLinkListHeadDel(DoubleLinkList * pList);

/* 链表尾删 */
int DoubleLinkListTaiDel(DoubleLinkList * pList);

/* 链表指定位置删 */
int DoubleLinkListDelAppointPos(DoubleLinkList * pList, int pos);

/* 链表删除指定的数据 */
int DoubleLinkListDelAppointData(DoubleLinkList * pList, ELEMENTTYPE val, int(*compareFunc )(ELEMENTTYPE , ELEMENTTYPE));

/* 获取链表的长度 */
int DoubleLinkListGetLength(DoubleLinkList * pList, int * pSize);

/* 链表的销毁 */
int DoubleLinkListDestroy(DoubleLinkList * pList);

/* 链表遍历接口 */
int DoubleLinkListForeach(DoubleLinkList * pList,int (*printFunc)(ELEMENTTYPE));

#endif
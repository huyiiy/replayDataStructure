#ifdef __DOUBLELINKLIST_QUEUE_H_
#define __DOUBLELINKLIST_QUEUE_H_

/* 队列的初始化*/
int doubleLinkListQueueInit();

/* 队列入队 */
int doubleLinkListQueuePush();

/* 队头元素 */
int doubleLinkListQueueTop();

/* 队尾元素 */
int doubleLinkListQueueRear();

/* 队列出队 */
int doubleLinkListQueuePop();

/* 队列的大小 */
int doubleLinkListQueueGetSize();

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty();

/* 队列销毁*/
int doubleLinkListQueueDestroy();

#endif
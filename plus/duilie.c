#include <stdio.h>
#include <stdlib.h>
#define TRUE      1
#define FALSE    -1
#define OK        1
#define ERROR    -1
#define OVERFLOW -2

/* ----     单链队列----队列的链式存储结构   ---- */
typedef struct Qnode
{
    int date;
    struct Qnode *next;
}QNode,* QueuePtr;

typedef struct
{
    QueuePtr head;    //队头指针
    QueuePtr tail;    //队尾指针
}LinkQueue; 

/* ---- 基本操作函数 ---- */
/* ---- 构造一个空队列 ---- */

int InitQueue(LinkQueue *Q)
{
    Q->head = Q->tail = (QueuePtr)malloc(sizeof(QNode));
    if (Q->head == NULL)
    {
        exit(OVERFLOW);
    }
    Q->tail->next = NULL;
    return OK;
}

/* ---- 销毁队列Q,Q不再存在 ---- */
int DestoryQueue(LinkQueue *Q)
{
    //head->node1->node2->node3->tail;
    //             tail
    //       head->node2       
    while(Q->head)
    {
        Q->tail = Q->head->next;
        free(Q->head);
        Q->head = Q->tail;
    }
    Q->head = Q->tail = NULL;
    return OK;

}

/* ---- 将Q清空空队列 ---- */
int ClearQueue(LinkQueue *Q)
{
     QueuePtr temp;
     Q->tail = Q->head->next;
     while(Q->tail)
     {
         temp = Q->tail->next; //指向下一个待释放的单元
         free(Q->tail);
         Q->tail = temp;
     }
     Q->tail = Q->head; //修改队尾指针
     return OK;
}

/* ---- 若队列Q为空队列,返回TRUE,否则返回FALSE ---- */
int QueueEmpty(LinkQueue Q)
{
    if (Q.head == Q.tail && Q.head != NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* ---- 返回Q的元素个数,即队列的长度 ---- */
int QueueLength(LinkQueue Q)
{
    if (Q.head == NULL)
    {
        return 0;
    }
    QueuePtr temp;
    int count = 0;
    temp = Q.head->next;
    while(temp != NULL)
    {
        temp = temp->next;
        ++count;
    }
    return count;
}

/* ---- 显示当前队列的值从队头到队尾 ---- */
void show_queue(LinkQueue Q)
{
    QueuePtr temp;
    temp = Q.head->next;
    printf("  当前队列从头到尾:");
    while(temp != NULL)
    {
        printf("%d  ", temp->date);
        temp = temp->next;
    }
    printf("\n");
}


/* ---- 若队列不空,则用e返回Q的队头元素,并返回OK, 否则返回ERROR ---- */
int GetHead(LinkQueue Q, int *e)
{
    if (QueueEmpty(Q) == TRUE)
    {
        return ERROR;
    }

    *e = Q.head->next->date;
    return  OK;

}

/* ---- 插入元素e为Q的新的对尾元素 ---- */
int EnQueue(LinkQueue *Q, int e)
{
    if (Q->head == NULL || Q->tail == NULL)
    {
        return ERROR;
    }
    QueuePtr ptr = (QueuePtr)malloc(sizeof(QNode));
    if (!ptr)
    {
        exit(OVERFLOW);
    }
    ptr->date = e;
    ptr->next = NULL;

    Q->tail->next = ptr;
    Q->tail = ptr;
    return OK;
}

/* ---- 若队列不空,则删除Q的队头元素,并用e返回其值,并返回OK,否则返回ERROR ---- */
int DeQueue(LinkQueue *Q, int *e)
{
    if (Q->head == Q->tail)
    {
        return ERROR;
    }
    /* ptr为临时变量 */
    QueuePtr ptr = (QueuePtr)malloc(sizeof(QNode));
    //head->node1->node2->tail;
    //       ptr
    //      head->node2->tail

    ptr = Q->head->next;
    *e = ptr->date;
    Q->head->next = ptr->next;
    if (Q->tail == ptr)
    {
        Q->head = Q->tail;
    }
    free(ptr);
    return OK;
}

int main()
{
    int i;        //循环变量
    int count;    //计数变量
    int outque;   //出队元素值
    LinkQueue Q;

    /* 初始化队列 */
    InitQueue(&Q);

    /* 插入10个元素 */
    printf("________________入队10个元素________________\n\n");
    for (i = 0; i < 10; i++)
    {
        /* 入队 */
        EnQueue(&Q, i);
        /* 获得当前队列中元素个数 */
        count = QueueLength(Q);
        printf("%2d 入队_当前队列中元素个数:%2d",i, count);
        show_queue(Q);
    }

    printf("________________出队5个元素________________\n\n");
    for (i = 0; i < 5; i++)
    {
        /* 出队 */
        DeQueue(&Q, &outque);
        /* 获得当前队列中元素个数 */
        count = QueueLength(Q);
        printf("%2d 出队_当前队列中元素个数:%2d", outque, count);
        show_queue(Q);
    }
    /* 获得当前队头值 */
    GetHead(Q, &outque);
    printf("\n当前队头为:%d\n", outque);

    printf("________________清空队列_________________\n\n");
    ClearQueue(&Q);

    count = QueueLength(Q);
    printf("当前队列中元素个数:%2d", count);
    show_queue(Q);

    printf("________________销毁队列_________________\n\n");
    DestoryQueue(&Q);
    count = QueueLength(Q);
    printf("当前队列中元素个数:%2d\n\n", count);

    return 0;
}

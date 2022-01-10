#include <stdio.h>
#include <stdlib.h>
typedef struct DuLNode{
    int data;
    struct DuLNode *next;
}DuLNode, *DuLinklist;  
DuLNode * CreateTailList(){//创建大小长度为n的链表
    DuLinklist L, p, end , r;//L头结点，p当前节点，end尾结点
    L = (DuLNode *)malloc(sizeof(DuLNode));
    L->next = NULL;
    r = L;
    int i = 0;
    while(i!=10){
        
        p = (DuLNode *)malloc(sizeof(DuLNode));
        p->data = i+1;
        r->next = p;
        r = p;
        i++;
    }
    r->next = NULL;
    end=r;
    L=L->next;
    return L;
}
void TraverseList(DuLinklist L){
    DuLinklist p;
    p = L;
    while(p->next != NULL){
        printf("%d  ", p->data);
        p = p->next;
    }
}
DuLNode *nixu(DuLinklist head)
{
    DuLinklist L,r,n;
    L=head;
    r = (DuLNode *)malloc(sizeof(DuLNode));
    while(L->next!=NULL)
    {
        L=L->next;
        r->next=L;
        n=L->next;
        if(L->next!=NULL)
        L->next=r;
        else break;
        L=n;
    }
    head=L;
    return head;
}
int main(void)
{
    DuLinklist Lb;
    Lb=CreateTailList();
    TraverseList(Lb);
    Lb=nixu(Lb);
    printf("\n");
    TraverseList(Lb);
    return 0;

}
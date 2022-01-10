#include <stdio.h>
#include <stdlib.h>
#define TRUE 1;
#define FALSE 0;
typedef struct DuLNode{
    int data;
    struct DuLNode *prior, *next;
}DuLNode, *DuLinklist;  
//尾插法创建双向链表
DuLNode * CreateTailList(int n){//创建大小长度为n的链表
    DuLinklist L, p, r;
    L = (DuLNode *)malloc(sizeof(DuLNode));
    L->next = NULL;
    L->prior = NULL;
    r = L;
    int i = 0;
    for(i = 0; i < n; i ++){
        p = (DuLNode *)malloc(sizeof(DuLNode));
        p->data = i+1;
        r->next = p;
        p->prior = r;
        r = p;
    }
    r->next = L->next;
    L->next->prior=r;//建立循环链表
    L=L->next;
    return L;
}
//删除第i个位置的元素//更改函数为输出某位置链表信息并删除该结点，且i清零，循环此任务，知道输出完最后一个结点的信息
int * DeleteElem(DuLinklist L, int i,int s,int n)//第一个参数链表头指针，第二个差数i=m,第三个s=k;实现josephus
{
  DuLinklist p, r;
  p = (DuLNode *)malloc(sizeof(DuLNode));
  p->next = L;
  int *c,*e;//e保存最后k个数的信息，并返回给main(),
  c=(int*)malloc(s*sizeof(int));
  int w[s-1];//记录倒数k个数，k=s
  e=&w[0];
  int j = 0,jishu=0,jishu1=0;//计数单位
  while(1)//结束循环条件：只剩下最后一个节点。
  {
  	if(p->next==p)
  	{
  		printf("%d  ",p->data);
      w[jishu1]=p->data;//从倒数第k(s)个开始计数
      jishu1++;
  	  break;
	  }
  	
    for(j = 1; j < i; j ++)
    {
      p = p->next;
    }    
    r = p->next;
    p->next = r->next;
    r->next->prior = p;
    jishu++;
    if(jishu>=n-s+1)
    {
      printf("%d  ",r->data);
      w[jishu1]=r->data;//从倒数第k(s)个开始计数
      jishu1++;
    }
    if(jishu==n)
    break;
    
  }
  return e;
}
//获取第i个元素

int main()
{
 
  DuLinklist Lb,H;
  int m,n,k;
  printf("请输入n：\n");
  scanf("%d",&n);
  printf("请输入要取的数的个数k：\n");
  scanf("%d",&k);
  int *c;
  int i,j,q,jidge;
  c=(int*)malloc(k*sizeof(int));
  int knum[k-1];
  printf("请依次输入取的数：");
  for(i=0;i<k;i++)
  {
    scanf("%d",&knum[i]);
  }
  printf("\n");
  int *pm;
  for(i=1;i<=n;i++)
  {
    Lb=CreateTailList(n);//第二个参数为链表节数
    pm=DeleteElem(Lb,i,k,n);  
    for(j=0;j<k;j++)
    {
      jidge=0;
      for(q=0;q<k;q++)
      {
        if(pm[j]==knum[q])
        jidge=1;
      }
      if(jidge==0)
      {
        printf("m=%d时不是答案\n",i);
        break;
      }
      if(j==k-1)
      {
        printf("m=%d时是答案\n",i);
        break;
      }
    }
    if(j==k-1)
    break;
  } 
  return 0;
}

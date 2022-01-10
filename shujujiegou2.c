#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#ifndef _Stack_h
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
#define Stack_Top 20
int carnum=0;
int Stack_IsEmpty(Stack S);//判断非空
Stack CreateStack(void);//创建一个空栈
//void DisposeStack(Stack S);//
void Stack_Make_Empty(Stack S);//清空栈
void Stack_Push(int X,Stack S);//入栈
int Stack_ReturnTop(Stack S);//返回栈顶元素
void Stack_Pop(Stack S);//出栈
int Stack_Full(Stack S);//栈满判定
#endif  /*_Stack_h*/

struct Node
{
    int Stack_Element;
    Stack Next;
};

int Stack_IsEmpty(Stack S)
{
    return S->Next==NULL;
}

Stack CreateStack(void)
{
    Stack S;
    S=(Stack)malloc(sizeof(struct Node));
    if(S==NULL)
      printf("Out of space!!!\n");
      S->Next=NULL;
      Stack_Make_Empty(S);
      return S;
}

void Stack_Make_Empty(Stack S)//清空栈
{
    if(S==NULL)
      printf("Aleady Empty\n");
    else
      while(!Stack_IsEmpty(S))
        Stack_Pop(S);
}

void Stack_Push(int X,Stack S)//进栈
{
  PtrToNode TmpCell;
  TmpCell = (Stack)malloc(sizeof(struct Node));  
  if(TmpCell==NULL)
    printf("Out of space!!!");
    else if(X<=20)
    {
      TmpCell->Stack_Element=X;
      TmpCell->Next=S->Next;
      S->Next=TmpCell;
    }
    else 
    {
      printf("停车位已满\n");
      carnum--;
    }
}

int Stack_ReturnTop(Stack S)//返回栈顶元素
{
  if(!Stack_IsEmpty(S))
  {
    printf("当前有%d辆车\n",carnum);
    return S->Next->Stack_Element;
  }
  //printf("Empty stack\n");
  printf("当前没有车辆进入\n");
  return 0;
}

void Stack_Pop(Stack S)//出栈
{
  PtrToNode Firstcell;
  if(Stack_IsEmpty(S))
    printf("Empty Stack");
  else
  {
    Firstcell=S->Next;
    S->Next=S->Next->Next;
    free(Firstcell);
  }
}

int Stack_Full(Stack S)
{
  int i=0;
  while(S->Next!=NULL)
  {
    i++;
    S=S->Next;
  }
  if(i+1<=Stack_Top)
  return 0;
  else
  return 1;
}

int main(void)
{
  Stack S;
  int num1;
  S=CreateStack();
  Stack_IsEmpty(S);
  puts("-----------------------");
  puts("停车场管理系统");
  puts("1.查看当前停车场状态");
  puts("2.有车驶入");
  puts("3.有车驶出");
  puts("4.停车场是否为空");
  puts("0.结束营业");
  puts("-----------------------");
  int choice,k=0;
  scanf("%d",&choice);
  while(choice!=0)
  {
    switch (choice)
    {
      case 1:Stack_ReturnTop(S);break;
      case 2:Stack_Push(carnum+1,S);carnum++;printf("当前车辆数:%d\n",carnum);break;
      case 3:Stack_Pop(S);carnum--;printf("当前车辆数:%d\n",carnum);break;
      case 4:if(carnum==0)printf("为空\n");else printf("不为空\n");break;
      default:puts("error choice!please try again");break;
    }
    puts("-----------------------");
    puts("停车场管理系统");
    puts("1.查看当前停车场状态");
    puts("2.有车驶入");
    puts("3.有车驶出");
    puts("4.停车场是否为空");
    puts("0.结束营业");
    puts("-----------------------");
    scanf("%d",&choice);
  }
  printf("剩余车辆数:%d",carnum);

  
  return 0;
}
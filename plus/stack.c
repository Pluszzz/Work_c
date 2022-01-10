#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#ifndef _Stack_h
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int Stack_IsEmpty(Stack S);//判断非空
Stack CreateStack(void);//创建一个空栈
//void DisposeStack(Stack S);//
void Stack_Make_Empty(Stack S);//清空栈
void Stack_Push(int X,Stack S);//入栈
int Stack_ReturnTop(Stack S);//返回栈顶元素
void Stack_Pop(Stack S);//出栈
#endif  /*_Stack_h*/

struct Node
{
    int Stack_Element;
    PtrToNode Next;
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
    else
    {
      TmpCell->Stack_Element=X;
      TmpCell->Next=S->Next;
      S->Next=TmpCell;
    }
}

int Stack_ReturnTop(Stack S)//返回栈顶元素
{
  if(!Stack_IsEmpty(S))
    return S->Next->Stack_Element;
  printf("Empty stack\n");
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

int main(void)
{
  Stack S;
  int num1;
  S=CreateStack();
  Stack_IsEmpty(S);
  Stack_Push(1,S);
  num1=Stack_ReturnTop(S);
  printf("%d\n",num1);
  Stack_Pop(S);
  num1=Stack_ReturnTop(S);
  printf("%d\n",num1);
  Stack_Make_Empty(S);
  Stack_IsEmpty(S);


  
  return 0;
}
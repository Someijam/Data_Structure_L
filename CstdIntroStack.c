/*
Author:Someijam
Date:2022/10/13
Problem description:
Intro Stack
*/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000

typedef struct stack
{
    //根据需求选用合适数据类型
    int *base;
    int *top;
    int stacksize;
}SqStack;

void InitStack(SqStack *S)//初始化栈，最大元素数目为MAXSIZE
{
    S->base=malloc(MAXSIZE*sizeof(SqStack));
    if(!S->base)
    {
        //printf(stderr,"Allocated Failed, why not try again.");
        return;
    }
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return;
}

void Push(SqStack *S,int e)//插入元素e为栈顶元素
{
    if(S->top-S->base==S->stacksize)
    {
        //printf(stderr,"Stack is full now.");
        return;
    }
    *(S->top)=e;
    S->top++;
    return;
}

int PopNum(SqStack *S)
{
    if(S->top==S->base)
    {
        //printf(stderr,"Stack is empty now.");
        return -0xFFFFFFF;
    }
    S->top--;
    int e=*(S->top);
    return e;
}

void Pop(SqStack *S)
{
    if(S->top==S->base)
    {
        //printf(stderr,"Stack is empty now.");
        return;
    }
    S->top--;
    return;
}

int Top(SqStack *S)
{
    if(S->top==S->base)
    {
        //printf(stderr,"Stack is empty now.");
        return -0xFFFFFFF;
    }
    if(S->top!=S->base)return *(S->top-1);
    return 0;
}

int main(int argc, char const *argv[])
{
    SqStack st1;
    SqStack* pst1=&st1;
    //初始化栈st1，使用指针pst1操作
    InitStack(pst1);
    Push(pst1,1);
    Push(pst1,2);
    Push(pst1,3);
    //返回栈顶元素
    int st1Top=Top(pst1);
    printf("%d\n",st1Top);
    Pop(pst1);
    st1Top=Top(pst1);
    printf("%d\n",st1Top);
    int numTop=PopNum(pst1);
    printf("%d\n",numTop);
    return 0;
}
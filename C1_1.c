/*
Author:Someijam
Date:2022/11/15
Problem description:
第1关：链式循环队列建队与操作
*/
#include<stdio.h>
#include<stdlib.h>

struct item
{
    int index;
    int data;
    struct item *next;
}headItem;


int main(int argc, char const *argv[])
{
    int n,i,k;
    scanf("%d %d %d",&n,&i,&k);
    if(k>8)
    {
        printf("Error");
        return 0;
    }
    if(k>n)
    {
        printf("Fault");
        return 0;
    }
    if(n==8)
    {
        printf("Full ");
    }
    struct item *p=&headItem;
    for(int i=1;i<=8;i++)//搞8个节点
    {
        struct item *newItem=(struct item *)malloc(sizeof(struct item));
        p->next=newItem;
        newItem->index=i;
        newItem->next=NULL;
        p=p->next;
        if(i==8)newItem->next=headItem.next;
    }
    //从第i个人开始，输入n个数据
    p=&headItem;
    while (p->index!=i)
    {
        p=p->next;
    }//到第i个人了
    for(int cnt=0;cnt<n&&cnt<8;cnt++)
    {
        scanf("%d",&p->data);
        p=p->next;
    }
    char temp[20];
    if(n>8)scanf("%s",temp);
    p=&headItem;
    while (p->index!=i)
    {
        p=p->next;
    }//到第i个人了
    for(int cnt=0;cnt<k;cnt++)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    return 0;
}
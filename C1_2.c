/*
Author:Someijam
Date:2022/11/16
Problem description:
1-2
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct polyItem
{
    struct polyItem *prev;
    int c;
    int e;
    struct polyItem *next;
}polyHead1,polyHead2;

bool exitFlag=false;

void inputProcess()
{
    int tmpC;
    int tmpE;
    int i=0;
    int cnt1=1;
    int cnt2=1;
    struct polyItem *lastItem=&polyHead1;
    while(1)
    {
        if(scanf("%d",&tmpC))//扫到分号会吐出来，并且返回0
        {
            scanf("%d",&tmpE);
            struct polyItem *newItem = (struct polyItem *)malloc(sizeof(struct polyItem));
            (*newItem).c=tmpC;
            (*newItem).e=tmpE;
            (*newItem).next=NULL;
            cnt1++;
            (*lastItem).next=newItem;
            (*newItem).prev=lastItem;
            lastItem=newItem;
        }
        else break;
        if(cnt1>6)
        {
            printf("Full!");
            exitFlag=true;
            return;
        }
    }
    char useless;
    scanf("%c",&useless);
    lastItem=&polyHead2;
    while (scanf("%d",&tmpC)!=EOF)
    {
        scanf("%d",&tmpE);
        struct polyItem *newItem = (struct polyItem *)malloc(sizeof(struct polyItem));
        (*newItem).c=tmpC;
        (*newItem).e=tmpE;
        (*newItem).next=NULL;
        cnt2++;
        (*lastItem).next=newItem;
        (*newItem).prev=lastItem;
        lastItem=newItem;  
    }
    if(cnt2>6)
    {
        printf("Full!");
        exitFlag=true;
        return;
    }
    return;
}

void printProcess()
{
    struct polyItem *p1=&polyHead1;
    struct polyItem *p2=&polyHead2;
    while(p1->next)p1=p1->next;
    while(p2->next)p2=p2->next;
    while (1)
    {
        if(p1!=&polyHead1&&p2!=&polyHead2)//还没到头，谁大输出谁
        {   
            if((*p1).e>(*p2).e)
            {
                printf("%d %d ",p1->c,p1->e);
                p1=p1->prev;
                free(p1->next);
            }
            else 
            {
                printf("%d %d ",p2->c,p2->e);
                p2=p2->prev;
                free(p2->next);
            }
        }
        else if(p1==&polyHead1)
        {
            while (p2!=&polyHead2)
            {
                printf("%d %d ",p2->c,p2->e);
                p2=p2->prev;
                free(p2->next);
            }
            break;
        }
        else if(p2==&polyHead2)
        {
            while (p1!=&polyHead1)
            {
                printf("%d %d ",p1->c,p1->e);
                p1=p1->prev;
                free(p1->next);
            }
            break;
        }
    }
    return;
}
/*
void deleteProcess()
{
    struct polyItem *p=&polyHead1;
    while (p->next)
    {
        p=p->next;
        struct polyItem *q=p->prev;
        if(q!=&polyHead1)free(q);
    }
    free(p);

    p=&polyHead2;
    while (p->next)
    {
        p=p->next;
        struct polyItem *q=p->prev;
        if(q!=&polyHead2)
            free(q);
    }
    free(p);
    return;
}
*/
int main(int argc, char const *argv[])
{
    inputProcess();
    if(exitFlag)return 0;
    printProcess();
    //deleteProcess();
    return 0;
}
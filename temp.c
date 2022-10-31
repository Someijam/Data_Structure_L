// d2.1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
typedef struct arcnode
{
    char name[26];
    float dis;
    struct arcnode *nest;
}arcnode, * anode;
typedef struct startnode
{
    int lineNo;
    anode firstStation;
}startnode,*snode;
typedef struct map
{
    startnode line[10];
    int lineNum;
}*m;
m createmap(int n)
{
    m temp = (m)malloc(sizeof(struct map));
    temp->lineNum = n;
    float td;
    char ne[30];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp->line[i].lineNo);
        scanf("%s %f",ne,&td);
        anode j = (anode)malloc(sizeof(arcnode));
        j->dis = td;
        strcpy(j->name, ne);
        j->nest = NULL;
        temp->line[i].firstStation = j;
        while (scanf("%s %f", ne,&td))
        {
            anode th = j;
            j = (anode)malloc(sizeof(arcnode));
            j->dis = td;
            strcpy(j->name, ne);
            j->nest = NULL;
            th->nest = j;
            if (td == 0)
                break;
        }
    }
    return temp;
}
void displaymap(m g)
{
    anode p=(anode)malloc(sizeof(arcnode));
    for (int i = 0; i < g->lineNum; i++)
    {
        printf("%d ", g->line[i].lineNo);
         p = g->line[i].firstStation;
        while (p->nest!=NULL)
        {
            printf("%s %.2f ", p->name, p->dis);
            p = p->nest;
        }
        printf("%s\n", p->name);
    }
    
}
int main()
{
    int n;
    m ans;
    scanf("%d", &n);
    ans = createmap(n);
    displaymap(ans);
}
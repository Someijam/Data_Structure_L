/*
Author:Someijam
Date:2022/10/31
Problem description:
第1关：基于链表的建图
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct station//站点
{
    struct station *prev;
    char name[30];
    float dis;
    struct station *next;
};
struct line//地铁线路
{
    int lineNo;
    struct station *St1;
};
struct map//地铁总图
{
    int n;
    struct line Line[4];
}metroMap;

void iniMap()
{
    for(int i=0;i<metroMap.n;i++)
    {
        scanf("%d",&(metroMap.Line[i].lineNo));
        struct station *prev=NULL;
        while (1)
        {
            char currentStName[30];
            float currentStDis;
            scanf("%s %f",currentStName,&currentStDis);
            struct station *currentSt=(struct station*)malloc(sizeof(struct station));
            if(prev==NULL)metroMap.Line[i].St1=currentSt;
            else 
            {
                (*currentSt).prev=prev;
                (*currentSt).prev->next=currentSt;//上一站的下一站指向自己
            }
            (*currentSt).next=NULL;

            strcpy((*currentSt).name,currentStName);
            (*currentSt).dis=currentStDis;
            
            prev=currentSt;
            if(currentStDis==0)break;
        }
        
    }
}

void printMap()
{
    for(int i=0;i<metroMap.n;i++)
    {
        printf("%d ",metroMap.Line[i].lineNo);
        struct station *currentSt=metroMap.Line[i].St1;
        //struct station *p;
        while ((*currentSt).next)
        {
            printf("%s %.2f ",(*currentSt).name,(*currentSt).dis);
            currentSt=(*currentSt).next;
        }
        printf("%s",(*currentSt).name);
        printf("\n");
    }
}

void deleteMap()
{
    for(int i=0;i<metroMap.n;i++)
    {
        struct station *currentSt=metroMap.Line[i].St1;
        while ((*currentSt).next)
        {
            currentSt=(*currentSt).next;
            free((*currentSt).prev);
        }
        free(currentSt);
        //puts("OK");
    }
}

int main(int argc, char const *argv[])
{
    scanf("%d",&metroMap.n);
    iniMap();
    printMap();
    deleteMap();
    return 0;
}
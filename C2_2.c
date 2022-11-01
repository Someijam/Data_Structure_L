/*
Author:Someijam
Date:2022/10/31
Problem description:
第2关：增加站点，删除
*/
/*
4
1 六渡桥 5.00 循礼门 4.00 大智路 4.00 三阳路 5.00 黄浦路 0
2 汉口火车站 10.00 范湖 2.00 王家墩东 2.00 青年路 4.00 中山公园 2.00 循礼门 2.00 江汉路 5.00 积玉桥 0
6 三眼桥 3.00 香港路 2.00 苗栗路 2.00 大智路 5.00 江汉路 1.00 汉正街 0
7 武汉商务区 1.00 王家墩东 2.00 取水楼 2.00 香港路 6.00 三阳路 9.00 徐家棚 3.00 三角路 3.00 三层楼 3.00 积玉桥 0
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

void printMetroLine(int lineNo)
{
    printf("%d ",lineNo);
    int lineIndex;
    for(lineIndex=0;lineIndex<metroMap.n;lineIndex++)
    {
        if(metroMap.Line[lineIndex].lineNo==lineNo)break;
    }
    //下标为lineIndex的线路号即为传参进来的线路号lineNo
    struct station *currentSt=metroMap.Line[lineIndex].St1;
    //struct station *p;
    while ((*currentSt).next)
    {
        printf("%s %.2f ",(*currentSt).name,(*currentSt).dis);
        currentSt=(*currentSt).next;
    }
    printf("%s\n",(*currentSt).name);
}

void addStation1(int lineNo,float prevDis,float nextDis,char *prevStName,char *addStName)//在后面增加站点
{
    int lineIndex;
    for(lineIndex=0;lineIndex<metroMap.n;lineIndex++)
    {
        if(metroMap.Line[lineIndex].lineNo==lineNo)break;
    }
    //下标为lineIndex的线路号即为传参进来的线路号lineNo
    struct station *currentSt=metroMap.Line[lineIndex].St1;
    while ((*currentSt).next)
    {
        if(!(strcmp(addStName,(*currentSt).name)))
        {
            printf("增加失败，已有同名站点\n");
            return;
        }
        currentSt=(*currentSt).next;
    }//已经有这个站点了
    currentSt=metroMap.Line[lineIndex].St1;
    while ((*currentSt).next)
    {
        if(!(strcmp(prevStName,(*currentSt).name)))break;
        currentSt=(*currentSt).next;
    }
    if(!((*currentSt).next))
    {
        printf("增加失败，没有与输入的增加位置前一站点同名的站点\n");//未找到前一站
        return;
    }
    //在currentSt后面添加名为addStName的站点
    struct station *newSt=(struct station*)malloc(sizeof(struct station));
    strcpy((*newSt).name,addStName);//新站点名字
    (*newSt).dis=nextDis;//新增站到下一站距离
    (*newSt).next=(*currentSt).next;//接下一个人
    (*newSt).next->prev=newSt;//更新下一站的上一站指向新站点
    (*newSt).prev=currentSt;//接上一个人
    (*currentSt).next=newSt;//更新前一站的下一站为新增站
    (*currentSt).dis=prevDis;//更新前一站到下一站（新增站）的距离
    printMetroLine(lineNo);
    return;
}

void addStation2(int lineNo,/*float prevDis=0,*/float nextDis,/*char *prevStName,*/char *addStName)//在第一站前增加站点
{
    int lineIndex;
    for(lineIndex=0;lineIndex<metroMap.n;lineIndex++)
    {
        if(metroMap.Line[lineIndex].lineNo==lineNo)break;
    }
    //下标为lineIndex的线路号即为传参进来的线路号lineNo
    struct station *newSt=(struct station*)malloc(sizeof(struct station));
    struct station *currentSt=metroMap.Line[lineIndex].St1;
    while ((*currentSt).next)
    {
        if(!(strcmp(addStName,(*currentSt).name)))
        {
            printf("增加失败，已有同名站点\n");
            return;
        }
        currentSt=(*currentSt).next;
    }//已经有这个站点了
    strcpy((*newSt).name,addStName);//新站点名字
    (*newSt).dis=nextDis;//新站点距离下一站的距离
    (*newSt).next=metroMap.Line[lineIndex].St1;//新站点的下一个人指向原来的第一站
    metroMap.Line[lineIndex].St1->prev=newSt;//原来第一站的前一站更新为新站点
    metroMap.Line[lineIndex].St1=newSt;//第一站指针更新为新站点
    printMetroLine(lineNo);
    return;
}

void deleteStation(int lineNo,char *stName)//删除lineNo号线的“stName”站点
{
    int lineIndex;
    for(lineIndex=0;lineIndex<metroMap.n;lineIndex++)
    {
        if(metroMap.Line[lineIndex].lineNo==lineNo)break;
    }
    //下标为lineIndex的线路号即为传参进来的线路号lineNo
    struct station *currentSt=metroMap.Line[lineIndex].St1;
    while ((*currentSt).next)
    {
        if(!(strcmp(stName,(*currentSt).name)))break;
        currentSt=(*currentSt).next;
    }
    if(!((*currentSt).next))
    {
        printf("删除失败，没有同名站点\n");
        return;
    }
    //没找到
    //现在currentSt指向待删除站点
    (*currentSt).next->prev=(*currentSt).prev;//下一站接上上一站
    (*currentSt).prev->next=(*currentSt).next;//上一站接上下一站
    (*currentSt).prev->dis+=(*currentSt).dis;//更新距离
    free(currentSt);
    printMetroLine(lineNo);
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

void deleteMap()//释放内存用
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
    //printMetroLine(1);
    //addStation2(1,2.00,"码头潭公园");//Success，同名Success
    //addStation1(1,3.00,2.00,"六渡桥","码头潭公园");//Success
    //addStation1(1,3.00,2.00,"八渡桥","小智路");//Success
    //deleteStation(1,"小智路");//Success
    //printMetroLine(1);
    printMap();
    char op[10];
    scanf("%s",op);
    int lineNo;
    float prevDis;
    float nextDis;
    char prevStName[30];
    char addStName[30];
    char stName[30];
    if(!strcmp("add",op))//增加
    {
        scanf("%d %f %f",&lineNo,&prevDis,&nextDis);
        if(!prevDis)
        {
            scanf("%s",addStName);
            addStation2(lineNo,nextDis,addStName);
        }
        else
        {
            scanf("%s %s",prevStName,addStName);
            addStation1(lineNo,prevDis,nextDis,prevStName,addStName);
        }
    }
    else
    {
        scanf("%d %s",&lineNo,stName);
        deleteStation(lineNo,stName);
    }

    deleteMap();
    return 0;
}
/*
Issue:
1.struct map's Line[4] can be optimized as dynamic allocated structure.
*/
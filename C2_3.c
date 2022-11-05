/*
Author:Someijam
Date:2022/11/01
Problem description:
第3关：计算最短路径
*/
/*
4
1 六渡桥 5.00 循礼门 4.00 大智路 4.00 三阳路 5.00 黄浦路 0 
2 汉口火车站 10.00 范湖 2.00 王家墩东 2.00 青年路 4.00 中山公园 2.00 循礼门 2.00 江汉路 5.00 积玉桥 0 
6 三眼桥 3.00 香港路 2.00 苗栗路 2.00 大智路 5.00 江汉路 1.00 汉正街 0 
7 武汉商务区 1.00 王家墩东 2.00 取水楼 2.00 香港路 6.00 三阳路 9.00 徐家棚 3.00 三角路 3.00 三层楼 3.00 积玉桥 0
青年路 积玉桥
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct section//称section为两站之间的一段线路
{
    float length;//长度
    int targetIndex;//这条路线指向另一端的站点
    struct section *sameSrcNextSec;//相同站点延伸出的下一条路线
};

struct station
{
    char name[30];//站点名字
    struct section *firstSection;//站点发散出的第一条路线
}station[50];//全局存储图

void deleteStations()
{
    for(int i=0;i<100;i++)
    {
        struct section *toDelete=station[i].firstSection;
        struct section *wayPoint=(*toDelete).sameSrcNextSec;
        free(toDelete);
        while (wayPoint)
        {
            toDelete=wayPoint;
            wayPoint=(*wayPoint).sameSrcNextSec;
            free(toDelete);
        }
    }
    puts("OK");
}

int main(int argc, char const *argv[])
{
    int lineNo;
    int n;
    scanf("%d",&n);
    int prevStIndex=0;//上一站的下标
    int prevSecLength=0;//上一条路线的长度
    for(int currentIndex=0;currentIndex<100;currentIndex++)
    {
        if(prevSecLength==0)scanf("%d",&lineNo);
        char name[30];
        scanf("%s",name);
        int isDuplicated=0;
        int duplicatedIndex=-1;
        for(int i=0;i<currentIndex;i++)//遍历之前存储的名字
        {
            if(!strcmp(name,station[i].name))
            {
                isDuplicated=1;
                duplicatedIndex=i;
                break;
            }
        }
        if(isDuplicated)//已经有了
        {
            struct section *newSection = (struct section*)malloc(sizeof(struct section));
            (*newSection).sameSrcNextSec=station[duplicatedIndex].firstSection;
            station[duplicatedIndex].firstSection=newSection;
            scanf("%f",&((*newSection).length));
            prevSecLength=(*newSection).length;
            if(prevStIndex>=0/*避免第一个越界*/)station[prevStIndex].firstSection->targetIndex=duplicatedIndex;
            prevStIndex=duplicatedIndex;
            currentIndex--;
        }
        else//还没有
        {
            strcpy(station[currentIndex].name,name);
            struct section *newSection = (struct section*)malloc(sizeof(struct section));
            station[currentIndex].firstSection=newSection;
            scanf("%f",&((*newSection).length));
            prevSecLength=(*newSection).length;
            (*newSection).sameSrcNextSec=NULL;
            (*newSection).targetIndex=-1;
            //?if((*newSection).length!=0)(*newSection).targetIndex=currentIndex+1;
            if(prevStIndex>=0)station[prevStIndex].firstSection->targetIndex=currentIndex;//之前一站最近添加的section是firstSection
            prevStIndex=currentIndex;
        }
    }
    char startStationName[30];
    char destStationName[30];
    scanf("%s %s",startStationName,destStationName);

    
    return 0;
}
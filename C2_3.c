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
#include<errno.h>
#include<string.h>

int INF=0x3F3F3F3F;
int alongWay[50];

struct section//称section为两站点之间的一段线路
{
    float length;//长度
    int targetIndex;//这条路线指向另一端的站点
    int srcIndex;//发散出这条路线的站点
    int isReverse;//是后来增加的逆向线路吗？
    struct section *sameSrcNextSec;//相同站点延伸出的下一条路线
};

struct station//称station为站点
{
    char name[30];//站点名字
    struct section *firstSection;//站点发散出的第一条路线
}station[50];//全局存储图
int stationCount=0;//总共站点数，遍历用

float distanceFromStartSt[50];//认为这里存的是所有点到出发点的最短距离，会被逐渐更新
int shortestPrevSt[50];//最短路径中每一个节点前面的节点，例如从某点到station[5]的最短路径为……1-4-5，那么shortestPrevSt[5]=4;
int isInShortestPath[50];//标记最短路径中的站点

void calcDisFromA(int A)
{
    /*
    A的相邻节点是station[A].firstSection->targetIndex
    以及(*station[A].firstSection).sameSrcNextSec->targetIndex
    */
    for(struct section *p=station[A].firstSection;p;p=p->sameSrcNextSec)//p是正在检测的线路
    {
        if((distanceFromStartSt[A]+(*p).length)<distanceFromStartSt[(*p).targetIndex])
        {
            distanceFromStartSt[(*p).targetIndex]=distanceFromStartSt[A]+(*p).length;
            shortestPrevSt[(*p).targetIndex]=A;
        }
    }

    return;
}

void Dijkstra(int startIndex,int destIndex)
{
    for(int i=0;i<stationCount;i++)distanceFromStartSt[i]=INF;//所有站点(i)到起始站点距离初始化为INF
    for(int i=0;i<stationCount;i++)shortestPrevSt[i]=-1;//前一个点默认初始化为空（-1）
    distanceFromStartSt[startIndex]=0;//起始站点到自身的最短距离当然为0
    int prevAddedSt=startIndex;//刚刚被标记的点，第一个自然是起始点
    while (isInShortestPath[destIndex]!=1)//循环条件，终点未被标记
    {
        int minDis=INF;
        int minIndex=-1;
        /*调试用，输出寻路过程
        for(int i=0;i<21;i++)
        {
            if(distanceFromStartSt[i]<100)printf("%d %s  \t %d \t %.2f \t %d %s\n",i,station[i].name,isInShortestPath[i],distanceFromStartSt[i],shortestPrevSt[i],station[shortestPrevSt[i]].name);
            else printf("%d %s  \t %d \t INF \t %d %s\n",i,station[i].name,isInShortestPath[i],shortestPrevSt[i],station[shortestPrevSt[i]].name);
        }
        */
        //printf("\n");
        for(int i=0;i<stationCount;i++)//遍历所有未标记节点
        {
            if(isInShortestPath[i])continue;
            if(distanceFromStartSt[i]<minDis)
            {
                minDis=distanceFromStartSt[i];
                minIndex=i;
            }
        }
        //这时，minIndex就是未标记节点中距离出发点最近节点
        isInShortestPath[minIndex]=1;//标记它
        int A=minIndex;
        calcDisFromA(A);//计算刚刚标记的节点A与其相邻节点B的距离，不包含已标记的节点
        //更新B距离，条件(A～B+Length AB)< B原本到起点的最短距离
    }
    

}

void revAlongWay()//输出用，逆序数组
{
    int l,r;
    l=0;
    r=49;
    while (alongWay[r]==-1)
    {
        r--;
    }
    while (l<r)
    {
        alongWay[l]=alongWay[l]+alongWay[r];
        alongWay[r]=alongWay[l]-alongWay[r];
        alongWay[l]=alongWay[l]-alongWay[r];
        l++;
        r--;
    }
    return;
}

float disFromTwoSt(int sta,int stb)//查找sta到stb的距离
{
    for(struct section *p=station[sta].firstSection;p;p=p->sameSrcNextSec)
    {
        if(!strcmp(station[stb].name,station[(*p).targetIndex].name))return (*p).length;
    }
    return INF;
}

void deleteStations()//删除整个邻接表，释放空间
{
    for(int i=0;station[i].name[0]!=0;i++)
    {
        struct section *q=station[i].firstSection;
        struct section *p=q;
        while (q->sameSrcNextSec)
        {
            p=q->sameSrcNextSec;
            free(q);
            q=p;
        }
        free(q);
        //printf("Freed %d\n",i);
    }
}

int main(int argc, char const *argv[])
{
    int lineNo;
    int n;
    scanf("%d",&n);
    int prevStIndex=0;//上一站的下标
    int prevSecLength=0;//上一条路线的长度
    int processedLines=0;
    for(int currentIndex=0;currentIndex<100&&processedLines<n;currentIndex++)//处理输入，存储整张图
    {
        if(prevSecLength==0)
        {
            scanf("%d",&lineNo);
        }
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
            struct section *newSection = (struct section*)malloc(sizeof(struct section));//新建线路
            (*newSection).isReverse=0;
            (*newSection).sameSrcNextSec=station[duplicatedIndex].firstSection;
            (*newSection).srcIndex=duplicatedIndex;
            station[duplicatedIndex].firstSection=newSection;//把新线路增加进已经存在的站点下
            scanf("%f",&((*newSection).length));
            prevSecLength=(*newSection).length;
            if(prevSecLength==0)(*newSection).length=100;//终点站
            if(prevStIndex>=0/*避免第一个越界*/)station[prevStIndex].firstSection->targetIndex=duplicatedIndex;
            prevStIndex=duplicatedIndex;
            currentIndex--;
        }
        else//还没有
        {
            strcpy(station[currentIndex].name,name);
            struct section *newSection = (struct section*)malloc(sizeof(struct section));//新建线路
            (*newSection).isReverse=0;
            station[currentIndex].firstSection=newSection;//绑定到这个站点下
            scanf("%f",&((*newSection).length));
            prevSecLength=(*newSection).length;
            if(prevSecLength==0)(*newSection).length=100;//终点站
            (*newSection).sameSrcNextSec=NULL;
            (*newSection).targetIndex=-1;
            (*newSection).srcIndex=currentIndex;
            //?if((*newSection).length!=0)(*newSection).targetIndex=currentIndex+1;
            if(prevStIndex>=0)station[prevStIndex].firstSection->targetIndex=currentIndex;//之前一站最近添加的section是firstSection
            prevStIndex=currentIndex;
        }
        //if(processedLines==n)break;
        if(prevSecLength==0)processedLines++;
    }
    for(int i=0;station[i].name[0]!=0;i++)stationCount++;
    for(int i=0;i<stationCount;i++)//遍历，把反向线路也加上去
    {
        for(struct section *p=station[i].firstSection;p;p=p->sameSrcNextSec)
        {
            if((*p).isReverse)continue;
            struct section *newRevSec = (struct section*)malloc(sizeof(struct section));//新建反向线路
            (*newRevSec).length=(*p).length; //反向线路长度等于当前线路长度
            (*newRevSec).targetIndex=i; //反向线路指向当前站点
            (*newRevSec).srcIndex=(*p).targetIndex; //反向线路的源站点为当前线路指向站点
            (*newRevSec).isReverse=1; //记录一下这是逆向的线路

            (*newRevSec).sameSrcNextSec=station[(*p).targetIndex].firstSection;
            station[(*p).targetIndex].firstSection=newRevSec;
            //反向线路(*newRevSec)绑定到当前线路(*p)指向站点的第一个线路前(左站点station[i],右站点station[(*p).targetIndex])
        }
    }
    char startStationName[30];
    char destStationName[30];
    int startIndex=0;
    int destIndex=0;
    scanf("%s %s",startStationName,destStationName);
    for(int i=0;i<100&&(station[i].name[0]!=0);i++)
    {
        if(!strcmp(startStationName,station[i].name))startIndex=i;
        if(!strcmp(destStationName,station[i].name))destIndex=i;
    }
    //printf("%s\n",station[startIndex].name);
    //printf("%s\n",station[destIndex].name);
    //此处，已完成起始站点和最终站点的录入，它们在station中的下标分别为startIndex,destIndex
    Dijkstra(startIndex,destIndex);
    //以下处理输出
    printf("%.2f ",distanceFromStartSt[destIndex]);
    for(int i=0;i<50;i++)alongWay[i]=-1;
    int destIndex2=destIndex;
    alongWay[0]=destIndex;
    for(int i=1;i<50&&(destIndex2!=startIndex);i++)
    {
        alongWay[i]=shortestPrevSt[destIndex2];
        destIndex2=alongWay[i];
    }
    revAlongWay();
    for(int i=0;alongWay[i+1]!=-1;i++)
    {
        printf("%s %.2f ",station[alongWay[i]].name,disFromTwoSt(alongWay[i],alongWay[i+1]));
    }
    printf("%s",station[destIndex].name);
    //释放空间
    deleteStations();
    return 0;
}
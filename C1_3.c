/*
Author:Someijam
Date:2022/11/16
Problem description:
第3关：一元稀疏多项式加减运算
*/
/*
6 -3 -1 1 4.4 2 -1.2 9 - -6 -3 5.4 2 7.8 15
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
struct polyItem
{
    float c;
    int e;
}poly1[100],poly2[100],polySum[100];
bool opPlus=true;
int cnt1=0;
int cnt2=0;
int cntSum=0;
int printSum=0;
bool containsNeg=false;
void polySwap(int polyNo,int i,int j)
{
    //polyNo[i,j].c,e
    if(polyNo==1)
    {
        poly1[i].c=poly1[i].c+poly1[j].c;//a=a+b
        poly1[j].c=poly1[i].c-poly1[j].c;//b=a-b
        poly1[i].c=poly1[i].c-poly1[j].c;//a=a-b
        poly1[i].e=poly1[i].e+poly1[j].e;//a=a+b
        poly1[j].e=poly1[i].e-poly1[j].e;//b=a-b
        poly1[i].e=poly1[i].e-poly1[j].e;//a=a-b
    }
    else if(polyNo==2)
    {
        poly2[i].c=poly2[i].c+poly2[j].c;//a=a+b
        poly2[j].c=poly2[i].c-poly2[j].c;//b=a-b
        poly2[i].c=poly2[i].c-poly2[j].c;//a=a-b
        poly2[i].e=poly2[i].e+poly2[j].e;//a=a+b
        poly2[j].e=poly2[i].e-poly2[j].e;//b=a-b
        poly2[i].e=poly2[i].e-poly2[j].e;//a=a-b
    }
    return;
}

void inputProcess()
{
    char tempNum[20];
    while (scanf("%s",tempNum)&&strcmp(tempNum,"+")&&strcmp(tempNum,"-"))
    {
        poly1[cnt1].c=atof(tempNum);
        scanf("%d",&poly1[cnt1].e);
        cnt1++;
    }
    if(!strcmp(tempNum,"-"))opPlus=false;
    while (scanf("%s",tempNum)!=EOF)
    {
        poly2[cnt2].c=atof(tempNum);
        scanf("%d",&poly2[cnt2].e);
        cnt2++;
    }
    return;
}

void sortProcess()//都改为降幂
{
    for(int i=0;i<cnt1-1;i++)
    {
        for(int j=i+1;j<cnt1;j++)
        {
            if(poly1[i].e<poly1[j].e)
            {
                polySwap(1,i,j);
            }
        }
    }
    for(int i=0;i<cnt2-1;i++)
    {
        for(int j=i+1;j<cnt2;j++)
        {
            if(poly2[i].e<poly2[j].e)
            {
                polySwap(2,i,j);
            }
        }
    }
    return;
}

void calcProcess()
{
    for(int i=0,j=0;i<cnt1&&j<cnt2;cntSum++)
    {
        if(poly1[i].e>poly2[j].e)
        {
            polySum[cntSum].e=poly1[i].e;
            polySum[cntSum].c=poly1[i].c;
            if(polySum[cntSum].c<0)containsNeg=true;
            i++;
        }
        else if(poly1[i].e<poly2[j].e)
        {
            polySum[cntSum].e=poly2[j].e;
            if(opPlus)polySum[cntSum].c=poly2[j].c;
            else polySum[cntSum].c=-poly2[j].c;
            if(polySum[cntSum].c<0)containsNeg=true;
            j++;
        }
        else if(poly1[i].e==poly2[j].e)
        {
            assert(poly1[i].e==poly2[j].e);
            polySum[cntSum].e=poly1[i].e;
            if(opPlus)polySum[cntSum].c=poly1[i].c+poly2[j].c;
            else polySum[cntSum].c=poly1[i].c-poly2[j].c;
            if(polySum[cntSum].c<0)containsNeg=true;
            i++;
            j++;
        }
    }
    return;
}

void printProcess()
{
    if(containsNeg)cntSum++;
    for(int i=0;i<cntSum;i++)
    {
        if(polySum[i].c==0&&polySum[i].e!=0)continue;
        else 
        {
            if(printSum!=0&&polySum[i].c==0&&polySum[i].e==0)continue;
            printf("%g %d ",polySum[i].c,polySum[i].e);
            printSum++;
        }
    }
    if(printSum==0)printf("0 0");
    return;
}

int main(int argc, char const *argv[])
{
    inputProcess();
    sortProcess();
    calcProcess();
    printProcess();
    return 0;
}
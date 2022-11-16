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
#include<stdbool.h>
struct polyItem
{
    float c;
    int e;
}poly1[100],poly2[100];
bool opPlus=true;
int cnt1=0;
int cnt2=0;
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
    for(int i=0;i<cnt1-1;i++)
    {
        for(int j=i+1;j<cnt1;j++)
        {
            if(poly2[i].e<poly2[j].e)
            {
                polySwap(2,i,j);
            }
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    inputProcess();
    sortProcess();

    return 0;
}
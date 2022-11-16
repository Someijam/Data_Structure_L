/*
Author:Someijam
Date:2022/11/16
Problem description:
temp
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    char tempNum[20];
    float c;
    int e;
    while (scanf("%s",tempNum)&&strcpy(tempNum,"+")&&strcpy(tempNum,"-"))
    {
        c=atof(tempNum);
        scanf("%d",&e);
        printf("%f\n",c);
        printf("%d\n",e);
    }
    return 0;
}
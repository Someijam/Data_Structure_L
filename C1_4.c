/*
Author:Someijam
Date:2022/11/16
Problem description:
第4关：一元稀疏多项式运算的升级功能
*/

/*
(c1x^e1±c2x^e2±...±cnx^en1)±(c1'x^e1'±c2'x^e2'±...±cn'x^en2')
 [---------poly1---------] * [------------poly2------------]
                           i

polyStr:
c1x^e1±c2x^e2±...±cnx^en1

[---------poly?---------]

x+x^3
-x +4.4x^2 +6x^-3 -1.2x^9\0
i  i   j   i      i
特殊情况：
‘+’或者‘-’后面跟着‘x’，系数绝对值为1
‘x’后面不是‘^‘，指数为1
数字后面没有’x‘，常数项

指针i拜访每一项开头的系数符号，条件：
(i==0)||(polyStr[i]=='+')||((polyStr[i]=='-')&&((i==1)||(polyStr[i-1]!='^')))

1.定符号
polyStr[i]=='-' ...
else ...(+)

2.找系数
while(polyStr[j]是数字或者点)j++;
系数绝对值为:
[i+1,j-1],(polyStr[i+1]!='x')
1        ,(polyStr[i+1]=='x')

3.找指数
k=j;
while(polyStr[k])


*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
struct polyItem
{
    float c;
    int e;
}poly1[100],poly2[100],polySum[100];
struct fullItem
{
    bool signNeg;//系数是负的吗？
    float cAbs;
    int exp;
};

bool opPlus=true;//这俩多项式进行什么运算
int cnt1=0;
int cnt2=0;
int cntSum=0;
int printSum=0;
bool containsNeg=false;
char phrases[1000];
char polyStr1[500];
char polyStr2[500]; 

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
    gets(phrases);
    int opSignPos=0;
    for(int i=0;i<strlen(phrases);i++)
    {
        if((phrases[i]=='+'||phrases[i]=='-')&&phrases[i-1]==')'&&phrases[i+1]=='(')//i指向两个表达式运算符
        {
            if(phrases[i]=='-')opPlus=false;
            opSignPos=i;
            break;
        }
    }
    for(int j=1;j<=opSignPos-2;j++)polyStr1[j-1]=phrases[j];
    for(int j=opSignPos+2;j<=strlen(phrases)-2;j++)polyStr2[j-opSignPos-2]=phrases[j];
    //把无意义的括号去掉，两端表达式分开到两个字符串中
    bool itemRead=false;
    for(int i=0;i<strlen(polyStr1);)//处理第一个多项式,循环一次处理一项
    {

        /*
        if(polyStr1[i]=='+')//如果是加号，那么一定是这一项系数的符号
        {
            if(polyStr1[i+1]=='x')tempItem.cAbs=1;
            tempItem.signNeg=false;
            continue;
        }
        else if(polyStr1[i]=='-'&&(i==0||polyStr1[i-1]!='^'))//减号：系数的符号(this)，指数的符号
        {
            if(polyStr1[i+1]=='x')tempItem.cAbs=1;
            tempItem.signNeg=true;
            continue;
        }
        else if('0'<=polyStr1[i]&&polyStr1[i]<='9')//是数字
        {
            int j=i+1;
            while (('0'<=polyStr1[j]&&polyStr1[j]<='9')||polyStr1[j]=='.')j++;
            //|coef|=[i,j-1]
            char numAbs[20]={0};
            for(int k=i;k<=j-1;k++)numAbs[k-i]=polyStr1[k];
            tempItem.cAbs=atof(numAbs);
            i=j;
        }
        else if(polyStr1[i]=='x')
        {
            if(polyStr1[i+1]!='^')tempItem.exp=1;
            continue;
        }
        else if(polyStr1[i]=='^')//表示后面的数是指数
        {
            int j=i+1;
            int k=j+1;
            while (polyStr1[k]!='+'&&polyStr1[k]!='-')k++;//k:指数中间的某一位 或 后面一项系数的符号(this) 或 到头了
            //exp=atoi[j,k-1]
            char numAbs[20]={0};
            for(int l=j;l<=k-1;l++)numAbs[l-j]=polyStr1[l];
            tempItem.exp=atoi(numAbs);
            i=k;
        }
        poly1[cnt1].c=tempItem.cAbs;
        if(tempItem.signNeg)poly1[cnt1].c*=-1;
        poly1[cnt1].e=tempItem.exp;
        cnt1++;
        */
    }

    itemRead=false;//下面处理第二个


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
    for(int i=0,j=0;i+j<cnt1+cnt2;cntSum++)
    {
        if((poly1[i].e>poly2[j].e)&&i<cnt1)
        {
            polySum[cntSum].e=poly1[i].e;
            polySum[cntSum].c=poly1[i].c;
            if(polySum[cntSum].c<0)containsNeg=true;
            i++;
        }
        else if((poly1[i].e<poly2[j].e)&&j<cnt2)
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
        else if(i>=cnt1)//第一个人加完了
        {
            while (j<cnt2)
            {
                polySum[cntSum].e=poly2[j].e;
                if(opPlus)polySum[cntSum].c=poly2[j].c;
                else polySum[cntSum].c=-poly2[j].c;
                if(polySum[cntSum].c<0)containsNeg=true;
                j++;
                cntSum++;
            }
            cntSum--;
        }
        else if(j>=cnt2)//第二个人加完了
        {
            while (i<cnt1)
            {
                polySum[cntSum].e=poly1[i].e;
                polySum[cntSum].c=poly1[i].c;
                if(polySum[cntSum].c<0)containsNeg=true;
                i++;
                cntSum++;
            }
            cntSum--;
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
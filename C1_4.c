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
ij i   j   i j    i   j
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
int j=i+1;
while(polyStr[j]是数字或者点)j++;
系数绝对值为:
[i+1,j-1],(polyStr[j+1]!='x')
1        ,(polyStr[j+1]=='x')

3.找指数
if [j+1]=='^'
    [k+2]不是指数的负号就是数字， k从 [j+3]往后找，until [k] 不是数字
    e=[j+2,k-1];
if [j+1]!='^'
    e=1;

4.存数据，引用数据，计数

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>
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
    for(int i=0;i<strlen(polyStr1);)//处理第一个多项式,循环一次处理一项
    {
        struct fullItem temp;
        bool isItemReady=false;
        if((i==0)||(polyStr1[i]=='+')||((polyStr1[i]=='-')&&((i==1)||(polyStr1[i-1]!='^'))))//到达一项的开头
        {
            int j=i+1;
            if(polyStr1[i]=='-')temp.signNeg=true;
            else 
            {
                temp.signNeg=false;//定符号
                if(i==0)j=i;
            }
            while (('0'<=polyStr1[j]&&polyStr1[j]<='9')||polyStr1[j]=='.')j++;//j到'x'了
            char tempAbs[20]={0};
            //|c|=[i+1(i!=0),j-1]
            if(polyStr1[i+1]!='x')//系数绝对值为1的项
            {
                if(i!=0)for(int p=i+1;p<=j-1;p++)tempAbs[p-i-1]=polyStr1[p];
                else if(i==0)for(int p=0;p<=j-1;p++)tempAbs[p]=polyStr1[p];
                temp.cAbs=atof(tempAbs);
            }
            else if(polyStr1[i+1]=='x')
            {
                temp.cAbs=1;
            }//找系数
            if(polyStr1[j+1]!='^')
            {
                temp.exp=1;
                i=j+1;
            }
            else 
            {
                if(polyStr1[j+2]=='-')
                {
                    int k=j+3;
                    while ('0'<=polyStr1[k]&&polyStr1[k]<='9')k++;
                    char tempExp[20]={0};
                    for(int p=j+2;p<=k-1;p++)tempExp[p-j-2]=polyStr1[p];
                    temp.exp=atoi(tempExp);
                    i=k;
                }
                else
                {
                    int k=j+2;
                    while ('0'<=polyStr1[k]&&polyStr1[k]<='9')k++;
                    char tempExp[20]={0};
                    for(int p=j+2;p<=k-1;p++)tempExp[p-j-2]=polyStr1[p];
                    temp.exp=atoi(tempExp);
                    i=k;
                }
            }//找指数
            isItemReady=true;
            //至此，一项的信息存储到temp中
        }
        poly1[cnt1].c=temp.cAbs;
        if(temp.signNeg)poly1[cnt1].c*=-1;
        poly1[cnt1].e=temp.exp;
        cnt1++;
        //把这一项添加到poly1中
    }
    //下面处理第二个
    for(int i=0;i<strlen(polyStr2);)//处理第一个多项式,循环一次处理一项
    {
        struct fullItem temp;
        bool isItemReady=false;
        if((i==0)||(polyStr2[i]=='+')||((polyStr2[i]=='-')&&((i==1)||(polyStr2[i-1]!='^'))))//到达一项的开头
        {
            int j=i+1;
            if(polyStr2[i]=='-')temp.signNeg=true;
            else 
            {
                temp.signNeg=false;//定符号
                if(i==0)j=i;
            }
            while (('0'<=polyStr2[j]&&polyStr2[j]<='9')||polyStr2[j]=='.')j++;
            char tempAbs[20]={0};
            if(polyStr2[i+1]!='x')
            {
                if(i!=0)for(int p=i+1;p<=j-1;p++)tempAbs[p-i-1]=polyStr2[p];
                else if(i==0)for(int p=0;p<=j-1;p++)tempAbs[p]=polyStr2[p];
                temp.cAbs=atof(tempAbs);
            }
            else if(polyStr2[i+1]=='x')
            {
                temp.cAbs=1;
            }//找系数
            if(polyStr2[j+1]!='^')
            {
                temp.exp=1;
                i=j+1;
            }
            else 
            {
                if(polyStr2[j+2]=='-')
                {
                    int k=j+3;
                    while ('0'<=polyStr2[k]&&polyStr2[k]<='9')k++;
                    char tempExp[20]={0};
                    for(int p=j+2;p<=k-1;p++)tempExp[p-j-2]=polyStr2[p];
                    temp.exp=atoi(tempExp);
                    i=k;
                }
                else
                {
                    int k=j+2;
                    while ('0'<=polyStr2[k]&&polyStr2[k]<='9')k++;
                    char tempExp[20]={0};
                    for(int p=j+2;p<=k-1;p++)tempExp[p-j-2]=polyStr2[p];
                    temp.exp=atoi(tempExp);
                    i=k;
                }
            }//找指数
            isItemReady=true;
            //至此，一项的信息存储到temp中
        }
        poly2[cnt2].c=temp.cAbs;
        if(temp.signNeg)poly2[cnt2].c*=-1;
        poly2[cnt2].e=temp.exp;
        cnt2++;
        //把这一项添加到poly2中
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
        if(polySum[i].c==0&&polySum[i].e!=0)continue;//系数为0省略此项
        else 
        {
            if(printSum!=0&&polySum[i].c==0&&polySum[i].e==0)continue;//值为0省略此项
            //printf("%g %d ",polySum[i].c,polySum[i].e);
            if(polySum[i].c>0&&printSum!=0)printf("+");//正系数并且不是第一个，要输出加号
            if(polySum[i].c<0)printf("-");
            if(fabsf(polySum[i].c)!=1)//polySum[i].c的绝对值不为1
                printf("%g",fabs(polySum[i].c));//系数绝对值为1不输出系数绝对值
            if(polySum[i].e!=1&&polySum[i].e!=0)printf("x^%d",polySum[i].e);//指数为1不输出指数
            else if(polySum[i].e==1)printf("x");
            //指数为0只输出系数
            printSum++;
        }
    }
    if(printSum==0)printf("0");
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
//-7.8x^15-1.2x^9 -1x^2 -x +12x^-3
//-7.8x^15-1.2x^9 -x^2  -x +12x^-3
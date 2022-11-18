/*
Author:Someijam
Date:2022/11/16
Problem description:
temp
*/
/*
(c1x^e1±c2x^e2±...±cnx^en1)±(c1'x^e1'±c2'x^e2'±...±cn'x^en2')
 [---------poly2---------] * [------------poly2------------]
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
while(polyStr[j]是数字或者点)j++;
系数绝对值为:
[i+1,j-1],(polyStr[j+1]!='x')
1        ,(polyStr[j+1]=='x')

3.找指数
if [j+1]=='^'
    [j+2]不是指数的负号就是数字， k从 [j+3]往后找，until [k] 不是数字
    e=[j+2,k-1];
if [j+1]!='^'
    e=1;

4.存数据，引用数据，计数
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    char tempNum[20];//="dadada";
    gets(tempNum);
    printf("%lu",strlen(tempNum));
    return 0;
}
void a()
{
    
}
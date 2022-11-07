/*
Author:Someijam
Date:2022/11/06
Problem description:
exp
*/
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    char s[300]={0};
    cin.getline(s,300);
    for(int i=0;s[i]!=0;i++)
    {
        if(s[i]=='\t')s[i]=',';
    }
    cout<<s<<endl;
    return 0;
}
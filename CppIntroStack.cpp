/*
Author:Someijam
Date:2022/10/13
Problem description:
Intro Stack
*/
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
int main()
{
    std::stack<int> st1,st2;
    //1.使用push(int &&__v)方法压入元素
    st1.push(1);
    st1.push(2);
    //2.用等号来复制构造另外一个栈
    st2=st1;
    //3.使用top()方法获取栈顶元素
    cout<<st2.top()<<endl;
    //使用pop()弹出栈顶
    st1.pop();
    //st1是空的吗？
    bool isStack1Empty=st1.empty();
    cout<<isStack1Empty<<endl;
    //st2有多少个元素？
    int countOfSt2=st2.size();
    cout<<countOfSt2<<endl;
    return 0;
}
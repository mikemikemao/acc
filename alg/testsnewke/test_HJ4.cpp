//
// Created by maochaoqun on 2025/2/14.
//
/*
描述
对于给定的由小写字母和数字混合构成的字符串
s
s ，你需要按每
8
8 个字符换一行的方式书写它，具体地：
∙
 
∙书写前
8
8 个字符，换行；
∙
 
∙书写接下来的
8
8 个字符，换行；
∙
 
∙……
∙
 
∙重复上述过程，直到字符串被完全书写。
特别地，如果最后一行不满
8
8 个字符，则需要在字符串末尾补充
0
0 ，直到长度为
8
8 。
输入描述：
在一行上输入一个长度
1
≦
l
e
n
g
t
h
(
s
)
≦
100
1≦length(s)≦100 ，由小写字母和数字混合构成的字符串
s
s 。
输出描述：
输出若干行，每行输出
8
8 个字符，代表按题意书写的结果。*/
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    std::string s;
    cin >> s;

        int buLen = s.length() % 8;
        cout << s.length() <<endl;
        cout << buLen <<endl;
        if(buLen != 0) {
            s.append(8-buLen,'0');
        }
        cout << s.length() <<endl;
        for (int i = 0; i < s.length();i += 8) {
            cout << s.substr(i,8) << endl;
        }

    return 0;
}
//
// Created by maochaoqun on 2025/2/14.
//
/*
描述
对于给定的十六进制数，输出其对应的十进制表示。
在本题中，十六进制数的格式为：
0x
0x 开头，后跟若干个十六进制数字（
0-9
0-9 和
A-F
A-F ）。其中，
A-F
A-F 依次代表
10
−
15
10−15 。
输入描述：
在一行上输入一个十六进制数
s
s ，代表待转换的十六进制数。
保证
s
s 转化得到的十进制数
x
x 的范围为
1
≦
x
≦
2
31
−
1
1≦x≦2
31
 −1 。
输出描述：
在一行上输出一个整数，代表
s
s 对应的十进制数。
示例1
输入：
0xFA93
复制
输出：
64147
复制
说明：
回忆十六进制转化为十进制的方法：从右往左，将第
i
i 位乘以
1
6
i
16
i
  ，然后求和。

在这个样例中，
0xFA93
0xFA93 的第
0
0 位是
3
3 ，第
1
1 位是
9
9 ，第
2
2 位是
A
A ，第
3
3 位是
F
F ，因此
0xFA93
=
3
×
1
6
0
+
9
×
1
6
1
+
10
×
1
6
2
+
15
×
1
6
3
=
64147
0xFA93=3×16
0
 +9×16
1
 +10×16
2
 +15×16
3
 =64147 。*/
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <algorithm> // 包含reverse函数
#include <string>
using namespace std;
int main()
{
 int sum = 0;
 std::string s;
 std::string substr;
 cin >> s;
int temp[8] ={1,16,256,256*16,256*256,256*256*16,256*256*256,256*256*256*16};
 int temp1[16] ={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
 substr = s.substr(2,s.length()-2);
 cout << substr <<endl;
 std::reverse(substr.begin(),substr.end());
for (int i = 0; i< substr.length();i++) {
 for (int j = 0; j <16;j++ ) {
     if(substr.at(i) == temp1[j]) {
       sum += j*temp[i];
     }
 }

}
 cout << sum << endl;
 return 0;
}
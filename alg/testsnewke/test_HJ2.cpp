//
// Created by maochaoqun on 2025/2/12.
//
/*描述
对于给定的由大小写字母、数字和空格混合构成的字符串
s
s ，统计字符
c
c 在其中出现的次数。具体来说：
∙
 
∙若
c
c 为大写或者小写字母，统计其大小写形态出现的次数和；
∙
 
∙若
c
c 为数字，统计其出现的次数。
保证字符
c
c 仅为大小写字母或数字。
输入描述：
第一行输入一个长度
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
1
0
3
1≦length(s)≦10
3
  ，由大小写字母、数字和空格混合构成的字符串
s
s 。保证首尾不为空格。
第二行输入一个字符
c
c ，代表需要统计的字符。
输出描述：
在一行上输出一个整数，代表字符
c
c 在字符串
s
s 中出现的次数。
示例1
输入：
HELLONowcoder123
o
复制
输出：
3
复制
说明：
由于
o
o 为小写字母，因此统计其小写形态出现的次数和，即
3
3 。
示例2
输入：
H E L L O Nowcoder123
1
复制
输出：
1*/

#include <iostream>
#include <string>
using namespace std;

int main() {
  std::string s;
  string a;
  int num = 0;
  int tmpa = 0;
  int tmpb = 0;
  std::getline(std::cin, s);//接收带空格的字符串要用getline
  //反向寻找空格
  while(cin >> a)
  {
    tmpa = a.at(0);
    for(int i=0;i < s.length();i++) {
      tmpb = s.at(i);
      if( tmpa == tmpb) {
          num++;
      }
      if(tmpa >= 'a' && tmpa <= 'z') {
        if( (tmpa-32) == tmpb) {
          num++;
      }
      if(tmpa >= 'A' && tmpa <= 'Z') {
        if( (tmpa+32) == tmpb) {
          num++;
        }
      }
    }
    cout << num << endl;
  }
  return 0;
}

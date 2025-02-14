//
// Created by maochaoqun on 2025/2/14.
//
/*
描述
对于给定的整数
n
n ，从小到大依次输出它的全部质因子。即找到这样的质数
p
1
,
p
2
,
⋯
 
,
p
k
p
1
​
 ,p
2
​
 ,⋯,p
k
​
  ，使得
n
=
p
1
×
p
2
×
⋯
×
p
k
n=p
1
​
 ×p
2
​
 ×⋯×p
k
​
  。
输入描述：
在一行上输入一个整数
n
(
2
≦
n
≦
2
×
1
0
8
+
14
)
n(2≦n≦2×10
8
 +14) 代表待分解的整数。
输出描述：
在一行上从小到大输出若干个整数，代表
n
n 的质因子。
示例1
输入：
180
复制
输出：
2 2 3 3 5
复制
说明：
在这个样例中，
180
=
2
×
2
×
3
×
3
×
5
180=2×2×3×3×5 。
示例2
输入：
47
复制
输出：
47*/
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <algorithm> // 包含reverse函数
#include <string>
using namespace std;
#include <vector>
#include <cmath>

std::vector<int> prime_factorization(int n) {
 std::vector<int> factors;
 if (n <= 1) {
  return factors;
 }
 // 处理2的情况
 while (n % 2 == 0) {
  factors.push_back(2);
  n /= 2;
 }
 // 从3开始，步长为2，检查到sqrt(n)
 for (int i = 3; i <= sqrt(n); i += 2) {
  while (n % i == 0) {
   factors.push_back(i);
   n /= i;
  }
 }
 // 如果剩下的n是一个质数
 if (n > 2) {
  factors.push_back(n);
 }
 return factors;
}

// 示例使用
int main() {
 string s;
 cin >> s;
 int num = atoi(s.c_str());
 std::vector<int> result = prime_factorization(num);
 for (int factor : result) {
  // 输出每个质因数
  cout << factor << " ";
 }
 return 0;
}
//
// Created by maochaoqun on 2025/2/13.
//
/*
描述
对于明明生成的
n
n 个
1
1 到
500
500 之间的随机整数，你需要帮助他完成以下任务：
∙
 
∙删去重复的数字，即相同的数字只保留一个，把其余相同的数去掉；
∙
 
∙然后再把这些数从小到大排序，按照排好的顺序输出。
你只需要输出最终的排序结果。
输入描述：
第一行输入一个整数
n

(
1
≦
n
≦
1000
)
n (1≦n≦1000)，代表明明生成的数字个数。
此后
n
n 行，第
i
i 行输入一个整数
a
i

(
1
≦
a
i
≦
500
)
a
i
​
  (1≦a
i
​
 ≦500)，代表明明生成的随机整数。
输出描述：
输出若干行，每行输出一个整数，代表输入数据排序后的结果。第一行输出最小的数字。
示例1
输入：
3
2
2
1
复制
输出：
1
2
*/
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    int num = 0;
    int tmp = 0;
    set<int> numSet;
    std::string strNum;
    cin >> strNum;
    num = atoi(strNum.c_str());
    for (int i = 0; i < num; i++ ) {
        cin >> strNum;
        tmp = atoi(strNum.c_str());
        numSet.insert(tmp);
    }
    for (auto num : numSet) {
        cout << num << endl;
    }

}
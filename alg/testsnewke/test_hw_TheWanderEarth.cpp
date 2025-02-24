//
// Created by maochaoqun on 2025/2/24.
//

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
const int MAX = 1e3 + 5;
/*题目描述
流浪地球计划在赤道上均匀部署了N个转向发动机，按位置顺序编号为0~N-1。
初始状态下所有的发动机都是未启动状态。
发动机启动的方式分为“手动启动”和“关联启动”两种方式如果在时刻1一个发动机被启动，下一个时刻 2与之相邻的两个发动机就会被“关联启动”。如果准备启动某个发动机时，它已经被启动了，则什么都不用做。发动机0与发动机 N-1是相邻的。
地球联合政府准备挑选某些发动机在某些时刻进行“手动启动”。当然最终所有的发动机都会被启动。哪些发动机最晚被启动呢?
输入描述:
第一行两个数字N和E，中间有空格。
N 代表部署发动机的总个数，E 代表计划手动启动的发动机总个数。
接下来共E行，每行都是两个数字T和P，中间有空格。
T 代表发动机的手动启动时刻，P 代表此发动机的位置编号。
输出描述:
第一行一个数字 N，以回车结束。
N 代表最后被启动的发动机个数。
第二行 N个数字，中间有空格，以回车结束。
每个数字代表发动机的位置编号，从小到大排序
*/
//主要思路：记录数组每次标记的个数，标记个数等于全部个数 内容为第几次点亮的 表示全部点亮 退出循环。
//用times 表示第几次点亮的
int main() {
    int N, E, T, P, launch[MAX];
    memset(launch, -1, sizeof(launch));
    cin >> N >> E;
    for (int i = 0; i < E; i++)
    {
        cin >> T >> P;
        launch[P] = T;
    }
    for (int timer = 0; timer <= N; timer++)
    {
        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            if (launch[i] == -1)
            {
                if (launch[(i + 1) % N] != -1 && launch[(i + 1) % N] < timer ||
                    launch[(i + N - 1) % N] != -1 && launch[(i + N - 1) % N] < timer)
                {
                    launch[i] = timer;
                    cnt++;
                }
            }
            else if (launch[i] <= timer)
            {
                cnt++;
            }
        }
        cout << cnt << endl;
        if (cnt == N)
        {
            vector<int> nums;
            for (int i = 0; i < N; i++)
            {
                if (launch[i] == timer)
                {
                    nums.push_back(i);
                }
            }
            cout << nums.size() << endl;
            for (int i = 0; i < nums.size(); i++)
            {
                cout << nums[i] << " ";
            }
            break;
        }
    }
    return 0;
}

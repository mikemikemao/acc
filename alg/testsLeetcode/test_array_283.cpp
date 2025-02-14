//
// Created by maochaoqun on 2025/2/14.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
/**
 * 目标 最多改一个元素 成为非递减数列
 * @param array
 * @return
 */
int deletezero(vector<int> & array) {
    int times = 0;
    auto it = array.begin();
    while (it != array.end()) {
        it = std::find(array.begin(),array.end(),0);
        if(it != array.end()) {
            array.erase(it);
            times++;
        }
    }
    return times;
}
int addzero(vector<int> & array,int num) {
    array.insert(array.begin(),num,0);
    return 0;
}

int movZero(vector<int> & array) {
    int num = deletezero(array);
    addzero(array,num);
    return 0;
}

int main() {
    int min = 0;
    vector<int> array ={4,0,2,1,0,5};
    movZero(array);
    for (auto num : array) {
        cout << num << endl;
    }
    return 0;
}
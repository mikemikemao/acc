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
bool check(vector<int> & array) {
    int times = 0;
    for (int i =0; i< array.size()-1;i++) {
        if(array[i] > array[i+1]) {
            times++;
            if (times > 1) {
                break;
            }
        }
    }
    if(times <= 1) {
        return true;
    }else {
        return false;
    }
}

int main() {
    int min = 0;
    vector<int> array ={4,2,1,5};
    min = check(array);
    cout << min << endl;
}
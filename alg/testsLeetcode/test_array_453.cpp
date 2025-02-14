#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/**
 * 目标 array中所有元素都一致 每次操作使n-1个元素加1 等效于 每次操作使某个元素减一
 * @param array
 * @return
 */
int minMove(vector<int> & array) {
    int sum = 0;
    int min = *min_element(array.begin(),array.end());
    for (auto num : array) {
        sum += (num-min);
    }
    return sum;
}

int main() {
    int min = 0;
    vector<int> array ={1,2,3,5};
    min = minMove(array);
    cout << min << endl;
    return 0;
}


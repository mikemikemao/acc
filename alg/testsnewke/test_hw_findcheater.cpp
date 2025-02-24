//
// Created by maochaoqun on 2025/2/24.
//
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
struct Employee {
    Employee(int _id, int _score)
        :id(_id)
        ,score(_score)
    {}
    Employee()
    :id(-1)
    ,score(-1){}
    void toString() {
        cout << id << " " << score << endl;
    }
    int id;
    int score;
};

using namespace std;
int main() {
    vector<Employee> vecScore;
    int num = 0;
    int serial = 0;
    int score = 0;
    int min = 100;
    int startIdx = 0;
    int endIdx = 0;
    int diff = 0;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> serial >> score;
        Employee emp(serial, score);
        vecScore.push_back(emp);
    }
    vecScore.resize(num);
    cout << vecScore.size() << endl;
    for (auto emp : vecScore) {
        emp.toString();
    }
    std::sort(vecScore.begin(), vecScore.end(), [](Employee a, Employee b) {
        return a.score < b.score;
    });
    for (auto emp : vecScore) {
        emp.toString();
    }
    // //根据最小差值找到所有相同分数的编号
    startIdx = 0;
    endIdx = num-1;
    for (int i = 0; i < num-1; i++) {
        diff =vecScore[i+1].score - vecScore[i].score;
        if(diff == 0) {
            break;
        }
        if(diff < min) {
            min = diff;
        }
    }
    for (int i = 0; i < num-1; i++) {
        diff =vecScore[i+1].score - vecScore[i].score;
        if(diff == min) {
            cout << vecScore[i].id << " " << vecScore[i+1].id << endl ;
        }
    }
    return 0;
}

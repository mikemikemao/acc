//
// Created by maochaoqun on 2024/12/31.
//
#include <iostream>
#include "../Builder.h"
int main() {
    Director d1;
    Player * p1 = d1.construct("xiaowang",999,9999,1);   //输入构建规则需要的参数
    Player * p2 = Director().construct("xiaosong",888,8888,8);
    Player * p3 = playBuilder().SetName("zhangsan")->SetID(92)->build();
    p1->show();
    p2->show();
    p3->show();
    return 0;
}
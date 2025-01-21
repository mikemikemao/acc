//
// Created by maochaoqun on 2025/1/17.
//
#include "../State.h"

int main() {
    Worker *w1 = new Worker;
    w1->setHour(7);
    w1->doSomeThing();
    w1->setHour(9);
    w1->doSomeThing();
    delete w1;
    return 0;
}

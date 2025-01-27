//
// Created by pirat on 2025/1/27.
//
#include "../Interator.h"
#include <iostream>
#include <string>
int main() {
    myContainer<int>* pcon = new myVector<int>();
    myIter<int>* iter = pcon->CreateIterator();
    for (iter->First(); !iter->IsDone(); iter->Next())
    {
        std::cout << iter->CurrentItem() << std::endl;
    }
}
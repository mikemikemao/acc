//
// Created by maochaoqun on 2025/1/21.
//
#include "../Memento.h"
int main()
{
    Originator orginator;

    //捕获对象状态，存储到备忘录
    Memento mem = orginator.createMomento();

    //... 改变orginator状态

    //从备忘录中恢复
    orginator.setMomento(mem);



}
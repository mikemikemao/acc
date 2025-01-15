//
// Created by maochaoqun on 2025/1/15.
//
#include "../Adapter.h"
#include <iostream>
int main()
{
    Translator* translator = new Translator();
    Target *tar1 = new ClassAdapter();
    Target *tar2 = new ObjectAdapter(translator);

    tar1->translate("中文", "英文", "你好世界！");
    tar1->translate("英文", "中文", "hello world!");
    cout << endl;
    tar2->translate("中文", "英文", "你好世界！");
    tar2->translate("英文", "中文", "hello world!");
    return 0;
}

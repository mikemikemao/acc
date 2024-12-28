//
// Created by pirat on 2024/12/28.
//

#include <iostream>
#include "../FactoryMethod.h"
int main() {
    BinarySplitterFactory binarySplitterFactory;
    TxtSplitterFactory txtSplitterFactory;
    FactoryMethod factoryMethod;
    factoryMethod.setFacory(&binarySplitterFactory);
    //factoryMethod.setFacory(&txtSplitterFactory);
    factoryMethod.test();
    return 0;
}


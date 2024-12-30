//
// Created by maochaoqun on 2024/12/30.
//
#include <iostream>
#include "../Prototype.h"
int main() {
    BinarySplitter * binarySplitter =  new BinarySplitter();
    TxtSplitter * txtSplitter =  new TxtSplitter();
    ProtoType protoType;
    protoType.set(txtSplitter);
    protoType.test();
    return 0;
}


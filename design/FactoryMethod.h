//
// Created by pirat on 2024/12/28.
//

#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#include <iostream>

//抽象类
class ISplitter{
public:
    virtual void split()=0;
    virtual ~ISplitter(){}
};

//工厂基类
class SplitterFactory{
public:
    virtual ISplitter* CreateSplitter()=0;
    virtual ~SplitterFactory(){}
};

//具体类
class BinarySplitter : public ISplitter{
    void split() override {
        std::cout << "BinarySplitter" << std::endl;
    }
};

class TxtSplitter: public ISplitter{
    void split() override {
        std::cout << "TxtSplitter" << std::endl;
    }
};

//具体工厂
class BinarySplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new BinarySplitter();
    }
};

class TxtSplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new TxtSplitter();
    }
};

class FactoryMethod
{
private:
    SplitterFactory*  factory;//工厂
public:
    int setFacory(SplitterFactory*  factory){
        this->factory=factory;
        return 0;
    }
    void test(){
        ISplitter * splitter=factory->CreateSplitter(); //多态new
        splitter->split();
    }
};
#endif //FACTORYMETHOD_H

//
// Created by maochaoqun on 2024/12/30.
//

#ifndef PROTOTYPE_H
#define PROTOTYPE_H

//抽象类
class ISplitter{
public:
    virtual void split()=0;
    virtual ISplitter* clone()=0; //通过克隆自己来创建对象
    virtual ~ISplitter(){}

};

//具体类
class BinarySplitter : public ISplitter{
public:
    virtual ISplitter* clone(){
        return new BinarySplitter(*this);
    }
    virtual void split() override {
        std::cout << "BinarySplitter" << std::endl;
    }
};

class TxtSplitter: public ISplitter{
public:
    virtual ISplitter* clone(){
        return new TxtSplitter(*this);
    }
    virtual void split() override {
        std::cout << "TxtSplitter" << std::endl;
    }
};

class ProtoType
{
    ISplitter*  prototype;//原型对象
public:
    void set(ISplitter*  prototype){
        this->prototype=prototype;
    }
    void test(){
        ISplitter * splitter= prototype->clone(); //克隆原型
        splitter->split();
    }
};


#endif //PROTOTYPE_H

//
// Created by maochaoqun on 2025/1/21.
//

#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <iostream>
#include <map>
using namespace std;
// 组件接口会声明组合中简单和复杂对象的通用操作, C++中实现成抽象基类。
class Graphic {
public:
    virtual void move2somewhere(int x, int y) = 0;
    virtual void draw() = 0;
};

// 组合类表示可能包含子项目的复杂组件。组合对象通常会将实际工作委派给子项目，然后“汇总”结果。
class CompoundGraphic : public Graphic {
public:
    void add(int id, Graphic* child) {
        childred_[id] = (child);
    }
    void remove(int id) {
        childred_.erase(id);
    }
    void move2somewhere(int x, int y) override {
        for (auto iter = childred_.cbegin(); iter != childred_.cend(); iter++) {
            iter->second->move2somewhere(x, y);
        }
    }
    void draw() override {
        for (auto iter = childred_.cbegin(); iter != childred_.cend(); iter++) {
            iter->second->draw();
        }
    }

private:
    // key是图表id, value是图表指针
    std::map<int, Graphic*> childred_;
};


// 点
class Dot : public Graphic {
public:
    Dot(int x, int y) : x_(x), y_(y) {}
    void move2somewhere(int x, int y) override {
        x_ += x;
        y_ += y;
        return;
    }
    void draw() override {
        cout << "在("<< x_ <<","<< y_ <<")处绘制点"<<endl;
        return;
    }

private:
    int x_;
    int y_;
};

// 圆
class Circle : public Graphic {
public:
    explicit Circle(int r, int x, int y) : radius_(r), x_(x), y_(y) {}
    void move2somewhere(int x, int y) override {
        x_ += x;
        y_ += y;
        return;
    }
    void draw() override {
        cout << "在("<< x_ <<","<< y_ <<")为圆心绘制半径为%d的圆"<<endl;
    }

private:
    // 半径与圆心坐标
    int radius_;
    int x_;
    int y_;
};

#endif //COMPOSITE_H

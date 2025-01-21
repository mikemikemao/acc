//
// Created by maochaoqun on 2025/1/21.
//

#ifndef MEMENTO_H
#define MEMENTO_H
#include <iostream>
using namespace std;

class Memento
{
    string state;
    //..
public:
    Memento(const string & s) : state(s) {}
    string getState() const { return state; }
    void setState(const string & s) { state = s; }
};

class Originator
{
    string state;
    //....
public:
    Originator() {}
    Memento createMomento() {
        Memento m(state);
        return m;
    }
    void setMomento(const Memento & m) {
        state = m.getState();
    }
};

#endif //MEMENTO_H

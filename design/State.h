//
// Created by maochaoqun on 2025/1/17.
//

#ifndef STATE_H
#define STATE_H
#include <iostream>
using namespace std;

class Worker;

class State {
public:
    virtual void doSomeThing(Worker *w) = 0;
};

class Worker {
public:
    Worker();
    int getHour()
    {
        return m_hour;
    }
    void setHour(int hour)
    {
        m_hour = hour;
    }
    State* getCurrentState()
    {
        return m_currstate;
    }
    void setCurrentState(State *state)
    {
        m_currstate = state;
    }
    void doSomeThing()
    {
        m_currstate->doSomeThing(this);
    }
private:
    int m_hour;
    State *m_currstate;
};

class State1 : public State {
public:
    void doSomeThing(Worker *w);
};

class State2 : public State {
public:
    void doSomeThing(Worker *w);
};

void State1::doSomeThing(Worker *w) {
    if(w->getHour() == 7 || w->getHour() == 8)
    {
        cout << "eat food!" <<endl;
    }
    else
    {
        delete w->getCurrentState();
        w->setCurrentState(new State2);
        w->getCurrentState()->doSomeThing(w);
    }
}

void State2::doSomeThing(Worker *w) {
    if(w->getHour() == 9 || w->getHour() == 10)
    {
        cout << "working!" << endl;
    }
    else
    {
        delete w->getCurrentState();
        w->setCurrentState(new State1);
        cout << "currenttime:" << w->getHour() << endl;
    }
}

Worker::Worker() {
    m_currstate = new State1;
}


#endif //STATE_H

//
// Created by maochaoqun on 2025/1/13.
//

#ifndef PROXY_H
#define PROXY_H
#include <iostream>
#include <memory>

// 定义一个简单的接口
class Subject {
public:
    virtual void request() = 0;
    virtual ~Subject() = default;
};

// 实现实际的业务逻辑
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject processing request." << std::endl;
    }
};

// 动态代理类
class Proxy : public Subject {
public:
    Proxy(std::shared_ptr<Subject> realSubject) : realSubject_(realSubject) {}

    void request() override {
        preRequest();
        if (realSubject_) {
            realSubject_->request();
        }
        postRequest();
    }

private:
    std::shared_ptr<Subject> realSubject_;

    void preRequest() {
        std::cout << "Pre-request processing." << std::endl;
    }

    void postRequest() {
        std::cout << "Post-request processing." << std::endl;
    }
};

#endif //PROXY_H

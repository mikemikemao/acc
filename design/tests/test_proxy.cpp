//
// Created by maochaoqun on 2025/1/13.
//
#include "../Proxy.h"
int main() {
    // 创建实际对象
    std::shared_ptr<RealSubject> realSubject = std::make_shared<RealSubject>();

    // 创建代理对象
    std::shared_ptr<Proxy> proxy = std::make_shared<Proxy>(realSubject);

    // 通过代理对象调用方法
    proxy->request();

    return 0;
}
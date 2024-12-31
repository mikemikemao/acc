//
// Created by maochaoqun on 2024/12/31.
//

#ifndef SINGLETON_H
#define SINGLETON_H
#include <atomic>
#include <iostream>
#include <mutex>
class Singleton;

std::mutex m_mutex;

class Singleton{
private:
    Singleton() {
        std::cout << "Singleton" << std::endl;
    }
    Singleton(const Singleton& other){}
public:
    //线程非安全版本
    static Singleton* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new Singleton();
        }
        return m_instance;
    }
    //线程安全版本，但锁的代价过高
    static Singleton* getInstance1() {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_instance == nullptr) {
            m_instance = new Singleton();
        }
        return m_instance;
    }
    //双检查锁，但由于内存读写reorder不安全
    static Singleton* getInstance2() {
        if(m_instance==nullptr){
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr) {
                m_instance = new Singleton();
            }
        }
        return m_instance;
    }
    static Singleton* m_instance;
};

Singleton* Singleton::m_instance=nullptr;

std::mutex m_mutex_Ex;
class SingletonEx{
private:
    SingletonEx() {
        std::cout << "SingletonEx" << std::endl;
    }
    SingletonEx(const SingletonEx& other){}
public:
    static SingletonEx* getInstance() {
        SingletonEx* tmp = m_instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new SingletonEx();
                std::atomic_thread_fence(std::memory_order_release);//释放内存fence
                m_instance.store(tmp, std::memory_order_relaxed);
            }
        }
        return tmp;
    }
    static std::atomic<SingletonEx*> m_instance;//C++ 11版本之后的跨平台实现 (volatile)
};
#endif //SINGLETON_H

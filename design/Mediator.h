//
// Created by maochaoqun on 2025/1/17.
//

#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <iostream>
#include <map>
//Mediator.h
/****************************************************/
#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Person;

// 抽象中介者
class Mediator
{
public:
    // 发出信息
    virtual void sendMessage(std::string message, Person* colleague) = 0;

};

// 抽象类-人
class Person
{
public:
    // 构造函数
    Person(Mediator* mediator) : m_mediator(mediator) {}

    // 发出消息
    virtual void sendMessage(std::string message) = 0;

    // 获取消息
    virtual void getMessage(std::string message) = 0;

protected:
    Mediator* m_mediator;
};

// 具体类-租客
class Tenant : public Person
{
public:
    // 构造函数
    Tenant(Mediator* mediator) : Person(mediator) {}

    // 发出消息
    virtual void sendMessage(std::string message) {
        m_mediator->sendMessage(message, this);
    }

    // 获取消息
    virtual void getMessage(std::string message) {
        std::cout << "租客得到消息：" << message << std::endl;
    }
};

// 具体类-房东
class Landlord : public Person
{
public:
    // 构造函数
    Landlord(Mediator* mediator) : Person(mediator) {}

    // 发出消息
    virtual void sendMessage(std::string message) {
        m_mediator->sendMessage(message, this);
    }

    // 获取消息
    virtual void getMessage(std::string message) {
        std::cout << "房东得到消息：" << message << std::endl;
    }
};

// 具体中介者-房产中介
class RealEstateMediator : public Mediator
{
public:
    // 设置租客
    void setTenant(Person* tenant) {
        m_tenant = tenant;
    }

    // 设置房东
    void setLandlord(Person* landlord) {
        m_landlord = landlord;
    }

    // 发出信息
    virtual void sendMessage(std::string message, Person* colleague) {
        if (colleague == m_tenant) {
            m_landlord->getMessage(message);
        }
        else {
            m_tenant->getMessage(message);
        }
    }

private:
    Person* m_tenant;
    Person* m_landlord;

};
#endif //MEDIATOR_H

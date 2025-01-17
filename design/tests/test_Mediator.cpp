//
// Created by maochaoqun on 2025/1/17.
//
#include "../Mediator.h"
#include <iostream>
//main.cpp
/****************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    // 创建对象
    RealEstateMediator *mediator = new RealEstateMediator();
    Person *tenant = new Tenant(mediator);
    Person *landlord = new Landlord(mediator);

    // 中介设置房东和租客
    mediator->setTenant(tenant);
    mediator->setLandlord(landlord);

    // 进行租房询问
    tenant->sendMessage("房租多少钱？");
    landlord->sendMessage("房租3000元。");

    // 删除
    delete mediator;
    delete tenant;
    delete landlord;
    mediator = nullptr;
    tenant = nullptr;
    landlord = nullptr;

    return 0;
}
//
// Created by pirat on 2024/12/28.
//

#include <iostream>
#include "../FactoryMethod.h"
int main() {
    BinarySplitterFactory binarySplitterFactory;
    TxtSplitterFactory txtSplitterFactory;
    FactoryMethod factoryMethod;
    factoryMethod.setFacory(&binarySplitterFactory);
    //factoryMethod.setFacory(&txtSplitterFactory);
    factoryMethod.test();
    //抽象工厂
    SqlDBFactory sqlDBFactory;
    OracleDBFactory oracleDBFactory;
    EmployeeDAO employeeDAO;
    employeeDAO.setFacory(&oracleDBFactory);
    employeeDAO.test();
    return 0;
}


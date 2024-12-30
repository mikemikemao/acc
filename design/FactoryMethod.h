//
// Created by pirat on 2024/12/28.
//

#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#include <iostream>
#include <vector>

//抽象类
class ISplitter{
public:
    virtual void split()=0;
    virtual ~ISplitter(){}
};

//工厂基类
class SplitterFactory{
public:
    virtual ISplitter* CreateSplitter()=0;
    virtual ~SplitterFactory(){}
};

//具体类
class BinarySplitter : public ISplitter{
    void split() override {
        std::cout << "BinarySplitter" << std::endl;
    }
};

class TxtSplitter: public ISplitter{
    void split() override {
        std::cout << "TxtSplitter" << std::endl;
    }
};

//具体工厂
class BinarySplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new BinarySplitter();
    }
};

class TxtSplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new TxtSplitter();
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////
class FactoryMethod
{
private:
    SplitterFactory*  factory;//工厂
public:
    int setFacory(SplitterFactory*  factory){
        this->factory=factory;
        return 0;
    }
    void test(){
        ISplitter * splitter=factory->CreateSplitter(); //多态new
        splitter->split();
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////
///抽象工厂
/////数据库访问有关的基类
class IDBConnection {
public:
    virtual void ConnectionString()=0;
};

class IDBCommand {
public:
    virtual void SetConnection(IDBConnection * splitter)=0;
};

class IDataReader {
public:
    virtual void DataReader()=0;
};


class IDBFactory {
public:
    virtual IDBConnection *CreateDBConnection() =0;

    virtual IDBCommand *CreateDBCommand() =0;

    virtual IDataReader *CreateDataReader() =0;
};


//支持SQL Server
class SqlConnection : public IDBConnection {
    virtual void ConnectionString() override {
        std::cout << "SqlConnection" << std::endl;
    }
};

class SqlCommand : public IDBCommand {
    virtual void SetConnection(IDBConnection * splitter) override {
        std::cout << "SqlCommand" << std::endl;
    }
};

class SqlDataReader : public IDataReader {
    virtual void DataReader() override {
        std::cout << "SqlDataReader" << std::endl;
    }
};


class SqlDBFactory:public IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection() override {
        return new SqlConnection();
    }
    virtual IDBCommand* CreateDBCommand() override {
        return new SqlCommand();
    }
    virtual IDataReader* CreateDataReader() override {
        return new SqlDataReader();
    }

};


//支持Oracle
class OracleConnection: public IDBConnection{
    virtual void ConnectionString() override {
        std::cout << "OracleConnection" << std::endl;
    }
};

class OracleCommand: public IDBCommand{
    virtual void SetConnection(IDBConnection * splitter) override {
        std::cout << "OracleCommand" << std::endl;
    }
};

class OracleDataReader: public IDataReader{
    virtual void DataReader() override {
        std::cout << "OracleDataReader" << std::endl;
    }
};

class OracleDBFactory:public IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection() override {
        return new OracleConnection();
    }
    virtual IDBCommand* CreateDBCommand() override {
        return new OracleCommand();
    }
    virtual IDataReader* CreateDataReader() override {
        return new OracleDataReader();
    }

};

class EmployeeDAO{
    IDBFactory* dbFactory;

public:
    int setFacory(IDBFactory*  factory){
        this->dbFactory=factory;
        return 0;
    }
    void test(){
        IDBConnection * splitter= dbFactory->CreateDBConnection(); //多态new
        splitter->ConnectionString();
        IDBCommand* command = dbFactory->CreateDBCommand();//强调关联性 即同一个Factory下各个对象的关联性操作
        command->SetConnection(splitter);
    }
};

#endif //FACTORYMETHOD_H

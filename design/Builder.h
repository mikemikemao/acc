//
// Created by maochaoqun on 2024/12/31.
//

#ifndef BUILDER_H
#define BUILDER_H
#include <iostream>
#include <string>
using namespace std;

class Player;

class playBuilder
{
public:
    string Name;
    int ID;
    int HP;
    int Level;
public:
    playBuilder() {    //参数默认值
        Name = "xiaoming";
        ID = 1001;
        HP = 100;
        Level = 1;
        cout<<"默认构造函数"<<endl;
    }
    playBuilder* SetName(string Name) {this->Name = Name;return this;}
    playBuilder* SetID(int ID) {this->ID = ID;return this;}
    playBuilder* SetHP(int HP) {this->HP = HP;return this;}
    playBuilder* SetLevel(int Level) {this->Level = Level;return this;}
    Player *build();
};

class Player {
public:
    string Name;
    int ID;
    int HP;
    int Level;
public:
    string GetName() {return Name;}
    int GetID() {return ID;}
    int GetHP() {return HP;}
    int GetLevel() {return Level;}

    Player() {cout<<"默认构造函数"<<endl;}
    Player (playBuilder const &temp) {
        this->Name = temp.Name;
        this->ID = temp.ID;
        this->HP = temp.HP;
        this->Level = temp.Level;
    }
    ~Player() {}
    void show() {
        cout<<Name<<"-"<<ID<<"-"<<HP<<"-"<<Level<<endl;
    }
};

Player *playBuilder::build(){
    return new Player(*this);
}

class Director {
public:
    playBuilder *builder;
    Director() {
        builder = new playBuilder();
    }
    Player * construct(string Name,int ID,int HP,int Level) {   //构造规则
        builder = builder->SetName(Name);
        builder = builder->SetID(ID);
        builder = builder->SetHP(HP);
        builder = builder->SetLevel(Level);
        return builder->build();
    }
    ~ Director() {
        delete builder;
    }
};

#endif //BUILDER_H

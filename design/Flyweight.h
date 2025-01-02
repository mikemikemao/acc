//
// Created by maochaoqun on 2025/1/2.
//

#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <iostream>
#include <list>
#include <map>

using namespace std;

enum EnumColor  //棋子颜色
{
    Black,  //黑
    White   //白
};

struct Position //棋子位置
{
    int m_x;
    int m_y;
    Position(int tmpx, int tmpy) :m_x(tmpx), m_y(tmpy) {} //构造函数
};

class Piece //棋子抽象类
{
public:
    virtual ~Piece() {} //做父类时析构函数应该为虚函数

public:
    virtual void draw(Position tmppos) = 0;
};

class BlackPiece : public Piece //黑色棋子
{
public:
    virtual void draw(Position tmppos)
    {
        cout << "在位置：(" << tmppos.m_x << "," << tmppos.m_y << ")处绘制了一个黑色棋子！" << endl;
    }
};
class WhitePiece : public Piece //白色棋子
{
public:
    virtual void draw(Position tmppos)
    {
        cout << "在位置：(" << tmppos.m_x << "," << tmppos.m_y << ")处绘制了一个白色棋子！" << endl;
    }
};

class pieceFactory  //创建棋子的工厂
{
public:
    ~pieceFactory() //析构函数
    {
        //释放内存
        for (auto iter = m_FlyWeihgtMap.begin(); iter != m_FlyWeihgtMap.end(); ++iter)
        {
            Piece* tmpfw = iter->second;
            delete tmpfw;
        }
        m_FlyWeihgtMap.clear();//这句其实可有可无
    }
public:
    Piece* getFlyWeight(EnumColor tmpcolor) //获取享元对象，也就是获取被共享的棋子对象
    {
        auto iter = m_FlyWeihgtMap.find(tmpcolor);
        if (iter == m_FlyWeihgtMap.end())
        {
            //没有该享元对象，那么就创建出来
            Piece* tmpfw = nullptr;
            if (tmpcolor == Black) //黑子
            {
                tmpfw = new BlackPiece();
            }
            else //白子
            {
                tmpfw = new WhitePiece();
            }
            m_FlyWeihgtMap.insert(make_pair(tmpcolor, tmpfw));//以棋子颜色枚举值为key，增加条目到map中
            return tmpfw;
        }
        else
        {
            return iter->second;
        }
    }
private:
    //在文件头增加#include <map>
    std::map<EnumColor, Piece*> m_FlyWeihgtMap; //用map容器来保存所有的享元对象，一共就两个享元对象（黑色棋子一个，白色棋子一个）
};

#endif
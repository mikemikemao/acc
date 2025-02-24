//
// Created by maochaoqun on 2025/2/24.
//
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

enum EnumColor  //棋子颜色
{
    Black,  //黑
    White   //白
};

struct Position //棋子位置
{
    int m_color;
    int m_x;
    int m_y;
    Position(){}
    Position(int color,int tmpx, int tmpy) :m_color(color),m_x(tmpx), m_y(tmpy) {} //构造函数
    void toString() {
        cout << m_color << " " << m_x << " " << m_y << endl;
    }
};

int isExt(vector<Position>& weiqi,int x, int y) {
    for(auto tmp : weiqi) {
        if(x == tmp.m_x && y == tmp.m_y) {
            return 1;
        }
    }
    return 0;
}
int getOneQi(vector<Position>& weiqi,set<int>& repeat,int x, int y) {
    if(isExt(weiqi,x,y) == 0) {
        int key =x*10+y;
        if(repeat.find(key) != repeat.end()) {
            return  0;
        }else {
            repeat.insert(key);
            return 1;
        }
    }
    return 0;
}


int getQi(vector<Position>& weiqi,set<int>& repeat,Position position) {
    int sumqi = 0;
    int pox = position.m_x;
    int poy = position.m_y;
    int pox0 = (pox -1) < 0 ? 0 : (pox -1);
    int pox1 = pox+1;
    int poy0 = (poy -1) < 0 ? 0 : (poy -1);
    int poy1 = poy+1;
    int qi = getOneQi(weiqi,repeat,pox0, poy);
    sumqi += qi;
    qi = getOneQi(weiqi,repeat,pox1, poy);
    sumqi += qi;
    qi = getOneQi(weiqi,repeat,pox, poy0);
    sumqi += qi;
    qi = getOneQi(weiqi,repeat,pox, poy1);
    sumqi += qi;
    position.toString();
    cout << sumqi << endl;
    return sumqi;
}

int main() {
    int pox = 0;
    int poy = 0;
    int num = 0;
    string str;
    vector<Position> weiqi;
    string strtmp;
    vector<Position> vecPos;
    set<int> repeatblack;
    set<int> repeatwhite;
    int times = 0;
    //黑
    getline(cin,str);
    cout << str << endl;
    istringstream ss(str);
    while (ss >> strtmp)
    {
        int temp = atoi(strtmp.c_str());
        if(times == 0) {
            pox = temp;
            times++;
        }else {
            poy = temp;
            times = 0;
            cout << pox << " " << poy << endl;
            Position blackPosition(0,pox,poy);
            weiqi.push_back(blackPosition);
            num++;
        }
    }
    //白
    times = 0;
    getline(cin,str);
    istringstream ss1(str);
    while (getline(ss1,strtmp,' '))
    {
        int temp = atoi(strtmp.c_str());
        if(times == 0) {
            pox = temp;
            times++;
        }else {
            poy = temp;
            times = 0;
            Position whitePosition(1,pox,poy);
            weiqi.push_back(whitePosition);
            num++;
        }
    }
    weiqi.resize(num);
    for(auto tmp : weiqi) {
        tmp.toString();
    }
    int qi = 0;
    int blackqi = 0;
    int whiteqi = 0;
    for(auto tmp : weiqi) {
        if(tmp.m_color == Black) {
            qi = getQi(weiqi,repeatblack,tmp);
            blackqi +=qi;
        }else {
            qi = getQi(weiqi,repeatwhite,tmp);
            whiteqi+=qi;
        }
    }
    cout << blackqi << " " << whiteqi << endl;
    return 0;
};


//
// Created by maochaoqun on 2025/1/2.
//
#include <iostream>
#include "../Flyweight.h"
int main()
{
    pieceFactory* pfactory = new pieceFactory();

    Piece* p_piece1 = pfactory->getFlyWeight(Black);
    p_piece1->draw(Position(3, 3));//黑子落子到3,3位置
    cout << "p_piece1" << (void*)p_piece1 << endl;

    Piece* p_piece2 = pfactory->getFlyWeight(White);
    p_piece2->draw(Position(5, 5));//白子落子到5,5位置

    Piece* p_piece3 = pfactory->getFlyWeight(Black);
    p_piece3->draw(Position(4, 6));//黑子落子到4,6位置
    cout << "p_piece3" << (void*)p_piece3 << endl;

    Piece* p_piece4 = pfactory->getFlyWeight(White);
    p_piece4->draw(Position(5, 7));//白子落子到5,7位置

    //释放资源
    delete pfactory;

    return 0;
}

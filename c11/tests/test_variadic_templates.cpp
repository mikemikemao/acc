//
// Created by pirate on 2025/2/6.
//
#include <bitset>
#include <iostream>
using namespace std;
void print()
{
    cout << "print is null" << endl;
}
/***
 * ...就是所谓的pack
 */
template <typename T,typename ... Types>
void print(const T & firstArg,const Types&... args)
{
    cout << firstArg << endl;
    cout << sizeof...(args) << endl;//计算包的个数
    print(args...);
}
//const 是函数签名的组成部分 返回值不算
int main()
{
    print(7.5,"hello",bitset<16>(377),43);
    return 0;
}

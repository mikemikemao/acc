//
// Created by maochaoqun on 2025/1/15.
//

#ifndef ADAPTER_H
#define ADAPTER_H
#include <iostream>
#include <stdlib.h>
using namespace std;

class Target
{
public:
    virtual void translate(string source, string target, string words) = 0;
};

class Translator
{
public:
    void translateInZh(string words)
    {
        if (words == "hello world!")
            cout << "你好世界！" << endl;
    }
    void translateInEn(string words)
    {
        if (words == "你好世界！")
            cout << "Translate in English: \"hello world!\"" << endl;
    }
};
//类适配器 一般不用
class ClassAdapter : public Target, public Translator
{
public:
    virtual void translate(string source, string target, string words)
    {
        if (source == "中文" && target == "英文")
            this->translateInEn(words);
        else
            this->translateInZh(words);
    }
};
//对象适配器
class ObjectAdapter : public Target
{
private:
    Translator *m_pTranslator;

public:
    ObjectAdapter(Translator *trans) : m_pTranslator(trans){};
    virtual ~ObjectAdapter()
    {
        delete m_pTranslator;
    }

    virtual void translate(string source, string target, string words)
    {
        if (source == "中文" && target == "英文")
            m_pTranslator->translateInEn(words);
        else
            m_pTranslator->translateInZh(words);
    }
};

#endif //ADAPTER_H

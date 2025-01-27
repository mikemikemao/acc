//
// Created by pirat on 2025/1/27.
//

#ifndef INTERATOR_H
#define INTERATOR_H
template<class T>
class myIter{
public:
    virtual void First() = 0;
    virtual void Next() = 0;//指向下一个元素
    virtual bool IsDone() = 0;//是否遍历完
    virtual T& CurrentItem() = 0;//获取当前的元素
    virtual ~myIter() {}//作父类时析构函数应该为虚函数
};

template<class T>
class myContainer{
public:
    virtual myIter<T>* CreateIterator() = 0;//创建选代器
    virtual T& getItem(int index) = 0;//获取当前元素
    virtual int getSize() = 0;//容器中元素数量
    virtual ~myContainer() {}//作父类时析构函数应该为虚函数
};
template<class T>
class myVectorIter :public myIter<T>
{
public:
    myVectorIter(myContainer<T>*tmpc) :myvector(tmpc)
    {
        m_current = 0;
    }
    virtual void First()
    {
        m_current = 0;//容器(数组)中的第一个元素下标为0
    }
    virtual void Next()
    {
        m_current++;//下标+1，意味着数组中的下一个元素
    }
    virtual bool IsDone()
    {
        if (m_current >= myvector->getSize())
            return true;
        return false;
    }
    virtual T& CurrentItem()
    {
        return myvector->getItem(m_current);
    }
private:
    myContainer<T>* myvector;
    int m_current;//记录数组的当前下标(选代器在当前容器中的位置)
};

//具体容器类模板
template<typename T>
class myVector :public myContainer<T>{
public:
    myVector()//将数组中元素进行初始化
    {
        for (int i = 0; i < 10; ++i)
            m_elem[i] = i;
    }
    virtual myIter<T>* CreateIterator()
    {
        return new myVectorIter<T>(this);//要考虑在哪里释放的问题
    }
    virtual T& getItem(int index)
    {
        return m_elem[index];
    }
    virtual int getSize()
    {
        return 10;//为简化代码，返回固定数字
    }
private:
    //为了简化代码，将容器实现为固定装人10个元素的数组
    T m_elem[10];
};


#endif //INTERATOR_H

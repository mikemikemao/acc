//
// Created by maochaoqun on 2025/2/25.
//

#ifndef VERTEXITERATOR_H
#define VERTEXITERATOR_H

using namespace std;

template<class T>
class vertexIterator
{
public:
    virtual ~vertexIterator() {}
    virtual int next() = 0;
    virtual int next(T&) = 0;
};

#endif //VERTEXITERATOR_H

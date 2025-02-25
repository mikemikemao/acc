//
// Created by maochaoqun on 2025/2/25.
//

#ifndef EDGE_H
#define EDGE_H
template<class T>
class Edge{
public:
    virtual ~Edge() {};
    virtual int vertex1() const = 0;
    virtual int vertex2() const = 0;
    virtual T weight() const = 0;
};

#endif //EDGE_H

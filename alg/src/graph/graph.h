//
// Created by maochaoqun on 2025/2/25.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "edge.h"
#include "vertexIterator.h"
template<class T>
class Graph
{
public:
    virtual ~Graph() {}
    virtual int numberOfVertices() const = 0;
    virtual int numberOfEdges() const = 0;
    virtual bool existsEdge(int, int) const = 0;
    virtual void insertEdge(Edge<T>*) = 0;
    virtual void eraseEdge(int, int) = 0;
    virtual int degree(int) const = 0;
    virtual int inDegree(int) const = 0;
    virtual int outDegree(int) const = 0;
    virtual bool directed() const = 0;
    virtual bool weighted() const = 0;
    virtual vertexIterator<T>* iterator(int) = 0;
};
#endif //GRAPH_H

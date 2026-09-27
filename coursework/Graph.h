#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vector.h"
#include "Queue.h"
#include <iostream>
#include <stdexcept>

class Graph {
private:
    // Список смежности: для каждой вершины храним Vector её соседей
    Vector<Vector<int>> adj_;
    int vertices_;

    Vector<int> dist_;      // расстояния от стартовой вершины
    Vector<int> parent_;    // родители в дереве BFS
    Vector<bool> visited_;  // посещённые вершины
    Vector<int> order_;     // порядок обхода вершин

    void resetArrays();
    void findDiameterPath(int start, Vector<int>& outPath, int& outDiameter);

public:
    Graph();
    Graph(int n);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph() = default;

    // Основные методы
    bool isEmpty() const;
    bool hasVertex(int v) const;
    bool hasEdge(int u, int v) const;
    void addVertex();
    void removeVertex(int v);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    int getVertexCount() const;
    void print() const;

    // 1. Обход в ширину
    void bfs(int start);
    void printBFSTree(int start);

    // 2. Кратчайший путь
    void printShortestPath(int start, int target);
    int getDistance(int v) const;

    // 3. Диаметр дерева
    int getDiameter(int start);
    void printDiameterPath(int start);
};

#endif


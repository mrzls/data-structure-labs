#include "Graph.h"
#include <utility>

// Константы ошибок
const char* const ERR_INVALID_VERTEX = "Ошибка: Неверный индекс вершины!";
const char* const ERR_EMPTY_GRAPH = "Ошибка: Граф пуст!";
const char* const ERR_SELF_LOOP = "Ошибка: Петли запрещены!";
const char* const ERR_NEGATIVE_VERTICES = "Ошибка: Количество вершин должно быть целым неотрицательным числом";
const char* const ERR_EDGE_EXISTS = "Ошибка: Ребро уже существует!";

// Вспомогательные методы
void Graph::resetArrays() {
    for (int i = 0; i < vertices_; i++) {
        dist_[i] = -1;
        parent_[i] = -1;
        visited_[i] = false;
    }
    order_.clear();
}

// Приватный метод поиска диаметра дерева
void Graph::findDiameterPath(int start, Vector<int>& outPath, int& outDiameter) {
    bfs(start);
    Vector<int> treeParent = parent_;

    int end1 = start;
    for (int i = 0; i < vertices_; i++)
        if (dist_[i] > dist_[end1]) end1 = i;

    Vector<int> dist2(vertices_, -1);
    Vector<int> parent2(vertices_, -1);
    Queue<int> q;
    dist2[end1] = 0;
    q.push(end1);

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (size_t i = 0; i < adj_[curr].size(); i++) {
            int neighbor = adj_[curr][i];
            if ((treeParent[neighbor] == curr || treeParent[curr] == neighbor) && dist2[neighbor] == -1) {
                dist2[neighbor] = dist2[curr] + 1;
                parent2[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }
   
    int end2 = end1;
    outDiameter = 0;
    for (int i = 0; i < vertices_; i++) {
        if (dist2[i] > outDiameter) {
            outDiameter = dist2[i];
            end2 = i;
        }
    }

    outPath.clear();
    for (int cur = end2; cur != -1; cur = parent2[cur])
        outPath.push_back(cur);
}
// Конструкторы и деструктор

Graph::Graph() : vertices_(0) {}

Graph::Graph(int n) {
    if (n < 0) {
        throw std::invalid_argument(ERR_NEGATIVE_VERTICES);
    }

    vertices_ = n;
    adj_ = Vector<Vector<int>>();

    for (int i = 0; i < n; i++) {
        adj_.push_back(Vector<int>());
    }

    dist_ = Vector<int>(n, -1);
    parent_ = Vector<int>(n, -1);
    visited_ = Vector<bool>(n, false);
    order_ = Vector<int>();
}

Graph::Graph(const Graph& other) {
    vertices_ = other.vertices_;
    adj_ = Vector<Vector<int>>();

    for (int i = 0; i < vertices_; i++) {
        adj_.push_back(Vector<int>());
    }

    dist_ = Vector<int>(vertices_, -1);
    parent_ = Vector<int>(vertices_, -1);
    visited_ = Vector<bool>(vertices_, false);
    order_ = Vector<int>();

    for (int i = 0; i < vertices_; i++) {
        adj_[i] = other.adj_[i];
        dist_[i] = other.dist_[i];
        parent_[i] = other.parent_[i];
        visited_[i] = other.visited_[i];
    }
    order_ = other.order_;
}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        Graph temp(other);
        adj_.swap(temp.adj_);
        std::swap(vertices_, temp.vertices_);
        dist_.swap(temp.dist_);
        parent_.swap(temp.parent_);
        visited_.swap(temp.visited_);
        order_.swap(temp.order_);
    }
    return *this;
}

bool Graph::isEmpty() const {
    return vertices_ == 0;
}

bool Graph::hasVertex(int v) const {
    return v >= 0 && v < vertices_;
}

bool Graph::hasEdge(int u, int v) const {
    if (!hasVertex(u) || !hasVertex(v)) return false;

    for (size_t i = 0; i < adj_[u].size(); i++) {
        if (adj_[u][i] == v) return true;
    }
    return false;
}

void Graph::addVertex() {
    adj_.push_back(Vector<int>());
    dist_.push_back(-1);
    parent_.push_back(-1);
    visited_.push_back(false);
    vertices_++;
}

void Graph::removeVertex(int v) {
    if (!hasVertex(v)) {
        throw std::out_of_range(ERR_INVALID_VERTEX);
    }

    int oldVertices = vertices_;

    // Удаляем все рёбра, связанные с v
    for (int i = 0; i < oldVertices; i++) {
        if (i != v) removeEdge(i, v);
    }

    // Перестраиваем список смежности
    Vector<Vector<int>> newAdj;

    for (int i = 0; i < oldVertices; i++) {
        if (i == v) continue;

        Vector<int> newNeighbors;
        for (size_t j = 0; j < adj_[i].size(); j++) {
            int neighbor = adj_[i][j];
            if (neighbor == v) continue;

            int newNeighbor = neighbor;
            if (neighbor > v) newNeighbor--;
            newNeighbors.push_back(newNeighbor);
        }
        newAdj.push_back(newNeighbors);
    }

    adj_ = newAdj;
    vertices_--;

    // Перестраиваем массивы BFS
    Vector<int> newDist;
    Vector<int> newParent;
    Vector<bool> newVisited;

    for (int i = 0; i < oldVertices; i++) {
        if (i == v) continue;
        newDist.push_back(dist_[i]);
        newParent.push_back(parent_[i]);
        newVisited.push_back(visited_[i]);
    }

    dist_ = newDist;
    parent_ = newParent;
    visited_ = newVisited;
    order_.clear();
}

void Graph::addEdge(int u, int v) {
    if (!hasVertex(u) || !hasVertex(v)) {
        throw std::out_of_range(ERR_INVALID_VERTEX);
    }
    if (u == v) {
        throw std::invalid_argument(ERR_SELF_LOOP);
    }
    if (hasEdge(u, v)) {
        throw std::invalid_argument(ERR_EDGE_EXISTS);
    }

    adj_[u].push_back(v);
    adj_[v].push_back(u);
}

void Graph::removeEdge(int u, int v) {
    if (!hasVertex(u) || !hasVertex(v)) return;

    // Удаляем v из списка u
    Vector<int> newU;
    for (size_t i = 0; i < adj_[u].size(); i++) {
        if (adj_[u][i] != v) {
            newU.push_back(adj_[u][i]);
        }
    }
    adj_[u] = newU;

    // Удаляем u из списка v
    Vector<int> newV;
    for (size_t i = 0; i < adj_[v].size(); i++) {
        if (adj_[v][i] != u) {
            newV.push_back(adj_[v][i]);
        }
    }
    adj_[v] = newV;
}

int Graph::getVertexCount() const {
    return vertices_;
}

void Graph::print() const {
    if (isEmpty()) {
        std::cout << "Граф пуст\n";
        return;
    }

    std::cout << "Граф (" << vertices_ << " вершин):\n";
    for (int i = 0; i < vertices_; i++) {
        std::cout << "  " << i << ": ";
        for (size_t j = 0; j < adj_[i].size(); j++) {
            std::cout << adj_[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// 1. Обход в ширину

void Graph::bfs(int start) {
    if (!hasVertex(start)) {
        throw std::out_of_range(ERR_INVALID_VERTEX);
    }
    if (isEmpty()) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    resetArrays();

    Queue<int> q;
    dist_[start] = 0;
    visited_[start] = true;
    q.push(start);
    order_.push_back(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < adj_[current].size(); i++) {
            int neighbor = adj_[current][i];
            if (!visited_[neighbor]) {
                visited_[neighbor] = true;
                dist_[neighbor] = dist_[current] + 1;
                parent_[neighbor] = current;
                q.push(neighbor);
                order_.push_back(neighbor);
            }
        }
    }
}

void Graph::printBFSTree(int start) {
    std::cout << "\n\t Дерево BFS от вершины " << start << "\n";

    if (isEmpty()) {
        std::cout << "Граф пуст\n\n";
        return;
    }

    bfs(start);

    for (int i = 0; i < vertices_; i++) {
        if (i == start) {
            std::cout << "  Вершина " << i << " (корень)\n";
        }
        else if (parent_[i] != -1) {
            std::cout << "  Вершина " << i << " <- родитель " << parent_[i]
                << " (расстояние " << dist_[i] << ")\n";
        }
        else if (dist_[i] == -1) {
            std::cout << "  Вершина " << i << " (недостижима)\n";
        }
    }

    std::cout << "\nПорядок обхода: ";
    for (size_t i = 0; i < order_.size(); i++) {
        std::cout << order_[i];
        if (i < order_.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}

// 2. Кратчайший путь

void Graph::printShortestPath(int start, int target) {

    if (!hasVertex(start)) throw std::out_of_range(ERR_INVALID_VERTEX);
    if (!hasVertex(target)) throw std::out_of_range(ERR_INVALID_VERTEX);

    bfs(start);

    if (dist_[target] == -1) {
        std::cout << "Нет пути от " << start << " до " << target << "\n";
        return;
    }

    Vector<int> path;
    int current = target;

    while (current != -1) {
        path.push_back(current);
        current = parent_[current];
    }

    std::cout << "Путь от " << start << " до " << target << ": ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i > 0) std::cout << " -> ";
    }
    std::cout << " (длина: " << dist_[target] << ")\n";
}

int Graph::getDistance(int v) const {
    if (!hasVertex(v)) {
        throw std::out_of_range(ERR_INVALID_VERTEX);
    }
    return dist_[v];
}

// 3. Диаметр дерева

int Graph::getDiameter(int start) {
    if (isEmpty()) throw std::logic_error(ERR_EMPTY_GRAPH);
    if (!hasVertex(start)) throw std::out_of_range(ERR_INVALID_VERTEX);

    Vector<int> path;
    int diameter = 0;
    findDiameterPath(start, path, diameter);
    return diameter;
}

void Graph::printDiameterPath(int start) {
    if (isEmpty()) throw std::logic_error(ERR_EMPTY_GRAPH);
    if (!hasVertex(start)) throw std::out_of_range(ERR_INVALID_VERTEX);

    Vector<int> path;
    int diameter = 0;
    findDiameterPath(start, path, diameter);

    std::cout << "\nДиаметр BFS-дерева: " << diameter << "\nПуть: ";
    for (int i = path.size() - 1; i >= 0; i--)
        std::cout << path[i] << (i > 0 ? " -> " : "");
    std::cout << "\n";
}
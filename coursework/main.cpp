#include "Graph.h"
#include <iostream>
#include <limits>
#include <cassert>
#include <sstream>

using namespace std;

// Константы ошибок
const char* const ERR_INVALID_CHOICE = "Ошибка: Некорректный ввод! Введите число от 1 до 3";
const char* const ERR_INVALID_CHOICE_2 = "Ошибка: Некорректный ввод! Введите число от 1 до 9";
const char* const ERR_INVALID_INPUT = "Ошибка: Некорректный ввод! Введите целое неотрицательное число";
const char* const ERR_OUT_OF_RANGE = "Ошибка: Некорректный ввод! Введите число из диапазона: ";
const char* const ERR_EMPTY_GRAPH = "Ошибка: Граф пуст!";
const char* const ERR_SELF_LOOP = "Ошибка: Петли запрещены!";
const char* const ERR_NO_PATH = "Ошибка: Путь не существует!";
const char* const ERR_NEGATIVE_VERTICES = "Ошибка: Количество вершин должно быть целым неотрицательным числом!";
const char* const ERR_INVALID_EDGES = "Ошибка: Количество рёбер должно быть целым неотрицательным числом, не превышающим ";
const char* const ERR_EDGE_EXISTS = "Ошибка: Ребро уже существует!";

// Объявление функций
int safeInputInt(const string& prompt, int minVal, int maxVal);
int safeInputVertex(const string& prompt, int minVal, int maxVal);
void printMenu();

// Тесты
void testAll();
void testConstructors();
void testIsEmpty();
void testHasVertex();
void testHasEdge();
void testAddVertex();
void testRemoveVertex();
void testAddEdge();
void testRemoveEdge();
void testBFS();
void testShortestPaths();
void testDiameter();
void testExceptions();

// Ручной режим
void manualMode();
void addVertexMode(Graph& g, int& n);
void addEdgeMode(Graph& g, int n);
void removeVertexMode(Graph& g, int& n);
void removeEdgeMode(Graph& g, int n);
void bfsMode(Graph& g, int n);
void shortestPathMode(Graph& g, int n);
void diameterMode(Graph& g, int n);

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Курсовая работа\n";
    cout << "Вариант 2.2\n";
    cout << "Обход в ширину неориентированного графа\n";
    
    while (true) {
        cout << "\nГЛАВНОЕ МЕНЮ\n";
        cout << "1 - Ручное тестирование\n";
        cout << "2 - Автоматические тесты\n";
        cout << "3 - Выход\n";

        int choice;
        try {
            choice = safeInputInt("Выбор: ", 1, 3);
        }
        catch (const exception& e) {
            cerr << ERR_INVALID_CHOICE << "\n";
            continue;
        }

        switch (choice) {
        case 1:
            manualMode();
            break;
        case 2:
            testAll();
            break;
        case 3:
            cout << "Тестирование завершено\n";
            return EXIT_SUCCESS;
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}

// Вспомогательные функции
int safeInputInt(const string& prompt, int minVal, int maxVal) {
    string input;
    int value;

    cout << prompt;
    getline(cin, input);

    if (input.empty()) {
        throw invalid_argument(ERR_INVALID_INPUT);
    }

    size_t start = 0;
    if (input[0] == '-') {
        start = 1;
        if (input.length() == 1) {
            throw invalid_argument(ERR_INVALID_INPUT);
        }
    }

    for (size_t i = start; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            throw invalid_argument(ERR_INVALID_INPUT);
        }
    }

    value = stoi(input);

    if (value < minVal || value > maxVal) {
        throw out_of_range(ERR_OUT_OF_RANGE + to_string(minVal) + " - " + to_string(maxVal) );
    }

    return value;
}

int safeInputVertex(const string& prompt, int minVal, int maxVal) {
    return safeInputInt(prompt, minVal, maxVal);
}

void printMenu() {
    cout << "\nОПЕРАЦИИ\n";
    cout << "1 - Добавить вершину\n";
    cout << "2 - Добавить ребро\n";
    cout << "3 - Удалить вершину\n";
    cout << "4 - Удалить ребро\n";
    cout << "5 - Обход в ширину (BFS)\n";
    cout << "6 - Кратчайший путь\n";
    cout << "7 - Диаметр BFS-дерева\n";
    cout << "8 - Показать граф\n";
    cout << "9 - Назад\n";
}

// Ручное тестирование
void manualMode() {
    cout << "\n=== РУЧНОЙ РЕЖИМ ===\n";

    int n;
    try {
        n = safeInputInt("Введите количество вершин: ", 0, 1000);
    }
    catch (...) {
        cerr << ERR_NEGATIVE_VERTICES << "\n";
        return;
    }

    Graph g(n);

    if (n > 0) {
        cout << "\nГраф создан с вершинами 0.." << n - 1 << "\n";
        g.print();

        int maxPossibleEdges = n * (n - 1) / 2;
        int m;
        try {
            m = safeInputInt("Введите количество рёбер: ", 0, maxPossibleEdges);
        }
        catch (...) {
            cerr << ERR_INVALID_EDGES << maxPossibleEdges << "\n";
            return;
        }

        for (int i = 0; i < m; i++) {
            cout << "Ребро " << i + 1 << ":\n";

            int u, v;
            try {
                u = safeInputVertex("  u: ", 0, n - 1);
                v = safeInputVertex("  v: ", 0, n - 1);
            }
            catch (const exception& e) {
                cerr << e.what() << "\n";
                i--;
                continue;
            }

            if (u == v) {
                cerr << ERR_SELF_LOOP << "\n";
                i--;
                continue;
            }
            if (g.hasEdge(u, v)) {
                cerr << ERR_EDGE_EXISTS << "\n";
                i--;
                continue;
            }
            g.addEdge(u, v);
            cout << "Добавлено\n";
        }
    }
    else {
        cout << "\nСоздан пустой граф\n";
        g.print();
    }
    while (true) {
        printMenu();

        int choice;
        try {
            choice = safeInputInt("Выбор: ", 1, 9);
        }
        catch (const exception& e) {
            cerr << ERR_INVALID_CHOICE_2 << "\n";
            continue;
        }
        try {
            switch (choice) {
            case 1:
                addVertexMode(g, n);
                break;
            case 2:
                addEdgeMode(g, n);
                break;
            case 3:
                removeVertexMode(g, n);
                break;
            case 4:
                removeEdgeMode(g, n);
                break;
            case 5:
                bfsMode(g, n);
                break;
            case 6:
                shortestPathMode(g, n);
                break;
            case 7:
                diameterMode(g, n);
                break;
            case 8:
                g.print();
                break;
            case 9:
                return;
            default:
                break;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << "\n";
        }
    }
}

void addVertexMode(Graph& g, int& n) {
    g.addVertex();
    n++;
    cout << "Вершина " << n - 1 << " добавлена. Теперь вершин: " << n << "\n";
    g.print();
}

void addEdgeMode(Graph& g, int n) {
    if (n == 0) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    int u, v;
    u = safeInputVertex("u (0.." + to_string(n - 1) + "): ", 0, n - 1);
    v = safeInputVertex("v (0.." + to_string(n - 1) + "): ", 0, n - 1);

    if (u == v) {
        throw std::logic_error(ERR_SELF_LOOP);
    }
    if (g.hasEdge(u, v)) {
        throw std::logic_error(ERR_EDGE_EXISTS);
    }
    g.addEdge(u, v);
    cout << "Ребро добавлено\n";
    g.print();
}

void removeVertexMode(Graph& g, int& n) {
    if (n == 0) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    int v = safeInputVertex("Вершина для удаления (0.." + to_string(n - 1) + "): ", 0, n - 1);

    g.removeVertex(v);
    n--;
    cout << "Вершина " << v << " удалена. Теперь вершин: " << n << "\n";
    g.print();
}

void removeEdgeMode(Graph& g, int n) {
    if (n == 0) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    int u = safeInputVertex("u (0.." + to_string(n - 1) + "): ", 0, n - 1);
    int v = safeInputVertex("v (0.." + to_string(n - 1) + "): ", 0, n - 1);

    if (!g.hasEdge(u, v)) {
        throw std::logic_error(ERR_NO_PATH);
    }
    g.removeEdge(u, v);
    cout << "Ребро удалено\n";
    g.print();
}

void bfsMode(Graph& g, int n) {
    if (n == 0) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    int start = safeInputVertex("Стартовая вершина (0.." + to_string(n - 1) + "): ", 0, n - 1);

    g.printBFSTree(start); 
}

void shortestPathMode(Graph& g, int n) {
    if (n == 0) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    int start = safeInputVertex("Стартовая вершина (0.." + to_string(n - 1) + "): ", 0, n - 1);
    int target = safeInputVertex("Целевая вершина (0.." + to_string(n - 1) + "): ", 0, n - 1);

    g.printShortestPath(start, target);
}

void diameterMode(Graph& g, int n) {
    if (n == 0) {
        throw std::logic_error(ERR_EMPTY_GRAPH);
    }

    int start = safeInputVertex("Стартовая вершина (0.." + to_string(n - 1) + "): ", 0, n - 1);

    g.printDiameterPath(start);
}

// АВТОТЕСТЫ

void testAll() {
    cout << "\n=== АВТОМАТИЧЕСКИЕ ТЕСТЫ ===\n";
    testConstructors();
    testIsEmpty();
    testHasVertex();
    testHasEdge();
    testAddVertex();
    testRemoveVertex();
    testAddEdge();
    testRemoveEdge();
    testBFS();
    testShortestPaths();
    testDiameter();
    testExceptions();
    cout << "\nВСЕ ТЕСТЫ ПРОЙДЕНЫ!\n";
}

void testConstructors() {
    Graph g1;
    assert(g1.isEmpty());
    assert(g1.getVertexCount() == 0);

    Graph g2(5);
    assert(!g2.isEmpty());
    assert(g2.getVertexCount() == 5);

    Graph g3(g2);
    assert(g3.getVertexCount() == 5);
    cout << "(+) Тест constructors - пройден\n";
}

void testIsEmpty() {
    Graph g1;
    assert(g1.isEmpty());
    Graph g2(3);
    assert(!g2.isEmpty());
    cout << "(+) Тест isEmpty - пройден\n";
}

void testHasVertex() {
    Graph g(5);
    assert(g.hasVertex(0));
    assert(g.hasVertex(4));
    assert(!g.hasVertex(5));
    cout << "(+) Тест hasVertex - пройден\n";
}

void testHasEdge() {
    Graph g(3);
    g.addEdge(0, 1);
    assert(g.hasEdge(0, 1));
    assert(!g.hasEdge(0, 2));
    cout << "(+) Тест hasEdge - пройден\n";
}

void testAddVertex() {
    Graph g(3);
    assert(g.getVertexCount() == 3);
    g.addVertex();
    assert(g.getVertexCount() == 4);
    cout << "(+) Тест addVertex - пройден\n";
}

void testRemoveVertex() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.removeVertex(1);
    assert(g.getVertexCount() == 3);
    cout << "(+) Тест removeVertex - пройден\n";
}

void testAddEdge() {
    Graph g(3);
    g.addEdge(0, 1);
    assert(g.hasEdge(0, 1));
    cout << "(+) Тест addEdge - пройден\n";
}

void testRemoveEdge() {
    Graph g(3);
    g.addEdge(0, 1);
    g.removeEdge(0, 1);
    assert(!g.hasEdge(0, 1));
    cout << "(+) Тест removeEdge - пройден\n";
}

void testBFS() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.bfs(0);
    assert(g.getDistance(0) == 0);
    assert(g.getDistance(1) == 1);
    assert(g.getDistance(2) == 1);
    assert(g.getDistance(3) == 2);
    assert(g.getDistance(4) == 2);
    assert(g.getDistance(5) == 3);
    cout << "(+) Тест BFS - пройден\n";
}

void testShortestPaths() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.bfs(0);
    assert(g.getDistance(5) == 3);
    cout << "(+) Тест shortest paths - пройден\n";
}

void testDiameter() {
    Graph linear(5);
    linear.addEdge(0, 1);
    linear.addEdge(1, 2);
    linear.addEdge(2, 3);
    linear.addEdge(3, 4);
    assert(linear.getDiameter(0) == 4);

    Graph star(5);
    star.addEdge(0, 1);
    star.addEdge(0, 2);
    star.addEdge(0, 3);
    star.addEdge(0, 4);
    assert(star.getDiameter(0) == 2);
    assert(star.getDiameter(1) == 2);

    Graph single(1);
    assert(single.getDiameter(0) == 0);
    cout << "(+) Тест diameter - пройден\n";
}

void testExceptions() {
    Graph g(3);
    bool exception = false;
    try {
        g.addEdge(0, 10);
    }
    catch (const out_of_range& e) {
        exception = true;
        cout << "  Исключение (неверный индекс): " << e.what() << "\n";
    }
    assert(exception);

    exception = false;
    try {
        g.addEdge(0, 0);
    }
    catch (const invalid_argument& e) {
        exception = true;
        cout << "  Исключение (петля): " << e.what() << "\n";
    }
    assert(exception);

    exception = false;
    try {
        Graph g2(-5);
    }
    catch (const invalid_argument& e) {
        exception = true;
        cout << "  Исключение (отрицательные вершины): " << e.what() << "\n";
    }
    assert(exception);

    cout << "(+) Тест exceptions - пройден\n";
}
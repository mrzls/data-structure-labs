#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>

template <typename T>
class BinarySearchTree
{
private:
    struct Node
    {
        T key_;
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        Node* p_ = nullptr;

        Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr)
            : key_(key), left_(left), right_(right), p_(p) {
        }

    };

    Node* root_ = nullptr;

    void clear(Node* node);
    Node* searchNode(const T& key) const; //поиск адреса узла по ключу
    size_t getNumberOfNodes(const Node* node) const; //кол-во узлов
    int getHeight(const Node* node) const; //высота
    void output(std::ostream& out, Node* root) const; //рекурсивный вывод
    void inorderWalk(Node* node) const; //инфиксный обход (рекурсивно)

    // Для варианта 5
    Node* removeLessThan(Node* node, const T& k);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& other) = delete;
    BinarySearchTree(BinarySearchTree<T>&& other) noexcept;
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other) = delete;
    BinarySearchTree<T>& operator=(BinarySearchTree<T>&& other) noexcept;
    virtual ~BinarySearchTree();

    bool searchIterative(const T& key) const; //поиск по ключу
    bool insert(const T& key); //вставка нового элемента
    bool remove(const T& key); //удаление элемента с заданным ключом
    void output(std::ostream& out) const; //вывод дерева
    size_t getNumberOfNodes() const; //определение кол-ва узлов
    int getHeight() const; //высота дерева
    void inorderWalkIterative() const; //инфиксный обход дерева (итеративный)
    void inorderWalk() const; //инфиксный обход (рекурсивный)
    void walkByLevels() const; //обход по уровням

    // Для варианта 5
    void removeLessThan(const T& k);
    
};

#endif


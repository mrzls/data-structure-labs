#ifndef BINARYSEARCHTREE_CPP
#define BINARYSEARCHTREE_CPP
#include "BinarySearchTree.h"
#include <algorithm>
#include <stack>
#include <queue>

//Private Методы

template<typename T>
void BinarySearchTree<T>::clear(Node* node)
{
    if (node == nullptr) return;
    clear(node->left_);
    clear(node->right_);
    delete node;
}

template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::searchNode(const T& key) const
{
    Node* current = root_;
    while (current != nullptr) {
        if (current->key_ == key)
            return current;
        else if (key < current->key_)
            current = current->left_;
        else
            current = current->right_;
    }
    return nullptr;
}

template<typename T>
size_t BinarySearchTree<T>::getNumberOfNodes(const Node* node) const
{
    if (node == nullptr) return 0;
    return (1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_));
}

template<typename T>
int BinarySearchTree<T>::getHeight(const Node* node) const
{
    if (node == nullptr) return -1;
    return (1+ std::max(getHeight(node->left_), getHeight(node->right_)));
}

template<typename T>
void BinarySearchTree<T>::output(std::ostream& out, Node* root) const
{
    if (root == nullptr)
    {
        out << "()";
        return;
    }

    out << "(" << root->key_;

    if (root->left_ != nullptr || root->right_ != nullptr)
    {
        out << " ";
        output(out, root->left_);
        out << " ";
        output(out, root->right_);
    }

    out << ")";
}

template<typename T>
void BinarySearchTree<T>::inorderWalk(Node* node) const
{
    if (node == nullptr) return;
    inorderWalk(node->left_);
    std::cout << node->key_ << " ";
    inorderWalk(node->right_);
}

//Public методы

//Констуркторы и деструктор
template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& other) noexcept : root_(other.root_) { other.root_ = nullptr; }

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& other) noexcept
{
    if (this != &other)
    {
        clear(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() { clear(root_); }

//Поис по ключу
template<typename T>
bool BinarySearchTree<T>::searchIterative(const T& key) const
{
    return searchNode(key) != nullptr;
}

//Вставка по ключу
template<typename T>
bool BinarySearchTree<T>::insert(const T& key)
{

    Node* newNode = new Node(key);

    if (root_ == nullptr)
    {
        root_ = newNode;
        return true;
    }

    Node* current = root_;
    Node* parent = nullptr;

    while (current != nullptr)
    {
        parent = current;

        if (key == current->key_)
        {
            delete newNode;  // ключ уже существует
            return false;
        }
        else if (key < current->key_)
            current = current->left_;
        else
            current = current->right_;
    }

    // Вставляем новый узел
    if (key < parent->key_)
        parent->left_ = newNode;
    else
        parent->right_ = newNode;
    newNode->p_ = parent;
    return true;
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& key)
{
    Node* current = searchNode(key);
    if (current == nullptr) return false;

    Node* parent = current->p_;

    //нет детей
    if (current->left_ == nullptr && current->right_ == nullptr)
    {
        if (parent == nullptr)
            root_ = nullptr;
        else if (parent->left_ == current)
            parent->left_ = nullptr;
        else
            parent->right_ = nullptr;

        delete current;
    }

    // только левый ребенок
    else if (current->right_ == nullptr)
    {
        if (parent == nullptr)
            root_ = current->left_;
        else if (parent->left_ == current)
            parent->left_ = current->left_;
        else
            parent->right_ = current->left_;

        if (current->left_ != nullptr)
            current->left_->p_ = parent;

        delete current;
    }

    // только правый ребенок
    else if (current->left_ == nullptr)
    {
        if (parent == nullptr)
            root_ = current->right_;
        else if (parent->left_ == current)
            parent->left_ = current->right_;
        else
            parent->right_ = current->right_;

        if (current->right_ != nullptr)
            current->right_->p_ = parent;

        delete current;
    }

    //два ребенка
    else
    {
        // Находим преемника (минимальный элемент в правом поддереве)
        Node* successor = current->right_;
        while (successor->left_ != nullptr)
            successor = successor->left_;

        // Сохраняем ключ преемника
        T successorKey = successor->key_;

        // Удаляем преемника
        remove(successorKey);

        // Заменяем ключ текущего узла
        current->key_ = successorKey;
    }

    return true;
}


//вывод
template<typename T>
void BinarySearchTree<T>::output(std::ostream& out) const
{
    output(out, root_);
}

template<typename T>
size_t BinarySearchTree<T>::getNumberOfNodes() const
{
    return getNumberOfNodes(root_);
}

template<typename T>
int BinarySearchTree<T>::getHeight() const
{
    return getHeight(root_);
}

//итеративный обход
template<typename T>
void BinarySearchTree<T>::inorderWalkIterative() const
{
    std::stack<Node*> stack;
    Node* current = root_;

    while (current != nullptr || !stack.empty())
    {
        while (current != nullptr)
        {
            stack.push(current);
            current = current->left_;
        }

        current = stack.top();
        stack.pop();
        std::cout << current->key_ << " ";
        current = current->right_;
    }
}

//рекурсивный обход
template<typename T>
void BinarySearchTree<T>::inorderWalk() const
{
    inorderWalk(root_);
    std::cout << "\n";
}

//обход по уровням
template<typename T>
void BinarySearchTree<T>::walkByLevels() const
{
    if (root_ == nullptr) return;

    std::queue <Node*> queue;
    queue.push(root_);

    while (!queue.empty()) 
    {
        Node* current = queue.front();
        queue.pop();
        std::cout << current->key_ << " ";
        if (current->left_ != nullptr) queue.push(current->left_);
        if (current->right_ != nullptr) queue.push(current->right_);
    
    }
    std::cout << "\n";
}

//Вар 5: удаления всех узлов, значения которых меньше заданного значения k 

template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::removeLessThan(Node* node, const T& k)
{
    if (node == nullptr) return nullptr;

    node->left_ = removeLessThan(node->left_, k);
    node->right_ = removeLessThan(node->right_, k);

    // Если текущий узел нужно удалить
    if (node->key_ < k)
    {
        Node* rightChild = node->right_;
        if (rightChild != nullptr)
            rightChild->p_ = node->p_;
        delete node;
        return rightChild;
    }

    return node;
}

template<typename T>
void BinarySearchTree<T>::removeLessThan(const T& k)
{
    root_ = removeLessThan(root_, k);
}

template class BinarySearchTree<int>;
template class BinarySearchTree<double>;
template class BinarySearchTree<char>;
template class BinarySearchTree<std::string>;

#endif


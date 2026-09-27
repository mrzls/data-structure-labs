#include "SinglyOrderedList.hpp"
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>

const char* const ERR_EMPTY_LIST = "List is empty";
const char* const ERR_DUPLICATE_KEY = "Element with this key already exists";
const char* const ERR_KEY_NOT_FOUND = "Key not found";

template <typename T>
void SinglyOrderedList<T>::swap(SinglyOrderedList& other) noexcept
{
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

// Копирующая вставка
template <typename T>
void SinglyOrderedList<T>::insert(const T& value)
{
    // Проверка на уникальность и поиск места вставки
    Node* current = head_;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->data_ == value) {
            throw std::invalid_argument(ERR_DUPLICATE_KEY);
        }
        if (current->data_ > value) {
            break;  // Нашли место для вставки (перед current)
        }
        prev = current;
        current = current->next_;
    }

    Node* newNode = new Node(value);

    // Вставка в пустой список
    if (head_ == nullptr) {
        head_ = tail_ = newNode;
    }
    // Вставка в начало списка
    else if (prev == nullptr) {
        newNode->next_ = head_;
        head_ = newNode;
    }
    // Вставка в середину или конец
    else {
        newNode->next_ = current;
        prev->next_ = newNode;

        // Если вставили в конец, обновляем tail_
        if (current == nullptr) {
            tail_ = newNode;
        }
    }

    size_++;
}

// Перемещающая вставка
template <typename T>
void SinglyOrderedList<T>::insert(T&& value)
{
    // Проверка на уникальность и поиск места вставки
    Node* current = head_;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->data_ == value) {
            throw std::invalid_argument(ERR_DUPLICATE_KEY);
        }
        if (current->data_ > value) {
            break; 
        }
        prev = current;
        current = current->next_;
    }

    Node* newNode = new Node(std::move(value));

    // Вставка в пустой список
    if (head_ == nullptr) {
        head_ = tail_ = newNode;
    }
    // Вставка в начало списка
    else if (prev == nullptr) { 
        newNode->next_ = head_;
        head_ = newNode;
    }
    // Вставка в середину или конец
    else {
        newNode->next_ = current;
        prev->next_ = newNode;

        // Если вставили в конец, обновляем tail_
        if (current == nullptr) {
            tail_ = newNode;
        }
    }

    size_++;
}

// КОНСТРУКТОРЫ И ДЕСТРУКТОР 

// Конструктор по умолчанию
template <typename T>
SinglyOrderedList<T>::SinglyOrderedList() : head_(nullptr), tail_(nullptr), size_(0) {}

// Конструктор с параметром
template <typename T>
SinglyOrderedList<T>::SinglyOrderedList(const T& value) : SinglyOrderedList() { insert(value); }

// Конструктор копирования
template <typename T>
SinglyOrderedList<T>::SinglyOrderedList(const SinglyOrderedList& other) : SinglyOrderedList()
{
    Node* current = other.head_;
    while (current != nullptr) {
        insert(current->data_);
        current = current->next_;
    }
}

// Конструктор перемещения
template <typename T>
SinglyOrderedList<T>::SinglyOrderedList(SinglyOrderedList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_)
{
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

// Деструктор
template <typename T>
SinglyOrderedList<T>::~SinglyOrderedList() { clear(); }

// Копирующее присваивание
template <typename T>
SinglyOrderedList<T>& SinglyOrderedList<T>::operator=(const SinglyOrderedList& other)
{
    if (this != &other) {
        SinglyOrderedList temp(other);
        swap(temp);
    }
    return *this;
}

// Перемещающее присваивание
template <typename T>
SinglyOrderedList<T>& SinglyOrderedList<T>::operator=(SinglyOrderedList&& other) noexcept
{
    if (this != &other) {
        swap(other);
    }
    return *this;
}

// Получение значения первого элемента
template <typename T>
T SinglyOrderedList<T>::head() const
{
    if (isEmpty()) {
        throw std::out_of_range(ERR_EMPTY_LIST);
    }
    return head_->data_;
}

// Получение значения последнего элемента
template <typename T>
T SinglyOrderedList<T>::tail() const
{
    if (isEmpty()) {
        throw std::out_of_range(ERR_EMPTY_LIST);
    }
    return tail_->data_;
}

// Поиск элемента по ключу
template <typename T>
bool SinglyOrderedList<T>::search(const T& key) const
{
    Node* current = head_;
    while (current && current->data_ < key) {
        current = current->next_;
    }
    return current && current->data_ == key;
}

// Удаление головного узла
template <typename T>
void SinglyOrderedList<T>::removeHead()
{
    if (isEmpty()) {
        throw std::out_of_range(ERR_EMPTY_LIST);
    }

    Node* temp = head_;
    head_ = head_->next_;

    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    delete temp;
    size_--;
}

// Удаление всех элементов
template <typename T>
void SinglyOrderedList<T>::clear()
{
    while (head_) {
        removeHead();
    }
}

// Текущее количество узлов
template <typename T>
size_t SinglyOrderedList<T>::size() const { return size_; }

// Проверка на пустоту
template <typename T>
bool SinglyOrderedList<T>::isEmpty() const { return size_ == 0; }

// Вывод всех элементов списка
template <typename T>
void SinglyOrderedList<T>::print() const
{
    Node* current = head_;
    std::cout << "List (" << size_ << " elements): ";
    while (current != nullptr) {
        std::cout << current->data_ << " ";
        current = current->next_;
    }
    std::cout << "\n";
}


template <typename T>
void SinglyOrderedList<T>::removeKey(const T& key)  // ИЗМЕНЕНО: теперь void
{
    if (isEmpty()) {
        throw std::out_of_range(ERR_EMPTY_LIST);  // ИЗМЕНЕНО: бросает исключение
    }

    if (head_->data_ == key) {
        removeHead();
        return;
    }

    Node* current = head_;

    while (current->next_ != nullptr && current->next_->data_ < key) {
        current = current->next_;
    }

    if (current->next_ == nullptr || current->next_->data_ != key) {
        throw std::invalid_argument(ERR_KEY_NOT_FOUND);
    }

    Node* temp = current->next_;
    current->next_ = temp->next_;

    if (temp == tail_) {
        tail_ = current;
    }

    delete temp;
    size_--;
}

//operator==
template <typename T>
bool SinglyOrderedList<T>::operator==(const SinglyOrderedList& other) const
{
    if (size_ != other.size_)
        return false;

    Node* a = head_;
    Node* b = other.head_;

    while (a != nullptr)
    {
        if (a->data_ != b->data_)
            return false;

        a = a->next_;
        b = b->next_;
    }

    return true;
}

//remove(удалить элементы другого списка)
template <typename T>
void SinglyOrderedList<T>::remove(const SinglyOrderedList& other)
{
    Node* current = other.head_;

    while (current && !isEmpty()) {
        if (search(current->data_)) {
            removeKey(current->data_);
        }
        current = current->next_;
    }
}

//getIntersection - реализация свободной функции
template<typename T>
SinglyOrderedList<T> getIntersection(
    const SinglyOrderedList<T>& a,
    const SinglyOrderedList<T>& b)
{
    SinglyOrderedList<T> result;

    auto nodeA = a.head_;
    auto nodeB = b.head_;

    while (nodeA != nullptr && nodeB != nullptr)
    {
        if (nodeA->data_ == nodeB->data_)
        {
            result.insert(nodeA->data_);
            nodeA = nodeA->next_;
            nodeB = nodeB->next_;
        }
        else if (nodeA->data_ < nodeB->data_)
        {
            nodeA = nodeA->next_;
        }
        else
        {
            nodeB = nodeB->next_;
        }
    }

    return result;
}

// Явная инстанциация шаблонов для конкретных типов
template class SinglyOrderedList<int>;
template class SinglyOrderedList<double>;
template class SinglyOrderedList<std::string>;

// Явная инстанциация для getIntersection
template SinglyOrderedList<int> getIntersection(const SinglyOrderedList<int>&, const SinglyOrderedList<int>&);
template SinglyOrderedList<double> getIntersection(const SinglyOrderedList<double>&, const SinglyOrderedList<double>&);
template SinglyOrderedList<std::string> getIntersection(const SinglyOrderedList<std::string>&, const SinglyOrderedList<std::string>&);
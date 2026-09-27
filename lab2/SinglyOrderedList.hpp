#pragma once
#include <iostream>
#include <utility>

template <typename T>
class SinglyOrderedList
{
private:
    // Приватная структура Node
    struct Node
    {
        T data_;
        Node* next_;

        Node(const T& data, Node* next = nullptr) : data_(data), next_(next) {}
        Node(T&& data, Node* next = nullptr) : data_(std::move(data)), next_(next) {}
    };

    // Приватные поля класса
    Node* head_;
    Node* tail_;
    size_t size_;

    // Вспомогательный приватный метод для обмена
    void swap(SinglyOrderedList& other) noexcept;

public:
    // Конструкторы и деструктор
    SinglyOrderedList();
    explicit SinglyOrderedList(const T& value);
    SinglyOrderedList(const SinglyOrderedList& other);
    SinglyOrderedList(SinglyOrderedList&& other) noexcept;
    ~SinglyOrderedList();

    // Оператор присваивания
    SinglyOrderedList& operator=(const SinglyOrderedList& other);
    SinglyOrderedList& operator=(SinglyOrderedList&& other) noexcept;

    // Доступ к узлам
    T head() const;
    T tail() const;
    bool search(const T& key) const;

    // Вставка узлов с сохранением упорядоченности
    void insert(const T& value);
    void insert(T&& value);

    // Удаление головного узла
    void removeHead();

    // Удаление всех элементов
    void clear();

    // Информация о состоянии
    size_t size() const;
    bool isEmpty() const;
    void print() const;

    // Удаление узла по ключу
    void removeKey(const T& key);

    // Сравнение списков
    bool operator==(const SinglyOrderedList& other) const;

    // Удалить элементы из списка
    void remove(const SinglyOrderedList& other);

    // Дружественная функция для пересечения списков
    template<typename U>
    friend SinglyOrderedList<U> getIntersection(
        const SinglyOrderedList<U>& a,
        const SinglyOrderedList<U>& b
    );
};

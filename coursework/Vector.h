#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template<typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t newCapacity);

public:
    // Конструкторы и деструктор
    Vector();
    Vector(size_t n, const T& value);
    Vector(const Vector& other);
    ~Vector();

    // Операторы
    Vector& operator=(const Vector& other);

    // Дополнительные методы
    void swap(Vector& other) noexcept;
    void clear();

    // Доступ
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Добавление
    void push_back(const T& value);

    // Информация
    size_t size() const;

};

#endif

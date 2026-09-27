#include "Vector.h"

template<typename T>
void Vector<T>::resize(size_t newCapacity) {
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size_; i++) {
        newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_t n, const T& value) : data_(new T[n]), size_(n), capacity_(n) {
    for (size_t i = 0; i < n; i++) {
        data_[i] = value;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ > 0) {
        data_ = new T[other.size_];
        size_ = other.size_;
        capacity_ = other.size_;
        for (size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
    }
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

template<typename T>
void Vector<T>::swap(Vector& other) noexcept {
    T* tempData = data_;
    data_ = other.data_;
    other.data_ = tempData;

    size_t tempSize = size_;
    size_ = other.size_;
    other.size_ = tempSize;

    size_t tempCap = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tempCap;
}

template<typename T>
void Vector<T>::clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data_[index];
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        resize(newCapacity);
    }
    data_[size_] = value;
    size_++;
}

template<typename T>
size_t Vector<T>::size() const {
    return size_;
}

// явные инстанцировани€ дл€ нужных типов
template class Vector<int>;
template class Vector<bool>;
template class Vector<Vector<int>>;
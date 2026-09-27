#pragma once
#include <iostream>
#include <algorithm>
#include <utility>
#include <stdexcept>

template<typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    static constexpr const char* ERROR_INDEX_OUT_OF_RANGE = "Index out of range";
    static constexpr const char* ERROR_EMPTY_VECTOR = "Vector is empty";
    static constexpr const char* ERROR_ITERATOR_OUT_OF_RANGE = "Iterator out of range";
    static constexpr const char* ERROR_ITERATOR_RANGE = "Iterator range out of range";

public:
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(size_t n) : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) {
            data_[i] = T();
        }
    }

    Vector(size_t n, const T& value) : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) {
            data_[i] = value;
        }
    }

    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
        if (this != &other) {
            Vector temp(other.size_);
            for (size_t i = 0; i < other.size_; ++i) {
                temp.data_[i] = other.data_[i];
            }
            swap(temp);
        }
    }

    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~Vector() {
        delete[] data_;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_)
            throw std::out_of_range(ERROR_INDEX_OUT_OF_RANGE);
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_)
            throw std::out_of_range(ERROR_INDEX_OUT_OF_RANGE);
        return data_[index];
    }

    T& front() {
        if (empty())
            throw std::out_of_range(ERROR_EMPTY_VECTOR);
        return data_[0];
    }

    const T& front() const {
        if (empty())
            throw std::out_of_range(ERROR_EMPTY_VECTOR);
        return data_[0];
    }

    T& back() {
        if (empty())
            throw std::out_of_range(ERROR_EMPTY_VECTOR);
        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty())
            throw std::out_of_range(ERROR_EMPTY_VECTOR);
        return data_[size_ - 1];
    }

    iterator begin() { return data_; }
    iterator end() { return data_ + size_; }

    const_iterator cbegin() const { return data_; }
    const_iterator cend() const { return data_ + size_; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

    void resize(size_t new_size) {
        if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i)
                (data_ + i)->~T();
            size_ = new_size;
        }
        else if (new_size > size_) {
            if (new_size > capacity_)
                reserve(new_size);
            for (size_t i = size_; i < new_size; ++i)
                data_[i] = T();
            size_ = new_size;
        }
    }

    void resize(size_t new_size, const T& value) {
        if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i)
                (data_ + i)->~T();
            size_ = new_size;
        }
        else if (new_size > size_) {
            if (new_size > capacity_)
                reserve(new_size);
            for (size_t i = size_; i < new_size; ++i)
                data_[i] = value;
            size_ = new_size;
        }
    }

    void shrink_to_fit() {
        if (size_ == 0) {
            delete[] data_;
            data_ = nullptr;
            capacity_ = 0;
            return;
        }

        if (size_ < capacity_) {
            T* new_data = new T[size_];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

    void push_back(const T& value) {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(value);
    }

    iterator insert(iterator pos, const T& value) {
        size_t index = pos - data_;
        if (index > size_)
            throw std::out_of_range(ERROR_ITERATOR_OUT_OF_RANGE);

        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            pos = data_ + index;
        }

        for (size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }

        data_[index] = value;
        ++size_;
        return data_ + index;
    }

    iterator insert(iterator pos, T&& value) {
        size_t index = pos - data_;
        if (index > size_)
            throw std::out_of_range(ERROR_ITERATOR_OUT_OF_RANGE);

        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            pos = data_ + index;
        }

        for (size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }

        data_[index] = std::move(value);
        ++size_;
        return data_ + index;
    }

    void pop_back() {
        if (empty())
            throw std::out_of_range(ERROR_EMPTY_VECTOR);
        --size_;
        (data_ + size_)->~T();
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i)
            (data_ + i)->~T();
        size_ = 0;
    }

    iterator erase(iterator pos) {
        size_t index = pos - data_;

        if (index >= size_)
            throw std::out_of_range(ERROR_ITERATOR_OUT_OF_RANGE);

        (data_ + index)->~T();

        for (size_t i = index + 1; i < size_; ++i) {
            data_[i - 1] = std::move(data_[i]);
        }

        --size_;
        return data_ + index;
    }

    iterator erase(iterator first, iterator last) {
        size_t start = first - data_;
        size_t end = last - data_;

        if (start > size_ || end > size_ || start > end)
            throw std::out_of_range(ERROR_ITERATOR_RANGE);

        size_t count = end - start;

        for (size_t i = start; i < end; ++i)
            (data_ + i)->~T();

        for (size_t i = end; i < size_; ++i)
            data_[i - count] = std::move(data_[i]);

        size_ -= count;
        return data_ + start;
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i)
            if (data_[i] != other.data_[i]) return false;
        return true;
    }

    bool operator!=(const Vector& other) const { return !(*this == other); }

    bool operator<(const Vector& other) const {
        for (size_t i = 0; i < size_ && i < other.size_; ++i) {
            if (data_[i] < other.data_[i]) return true;
            if (data_[i] > other.data_[i]) return false;
        }
        return size_ < other.size_;
    }

    bool operator>(const Vector& other) const { return other < *this; }
    bool operator<=(const Vector& other) const { return !(other < *this); }
    bool operator>=(const Vector& other) const { return !(*this < other); }

    template<typename Compare = std::less<T>>
    void SelectionSort(Compare comp = Compare()) {
        for (size_t i = 0; i < size_; ++i) {
            size_t minIndex = i;
            for (size_t j = i + 1; j < size_; ++j) {
                if (comp(data_[j], data_[minIndex]))
                    minIndex = j;
            }
            if (minIndex != i)
                std::swap(data_[minIndex], data_[i]);
        }
    }
};



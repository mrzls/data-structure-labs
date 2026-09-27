#include "Queue.h"

#include <stdexcept>

const char* const ERR_QUEUE_EMPTY = "ќшибка: ќчередь пуста!";

template<typename T>
Queue<T>::Node::Node(const T& val) : data(val), next(nullptr) {}

template<typename T>
Queue<T>::Queue() : head_(nullptr), tail_(nullptr), count_(0) {}

template<typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void Queue<T>::push(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head_ = newNode;
        tail_ = newNode;
    }
    else {
        tail_->next = newNode;
        tail_ = newNode;
    }
    count_++;
}

template<typename T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::out_of_range(ERR_QUEUE_EMPTY);
    }
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
    count_--;
    if (empty()) {
        tail_ = nullptr;
    }
}

template<typename T>
T& Queue<T>::front() {
    if (empty()) {
        throw std::out_of_range(ERR_QUEUE_EMPTY);
    }
    return head_->data;
}

template<typename T>
const T& Queue<T>::front() const {
    if (empty()) {
        throw std::out_of_range(ERR_QUEUE_EMPTY);
    }
    return head_->data;
}

template<typename T>
bool Queue<T>::empty() const {
    return count_ == 0;
}

// явное инстанцирование дл€ int
template class Queue<int>;
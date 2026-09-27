#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val);
    };

    Node* head_;
    Node* tail_;
    size_t count_;

public:
    Queue();
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    bool empty() const;
};

#endif
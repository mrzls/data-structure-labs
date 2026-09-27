#include "QueueList.hpp"
#include <utility>

template <typename T>
QueueList<T>::QueueList() : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
QueueList<T>::~QueueList()
{
    while (head_ != nullptr) {
        deQueue();        
    }
};

template<typename T>
void QueueList<T>::enQueue(const T& e)
{
    Node* newNode = new Node(e);

    if (isEmpty()) {
        head_ = newNode;
        tail_ = newNode;
    }
    else {
        tail_->next_ = newNode;
        tail_ = newNode;
    }
    size_++;
}

template<typename T>
T QueueList<T>::deQueue()
{
    if (isEmpty())
        throw QueueUnderflow();

    Node* temp = head_;
    head_ = head_->next_;
    T value = std::move(temp->data_);

    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    delete temp;
    size_--;
    return value;
}

template<typename T>
bool QueueList<T>::isEmpty() { return size_==0; }

template<typename T>
size_t QueueList<T>::size() const { return size_; }

template class QueueList<int>;
template class QueueList<double>;
template class QueueList<char>;
template class QueueList<std::string>;
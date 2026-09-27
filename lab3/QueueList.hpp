#ifndef QUEUELIST_HPP
#define QUEUELIST_HPP
#include "Queue.hpp"
#include "Exceptions.hpp"

template<typename T>
class QueueList: public Queue<T>
{
private:
	struct Node 
	{
		T data_;
		Node* next_;

		Node(const T& value) : data_(value), next_(nullptr) {};
	};
	Node* head_;
	Node* tail_;
	size_t size_;
public:
	QueueList();
	~QueueList() override;
	void enQueue(const T& e) override;
	T deQueue() override;
	bool isEmpty() override;
	size_t size() const;
};

#endif
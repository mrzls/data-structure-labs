#ifndef STACKVECTOR_HPP
#define STACKVECTOR_HPP
#include "Stack.hpp"
#include "Exceptions.hpp"

template <typename T>
class StackVector: public Stack<T>
{
private:
	T* data_ = nullptr;
	size_t capacity_ = 0;
	size_t size_ = 0;

    void reallocate(size_t new_capacity);
    
public:
	StackVector();
	StackVector(size_t n);
	~StackVector() override;
	void push(const T& e) override;
	T pop() override;
	bool isEmpty() override;
	size_t size() const;
	size_t capacity() const;
};

#endif

#include "StackVector.hpp"
#include <utility> 

template<typename T>
void StackVector<T>::reallocate(size_t new_capacity)
{
	T* new_data = new T[new_capacity];

	try {
		for (size_t i = 0; i < size_; ++i) {
			new_data[i] = std::move(data_[i]);
		}
	}
	catch (...) {
		delete[] new_data;
		throw;
	}

	delete[] data_;
	data_ = new_data;
	capacity_ = new_capacity;
}

template<typename T>
StackVector<T>::StackVector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
StackVector<T>::StackVector(size_t n) : data_(new T[n]), size_(0), capacity_(n) 
{
	if (n == 0)
		throw WrongStackSize();
}

template<typename T>
StackVector<T>::~StackVector() { delete[] data_; }

template<typename T>
void StackVector<T>::push(const T& e)
{
	if (size_ == capacity_) {
		size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
		reallocate(new_capacity);
	}
	data_[size_++] = e;
}

template<typename T>
T StackVector<T>::pop()
{
	if (isEmpty())
		throw StackUnderflow();
	size_--;
	return std::move(data_[size_]);
}

template<typename T>
bool StackVector<T>::isEmpty() { return size_ == 0; }

template<typename T>
size_t StackVector<T>::size() const { return size_; };

template<typename T>
size_t StackVector<T>::capacity() const { return capacity_; }

template class StackVector<int>;
template class StackVector<double>;
template class StackVector<char>;
template class StackVector<std::string>;
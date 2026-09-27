#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <stdexcept>

constexpr const char* ERR_STACK_OVERFLOW = "Error! Stack is overflow!";
constexpr const char* ERR_STACK_UNDERFLOW = "Error! Stack is underflow!";
constexpr const char* ERR_WRONG_SIZE = "Error! Wrong stack size!";

constexpr const char* ERR_QUEUE_OVERFLOW = "Error! Queue is overflow!";
constexpr const char* ERR_QUEUE_UNDERFLOW = "Error! Queue is underflow!";
constexpr const char* ERR_QUEUE_SIZE = "Error! Wrong queue size!";

class StackOverflow : public std::exception
{
public:
    const char* what() const noexcept override {
        return ERR_STACK_OVERFLOW;
    }
};

class StackUnderflow : public std::exception 
{
public:
    const char* what() const noexcept override {
        return ERR_STACK_UNDERFLOW;
    }
};

class WrongStackSize : public std::exception 
{
public:
    const char* what() const noexcept override {
        return ERR_WRONG_SIZE;
    }
};

class QueueOverflow : public std::exception
{
public:
    const char* what() const noexcept override {
        return ERR_QUEUE_OVERFLOW;
    }
};

class QueueUnderflow : public std::exception
{
public:
    const char* what() const noexcept override {
        return ERR_QUEUE_UNDERFLOW;
    }
};

class WrongQueueSize : public std::exception
{
public:
    const char* what() const noexcept override {
        return ERR_QUEUE_SIZE;
    }
};

#endif EXCEPTIONS_HPP
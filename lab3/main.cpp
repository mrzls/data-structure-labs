#include "StackVector.hpp"
#include "QueueList.hpp"
#include <iostream>
#include <cassert>

void testStackVector();
void testQueueList();

int main() {
	std::cout << "    TEST CLASS\n\n";
	testStackVector();
	testQueueList();
	return EXIT_SUCCESS;
}

void testStackVector() 
{
	std::cout << "    TEST STACKVECTOR\n\n";

    StackVector<int> v1;
    assert(v1.isEmpty());
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    std::cout << "(+) Test default constructor - PASSED\n";

    StackVector<int> v2(10);
    assert(v2.isEmpty());
    assert(v2.size() == 0);
    assert(v2.capacity() == 10);
    std::cout << "(+) Test constructor - PASSED\n";

    for (int i = 0; i < 20; ++i) {
        v2.push(i);
    }
    assert(!v2.isEmpty());
    assert(v2.size() == 20);
    assert(v2.capacity() >= 20);
    std::cout << "(+) Test push - PASSED\n";

    for (int i = 19; i >= 0; --i) {
        int val = v2.pop();
        assert(val == i);
    }
    assert(v2.isEmpty());
    assert(v2.size() == 0);
    std::cout << "(+) Test pop - PASSED\n";

    StackVector<int> v3;
    assert(v3.isEmpty());
    v3.push(1);
    assert(!v3.isEmpty());
    v3.pop();
    assert(v3.isEmpty());
    std::cout << "(+) Test isEmpty - PASSED\n";

    try {
        v2.pop();  // v2 уже пуст
    }
    catch (const StackUnderflow& ex) {
        std::cerr << "(+) Exception caught: " << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "(+) Unknown exception caught\n";
    }
    std::cout << "(+) Test StackUnderflow exception - PASSED\n";

    try {
        StackVector<int> v4(0);
    }
    catch (const WrongStackSize& ex) {
        std::cout << "(+) Exception caught: " << ex.what() << '\n';
    }
    std::cout << "(+) Test WrongStackSize exception - PASSED\n";

    std::cout << "\n    ALL STACK TESTS PASSED!\n";
}

void testQueueList()
{
    std::cout << "\n    TEST QUEUELIST\n\n";

    QueueList<int> q1;
    assert(q1.isEmpty());
    assert(q1.size() == 0);
    std::cout << "(+) Test default constructor - PASSED\n";

    QueueList<int> q2;
    q2.enQueue(10);
    q2.enQueue(20);
    q2.enQueue(30);
    assert(!q2.isEmpty());
    assert(q2.size() == 3);
    std::cout << "(+) Test enQueue - PASSED\n";

    int val = q2.deQueue();
    assert(val == 10);
    assert(q2.size() == 2);

    val = q2.deQueue();
    assert(val == 20);
    assert(q2.size() == 1);

    val = q2.deQueue();
    assert(val == 30);
    assert(q2.isEmpty());
    assert(q2.size() == 0);
    std::cout << "(+) Test deQueue (FIFO) - PASSED\n";

    QueueList<int> q3;
    assert(q3.isEmpty());
    q3.enQueue(1);
    assert(!q3.isEmpty());
    q3.deQueue();
    assert(q3.isEmpty());
    std::cout << "(+) Test isEmpty - PASSED\n";

    try {
        q2.deQueue();
    }
    catch (const QueueUnderflow& ex) {
        std::cout << "(+) Exception caught: " << ex.what() << '\n';
    }
    std::cout << "(+) Test QueueUnderflow exception - PASSED\n";

    std::cout << "\n    ALL QUEUE TESTS PASSED!\n";
}

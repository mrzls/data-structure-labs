#include "Vector.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <stdexcept>
#include <cmath>

void testConstructors();
void testAssignmentOperators();
void testElementAccess();
void testPushBack();
void testPopBackClear();
void testInsertErase();
void testReserveShrink();
void testComparisonOperators();
void testSelectionSort();
void testIterators();
void testExceptions();

int main() {

    std::cout << "     VECTOR TESTS      \n";

    testConstructors();
    testAssignmentOperators();
    testElementAccess();
    testPushBack();
    testPopBackClear();
    testInsertErase();
    testReserveShrink();
    testComparisonOperators();
    testSelectionSort();
    testIterators();
    testExceptions();

    std::cout << "     ALL TESTS COMPLETED SUCCESSFULLY \n";
    return(EXIT_SUCCESS);
}

void testConstructors() {
    std::cout << "[TEST 1] Constructor Verification\n";

    Vector<double> v1;
    assert(v1.empty());
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    std::cout << "  (+) Default constructor - PASSED\n";

    Vector<int> v2(7);
    assert(v2.size() == 7);
    assert(v2.capacity() >= 7);
    for (size_t i = 0; i < v2.size(); ++i) {
        assert(v2[i] == 0);
    }
    std::cout << "  (+) Size constructor (7 elements) - PASSED\n";

    Vector<char> v3(4, 'X');
    assert(v3.size() == 4);
    for (size_t i = 0; i < v3.size(); ++i) {
        assert(v3[i] == 'X');
    }
    std::cout << "  (+) Size and value constructor (4x'X') - PASSED\n";

    Vector<int> v4(v2);
    assert(v4.size() == v2.size());
    for (size_t i = 0; i < v4.size(); ++i) {
        assert(v4[i] == v2[i]);
    }
    assert(v4 == v2);
    std::cout << "  (+) Copy constructor - PASSED\n";

    Vector<int> v5(std::move(v4));
    assert(v5.size() == 7);
    assert(v5[0] == 0);
    assert(v4.empty());
    assert(v4.capacity() == 0);
    std::cout << "  (+) Move constructor - PASSED\n";

    std::cout << "  (+) TEST 1 COMPLETED\n\n";
}

void testAssignmentOperators() {
    std::cout << "[TEST 2] Assignment Operators\n";

    Vector<std::string> v1(3, "hello");
    Vector<std::string> v2;

    v2 = v1;
    assert(v2.size() == 3);
    for (size_t i = 0; i < v2.size(); ++i)
        assert(v2[i] == v1[i]);
    assert(v2 == v1);
    std::cout << "  (+) Copy assignment - PASSED\n";

    Vector<std::string> v3;
    v3 = std::move(v2);
    assert(v3.size() == 3);
    assert(v3[0] == "hello");
    assert(v2.empty());
    std::cout << "  (+) Move assignment - PASSED\n";

    std::cout << "  (+) TEST 2 COMPLETED\n\n";
}

void testElementAccess() {
    std::cout << "[TEST 3] Element Access Methods\n";

    Vector<int> vec;
    for (int i = 0; i < 8; ++i) {
        vec.push_back(i * 5);
    }
    for (int i = 0; i < 8; ++i) {
        assert(vec[i] == (i * 5));
    }
    vec[4] = 999;
    assert(vec[4] == 999);
    std::cout << "  (+) operator[] - PASSED\n";

    assert(vec.at(2) == 10);
    assert(vec.at(6) == 30);
    std::cout << "  (+) at() (valid indices) - PASSED\n";

    assert(vec.front() == 0);
    vec.front() = 1111;
    assert(vec.front() == 1111);
    assert(vec[0] == 1111);
    std::cout << "  (+) front() - PASSED\n";

    assert(vec.back() == 35);
    vec.back() = 3535;
    assert(vec.back() == 3535);
    assert(vec[7] == 3535);
    std::cout << "  (+) back() - PASSED\n";

    std::cout << "  (+) TEST 3 COMPLETED\n\n";
}

void testPushBack() {
    std::cout << "[TEST 4] Push Back Operations\n";

    Vector<int> vec;
    assert(vec.empty());

    int value = 100;
    vec.push_back(value);
    assert(vec.size() == 1);
    assert(vec[0] == 100);
    std::cout << "  (+) Copy push_back - PASSED\n";

    vec.push_back(200);
    vec.push_back(300);
    vec.push_back(400);
    assert(vec.size() == 4);
    assert(vec[1] == 200);
    assert(vec[2] == 300);
    assert(vec[3] == 400);
    std::cout << "  (+) Multiple push_back - PASSED\n";

    vec.push_back(std::move(500));
    assert(vec[4] == 500);
    std::cout << "  (+) Move push_back - PASSED\n";

    size_t old_capacity = vec.capacity();
    for (int i = 0; i < 15; ++i) {
        vec.push_back(i * 10);
    }
    assert(vec.size() == 20);
    assert(vec.capacity() >= vec.size());
    assert(vec.capacity() > old_capacity);
    std::cout << "  (+) Capacity growth - PASSED\n";

    std::cout << "  (+) TEST 4 COMPLETED\n\n";
}

void testPopBackClear() {
    std::cout << "[TEST 5] Pop Back and Clear\n";

    Vector<std::string> vec;
    vec.push_back("alpha");
    vec.push_back("beta");
    vec.push_back("gamma");
    vec.push_back("delta");
    vec.push_back("epsilon");
    assert(vec.size() == 5);

    vec.pop_back();
    assert(vec.size() == 4);
    assert(vec.back() == "delta");
    vec.pop_back();
    assert(vec.size() == 3);
    assert(vec.back() == "gamma");
    vec.pop_back();
    assert(vec.size() == 2);
    assert(vec.back() == "beta");
    std::cout << "  (+) pop_back - PASSED\n";

    vec.clear();
    assert(vec.empty());
    assert(vec.size() == 0);
    assert(vec.capacity() >= 5);
    std::cout << "  (+) clear - PASSED\n";

    std::cout << "  (+) TEST 5 COMPLETED\n\n";
}

void testInsertErase() {
    std::cout << "[TEST 6] Insert and Erase Operations\n";

    Vector<int> vec;
    for (int i = 0; i < 6; ++i) {
        vec.push_back(i * 10);
    }

    auto it = vec.insert(vec.begin(), 999);
    assert(*it == 999);
    assert(vec.size() == 7);
    assert(vec[0] == 999);
    assert(vec[1] == 0);
    std::cout << "  (+) Insert at beginning - PASSED\n";

    it = vec.insert(vec.begin() + 4, 777);
    assert(*it == 777);
    assert(vec.size() == 8);
    assert(vec[3] == 20);
    assert(vec[4] == 777);
    assert(vec[5] == 30);
    std::cout << "  (+) Insert in middle - PASSED\n";

    it = vec.insert(vec.end(), 555);
    assert(*it == 555);
    assert(vec.size() == 9);
    assert(vec.back() == 555);
    std::cout << "  (+) Insert at end - PASSED\n";

    it = vec.erase(vec.begin() + 2);
    assert(*it == 20);
    assert(vec.size() == 8);
    assert(vec[1] == 0);
    assert(vec[2] == 20);
    std::cout << "  (+) Erase single - PASSED\n";

    it = vec.erase(vec.begin() + 3, vec.begin() + 6);
    assert(*it == 50);
    assert(vec.size() == 5);
    assert(vec[2] == 20);
    assert(vec[3] == 50);
    std::cout << "  (+) Erase range - PASSED\n";

    std::cout << "  (+) TEST 6 COMPLETED\n\n";
}

void testReserveShrink() {
    std::cout << "[TEST 7] Reserve and Shrink Operations\n";

    Vector<int> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(i * 10);
    }

    size_t old_capacity = vec.capacity();
    vec.reserve(25);
    assert(vec.capacity() >= 25);
    assert(vec.capacity() > old_capacity);
    assert(vec.size() == 5);
    std::cout << "  (+) reserve - PASSED\n";

    vec.shrink_to_fit();
    assert(vec.capacity() == vec.size());
    assert(vec.capacity() == 5);
    std::cout << "  (+) shrink_to_fit - PASSED\n";

    Vector<int> empty_vec;
    empty_vec.shrink_to_fit();
    assert(empty_vec.capacity() == 0);
    std::cout << "  (+) shrink_to_fit on empty - PASSED\n";

    std::cout << "  (+) TEST 7 COMPLETED\n\n";
}

void testComparisonOperators() {
    std::cout << "[TEST 8] Comparison Operators\n";

    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);

    Vector<int> v2;
    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(30);
    v2.push_back(40);

    Vector<int> v3;
    v3.push_back(10);
    v3.push_back(20);
    v3.push_back(35);
    v3.push_back(40);

    Vector<int> v4;
    v4.push_back(10);
    v4.push_back(20);
    v4.push_back(30);

    Vector<int> v5;
    v5.push_back(10);
    v5.push_back(20);
    v5.push_back(30);
    v5.push_back(40);
    v5.push_back(50);

    assert(v1 == v2);
    assert(!(v1 != v2));
    assert(v1 != v3);
    assert(v1 != v4);
    std::cout << "  (+) == and != - PASSED\n";

    assert(v4 < v1);
    assert(v1 > v4);
    assert(v3 > v1);
    assert(v1 < v5);
    assert(v1 < v3);
    assert(!(v1 < v2));
    assert(!(v1 > v2));
    std::cout << "  (+) < and > - PASSED\n";

    assert(v1 <= v2);
    assert(v1 >= v2);
    assert(v4 <= v1);
    assert(v1 >= v4);
    assert(v1 <= v3);
    assert(v3 >= v1);
    std::cout << "  (+) <= and >= - PASSED\n";

    std::cout << "  (+) TEST 8 COMPLETED\n\n";
}

void testSelectionSort() {
    std::cout << "[TEST 9] Selection Sort \n";

    Vector<int> vec;
    vec.push_back(42);
    vec.push_back(17);
    vec.push_back(33);
    vec.push_back(5);
    vec.push_back(28);
    vec.push_back(91);
    vec.push_back(14);

    std::cout << "  Original vector: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    vec.SelectionSort();

    std::cout << "  Sorted vector:   ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    for (size_t i = 1; i < vec.size(); ++i) {
        assert(vec[i - 1] <= vec[i]);
    }
    std::cout << "  (+) Int sorting  - PASSED\n";

    Vector<double> dvec;
    dvec.push_back(3.14);
    dvec.push_back(2.71);
    dvec.push_back(1.61);
    dvec.push_back(0.57);
    dvec.push_back(4.20);

    dvec.SelectionSort(std::greater<double>());

    assert(dvec[0] == 4.20);
    assert(dvec[1] == 3.14);
    assert(dvec[2] == 2.71);
    assert(dvec[3] == 1.61);
    assert(dvec[4] == 0.57);
    std::cout << "  (+) Double sorting - PASSED\n";

    Vector<std::string> str_vec;
    str_vec.push_back("zebra");
    str_vec.push_back("monkey");
    str_vec.push_back("apple");
    str_vec.push_back("tiger");
    str_vec.push_back("lion");

    str_vec.SelectionSort();
    assert(str_vec[0] == "apple");
    assert(str_vec[1] == "lion");
    assert(str_vec[2] == "monkey");
    assert(str_vec[3] == "tiger");
    assert(str_vec[4] == "zebra");
    std::cout << "  (+) String sorting - PASSED\n";

    std::cout << "  (+) TEST 9 COMPLETED\n\n";
}

void testIterators() {
    std::cout << "[TEST 10] Iterator Operations\n";

    Vector<int> vec;
    for (int i = 0; i < 6; ++i) {
        vec.push_back(i * 15);
    }

    auto it = vec.begin();
    assert(*it == 0);
    ++it;
    assert(*it == 15);
    it += 3;
    assert(*it == 60);
    assert(*(vec.end() - 1) == 75);
    std::cout << "  (+) begin/end - PASSED\n";

    auto cit = vec.cbegin();
    assert(*cit == 0);
    ++cit;
    assert(*cit == 15);
    assert(*(vec.cend() - 1) == 75);
    std::cout << "  (+) const iterators - PASSED\n";

    auto rit = vec.rbegin();
    assert(*rit == 75);
    ++rit;
    assert(*rit == 60);
    assert(*(vec.rend() - 1) == 0);
    std::cout << "  (+) reverse iterators - PASSED\n";

    assert(vec.end() - vec.begin() == 6);
    assert(vec.begin() + 4 == vec.end() - 2);
    std::cout << "  (+) iterator arithmetic - PASSED\n";

    int sum = 0;
    for (const auto& val : vec) {
        sum += val;
    }
    assert(sum == 225);
    std::cout << "  (+) range-based for loop - PASSED\n";

    std::cout << "  (+) TEST 10 COMPLETED\n\n";
}
void testExceptions() {
    std::cout << "[TEST 11] Exception Handling\n";

    Vector<int> vec(5, 100);
    Vector<int> empty_vec;

    bool exception_caught = false;
    try {
        vec.at(10);
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) at() out of bounds: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        empty_vec.front();
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) front() on empty: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        empty_vec.back();
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) back() on empty: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        empty_vec.pop_back();
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) pop_back() on empty: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        vec.insert(vec.end() + 10, 999);
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) insert with invalid iterator: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        vec.erase(vec.begin() + 20);
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) erase with invalid iterator: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        vec.erase(vec.begin() + 2, vec.begin());
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) erase with invalid range: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    std::cout << "  (+) TEST 11 COMPLETED\n\n";
}

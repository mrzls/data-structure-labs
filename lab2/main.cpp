#include "SinglyOrderedList.cpp"
#include <iostream>
#include <cassert>
#include <string>
#include <stdexcept>

void testConstructors();
void testAssignmentOperators();
void testElementAccess();
void testInsert();
void testRemoveHeadClear();
void testRemoveKey();
void testSearch();
void testComparisonOperators();
void testRemoveList();
void testGetIntersection();
void testExceptions();

int main() {
    std::cout << "     SINGLY ORDERED LIST TESTS     \n\n";
    testConstructors();
    testAssignmentOperators();
    testElementAccess();
    testInsert();
    testRemoveHeadClear();
    testRemoveKey();
    testSearch();
    testComparisonOperators();
    testRemoveList();
    testGetIntersection();
    testExceptions();

    std::cout << "     ALL TESTS COMPLETED SUCCESSFULLY \n";
    return EXIT_SUCCESS;
}

void testConstructors() {
    std::cout << "[TEST 1] Constructor Verification\n";

    // Тест конструктора по умолчанию
    SinglyOrderedList<int> list1;
    assert(list1.isEmpty());
    assert(list1.size() == 0);
    std::cout << "  (+) Default constructor - PASSED\n";

    // Тест конструктора с одним элементом
    SinglyOrderedList<int> list2(42);
    assert(!list2.isEmpty());
    assert(list2.size() == 1);
    assert(list2.head() == 42);
    assert(list2.tail() == 42);
    std::cout << "  (+) Single value constructor - PASSED\n";

    // Тест конструктора копирования
    list2.insert(17);
    list2.insert(33);
    SinglyOrderedList<int> list3(list2);
    assert(list3.size() == 3);
    assert(list3 == list2);
    assert(list3.head() == 17);  // Упорядоченный список: 17, 33, 42
    std::cout << "  (+) Copy constructor - PASSED\n";

    // Тест конструктора перемещения
    SinglyOrderedList<int> list4(std::move(list3));
    assert(list4.size() == 3);
    assert(list3.isEmpty());
    assert(list3.size() == 0);
    std::cout << "  (+) Move constructor - PASSED\n";

    std::cout << "  (+) TEST 1 COMPLETED\n\n";
}

void testAssignmentOperators() {
    std::cout << "[TEST 2] Assignment Operators\n";

    SinglyOrderedList<std::string> list1;
    list1.insert("banana");
    list1.insert("apple");
    list1.insert("orange");
    list1.insert("cherry");

    // Тест копирующего присваивания
    SinglyOrderedList<std::string> list2;
    list2 = list1;
    assert(list2.size() == 4);
    assert(list2 == list1);
    assert(list2.head() == "apple");
    assert(list2.tail() == "orange");
    std::cout << "  (+) Copy assignment - PASSED\n";

    // Тест перемещающего присваивания
    SinglyOrderedList<std::string> list3;
    list3 = std::move(list2);
    assert(list3.size() == 4);
    assert(list2.isEmpty());
    assert(list3.head() == "apple");
    assert(list3.tail() == "orange");
    std::cout << "  (+) Move assignment - PASSED\n";

    // Тест самоприсваивания
    list3 = list3;
    assert(list3.size() == 4);
    std::cout << "  (+) Self assignment - PASSED\n";

    std::cout << "  (+) TEST 2 COMPLETED\n\n";
}

void testElementAccess() {
    std::cout << "[TEST 3] Element Access Methods\n";

    SinglyOrderedList<int> list;
    for (int i : {50, 30, 10, 40, 20}) {
        list.insert(i);
    }
    // Упорядоченный список: 10, 20, 30, 40, 50

    // Тест head()
    assert(list.head() == 10);
    std::cout << "  (+) head() - PASSED\n";

    // Тест tail()
    assert(list.tail() == 50);
    std::cout << "  (+) tail() - PASSED\n";

    // Тест на пустом списке (исключения)
    SinglyOrderedList<int> empty_list;
    bool exception_caught = false;
    try {
        empty_list.head();
    }
    catch (const std::out_of_range&) {
        exception_caught = true;
        std::cout << "  (+) head() on empty throws exception - PASSED\n";
    }
    assert(exception_caught);

    exception_caught = false;
    try {
        empty_list.tail();
    }
    catch (const std::out_of_range&) {
        exception_caught = true;
        std::cout << "  (+) tail() on empty throws exception - PASSED\n";
    }
    assert(exception_caught);

    std::cout << "  (+) TEST 3 COMPLETED\n\n";
}

void testInsert() {
    std::cout << "[TEST 4] Insert Operations\n";

    // Тест вставки в пустой список
    SinglyOrderedList<int> list;
    list.insert(30);
    assert(list.size() == 1);
    assert(list.head() == 30);
    assert(list.tail() == 30);
    std::cout << "  (+) Insert into empty list - PASSED\n";

    // Тест вставки в начало
    list.insert(10);
    assert(list.size() == 2);
    assert(list.head() == 10);
    assert(list.tail() == 30);
    std::cout << "  (+) Insert at beginning - PASSED\n";

    // Тест вставки в середину
    list.insert(20);
    assert(list.size() == 3);
    assert(list.head() == 10);
    assert(list.tail() == 30);
    // Проверим порядок, удаляя элементы
    list.removeKey(20);
    assert(!list.search(20));
    list.insert(20); // Возвращаем обратно
    std::cout << "  (+) Insert in middle - PASSED\n";

    // Тест вставки в конец
    list.insert(40);
    assert(list.size() == 4);
    assert(list.tail() == 40);
    std::cout << "  (+) Insert at end - PASSED\n";

    // Тест вставки с перемещением
    SinglyOrderedList<std::string> string_list;
    std::string s = "temporary";
    string_list.insert(std::move(s));
    assert(string_list.size() == 1);
    assert(string_list.head() == "temporary");
    std::cout << "  (+) Move insert - PASSED\n";

    // Тест уникальности ключей
    bool exception_caught = false;
    try {
        list.insert(20); // 20 уже есть в списке
    }
    catch (const std::invalid_argument&) {
        exception_caught = true;
        std::cout << "  (+) Duplicate key throws exception - PASSED\n";
    }
    assert(exception_caught);

    std::cout << "  (+) TEST 4 COMPLETED\n\n";
}

void testRemoveHeadClear() {
    std::cout << "[TEST 5] Remove Head and Clear\n";

    SinglyOrderedList<int> list;
    for (int i : {5, 3, 1, 4, 2}) {
        list.insert(i);
    }
    // Упорядоченный список: 1, 2, 3, 4, 5
    assert(list.size() == 5);

    // Тест removeHead
    list.removeHead();
    assert(list.size() == 4);
    assert(list.head() == 2);
    assert(list.tail() == 5);
    std::cout << "  (+) removeHead - PASSED\n";

    // Удаляем все элементы по одному
    list.removeHead(); // удаляем 2
    list.removeHead(); // удаляем 3
    list.removeHead(); // удаляем 4
    list.removeHead(); // удаляем 5
    assert(list.isEmpty());
    assert(list.size() == 0);
    std::cout << "  (+) removeHead all elements - PASSED\n";

    // Тест removeHead на пустом списке
    bool exception_caught = false;
    try {
        list.removeHead();
    }
    catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);
    std::cout << "  (+) removeHead on empty returns false - PASSED\n";

    // Тест clear
    SinglyOrderedList<double> list2;
    list2.insert(1.1);
    list2.insert(2.2);
    list2.insert(3.3);
    assert(list2.size() == 3);
    list2.clear();
    assert(list2.isEmpty());
    assert(list2.size() == 0);
    std::cout << "  (+) clear - PASSED\n";

    std::cout << "  (+) TEST 5 COMPLETED\n\n";
}

void testRemoveKey() {
    std::cout << "[TEST 6] Remove by Key\n";

    SinglyOrderedList<int> list;
    for (int i : {5, 2, 8, 1, 9, 3, 7, 4, 6}) {
        list.insert(i);
    }
    // Упорядоченный список: 1, 2, 3, 4, 5, 6, 7, 8, 9
    assert(list.size() == 9);

    // Тест удаления из начала
    list.removeKey(1);
    assert(!list.search(1));
    assert(list.size() == 8);
    assert(list.head() == 2);
    std::cout << "  (+) removeKey from beginning - PASSED\n";

    // Тест удаления из середины
    list.removeKey(5);
    assert(!list.search(5));
    assert(list.size() == 7);
    // Проверим порядок
    list.removeKey(4);
    assert(!list.search(4));
    list.removeKey(6);
    assert(!list.search(6));
    assert(list.size() == 5);
    std::cout << "  (+) removeKey from middle - PASSED\n";

    // Тест удаления из конца
    list.removeKey(9);
    assert(!list.search(9));
    assert(list.size() == 4);
    assert(list.tail() == 8);
    std::cout << "  (+) removeKey from end - PASSED\n";

    // Тест удаления несуществующего ключа
    bool exception_caught = false;
    try {
        list.removeKey(100);
    }
    catch (const std::invalid_argument&) {
        exception_caught = true;
    }
    assert(exception_caught);
    assert(list.size() == 4);
    std::cout << "  (+) removeKey non-existent returns false - PASSED\n";

    // Тест удаления из пустого списка
    SinglyOrderedList<int> empty_list;
    exception_caught = false;
    try {
        empty_list.removeKey(42);
    }
    catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);
    std::cout << "  (+) removeKey on empty returns false - PASSED\n";

    std::cout << "  (+) TEST 6 COMPLETED\n\n";
}

void testSearch() {
    std::cout << "[TEST 7] Search by Key\n";

    SinglyOrderedList<std::string> list;
    list.insert("cat");
    list.insert("dog");
    list.insert("bird");
    list.insert("fish");
    list.insert("ant");
    // Упорядоченный список: ant, bird, cat, dog, fish

    // Тест поиска существующих элементов
    assert(list.search("ant"));
    assert(list.search("cat"));
    assert(list.search("fish"));
    std::cout << "  (+) search existing keys - PASSED\n";

    // Тест поиска несуществующих элементов
    assert(!list.search("zebra"));
    assert(!list.search("bat"));
    std::cout << "  (+) search non-existing keys - PASSED\n";

    // Тест поиска в пустом списке
    SinglyOrderedList<std::string> empty_list;
    assert(!empty_list.search("anything"));
    std::cout << "  (+) search on empty list - PASSED\n";

    std::cout << "  (+) TEST 7 COMPLETED\n\n";
}

void testComparisonOperators() {
    std::cout << "[TEST 8] Comparison Operators\n";
    std::cout << "----------------------------------------\n";

    SinglyOrderedList<int> list1;
    for (int i = 1; i < 5; ++i) {
        list1.insert(i);
    }

    SinglyOrderedList<int> list2 = list1;
    
    SinglyOrderedList<int> list3;
    for (int i = 1; i < 4; ++i) {
        list3.insert(i);
    }
    list3.insert(5);

    SinglyOrderedList<int> list4;
    for (int i = 1; i < 4; ++i) {
        list4.insert(i);
    }

    // Тест равенства
    assert(list1 == list2);
    assert(!(list1 == list3));
    assert(!(list1 == list4));
    std::cout << "  (+) == - PASSED\n";

    std::cout << "  (+) TEST 8 COMPLETED\n\n";
}

void testRemoveList() {
    std::cout << "[TEST 9] Remove Elements of Another List\n";

    SinglyOrderedList<int> list1;
    for (int i = 1; i < 11; ++i) {
        list1.insert(i);
    }

    SinglyOrderedList<int> list2;
    for (int i : {2, 4, 6, 8, 10}) {
        list2.insert(i);
    }
    // list2: 2, 4, 6, 8, 10

    // Удаляем элементы list2 из list1
    list1.remove(list2);
    assert(list1.size() == 5);
    // Ожидаем: 1, 3, 5, 7, 9
    assert(list1.search(1));
    assert(list1.search(3));
    assert(list1.search(5));
    assert(list1.search(7));
    assert(list1.search(9));
    assert(!list1.search(2));
    assert(!list1.search(4));
    assert(!list1.search(6));
    assert(!list1.search(8));
    assert(!list1.search(10));
    std::cout << "  (+) remove elements of another list - PASSED\n";

    // Удаление из пустого списка
    SinglyOrderedList<int> empty_list;
    empty_list.remove(list2);
    assert(empty_list.isEmpty());
    std::cout << "  (+) remove on empty list - PASSED\n";

    std::cout << "  (+) TEST 9 COMPLETED\n\n";
}

void testGetIntersection() {
    std::cout << "[TEST 10] Get Intersection\n";

    SinglyOrderedList<int> listA;
    for (int i : {1, 3, 5, 7, 9, 11, 13, 15}) {
        listA.insert(i);
    }

    SinglyOrderedList<int> listB;
    for (int i : {2, 3, 5, 7, 11, 13, 17, 19}) {
        listB.insert(i);
    }

    // Ожидаемое пересечение: 3, 5, 7, 11, 13
    SinglyOrderedList<int> result = getIntersection(listA, listB);

    assert(result.size() == 5);
    assert(result.search(3));
    assert(result.search(5));
    assert(result.search(7));
    assert(result.search(11));
    assert(result.search(13));
    assert(!result.search(1));
    assert(!result.search(2));
    assert(!result.search(9));
    std::cout << "  (+) getIntersection with common elements - PASSED\n";

    // Пересечение пустого списка
    SinglyOrderedList<int> empty_list;
    SinglyOrderedList<int> result2 = getIntersection(empty_list, listB);
    assert(result2.isEmpty());
    std::cout << "  (+) getIntersection with empty list - PASSED\n";

    // Пересечение без общих элементов
    SinglyOrderedList<int> listC;
    listC.insert(100);
    listC.insert(200);
    SinglyOrderedList<int> result3 = getIntersection(listA, listC);
    assert(result3.isEmpty());
    std::cout << "  (+) getIntersection with no common elements - PASSED\n";

    std::cout << "  (+) TEST 10 COMPLETED\n\n";
}

void testExceptions() {
    std::cout << "[TEST 11] Exception Handling\n";

    SinglyOrderedList<int> list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    // Тест head() на пустом списке
    SinglyOrderedList<int> empty_list;
    bool exception_caught = false;
    try {
        empty_list.head();
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) head() on empty: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    // Тест tail() на пустом списке
    exception_caught = false;
    try {
        empty_list.tail();
    }
    catch (const std::out_of_range& e) {
        exception_caught = true;
        std::cout << "  (+) tail() on empty: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    // Тест вставки дубликата
    exception_caught = false;
    try {
        list.insert(20); // 20 уже есть
    }
    catch (const std::invalid_argument& e) {
        exception_caught = true;
        std::cout << "  (+) duplicate key: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);

    // Тест удаления несуществующего ключа
    exception_caught = false;
    try {
        list.removeKey(999);
    }
    catch (const std::invalid_argument& e) {
        exception_caught = true;
        std::cout << "  (+) key not found: \"" << e.what() << "\"\n";
    }
    assert(exception_caught);
    assert(list.size() == 3);

    std::cout << "  (+) TEST 11 COMPLETED\n\n";
}
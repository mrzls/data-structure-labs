#include "HashTable.hpp"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testConstructor();
void testInsertAndSearch();
void testRemove();
void testCollisionCounting();
void testPrint();
void testExceptions();

int main() {
    cout << "    TEST HASH TABLE (VARIANT 5)\n\n";

    testConstructor();
    testInsertAndSearch();
    testRemove();
    testCollisionCounting();
    testPrint();
    testExceptions();

    cout << "\n    ALL TESTS PASSED!\n";
    return EXIT_SUCCESS;
}

void testConstructor()
{
    cout << "    TEST CONSTRUCTOR\n";

    HashTable ht1(13);
    assert(ht1.getSize() == 13);
    assert(ht1.getNumber() == 0);
    assert(ht1.getColNum() == 0);

    cout << "(+) Constructor - PASSED\n\n";
}

void testInsertAndSearch()
{
    cout << "    TEST INSERT AND SEARCH\n";

    HashTable ht(13);

    ht.insert("Barsik", "cat");
    ht.insert("Pushok", "cat");
    ht.insert("Sharik", "dog");
    ht.insert("Kesha", "parrot");
    ht.insert("Charli", "parrot");
    ht.insert("Dori", "fish");
    ht.insert("Natasha", "turtle");
    assert(ht.getNumber() == 7);
    cout << "(+) Insert 7 items - PASSED\n";

    // Поиск существующих ключей
    string* val = ht.search("Barsik");
    assert(*val == "cat");

    val = ht.search("Kesha");
    assert(*val == "parrot");

    val = ht.search("Dori");
    assert(*val == "fish");
    cout << "(+) Search existing keys - PASSED\n\n";
}

void testRemove()
{
    cout << "    TEST REMOVE\n";

    HashTable ht(13);

    // Вставка элементов
    ht.insert("Barsik", "cat");
    ht.insert("Sharik", "dog");
    ht.insert("Kesha", "parrot");
    ht.insert("Dori", "fish");
    assert(ht.getNumber() == 4);

    // Удаление существующего
    ht.remove("Barsik");
    assert(ht.getNumber() == 3);

    // Проверка, что ключ удалён
    bool exceptionThrown = false;
    try {
        ht.search("Barsik");
    }
    catch (const std::runtime_error& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    cout << "(+) Remove existing key - PASSED\n\n";

}

void testCollisionCounting()
{
    cout << "    TEST COLLISION COUNTING\n";

    HashTable ht(13);

    ht.insert("Barsik", "cat");
    ht.insert("Sharik", "dog");
    ht.insert("Kesha", "parrot");
    ht.insert("Murka", "cat");
    ht.insert("Tuzik", "dog");
    ht.insert("Pushok", "cat");
    ht.insert("Murzik", "cat");
    ht.insert("Bobik", "dog");
    
    cout << "(+) Number of collisions: " << ht.getColNum() << "\n";
    cout << "(+) Collision counting - PASSED\n\n";
}

void testPrint()
{
    cout << "    TEST PRINT TABLE\n";

    HashTable ht(13);

    cout << "=== Empty table ===\n";
    ht.print();

    ht.insert("Barsik", "cat");
    ht.insert("Sharik", "dog");
    ht.insert("Kesha", "parrot");
    ht.insert("Dori", "fish");
    ht.insert("Murka", "cat");
    ht.insert("Homa", "hamster");

    cout << "\n=== After inserting 6 items ===\n";
    ht.print();

    ht.remove("Sharik");
    ht.remove("Dori");

    cout << "\n=== After removing 'Sharik' and 'Dori' ===\n";
    ht.print();
    cout << "\n(+) Print - PASSED\n";
}

void testExceptions()
{
    cout << "    TEST EXCEPTIONS\n\n";

    // Тест 1: Создание таблицы с неверным размером
    cout << "  Test 1: Invalid table size (0 or negative)\n";
    bool exceptionThrown = false;
    try {
        HashTable ht(0);
    }
    catch (const std::invalid_argument& e) {
        exceptionThrown = true;
        cout << "    Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        HashTable ht(-5);
    }
    catch (const std::invalid_argument& e) {
        exceptionThrown = true;
        cout << "    Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);
    cout << "  Test 1 - PASSED\n\n";

    // Тест 2: Превышение load factor 
    cout << "  Test 2: Load factor limit (>= 0.7)\n";
    HashTable ht10(10);
    for (int i = 1; i < 7; i++) {
        ht10.insert(("key" + to_string(i)).c_str(), "value");
    }
    assert(ht10.getNumber() == 6);

    exceptionThrown = false;
    try {
        ht10.insert("key7", "value");
    }
    catch (const std::overflow_error& e) {
        exceptionThrown = true;
        cout << "    Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);
    assert(ht10.getNumber() == 6);
    cout << "  Test 2 - PASSED\n\n";

    // Тест 3: Удаление несуществующего ключа
    cout << "  Test 3: Remove non-existing key\n";
    HashTable ht13(13);
    ht13.insert("Barsik", "cat");

    exceptionThrown = false;
    try {
        ht13.remove("Murka");
    }
    catch (const std::runtime_error& e) {
        exceptionThrown = true;
        cout << "    Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);
    cout << "  Test 3 - PASSED\n\n";

    // Тест 4: Вставка существующего ключа
    cout << "  Test 4: Insert duplicate key\n";
  
    exceptionThrown = false;
    try {
        ht13.insert("Barsik", "siberian cat");
    }
    catch (const std::runtime_error& e) {
        exceptionThrown = true;
        cout << "    Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);
    assert(ht13.getNumber() == 1);  // количество не изменилось

    // Проверяем, что значение осталось прежним
    string* val = ht13.search("Barsik");
    assert(val != nullptr && *val == "cat");
    cout << "  Test 4 - PASSED\n\n";

    cout << "(+) All exception tests - PASSED\n\n";
}
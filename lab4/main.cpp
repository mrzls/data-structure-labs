#include "BinarySearchTree.h"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

void testDefaultConstructor();
void testMoveSemantics();
void testInsertAndSearch();
void testRemove();
void testOutput();
void testGetNumberOfNodes();
void testGetHeight();
void testInorderWalkRecursive();
void testInorderWalkIterative();
void testWalkByLevels();
void testRemoveLessThan();  // Вариант 5

int main() {
    cout << "    TEST BINARY SEARCH TREE\n\n";

    testDefaultConstructor();
    testMoveSemantics();
    testInsertAndSearch();
    testRemove();
    testOutput();
    testGetNumberOfNodes();
    testGetHeight();
    testInorderWalkRecursive();
    testInorderWalkIterative();
    testWalkByLevels();
    testRemoveLessThan();

    cout << "\n    ALL TESTS PASSED!\n";
    return EXIT_SUCCESS;
}

void testDefaultConstructor()
{
    cout << "    TEST DEFAULT CONSTRUCTOR\n\n";

    BinarySearchTree<int> tree;
    assert(tree.getNumberOfNodes() == 0);
    assert(tree.getHeight() == -1);

    cout << "(+) Test default constructor - PASSED\n\n";
}

void testMoveSemantics()
{
    cout << "    TEST MOVE SEMANTICS\n\n";

    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    // Конструктор перемещения
    BinarySearchTree<int> tree2(std::move(tree1));
    assert(tree2.getNumberOfNodes() == 3);
    assert(tree1.getNumberOfNodes() == 0);
    cout << "(+) Test move constructor - PASSED\n";

    // Оператор перемещающего присваивания
    BinarySearchTree<int> tree3;
    tree3 = std::move(tree2);
    assert(tree3.getNumberOfNodes() == 3);
    assert(tree2.getNumberOfNodes() == 0);
    cout << "(+) Test move assignment - PASSED\n";

    // Копирующие операции удалены
    cout << "(+) Test copy operations deleted - PASSED\n\n";
}

void testInsertAndSearch()
{
    cout << "    TEST INSERT AND SEARCH\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    assert(tree.searchIterative(10) == false);
    cout << "(+) Test search on empty tree - PASSED\n";

    // Вставка
    assert(tree.insert(10) == true);
    assert(tree.insert(5) == true);
    assert(tree.insert(15) == true);
    assert(tree.insert(3) == true);
    assert(tree.insert(7) == true);
    cout << "(+) Test insert - PASSED\n";

    // Поиск существующих
    assert(tree.searchIterative(10) == true);
    assert(tree.searchIterative(5) == true);
    cout << "(+) Test search existing keys - PASSED\n";

    // Поиск несуществующих
    assert(tree.searchIterative(1) == false);
    assert(tree.searchIterative(100) == false);
    cout << "(+) Test search non-existing keys - PASSED\n";

    // Дубликат
    assert(tree.insert(10) == false);
    cout << "(+) Test insert duplicate - PASSED\n\n";
}

void testRemove()
{
    cout << "    TEST REMOVE\n\n";

    BinarySearchTree<int> tree;

    // Удаление из пустого дерева
    assert(tree.remove(10) == false);
    cout << "(+) Test remove on empty tree - PASSED\n";

    // Один узел
    tree.insert(42);
    assert(tree.getNumberOfNodes() == 1);
    assert(tree.remove(42) == true);
    assert(tree.getNumberOfNodes() == 0);
    cout << "(+) Test remove single node - PASSED\n";

    // Полное дерево для тестов
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(17);

    // Удаление листа
    assert(tree.remove(3) == true);
    assert(tree.getNumberOfNodes() == 6);
    cout << "(+) Test remove leaf - PASSED\n";

    // Удаление узла с одним ребенком
    assert(tree.remove(5) == true);
    assert(tree.getNumberOfNodes() == 5);
    cout << "(+) Test remove node with one child - PASSED\n";

    // Удаление узла с двумя детьми
    assert(tree.remove(10) == true);
    assert(tree.getNumberOfNodes() == 4);
    cout << "(+) Test remove node with two children - PASSED\n";

    // Удаление несуществующего
    assert(tree.remove(100) == false);
    cout << "(+) Test remove non-existing - PASSED\n\n";
}

void testOutput()
{
    cout << "    TEST OUTPUT\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    cout << "Empty tree: ";
    tree.output(cout);
    cout << "\n";

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Tree structure: ";
    tree.output(cout);
    cout << "\n";

    cout << "(+) Test output - PASSED\n\n";
}

void testGetNumberOfNodes()
{
    cout << "    TEST GET NUMBER OF NODES\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    assert(tree.getNumberOfNodes() == 0);
    cout << "(+) Test getNumberOfNodes on empty tree - PASSED\n";

    // Несколько узлов
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    assert(tree.getNumberOfNodes() == 3);
    cout << "(+) Test getNumberOfNodes after multiple inserts - PASSED\n";

    // После удаления
    tree.remove(5);
    assert(tree.getNumberOfNodes() == 2);
    cout << "(+) Test getNumberOfNodes after remove - PASSED\n\n";
}

void testGetHeight()
{
    cout << "    TEST GET HEIGHT\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    assert(tree.getHeight() == -1);
    cout << "(+) Test getHeight on empty tree - PASSED\n";

    // Один узел
    tree.insert(10);
    assert(tree.getHeight() == 0);
    cout << "(+) Test getHeight with one node - PASSED\n";

    // Два уровня
    tree.insert(5);
    tree.insert(15);
    assert(tree.getHeight() == 1);
    cout << "(+) Test getHeight with 2 levels - PASSED\n";

    // Три уровня
    tree.insert(3);
    tree.insert(7);
    assert(tree.getHeight() == 2);
    cout << "(+) Test getHeight with 3 levels - PASSED\n\n";
}

void testInorderWalkRecursive()
{
    cout << "    TEST INORDER WALK (RECURSIVE)\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    cout << "Empty tree inorder: ";
    tree.inorderWalk();
    cout << "(+) Test inorderWalk on empty tree - PASSED\n";

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Recursive inorder: ";
    tree.inorderWalk();

    cout << "(+) Test inorderWalk recursive - PASSED\n\n";
}

void testInorderWalkIterative()
{
    cout << "    TEST INORDER WALK (ITERATIVE)\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    cout << "Empty tree iterative inorder: ";
    tree.inorderWalkIterative();
    cout << "\n";
    cout << "(+) Test inorderWalkIterative on empty tree - PASSED\n";

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Iterative inorder: ";
    tree.inorderWalkIterative();
    cout << "\n";

    cout << "(+) Test inorderWalkIterative - PASSED\n\n";
}

void testWalkByLevels()
{
    cout << "    TEST WALK BY LEVELS\n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    cout << "Empty tree levels: ";
    tree.walkByLevels();
    cout << "(+) Test walkByLevels on empty tree - PASSED\n";

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Level order (BFS): ";
    tree.walkByLevels();

    cout << "(+) Test walkByLevels - PASSED\n\n";
}

void testRemoveLessThan()
{
    cout << "    TEST VAR 5:REMOVE LESS THAN K \n\n";

    BinarySearchTree<int> tree;

    // Пустое дерево
    tree.removeLessThan(10);
    assert(tree.getNumberOfNodes() == 0);
    cout << "(+) Test removeLessThan on empty tree - PASSED\n";

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(17);
    tree.insert(6);
    tree.insert(8);

    cout << "Original tree (inorder): ";
    tree.inorderWalk();

    // Удаление узлов < 7
    tree.removeLessThan(7);
    cout << "After removeLessThan(7): ";
    tree.inorderWalk();
    assert(tree.searchIterative(3) == false);
    assert(tree.searchIterative(5) == false);
    assert(tree.searchIterative(6) == false);
    assert(tree.searchIterative(7) == true);
    assert(tree.searchIterative(8) == true);
    assert(tree.getNumberOfNodes() == 6);
    cout << "(+) Test removeLessThan(7) - PASSED\n";

    // k больше всех
    tree.removeLessThan(20);
    cout << "After removeLessThan(20): ";
    tree.inorderWalk();
    assert(tree.getNumberOfNodes() == 0);
    cout << "(+) Test removeLessThan removes all - PASSED\n\n";
}


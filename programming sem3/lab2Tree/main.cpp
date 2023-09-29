#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "ThreadBST.h"


// Тест конструктора по умолчанию
TEST(ThreadSafeBSTTest, DefaultConstructor) {
ThreadSafeBST<int> tree;
// Проверяем, что дерево пустое
ASSERT_TRUE(tree.find(42) == false);
}

// Тест вставки элемента и поиска
TEST(ThreadSafeBSTTest, InsertAndFind) {
ThreadSafeBST<int> tree;
tree.insert(42);
// Проверяем, что элемент 42 присутствует в дереве
ASSERT_TRUE(tree.find(42) == true);
// Проверяем, что другой элемент 24 отсутствует в дереве
ASSERT_TRUE(tree.find(24) == false);
}

// Тест удаления элемента
TEST(ThreadSafeBSTTest, Remove) {
ThreadSafeBST<int> tree;
tree.insert(42);
tree.remove(42);
// Проверяем, что элемент 42 удален из дерева
ASSERT_TRUE(tree.find(42) == false);
}

// Тест оператора <<
TEST(ThreadSafeBSTTest, OperatorStream) {
ThreadSafeBST<int> tree;
tree.insert(42);
tree.insert(24);
std::stringstream ss;
ss << tree;
// Проверяем, что оператор << выводит элементы дерева в правильном порядке
ASSERT_EQ(ss.str(), "24 42 ");
}

int main(int argc, char**argv) {
    ThreadSafeBST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::vector<int> postorderResult;
    tree.postorderTraversal(postorderResult);

    for (const int& value : postorderResult) {
        std::cout << value << " ";
    }
    testing::InitGoogleTest(&argc,argv);
// Вывод: 2 4 3 6 8 7 5
    return RUN_ALL_TESTS();
}

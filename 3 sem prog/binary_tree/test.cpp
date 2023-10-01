#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "binary_tree.hpp"
#include <vector>

class TestClass {
    private:
        int value;
    public:
        TestClass(const int& val) { value = val; }
        int get() { return value; }
        friend bool operator<(const TestClass& left, const TestClass& right) { return left.value < right.value; }
        friend bool operator>(const TestClass& left, const TestClass& right) { return left.value > right.value; }
        friend bool operator<=(const TestClass& left, const TestClass& right) { return left.value <= right.value; }
        friend bool operator==(const TestClass& left, const TestClass& right) { return left.value == right.value; }
        friend bool operator!=(const TestClass& left, const TestClass& right) { return left.value != right.value; }
};

TEST(TreeTest, intItitializerListConstructor) {
    ThreadTree<int> tree {3, 5, 13, 26, 2, 4, 12, 7};
    std::vector<int> v = {2, 3, 4, 5, 7, 12, 13, 26};
    EXPECT_EQ(v, tree.lkp());
}

TEST(TreeTest, doubleCopyAndDefaultConstructor) {
    ThreadTree<double> tree {3.34, 5.567, 13.12, 26.98, 2.5, 4.3, 12.1, 7.78};
    ThreadTree<double> tree2(tree);
    EXPECT_TRUE(tree == tree2);
    ThreadTree<double> tree3;
    tree3.add(tree);
    tree3.add(35.23);
    EXPECT_FALSE(tree3 == tree);
}

TEST(TreeTest, classIteratorConstructor) {
    std::vector<TestClass> v = {TestClass(200), TestClass(5), TestClass(250)};
    ThreadTree<TestClass> tree (v.begin(), v.end());
    EXPECT_TRUE(tree.find(TestClass(5)));
    ThreadTree<TestClass> tree2(tree.findTree(TestClass(200)));
    EXPECT_TRUE(tree2 == tree);
}

TEST(TreeTest, intMoveConstuctor) {
    ThreadTree<int> tree {3, 5, 13, 26, 2, 4, 12, 7};
    tree.remove(26);
    std::vector<int> v = {2, 3, 4, 5, 7, 12, 13};
    EXPECT_EQ(v, tree.lkp());
    ThreadTree<int> tree2(std::move(tree));
    tree2.clear();
    EXPECT_TRUE(tree == tree2);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
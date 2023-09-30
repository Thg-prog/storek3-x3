#include "Tree.hpp"
#include <thread>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

TEST(TreeTest, AddTests){
    laba2::Tree<int> tree;
    tree.add(2);
    tree.add(1);
    tree.add(4);
    tree.add(3);
    std::vector<int> vec = tree.LKP();
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    laba2::Tree<int> subtree(tree);
    subtree.add(tree);
    int i = 6;
    subtree << i;
    std::vector<int> vec2 = subtree.LKP();
    EXPECT_EQ(vec2.at(0), 1);
    EXPECT_EQ(vec2.at(1), 1);
    EXPECT_EQ(vec2.at(2), 2);
    EXPECT_EQ(vec2.at(3), 2);
    EXPECT_EQ(vec2.at(4), 3);
    EXPECT_EQ(vec2.at(5), 3);
    EXPECT_EQ(vec2.at(6), 4);
    EXPECT_EQ(vec2.at(7), 4);
    EXPECT_EQ(vec2.at(8), 6);
}

TEST(TreeTest, Equal_Test){
    laba2::Tree<double> tree;
    tree.add(2.6);
    tree.add(3.0);
    laba2::Tree<double> tree2(tree);
    EXPECT_TRUE(tree == tree2);
}

TEST(TreeTest, DeleteTest){
    laba2::Tree<int> tree;
    tree.add(2);
    tree.add(4);
    int i = 2;
    tree.deleteNode(i);
    std::vector<int> vec1 = tree.LKP();
    EXPECT_EQ(vec1.at(0), 4);
}

class TestClass{
    private:
        int cur;
    public:
        TestClass(int value){
            cur = value;
        }
        
        int getValue(){
            return cur;
        }

        friend bool operator<(const TestClass& left, const TestClass& right){
            return left.cur < right.cur;
        }
        friend bool operator>(const TestClass& left, const TestClass& right){
            return left.cur > right.cur;
        }

        friend bool operator<=(const TestClass& left, const TestClass& right){
            return left.cur <= right.cur;
        }
        
        friend bool operator==(const TestClass& left, const TestClass& right){
            return left.cur == right.cur;
        }
        friend bool operator!=(const TestClass& left, const TestClass& right){
            return left.cur != right.cur;
        }
};

TEST(TreeTest, ClassTest){
    laba2::Tree<TestClass> tree{TestClass(1), TestClass(10), TestClass(0)};
    std::vector<TestClass> vec1 = tree.LKP();
    EXPECT_EQ(vec1.at(0).getValue(), 0);
}

template <typename T>
void thread_func_test(laba2::Tree<T>& tree, int num1, int num2){
    std::cout << "Thread launched" << std::endl;
    for(int i = num1; i <= num2; i++){
        tree.add(i);
    }
    for(int i = num1; i <= num2; i++){
        if(i%4==0){
            tree.deleteNode(i);
        }
    }
}

int main(int argc, char** argv){
    ::benchmark::Initialize(&argc, argv);
    
    ::benchmark::RunSpecifiedBenchmarks();

    ::testing::InitGoogleTest(&argc, argv);    


    laba2::Tree<int> tree;
    
    std::thread thread_1([&tree](){thread_func_test(tree, 0, 50);});
    std::thread thread_2([&tree](){thread_func_test(tree, 51, 100);});
    thread_1.join();
    thread_2.join();

    std::cout << "Tree:" << tree << std::endl;


    return RUN_ALL_TESTS();
}
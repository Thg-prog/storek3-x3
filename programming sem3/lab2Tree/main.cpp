#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include<benchmark/benchmark.h>
#include "ThreadBST.h"


//// Тест конструктора по умолчанию
//TEST(ThreadSafeBSTTest, DefaultConstructor) {
//ThreadSafeBST<int> tree;
//// Проверяем, что дерево пустое
//ASSERT_TRUE(tree.find(42) == false);
//}
//
//// Тест вставки элемента и поиска
//TEST(ThreadSafeBSTTest, InsertAndFind) {
//ThreadSafeBST<int> tree;
//tree.insert(42);
//// Проверяем, что элемент 42 присутствует в дереве
//ASSERT_TRUE(tree.find(42) == true);
//// Проверяем, что другой элемент 24 отсутствует в дереве
//ASSERT_TRUE(tree.find(24) == false);
//}
//
//// Тест удаления элемента
//TEST(ThreadSafeBSTTest, Remove) {
//ThreadSafeBST<int> tree;
//tree.insert(42);
//tree.remove(42);
//// Проверяем, что элемент 42 удален из дерева
//ASSERT_TRUE(tree.find(42) == false);
//}
//
//// Тест оператора <<
//TEST(ThreadSafeBSTTest, OperatorStream) {
//ThreadSafeBST<int> tree;
//tree.insert(42);
//tree.insert(24);
//std::stringstream ss;
//ss << tree;
//// Проверяем, что оператор << выводит элементы дерева в правильном порядке
//ASSERT_EQ(ss.str(), "24 42 ");
//}
//
//
/////бенчмарки
//
//static void BM_Insert(benchmark::State& state) {
//    ThreadSafeBST<int> tree;
//    for (auto _ : state) {
//        tree.insert(rand());
//    }
//}
//BENCHMARK(BM_Insert);
//
//static void BM_Find(benchmark::State& state) {
//    ThreadSafeBST<int> tree;
//    for (int i = 0; i < 10000; ++i) {
//        tree.insert(i);
//    }
//    for (auto _ : state) {
//        bool result = tree.find(rand() % 10000);
//        benchmark::DoNotOptimize(result);
//    }
//}
//BENCHMARK(BM_Find);
//
//class TestClass{
//private:
//    int cur;
//public:
//    TestClass(int value){
//        cur = value;
//    }
//
//    int getValue(){
//        return cur;
//    }
//
//    friend bool operator<(const TestClass& left, const TestClass& right){
//        return left.cur < right.cur;
//    }
//    friend bool operator>(const TestClass& left, const TestClass& right){
//        return left.cur > right.cur;
//    }
//
//    friend bool operator<=(const TestClass& left, const TestClass& right){
//        return left.cur <= right.cur;
//    }
//
//    friend bool operator==(const TestClass& left, const TestClass& right){
//        return left.cur == right.cur;
//    }
//    friend bool operator!=(const TestClass& left, const TestClass& right){
//        return left.cur != right.cur;
//    }
//};
//
//TEST(TreeTest, ClassTest){
//    ThreadSafeBST<TestClass> tree{TestClass(1), TestClass(10), TestClass(0)};
//    std::vector<TestClass> vec1;
//    tree.inorderTraversal(vec1);
//    EXPECT_EQ(vec1.at(0).getValue(), 0);
//}


int main(int argc, char**argv) {

//    ThreadSafeBST<int> tree;
//    tree.insert(5);
//    tree.insert(3);
//    tree.insert(7);
//    tree.insert(2);
//    tree.insert(4);
//    tree.insert(6);
//    tree.insert(8);
//
//    std::vector<int> postorderResult;
//    tree.postorderTraversal(postorderResult);
//
//    for (const int& value : postorderResult) {
//        std::cout << value << " ";
//    }
//    std::cout<<std::endl;
//    ThreadSafeBST<double> tree1;
//    tree1.insert(5.6);
//    tree1.insert(3.6);
//    tree1.insert(7.6);
//    tree1.insert(2.6);
//    tree1.insert(4.6);
//    tree1.insert(6.6);
//    tree1.insert(8.6);
//
//    std::vector<double> postorderResult1;
//    tree1.postorderTraversal(postorderResult1);
//
//    for (const double& value : postorderResult1) {
//        std::cout << value << " ";
//    }
//    std::cout<<std::endl;
//
//// Вывод: 2 4 3 6 8 7 5
//    ::benchmark::Initialize(&argc,argv);
//    ::benchmark::RunSpecifiedBenchmarks();


    ThreadSafeBST<int> tree({10,4,45,2,7,12,56});
    ThreadSafeBST<int> tree2 =std::move(tree);
    //std::cout<<tree2;

    tree2.remove(10);
    std::cout << tree2;
//    testing::InitGoogleTest(&argc,argv);
//    return RUN_ALL_TESTS();
}

#include "Tree.hpp"
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
    std::vector<int> vec2 = subtree.LKP();
    EXPECT_EQ(vec2.at(0), 1);
    EXPECT_EQ(vec2.at(1), 1);
    EXPECT_EQ(vec2.at(2), 2);
    EXPECT_EQ(vec2.at(3), 2);
    EXPECT_EQ(vec2.at(4), 3);
    EXPECT_EQ(vec2.at(5), 3);
    EXPECT_EQ(vec2.at(6), 4);
    EXPECT_EQ(vec2.at(7), 4);
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

int main(int argc, char** argv){
    ::benchmark::Initialize(&argc, argv);
    
    ::benchmark::RunSpecifiedBenchmarks();

    ::testing::InitGoogleTest(&argc, argv);    


    return RUN_ALL_TESTS();
}
#include "stack.hpp"
#include "string"
#include <stack>

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
//-lbenchmark

TEST(StackTest, pushpop_test){
        laba::Stack<int> stack;
        stack.push(12);
        EXPECT_EQ(stack.size(), 1);
        int a = stack.check_pop();
        EXPECT_EQ(a, 12);
        EXPECT_EQ(stack.size(), 1);
        stack.pop();
        EXPECT_EQ(stack.size(), 0);
    }

TEST(StackTest, structure_test){
    struct teststr{
        int a;
        float b;
        std::string c;
    };
    teststr test;
    test.a = 10;
    test.b = 1.6f;
    test.c = "Влад не умеет писать код)";
    laba::Stack<teststr> stack;
    stack.push(test);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.check_pop().b, 1.6f);
    EXPECT_EQ(stack.check_pop().c, "Влад не умеет писать код)");

}

TEST(StackTest, Copy_Constructor_test){
    laba::Stack<int> stack1;
    stack1.push(10);
    laba::Stack<int> stack2(stack1);
    EXPECT_EQ(stack1.size(), 1);
    EXPECT_EQ(stack1.check_pop(), 10);
    EXPECT_EQ(stack2.size(), 1);
    EXPECT_EQ(stack2.check_pop(), 10);
    laba::Stack<int> stack3;
    stack3 = stack2;
    EXPECT_EQ(stack3.size(), 1);
    EXPECT_EQ(stack3.check_pop(), 10);
}

TEST(StackTest, Move_Operator_test){
    laba::Stack<int> stack1;
    stack1.push(10);
    laba::Stack<int> stack2;
    stack2 = std::move(stack1);
    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack2.check_pop(), 10);
}

TEST(StackTest, Itterator_Constructor_test){
    std::vector<float> vec = {1.0, 1.2, 1.3, 1.6, 1.8};
    laba::Stack<float> stack(vec.begin(), vec.end());
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.check_pop(), 1);
    stack.push(2.0);
    EXPECT_EQ(stack.size(), 6);
    EXPECT_EQ(stack.check_pop(), 2.0);
}

TEST(StackTest, operators_test){
    laba::Stack<int> stack1;
    stack1.push(4);
    int r;
    stack1 >> r;
    EXPECT_EQ(stack1.size(), 0);
    stack1 << 4;
    EXPECT_EQ(stack1.size(), 1);
    EXPECT_EQ(stack1.check_pop(), 4);
    laba::Stack<int> stack2;
    stack2 << 4;
    EXPECT_TRUE(stack1 == stack2);
    stack2 << 5 << 6;
    EXPECT_FALSE(stack1==stack2);
    EXPECT_EQ(stack2.pop(), 6);
    EXPECT_EQ(stack2.pop(), 5);
    EXPECT_EQ(stack2.pop(), 4);
}

TEST(StackTest, clear_test){
    laba::Stack<float> stack;
    stack.push(2.0f);
    stack.push(0.5f);
    EXPECT_EQ(stack.size(), 2);
    stack.clear();
    stack.push(3.0f);
    stack.push(4.0f);

    EXPECT_EQ(stack.check_pop(), 4.0f);
}

TEST(StackTest, const_test){
    std::initializer_list<float> list({1,2.4,5.6});
    const laba::Stack<float> stack(list);
    EXPECT_EQ(stack.check_pop(),1);
}


//БЕНЧМАРКИ

static void BM_MY_STACK_PUSH(benchmark::State& state){
    laba::Stack<int> stack;
    for(auto _:state)stack.push(10);
}

BENCHMARK(BM_MY_STACK_PUSH);


static void BM_STD_STACK_PUSH(benchmark::State& state){
     std::stack<int> stack;
     for(auto _ :state)stack.push(10);
}

BENCHMARK(BM_STD_STACK_PUSH);

static void BM_STD_STACK_POP(benchmark::State& state){
    std::stack<int> stack;
    for(auto _:state)stack.push(10);
    for(auto _:state)stack.pop();
}

BENCHMARK(BM_STD_STACK_POP);

static void BM_MY_STACK_POP(benchmark::State& state){
    laba::Stack<int> stack;
    for(auto _:state)stack.push(10);
    for(auto _:state)stack.pop();
}

BENCHMARK(BM_MY_STACK_POP);

static void BM_MY_STACK_SIZE(benchmark::State& state){
    laba::Stack<int> stack;
    for(auto _:state)stack.push(20);
    for(auto _:state)stack.size();
}
BENCHMARK(BM_MY_STACK_SIZE);

static void BM_STD_STACK_SIZE(benchmark::State& state){
    std::stack<int> stack;
    for(auto _:state)stack.push(20);
    for(auto _:state)stack.size();
}
BENCHMARK(BM_STD_STACK_SIZE);

static void BM_STD_STACK_CONSTRUCTOR(benchmark::State& state){
    for(auto _: state)std::stack<int> stack({1, 2, 3});
}

BENCHMARK(BM_STD_STACK_CONSTRUCTOR);

static void BM_MY_STACK_CONSTRUCTOR(benchmark::State& state){
    std::initializer_list<int> list({1,2,3});
    for(auto _: state)laba::Stack<int> stack(list);
}

BENCHMARK(BM_MY_STACK_CONSTRUCTOR);


int main(int argc, char** argv){

    ::benchmark::Initialize(&argc, argv);
    
    ::benchmark::RunSpecifiedBenchmarks();

    ::testing::InitGoogleTest(&argc, argv);


    try{
        std::vector<int> datas = {22,31,4};
        laba::Stack<int> itStack(datas.end(), datas.begin());
        std::cout << "stack itter:\n " << itStack << std::endl;
    }catch(laba::Stack_Exception e){
        std::cout << "\nError\n";
    }
    
    //try{
    //cout << st.pop();
    //cout << st.pop();
//
    //}catch(Stack_Exception e){
    //    cout << "ERROR";
    //}
    return RUN_ALL_TESTS();
}
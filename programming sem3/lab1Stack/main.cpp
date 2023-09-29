#include <iostream>
#include "Stack.h"
#include <stack>
#include <benchmark/benchmark.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct MyStruct{
    int a;
    int b;
    friend std::ostream& operator<<(std::ostream& os, const MyStruct& mystruct){
        os<<"value a:"<<mystruct.a<<", value b:"<<mystruct.b;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, MyStruct mystruct){
        std::cout<<"Enter value a:";
        is>>mystruct.a;
        std::cout<<"Enter value b:";
        is>>mystruct.b;
        return is;
    }
};

static void BM_MyStackPush(benchmark::State& state) {
    Stack<int> stack;
    for (auto _ : state) {
        stack.push(42);
    }
}
BENCHMARK(BM_MyStackPush);

static void BM_StdStackPush(benchmark::State& state) {
    std::stack<int> stack;
    for (auto _ : state) {
        stack.push(42);
    }
}
BENCHMARK(BM_StdStackPush);

static void BM_MyStackPop(benchmark::State& state) {
    Stack<int> stack;
    Stack<MyStruct> struckt;
    MyStruct rr;
    rr.a=9;
    rr.b=8;
    for (auto _ : state) {
        struckt.push(rr);
        stack.push(42);
    }
    for (auto _ : state) {
        struckt.pop();
        stack.pop();
    }
}
BENCHMARK(BM_MyStackPop);

static void BM_StdStackPop(benchmark::State& state) {
    std::stack<int> stack;
    for (auto _: state) {
        stack.push(42);
    }
    for (auto _ : state) {
        stack.pop();
    }
}
BENCHMARK(BM_StdStackPop);

TEST(StackTest, PushPopTest) {
    Stack<int> stack;
    Stack<int>stack2;
    stack2<<42<<32;
    EXPECT_EQ(stack2.size(),2);
    int a,b;
    stack2>>a>>b;
    EXPECT_EQ(stack2.size(),0);
    EXPECT_EQ(stack2.empty(), true);
    stack.push(42);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.check_pop(),42);
    EXPECT_EQ(stack.empty(),false);
    stack.pop();
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, CopyConstructorTest) {
    Stack<int> stack1;
    stack1.push(42);
    Stack<int> stack2 = stack1; // Используем конструктор копирования
    EXPECT_EQ(stack2.size(), 1);
    stack2.pop();
    EXPECT_TRUE(stack2.empty());
    EXPECT_EQ(stack1.size(), 1); // Проверка, что оригинальный стек не изменился
}

int main(int argc, char**argv) {
    std::cout << "Hello, World!" << std::endl;
    Stack<int>stack1 = {1,2,3};
    Stack<int>stack2;
    stack1.push(12);
    stack1<<52<<24;
    std::cout<<stack1<<std::endl;
    int value;
    int value2;
    stack1<<value<<value2;
    std::cout<<stack1<<std::endl;
    std::cout<<stack1.check_pop()<<std::endl;
    std::cout<<"Are stacks equal"<<(stack1==stack2) <<" Are they not equal"<< (stack1!=stack2)<<std::endl;
    //stack2.pop();
    std::cout<<stack1.size()<<std::endl;
    stack1 = std::move(stack2);
    std::cout<<"First stack:"<<stack1<<std::endl;
    std::cout<<"Is stacks equal"<<(stack1==stack2) <<" Are they not equal"<< (stack1!=stack2)<<std::endl;

    Stack<MyStruct> MyStructStack;
    MyStruct rr;
    rr.a=9;
    rr.b=8;
    MyStructStack.push(rr);
    rr.a=10;
    rr.b=8;
    MyStructStack.push(rr);
    std::cout<<"Stack elements for struct stack"<<std::endl;
    while(!MyStructStack.empty()){
        MyStruct tmpStruct;
        MyStructStack.swap(tmpStruct);
        std::cout<<"element №..\n"<<tmpStruct<<std::endl;
        MyStructStack.pop();
    }

    Stack<double>doubleStack{13.0,78.9,79.980979};
    std::cout<<doubleStack<<std::endl;
    doubleStack.push(1237.51);
    std::cout<<doubleStack<<std::endl;

    Stack<std::string>stringStack{"hello","world","it's", "me"};
    std::cout<<stringStack<<std::endl;
    std::string str="Julia";
    stringStack.swap(str);
    std::cout<<"My stack "<<stringStack<<std::endl;
    std::cout<<str<<std::endl;
//    std::cout<<str<<std::endl;

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

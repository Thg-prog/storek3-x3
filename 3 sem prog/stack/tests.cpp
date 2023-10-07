#include <iostream>
#include "stack.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

struct someStruct {
    private:
        int val1;
        double val2;
        std::string val3;
    public:
        someStruct() = default;
        someStruct(int val1, double val2, std::string val3);
        someStruct& operator=(const someStruct& st);
        bool operator==(const someStruct& st) const;
        bool operator!=(const someStruct& st) const;
        friend std::ostream& operator<<(std::ostream& out, const someStruct& s);
};

someStruct::someStruct(int val1, double val2, std::string val3) {
    this->val1 = val1;
    this->val2 = val2;
    this->val3 = val3;
}

someStruct& someStruct::operator=(const someStruct& st) {
    val1 = st.val1;
    val2 = st.val2;
    val3 = st.val3;
    return *this;
}

bool someStruct::operator==(const someStruct& st) const {
    return st.val1 == val1 && st.val2 == val2 && st.val3 == val3;
}

bool someStruct::operator!=(const someStruct& st) const {
    return !(*this == st);
}

inline std::ostream& operator<<(std::ostream& out, const someStruct& s) {
    return out << "{ " << s.val1 << "; " << s.val2 << "; " << s.val3 << " }";
}

// тестирование push, pop и конструктора по умолчанию на типе int
TEST(StackTest, PushInt) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(2, stack.pop());
    EXPECT_EQ(1, stack.pop());
    EXPECT_THROW(stack.check_pop(), std::underflow_error);
}

// тестирование push, pop и конструктора по умолчанию на типе double
TEST(StackTest, PushDouble) {
    Stack<double> stack;
    stack.push(1.36363);
    stack.push(2.1232);
    stack.push(3.00012);

    EXPECT_EQ(3.00012, stack.pop());
    EXPECT_EQ(2.1232, stack.pop());
    EXPECT_EQ(1.36363, stack.pop());
    EXPECT_THROW(stack.check_pop(), std::underflow_error);
}

// тестирование push, pop и конструктора по умолчанию на типе string
TEST(StackTest, PushString) {
    Stack<std::string> stack;
    stack.push("строка 1");
    stack.push("строка 2");
    stack.push("строка 3");

    EXPECT_EQ("строка 3", stack.pop());
    EXPECT_EQ("строка 2", stack.pop());
    EXPECT_EQ("строка 1", stack.pop());
    EXPECT_THROW(stack.check_pop(), std::underflow_error);
}

// тестирование push, pop и конструктора по умолчанию на struct
TEST(StackTest, PushStruct) {
    Stack<someStruct> stack;
    someStruct st(1, 2.5, "строка");
    stack.push(st);
    EXPECT_EQ(st, stack.pop());
    EXPECT_THROW(stack.check_pop(), std::underflow_error);
}

// тестирование конструктора копирования и check_pop на типе int
TEST(StackTest, copyConstuctorInt) {
    Stack<int> stack;
    stack.push(1);
    const Stack<int> stack2(stack);
    EXPECT_EQ(1, stack2.check_pop());
}

// тестирование конструктора копирования и check_pop на типе double
TEST(StackTest, copyConstuctorDouble) {
    Stack<double> stack;
    stack.push(3.578);
    const Stack<double> stack2(stack);
    EXPECT_EQ(3.578, stack2.check_pop());
}

// тестирование конструктора копирования и check_pop на типе string
TEST(StackTest, copyConstuctorString) {
    Stack<std::string> stack;
    stack.push("строка 1");
    const Stack<std::string> stack2(stack);
    EXPECT_EQ("строка 1", stack2.check_pop());
}

// тестирование конструктора копирования и check_pop на struct
TEST(StackTest, copyConstuctorStruct) {
    Stack<someStruct> stack;
    someStruct st(1, 2.5, "строка");
    stack.push(st);
    const Stack<someStruct> stack2(stack);
    EXPECT_EQ(stack.check_pop(), stack2.check_pop());
}

// тестирование конструктора перемещения, операторов <<, >> и isEmpty на типе int
TEST(StackTest, moveConstructorInt) {
    Stack<int> stack;
    stack << 1;
    Stack<int> stack2(std::move(stack));
    EXPECT_TRUE(stack.isEmpty());
    int val;
    stack2 >> val;
    EXPECT_EQ(1, val);
    EXPECT_TRUE(stack2.isEmpty());
}

// тестирование конструктора перемещения, операторов <<, >> и isEmpty на типе double
TEST(StackTest, moveConstructorDouble) {
    Stack<double> stack;
    stack << 3.9834;
    Stack<double> stack2(std::move(stack));
    EXPECT_TRUE(stack.isEmpty());
    double val;
    stack2 >> val;
    EXPECT_EQ(3.9834, val);
    EXPECT_TRUE(stack2.isEmpty());
}

// тестирование конструктора перемещения, операторов <<, >> и isEmpty на типе string
TEST(StackTest, moveConstructorString) {
    Stack<std::string> stack;
    stack << "строка 1";
    Stack<std::string> stack2(std::move(stack));
    EXPECT_TRUE(stack.isEmpty());
    std::string val;
    stack2 >> val;
    EXPECT_EQ("строка 1", val);
    EXPECT_TRUE(stack2.isEmpty());
}

// тестирование конструктора перемещения, операторов <<, >> и isEmpty на struct
TEST(StackTest, moveConstructorStruct) {
    Stack<someStruct> stack;
    someStruct st(1, 2.5, "строка");
    stack << st;
    Stack<someStruct> stack2(std::move(stack));
    EXPECT_TRUE(stack.isEmpty());
    someStruct val;
    stack2 >> val;
    EXPECT_EQ(st, val);
    EXPECT_TRUE(stack2.isEmpty());
}

// тестирование конструктора со списком инициализации и getSize на типе int
TEST(StackTest, initializerConstructorInt) {
    const Stack<int> stack{1, 2, 3};
    EXPECT_EQ(3, stack.getSize());
}

// тестирование конструктора со списком инициализации и getSize на типе double
TEST(StackTest, initializerConstructorDouble) {
    Stack<double> stack{1.5, 2.099, 3.123};
    EXPECT_EQ(3, stack.getSize());
}

// тестирование конструктора со списком инициализации и getSize на типе string
TEST(StackTest, initializerConstructorString) {
    Stack<std::string> stack{"строка1", "строка2", "строка3"};
    EXPECT_EQ(3, stack.getSize());
}

// тестирование конструктора со списком инициализации и getSize на struct
TEST(StackTest, initializerConstructorStruct) {
    someStruct st(1, 2.5, "строка3");
    Stack<someStruct> stack{st};
    EXPECT_EQ(1, stack.getSize());
}

// тестирование конструктора с итератором и clear на типе int
TEST(StackTest, iteratorConstructorInt) {
    std::vector<int> v {1, 2, 3};
    Stack<int> stack(v.begin(), v.end());
    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(2, stack.pop());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

// тестирование конструктора с итератором и clear на типе double
TEST(StackTest, iteratorConstructorDouble) {
    std::vector<double> v {1.123, 2.56, 3.5};
    Stack<double> stack(v.begin(), v.end());
    EXPECT_EQ(3.5, stack.pop());
    EXPECT_EQ(2.56, stack.pop());
    EXPECT_EQ(1.123, stack.pop());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

// тестирование конструктора с итератором и clear на типе string
TEST(StackTest, iteratorConstructorString) {
    std::vector<std::string> v {"строка1", "строка2", "строка3"};
    Stack<std::string> stack(v.begin(), v.end());
    EXPECT_EQ("строка3", stack.pop());
    EXPECT_EQ("строка2", stack.pop());
    EXPECT_EQ("строка1", stack.pop());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

// тестирование конструктора с итератором и clear на struct
TEST(StackTest, iteratorConstructorStruct) {
    someStruct st1(1, 2.5, "строка1");
    someStruct st2(1, 2.5, "строка1");
    someStruct st3(1, 2.5, "строка1");
    std::vector<someStruct> v {st1, st2, st3};
    Stack<someStruct> stack(v.begin(), v.end());
    EXPECT_EQ(st1, stack.pop());
    EXPECT_EQ(st2, stack.pop());
    EXPECT_EQ(st3, stack.pop());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

// тестирование оператора присваивания(копирования) и top на типе int
TEST(StackTest, copyInt) {
    Stack<int> stack = std::initializer_list{1, 2, 3};
    stack.top(4);
    EXPECT_EQ(4, stack.pop());
}

// тестирование оператора присваивания(копирования) и top на типе double
TEST(StackTest, copyDouble) {
    Stack<double> stack = std::initializer_list{1.5, 2.123, 3.456};
    stack.top(4.6);
    EXPECT_EQ(4.6, stack.pop());
}

// тестирование оператора присваивания(копирования) и top на типе string
TEST(StackTest, copyString) {
    Stack<std::string> stack = Stack<std::string>({"строка1", "строка2", "строка3"});
    stack.top("строка4");
    EXPECT_EQ("строка4", stack.pop());
}

// тестирование оператора присваивания(копирования) и top на struct
TEST(StackTest, copyStruct) {
    someStruct st(1, 1.5, "строка");
    Stack<someStruct> stack = Stack<someStruct>({st});
    someStruct st2(1, 2.45, "строка1");
    stack.top(st2);
    EXPECT_EQ(st2, stack.pop());
}

// тестирование оператора присваивания(перемещения) и swap на типе int
TEST(StackTest, moveInt) {
    Stack<int> stack = std::move(Stack<int>({1, 2, 3}));
    int buf = 4;
    stack.swap(buf);
    EXPECT_EQ(4, stack.pop());
    EXPECT_EQ(3, buf);
}

// тестирование оператора присваивания(перемещения) и swap на типе double
TEST(StackTest, moveDouble) {
    Stack<double> stack = std::move(Stack<double>({1.5, 2.123, 3.456}));
    double buf = 4.5;
    stack.swap(buf);
    EXPECT_EQ(4.5, stack.pop());
    EXPECT_EQ(3.456, buf);
}

// тестирование оператора присваивания(перемещения) и swap на типе string
TEST(StackTest, moveString) {
    Stack<std::string> stack = std::move(Stack<std::string>({"строка1", "строка2", "строка3"}));
    std::string buf = "строка4";
    stack.swap(buf);
    EXPECT_EQ("строка4", stack.pop());
    EXPECT_EQ("строка3", buf);
}

// тестирование оператора присваивания(перемещения) и swap на struct
TEST(StackTest, moveStruct) {
    someStruct st(1, 1.5, "строка");
    Stack<someStruct> stack = std::move(Stack<someStruct>({st}));
    someStruct buf(1, 2.33, "строка2");
    someStruct st2 = buf;
    stack.swap(buf);
    EXPECT_EQ(st2, stack.pop());
}

// тестирование равенства и неравенства стеков на типе int
TEST(StackTest, EqualityAndInequalityInt) {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2;
    stack2.push(1);
    stack2.push(2);
    stack2.push(3);

    Stack<int> stack3;
    stack3.push(4);
    stack3.push(5);

    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);

    EXPECT_FALSE(stack1 != stack2);
    EXPECT_TRUE(stack1 != stack3);
}

// тестирование равенства и неравенства стеков на типе double
TEST(StackTest, EqualityAndInequalityDouble) {
    Stack<double> stack1;
    stack1.push(1.5);
    stack1.push(2.6);
    stack1.push(3.123);
    Stack<double> stack2;
    stack2.push(1.5);
    stack2.push(2.6);
    stack2.push(3.123);
    Stack<double> stack3;
    stack3.push(4.99);
    stack3.push(5.01);
    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 != stack2);
    EXPECT_TRUE(stack1 != stack3);
}

// тестирование равенства и неравенства стеков на типе string
TEST(StackTest, EqualityAndInequalityString) {
    Stack<std::string> stack1;
    stack1.push("1");
    stack1.push("2");
    stack1.push("3");
    Stack<std::string> stack2;
    stack2.push("1");
    stack2.push("2");
    stack2.push("3");
    Stack<std::string> stack3;
    stack3.push("4");
    stack3.push("5");
    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 != stack2);
    EXPECT_TRUE(stack1 != stack3);
}

// тестирование равенства и неравенства стеков на struct
TEST(StackTest, EqualityAndInequalityStruct) {
    someStruct st(1, 1.45, "строка");
    Stack<someStruct> stack1({st});
    Stack<someStruct> stack2(stack1);
    someStruct st2(1, 2.45, "строка1223");
    Stack<someStruct> stack3 {st2};
    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 != stack2);
    EXPECT_TRUE(stack1 != stack3);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
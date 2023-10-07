#include <iostream>
#include "stack.hpp"
#include <new>


int main() {
    try {
        Stack<int> st;
        st.push(rand());
    } catch (const std::bad_alloc& message) {
        std::cout << message.what();
    }

    try {
        Stack<int> st;
        st << rand();
    } catch (const std::bad_alloc& message) {
        std::cout << message.what();
    }

    try {
        Stack<int> st;
        int value = rand();
        st >> value;
    } catch (std::string message) {
        std::cout << message;
    }

    try {
        Stack<int> st;
        int value = st.pop();
    } catch (std::string message) {
        std::cout << message;
    }

    try {
        Stack<int> st;
        int value = st.check_pop();
    } catch (std::string message) {
        std::cout << message;
    }

    try {
        Stack<int> st;
        st.top(rand());
    } catch (std::string message) {
        std::cout << message;
    }
    
    try {
        Stack<int> st;
        int number = rand();
        st.swap(number);
    } catch (std::string message) {
        std::cout << message;
    }
}
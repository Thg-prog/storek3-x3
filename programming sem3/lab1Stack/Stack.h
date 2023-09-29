//
// Created by Антон on 05.09.2023.
//

#ifndef LAB1STACK_STACK_H
#define LAB1STACK_STACK_H
#include <initializer_list>
#include <iostream>
#include <algorithm>//?
#include "StackExceptions.h"

template<typename T>
class Stack{
private:
    T* data;
    size_t m_stackSize;
    size_t m_currentSize;

public:
    /// конструкторы и деструктор
    Stack() ;

    Stack(const Stack& other);

    Stack(Stack&& other) noexcept;

    Stack(std::initializer_list<T> initlist);

    template<typename InpIterator>
    Stack(InpIterator begin, InpIterator end);

    ~Stack();

    ///оператор = копирования
    Stack& operator=(const Stack& other);

    ///оператор = перемещения
    Stack& operator=(Stack&& other) noexcept;

    /// требуемые методы
    void push(const T& value);

    T pop();

    T check_pop() const;

    bool empty() const noexcept;

    void clear() noexcept;

    size_t size() const noexcept;

    void top(const T& value);

    void swap(T& value);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, Stack<U>& stack);

    bool operator==(const Stack& other)const;

    bool operator!=(const Stack& other)const ;

    Stack& operator<<( const T& value);

    Stack& operator>>( T& value);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack){
    for(size_t i = 0; i<stack.m_currentSize; ++i){
        os<<stack.data[i]<<" ";
    }
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Stack<T>& stack){
    T value;
    is>>value;
    stack.push(value);
};

template<typename T>
Stack<T>::~Stack() {
    delete[] data;
}

// a
// a=b;
template<typename T>
Stack<T> &Stack<T>::operator=(Stack &&other)  noexcept{
    if(this!=&other){
        delete[] data;
        data = other.data;
        m_currentSize=other.m_currentSize;
        m_stackSize=other.m_stackSize;
        other.data = nullptr;
        other.m_currentSize=0;
        other.m_stackSize=0;
    }
    return *this;
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack &other) {
    if (this!=&other){
        delete[] data;
        m_stackSize=other.m_stackSize;
        m_currentSize=other.m_currentSize;
        data = new T[m_stackSize];
        std::copy(other.data,other.data+m_currentSize, data);
    }
    return *this;
}
template<typename T>
template<typename InpIterator>
Stack<T>::Stack(InpIterator begin, InpIterator end): m_currentSize(0){
    size_t dist= std::distance(begin,end);
    if (dist <0){
        throw stackLab::badStackSize();
    }else{
        m_stackSize = static_cast<size_t>(dist) * 2;
        data = new T[m_stackSize];
        for(InpIterator it = begin; it!=end;++it){
            data[m_currentSize++]=*it;
        }
    }
}
template<typename T>
Stack<T>::Stack(std::initializer_list<T> initlist): m_stackSize(initlist.size()), m_currentSize(initlist.size()){
    data = new T[m_stackSize];
    size_t i = 0;
    for(const T& el: initlist){
        data[i++] = el;
    }
}

template<typename T>
Stack<T>::Stack(Stack &&other) noexcept: data(other.data),m_stackSize(other.m_stackSize), m_currentSize(other.m_currentSize){
    other.data = nullptr;
}

template<typename T>
Stack<T>::Stack(const Stack &other):m_stackSize(other.m_stackSize), m_currentSize(other.m_currentSize){//?
    data = new T[m_stackSize];
    std::copy(other.data,other.data+m_currentSize,data);
}

template<typename T>
Stack<T>::Stack() : m_currentSize(0),m_stackSize(1){//?
    data =new T[m_stackSize];
}

template<typename T>
Stack<T>& Stack<T>::operator>>(T &value) {
    if(empty()){
        throw stackLab::popOutOfRange();
    }
    value = data[m_currentSize-1];
    pop();//?
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator<<(const T &value) {
    push(value);
    return *this;
}

template<typename T>
void Stack<T>::push(const T &value) {
    if(m_currentSize>=m_stackSize){
        size_t newStackSize = (m_stackSize +1)*2;
        T* newData = new T[newStackSize];
        std::copy(data, data+m_currentSize, newData);
        delete[] data;
        data = newData;
        m_stackSize = newStackSize;
    }
    data[m_currentSize++] = value;
}

template<typename T>
void Stack<T>::top(const T &value) {
    if(this->empty()) throw stackLab::badStackSize();
    data[m_currentSize-1] = value;
}

template<typename T>
void Stack<T>::swap(T &value) {
    if(this->empty()) throw stackLab::badStackSize();
    std::swap(data[m_currentSize-1], value);
}

template<typename T>
bool Stack<T>::operator==(const Stack &other) const{
    if(this==&other){
        return true;
    }else if(this->m_currentSize==other.m_currentSize){
        for(size_t i = 0; i< m_currentSize; ++i){
            if(this->data[i]!=other.data[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}
template<typename T>
bool Stack<T>::operator!=(const Stack& other) const{
    return !(*this==other);
}

template<typename T>
T Stack<T>::check_pop() const {
    if (this->empty()) throw stackLab::popOutOfRange();
    return this->data[this->m_currentSize-1];
}


template<typename T>
bool Stack<T>::empty() const noexcept{
    return !(m_currentSize>0);
}

template<typename T>
void Stack<T>::clear() noexcept{
    this->m_currentSize = 0;
}


template<typename T>
size_t Stack<T>::size() const noexcept{
    return m_currentSize;
}

template<typename T>
T Stack<T>::pop() {
    if(this->empty()) throw stackLab::popOutOfRange();
    this->m_currentSize-=1;
    T popedEl = this->data[this->m_currentSize];

    return popedEl;
}


#endif //LAB1STACK_STACK_H

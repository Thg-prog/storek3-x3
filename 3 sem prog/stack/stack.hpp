#pragma once

#include <iostream>
#include <initializer_list>

template <typename T>
class Stack {
    T* ar;
    int size;
    int capacity;
    const int startStackCapacity = 10;

    public:
    Stack();
    Stack(const Stack& stack);
    Stack(Stack&& stack) noexcept;
    Stack(std::initializer_list<T> list);
    template <typename Iterator>
    Stack(Iterator begin, Iterator end) ;
    Stack& operator=(const Stack& stack);
    Stack& operator=(Stack&& stack) noexcept;
    void push(const T& element);
    T pop();
    inline T check_pop() const;
    inline bool isEmpty() const noexcept;
    inline int getSize() const noexcept;
    inline void clear() noexcept;
    bool operator==(const Stack& stack) const noexcept;
    bool operator!=(const Stack& stack) const noexcept;
    void top(const T& element);
    void swap(T& element);
    Stack& operator<<(const T& element);
    Stack& operator>>(T& element);
    template <typename N> 
    friend std::ostream& operator<<(std::ostream& out, const Stack<N>& stack) noexcept;
    ~Stack();
};

template <typename T>
Stack<T>::Stack() {
    capacity = startStackCapacity;
    ar = new T[capacity];
    size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack& stack) {
    ar = new T[stack.capacity];
    capacity = stack.capacity;
    size = stack.size;
    for (int i = 0; i < size; i++) {
        ar[i] = stack.ar[i];
    }
}

template <typename T>
Stack<T>::Stack(Stack&& stack) noexcept {
    ar = stack.ar;
    capacity = stack.capacity;
    size = stack.size;
    stack.ar = nullptr;
    stack.capacity = startStackCapacity;
    stack.size = 0;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> list) {
    size = static_cast<int>(list.size());
    if (size > startStackCapacity) {
        capacity = size * 2;
    } else {
        capacity = startStackCapacity;
    }
    ar = new T[capacity];
    int i = 0;
    for (const T* p = list.begin(); p != list.end(); p++) {
        ar[i] = *p;
        i++;
    }
 }

template <typename T>
template <typename Iterator>
Stack<T>::Stack(Iterator begin, Iterator end) {
    size = std::distance(begin, end);
    if (size > startStackCapacity) {
        capacity = size * 2;
    } else {
        capacity = startStackCapacity;
    }
    ar = new T[capacity];
    int i = 0;
    for (auto it = begin; it != end; it++) {
        ar[i] = *it;
        i++;
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& stack) {
    if (this != &stack) {
        delete[] ar;
        ar = new T[stack.capacity];
        capacity = stack.capacity;
        size = stack.size;
        for (int i = 0; i < size; i++) {
            ar[i] = stack.ar[i];
        }
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& stack) noexcept {
    if (this != &stack) {
        delete[] ar;
        ar = stack.ar;
        size = stack.size;
        capacity = stack.capacity;
        stack.ar = nullptr;
        stack.size = 0;
        stack.capacity = startStackCapacity;
    }
    return *this;
}

template <typename T>
void Stack<T>::push(const T& element) {
    if (size == capacity) {
        T* newAr = new T[capacity * 2];
        for (int i = 0; i < capacity; i++) {
            newAr[i] = ar[i];
        }
        capacity *= 2;
        delete[] ar;
        ar = newAr;
    }
    ar[size++] = element;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    T element = ar[--size];
    if (size < capacity / 2) {
        T* newAr = new T[capacity / 2];
        for (int i = 0; i < size; i++) {
            newAr[i] = ar[i];
        }
        capacity /= 2;
        delete[] ar;
        ar = newAr;
    }
    return element;
}

template <typename T>
bool Stack<T>::operator==(const Stack& stack) const noexcept {
    if (stack.size != size) return false;
    for (int i = 0; i < size; i++) {
        if (ar[i] != stack.ar[i])
            return false;
    }
    return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& stack) const noexcept {
    return !(*this == stack);
}

template <typename T>
void Stack<T>::top(const T& element) {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    ar[size-1] = element;
}

template <typename T>
void Stack<T>::swap(T& element) {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    T el = check_pop();
    T buf = el;
    el = element;
    element = buf;
    top(el);
}

template <typename T>
Stack<T>& Stack<T>::operator<<(const T& element) {
    push(element);
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator>>(T& element) {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    element = pop();
    return *this;
}

template <typename T>
bool Stack<T>::isEmpty() const noexcept {
    return size == 0;
}

template <typename T>
int Stack<T>::getSize() const noexcept{
    return size;
}

template <typename T>
void Stack<T>::clear() noexcept{
    size = 0;
    capacity = startStackCapacity;
}

template <typename T>
T Stack<T>::check_pop() const {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return ar[size-1];
}

template <typename N>
inline std::ostream &operator<<(std::ostream &out, const Stack<N> &stack) noexcept
{
    for (int i = 0; i < stack.size; i++) {
        out << stack.ar[i] << " ";
    }
   out << "\n";
   return out;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] ar;
}
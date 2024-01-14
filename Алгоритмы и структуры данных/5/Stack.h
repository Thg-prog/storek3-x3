#pragma once
#include <iostream>

class Element {
public:
    int value;
    Element* next;
};

class Stack {
protected:
    Element* head;
public:
    Stack();
    void add(int val);
    bool isEmpty();
    int getHead();
    int deleteStart();
    void print();
    int size();
    ~Stack();
};
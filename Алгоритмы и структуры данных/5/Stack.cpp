#include <iostream>
#include "Stack.h"

Stack::Stack() {
    head = NULL;
}

void Stack::add(int val) {
    Element* el = new Element;
    el->value = val;
    el->next = head;
    head = el;
}

bool Stack::isEmpty() {
    return head == NULL;
}

int Stack::getHead() {
    return head->value;
}

int Stack::deleteStart() {
    int val = head->value;
    Element* el = head;
    head = head->next;
    delete el;
    return val;
}

void Stack::print() {
    Element* el = head;
    while (el != NULL) {
        std::cout << el->value << " ";
        el = el->next;
    }
    std::cout << std::endl;
}

int Stack::size() {
    int c = 0;
    Element* el = head;
    while (el != NULL) {
        c++;
        el = el->next;
    }
    return c;
}

Stack::~Stack() {
    Element* el = head;
    Element* el1 = head;
    while (el != NULL) {
        el1 = el;
        el = el->next;
        delete el1;
    }
}

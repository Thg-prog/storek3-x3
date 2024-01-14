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
    Stack() {
        head = NULL;
    }
    
    void add(int val) {
        Element* el = new Element;
        el->value = val;
        el->next = head;
        head = el;
    }

    bool isEmpty() {
        return head == NULL;
    }

    int getHead() {
        return head->value;
    }

    int deleteStart() {
        int val = head->value;
        Element* el = head;
        head = head->next;
        delete el;
        return val;
    }
    
    void print() {
        Element* el = head;
        while (el != NULL) {
            std::cout << el->value << " ";
            el = el->next;
        }
        std::cout << std::endl;
    }

    ~Stack() {
        Element* el = head;
        Element* el1 = head;
        while (el != NULL) {
            el1 = el;
            el = el->next;
            delete el1;
        }
    }
};

class Dack : public Stack {
public:
    void addEnd(int val) {
        if (!isEmpty()) {
            Element* el1 = head;
            Element* el2 = head;
            while (el1 != NULL) {
                el2 = el1;
                el1 = el1->next;
            }
            el1 = new Element;
            el1->value = val;
            el1->next = NULL;
            el2->next = el1;
        }
        else {
            add(val);
        }
    }

    int getTail() {
        Element* el = head;
        Element* el1 = head;
        while (el != NULL) {
            el1 = el;
            el = el->next;
        }
        return el1->value;
    }

    int deleteEnd() {
        Element* el1 = head;
        Element* el2 = head;
        Element* el = head;
        while (el != NULL) {
            el2 = el1;
            el1 = el;
            el = el->next;
        }
        int val = el2->value;
        el2->next = NULL;
        delete el1;
        return val;
    }
};

class Queue : public Stack {
public:
    void add(int val) {
        if (!isEmpty()) {
            Element* el1 = head;
            Element* el2 = head;
            while (el1 != NULL) {
                el2 = el1;
                el1 = el1->next;
            }
            el1 = new Element;
            el1->value = val;
            el1->next = NULL;
            el2->next = el1;
        }
        else {
            Element* el = new Element;
            el->value = val;
            el->next = head;
            head = el;
        }
    }
};

int main()
{
    std::cout << "-1-to exit; 0-to print; 1-to add; 2-to check isEmpty; 3-to getHead; 4-to get a tail of Dack; 5-to delete; " << std::endl;
    Stack s;
    Dack d;
    Queue q;
    int value;
    int action;
    while (true) {
        std::cout << "Enter value: ";
        std::cin >> value;
        if (value == -1) break;
        else if (value == 0) {
            std::cout << "1-to print Stack; 2-to prind Dack; 3-to print Queue: ";
            std::cin >> action;
            if (action == 1) s.print();
            else if (action == 2) d.print();
            else if (action == 3) q.print();
        }
        else if (value == 1) {
            std::cout << "1-to add in the start of the Stack; 2-to add in the start of Dack; 3-to add in the end of Dack; 4-to add in the end of Queue: ";
            std::cin >> action;
            std::cout << "Enter the value: ";
            int val;
            std::cin >> val;
            if (action == 1) s.add(val);
            else if (action == 2) d.add(val);
            else if (action == 3) d.addEnd(val);
            else if (action == 4) q.add(val);
        }
        else if (value == 2) {
            std::cout << "1-to check isEmpty Stack; 2-to check isEmpty Dack; 3-to check isEmpty Queue: ";
            std::cin >> action;
            if (action == 1) std::cout << s.isEmpty() << std::endl;
            else if (action == 2) std::cout << d.isEmpty() << std::endl;
            else if (action == 3) std::cout << q.isEmpty() << std::endl;
        }
        else if (value == 3) {
            std::cout << "1-to get a head of the Stack; 2-to get a head of the Dack; 3-to get a head of the Queue: ";
            std::cin >> action;
            if (action == 1) std::cout << s.getHead() << std::endl;
            else if (action == 2) std::cout << d.getHead() << std::endl;
            else if (action == 3) std::cout << q.getHead() << std::endl;
        }
        else if (value == 4) {
            std::cout << d.getTail() << std::endl;
        }
        else if (value == 5) {
            std::cout << "1-to delete start element of the Stack; 2-to delete start element of the Dack; 3-to delete start element of the Queue; 4-to delete end element of the Dack: ";
            std::cin >> action;
            if (action == 1) { 
                int el = s.deleteStart(); 
                std::cout << el << std::endl;
            }
            else if (action == 2) { 
                int el = d.deleteStart(); 
                std::cout << el << std::endl;
            }
            else if (action == 3) { 
                int el = q.deleteStart();
                std::cout << el << std::endl;
            }
            else if (action == 4) {
                int el = d.deleteEnd();
                std::cout << el << std::endl;
            }
        }
    } 
}

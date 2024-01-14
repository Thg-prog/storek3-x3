#include <iostream>

using namespace std;

class Element {
public:
    int key;
    int value;
    Element* next;
};

class Table {
private:
    Element* head;
public:
    Table();
    void pushStart(int key, int value);
    bool isEmpty();
    Element* findElement(int key);
    void deleteElement(int key);
    void print();
    void printElement(Element* el);
    void destroy();
};

Table::Table() {
    head = NULL;
}

void Table::pushStart(int key, int value) {
    Element* el = new Element;
    el->key = key;
    el->value = value;
    el->next = head;
    head = el;
}

bool Table::isEmpty() {
    return head == NULL;
}

Element* Table::findElement(int key) {
    Element* el = head;
    while (el != NULL && el->key != key) {
        el = el->next;
    }
    return el;
}

void Table::deleteElement(int key) {
    Element* el1 = head;
    Element* el2 = head;
    while (el1 != NULL && el1->key != key) {
        el2 = el1;
        el1 = el1->next;
    }
    if (el1 != NULL) {
        if (el1 == el2) {
            head = el1->next;
            delete el1;
        } else {
            el2->next = el1->next;
            delete el1;
        }
    }
}

void Table::print() {
    Element* el = head;
    while (el != NULL) {
        cout << el->key << ": " << el->value << endl;
        el = el->next;
    }
}

void Table::printElement(Element* el) {
    cout << el->key << ": " << el->value << endl;
}

void Table::destroy() {
    Element* el = head;
    while (el != NULL) {
        delete el;
        el = el->next;
    }
}

int main()
{
    Table t;
    cout << "0-to exit; 1-to push start; 2-to push back; 3-to delete element; 4-to find element; 5-to print elements" << endl;
    while (true) {
        cout << "Enter the number: ";
        int action;
        cin >> action;
        if (action == 0) {
            t.destroy();
            break;
        }
        else if (action == 1 || action == 2) {
            cout << "Enter the key: ";
            int key;
            cin >> key;
            cout << "Enter the value: ";
            int value;
            cin >> value;
            if (action == 1) t.pushStart(key, value);
            if (action == 2) t.pushBack(key, value);
        } else if (action == 3 || action == 4) {
            cout << "Enter the key: ";
            int key;
            cin >> key;
            if (action == 3) t.deleteElement(key);
            if (action == 4) {
                Element* el = t.findElement(key);
                t.printElement(el);
            } else {
                cout << "There is no current element" << endl;
            }
        } else if (action == 5) t.print();
    }
    return 0;
}

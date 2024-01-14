#include <iostream>

using namespace std;

class Element {
public:
    char ch;
    Element* next;
};

class Str {
    Element* head;
public:
    Str();
    bool isEmpty();
    void add(char ch);
    Str operator+(Str str);
    Str separate(int ind);
    int getLength();
    void removeSubstring(int indStart, int indEnd);
    void put(Str str, int indStart);
    int searching(Str str);
    void print();
    ~Str();
};

Str::Str() {
    head = NULL;
}

bool Str::isEmpty() {
    return head == NULL;
}

void Str::add(char ch) {
    if (!isEmpty()) {
        Element* el1 = head;
        Element* el2 = head;
        while (el1 != NULL) {
            el2 = el1;
            el1 = el1->next;
        }
        el1 = new Element;
        el1->ch = ch;
        el1->next = NULL;
        el2->next = el1;
    } else {
        Element* el = new Element;
        el->ch = ch;
        el->next = head;
        head = el;
    }
}

Str Str::operator+(Str str) {
    Str s;
    Element* el = head;
    s.head = head;
    Element* el1 = el;
    while (el != NULL) {
        el1 = el;
        el = el->next;
    }
    el1->next = str.head;
    return s;
}

Str Str::separate(int ind) {
    Element* el = head;
    int i = 0;
    Element* el1 = head;
    while(i != ind) {
        el1 = el;
        el = el->next;
        i++;
    }
    Str str;
    str.head = el;
    el1->next = NULL;
    return str;
}

int Str::getLength() {
    Element* el = head;
    int i = 0;
    while (el != NULL) {
        el = el->next;
        i++;
    }
    return i;
}

void Str::removeSubstring(int indStart, int indEnd) {
    Element* el = head;
    int i = 0;
    Element* el1 = head;
    while(i != indStart) {
        el1 = el;
        el = el->next;
        i++;
    }
    Element* el2 = head;
    while(i != indEnd) {
        el2 = el;
        el = el->next;
        i++;
    }
    el1->next = el2->next;
}

void Str::put(Str str, int indStart) {
    Element* el = head;
    Element* el1 = head;
    int i = 0;
    while (i != indStart) {
        el1 = el;
        el = el->next;
        i++;
    }
    Element* next = el1->next;
    Element* el2 = str.head;
    el1->next = str.head;
    Element* el3 = str.head;
    while (el2 != NULL) {
        el3 = el2;
        el2 = el2->next;
    }
    el3->next = next;
}

int Str::searching(Str str) {
    Element* el = head;
    int i = 0;
    while (el != NULL) {
        int j = 0;
        Element* el1 = str.head;
        while (el1 != NULL) {
            if (el->ch == el1->ch) return i;
             el1 = el1->next;
            j++;
        }
        el = el->next;
        i++;
    }
    return -1;
}

void Str::print() {
    Element* el = head;
    while (el != NULL) {
        cout << el->ch;
        el = el->next;
    }
    cout << endl;
}

Str::~Str() {
    Element* el = head;
    Element* el1 = head;
    while (el != NULL) {
        el1 = el;
        el = el->next;
        delete el1;
    }
}

int main()
{
    Str s1;
    Str s2;
    cout << "0-to exit; 1-to add; 2-to concatinate; 3-to separate; 4-to remove substring; 5-to put; 6-to find; 7-to print" << endl;
    int action;
    int value;
    while (true) {
        cout << "Enter number: ";
        cin >> action;
        if (action != 0) {
            cout << "Over which string (1 or 2): ";
            cin >> value;
        }
        if (action == 1) {
            char ch;
            cout << "Enter the symbol: ";
            cin >> ch;
            if (value == 1) s1.add(ch);
            else s2.add(ch);
        } else if (action == 2) {
            if (value == 1) s1 = s1 + s2;
            else s2 = s2 + s1;
        } else if (action == 3) {
            int ind;
            cout << "Enter the index: ";
            cin >> ind;
            if (value == 1) s1.separate(ind);
            else s2.separate(ind);
        } else if (action == 4) {
            int startInd, endInd;
            cout << "Enter startInd: ";
            cin >> startInd;
            cout << "Enter endInd: ";
            cin >> endInd;
            if (value == 1) s1.removeSubstring(startInd, endInd);
            else s2.removeSubstring(startInd, endInd);
        } else if (action == 5) {
            int ind;
            cout << "Enter the index: ";
            cin >> ind;
            if (value == 1) s1.put(s2, ind);
            else s2.put(s1, ind);
        } else if (action == 6) {
            int ind;
            if (value == 1) ind = s1.searching(s2);
            else ind = s2.searching(s1);
            cout << ind << endl;
        } else if (action == 7) {
            if (value == 1) s1.print();
            else s2.print();
        } else if (action == 0) break;
    }
    return 0;
}

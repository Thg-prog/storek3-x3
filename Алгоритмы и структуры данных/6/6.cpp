#include <iostream>
#include <vector>

struct Element {
    Element* next;
    int v;
    Element* level;
    char atom;
};


class List {
    double value;
    char* str;
    Element* head;
    std::vector<double> v1;
    std::vector<char> v2;

    void add(Element*& el) {
        char ch = *str;
        str++;
        if (ch != 0) {
            if (ch == '(') {
                el = new Element;
                el->v = 0;
                add(el->level);
                add(el->next);
            }
            else if (isalpha(ch) || ch == '/' || ch == '*' || ch == '-' || ch == '+') {
                el = new Element;
                el->v = 1;
                el->atom = ch;
                el->level = NULL;
                if (isalpha(ch)) v2.push_back(ch);
                add(el->next);
            }
            else if (ch == ')') el = NULL;
        }
        else el = NULL;
    }

    void printElement(Element*& el) {
        if (el != NULL) {
            if (el->v == 1) {
                std::cout << el->atom;
            }
            else {
                Element* el1 = el->level;
                std::cout << "(";
                while (el1 != NULL) {
                    printElement(el1);
                    el1 = el1->next;
                }
                std::cout << ")";
            }
        }
    }

    void deleteElement(Element*& el) {
        if (el != NULL) {
            if (el->v == 1) {
                delete el;
            }
            else {
                Element* el1 = el->level;
                Element* el2 = el1;
                while (el1 != NULL) {
                    el2 = el1;
                    el1 = el1->next;
                    deleteElement(el2);
                }

            }
        }
    }

    Element* getHead(Element* e) {
        Element* el = e->level;
        e->level = el->next;
        el->next = NULL;
        return el;
    }

    double val(Element* el) {
        if (el != NULL) {
            if (el->level != NULL) {
                double x = val(getHead(el));
                char operation = getHead(el)->atom;
                double y = val(getHead(el));
                switch (operation) {
                case '/':
                    return x / y;
                    break;
                case '*':
                    return x * y;
                    break;
                case '-':
                    return x - y;
                    break;
                case '+':
                    return x + y;
                    break;
                }
            }
            else
            {
                for (int i = 0; i < v2.size(); i++) {
                    if (v2[i] == el->atom) {
                        return v1[i];
                    }
                }
            }
        }
        return 0;
    }

public:
    List() {
        head = NULL;
    }

    void set(char* _str) {
        head = NULL;
        str = new char[100];
        for (int i = 0; i < 100; i++) {
            str[i] = _str[i];
        }
        add(head);
    }

    void setValues(std::vector<double> v) {
        for (int i = 0; i < v.size(); i++) {
            v1.push_back(v[i]);
        }
    }

    void printList() {
        printElement(head);
        std::cout << std::endl;
    }

    double getValue() {
        return val(head);
    }

    std::vector<char> getLetters() {
        return v2;
    }

    ~List() {
        deleteElement(head);
    }
};


int main()
{
    char* str = new char[100];
    std::cout << "0-to exit; 1-to convert; 2-to print" << std::endl;
    List l;
    int value;
    while (true) {
        std::cout << "Enter the value: ";
        std::cin >> value;
        if (value == 0) break;
        else if (value == 1) {
            std::cout << "Enter the string: ";
            std::cin >> str;
            l.set(str);
        }
        else if (value == 2) {
            int v;
            std::cout << "To calculate(0/1): ";
            std::cin >> v;
            if (v == 0) {
                l.printList();
            }
            else {
                std::vector<char> v = l.getLetters();
                std::vector<double> v2;
                for (int i = 0; i < v.size(); i++) {
                    std::cout << v[i] << "=";
                    double d;
                    std::cin >> d;
                    v2.push_back(d);
                }
                l.setValues(v2);
                std::cout << l.getValue() << std::endl;
            }
        }
    }
    delete[] str;
    return 0;
}

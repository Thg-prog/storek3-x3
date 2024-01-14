#include <iostream>
#include <fstream>

struct Element {
    int value;
    Element* next;
};

class Array {
    int n;
    Element* head;
public:
    Array();
    int getLength() const;
    void add(int value);
    void pop();
    int binary_insert_sort();
    int insert_sort();
    int bubble_sort();
    int& operator[](int j);
    int operator[](int j) const;
    friend std::istream& operator>>(std::istream& in, Array& ar);
    friend std::ostream& operator<<(std::ostream& out, const Array& ar);
    ~Array();
};

Array::Array() {
    n = 0;
    head = NULL;
}

int Array::getLength() const {
    return n;
}

void Array::add(int value) {
    if (head != NULL) {
        Element* el1 = head;
        Element* el2 = head;
        while (el1 != NULL) {
            el2 = el1;
            el1 = el1->next;
        }
        el1 = new Element;
        el1->value = value;
        el1->next = NULL;
        el2->next = el1;
    }
    else {
        Element* el = new Element;
        el->value = value;
        el->next = head;
        head = el;
    }
    n++;
}

int& Array::operator[](int j) {
    Element* el = head;
    Element* el1 = head;
    int i = 0;
    while (el != NULL && i <= j) {
        i++;
        el1 = el;
        el = el->next;
    }
    return el1->value;
}

int Array::operator[](int j) const {
    int i = 0;
    Element* el = head;
    Element* el1 = head;
    while (el != NULL && i <= j) {
        i++;
        el1 = el;
        el = el->next;
    }
    return el1->value;
}

void Array::pop() {
    if (head != NULL) {
        Element* el1 = head;
        Element* el = head;
        while (el != NULL) {
            el1 = el;
            el = el->next;
        }
        delete el1;
        n--;
    }
}

int Array::binary_insert_sort() {
	int c = 0;
    for (int i = 1; i < n; i++) {
        int val = (*this)[i];
        int left = 0; 
        int right = i;
        while (left < right) {
            int middle = (left + right) / 2;
            if ((*this)[middle] <= val) {
                left = middle + 1;   
            } else {
                right = middle;
                c++; 
            }
        }
        for (int j = i; j >= right; j--) {
            (*this)[j] = (*this)[j-1];
        }
        (*this)[right] = val;
    }
    return c;
}

int Array::insert_sort() {
	int c = 0;
    for (int i = 1; i < n; i++) {
        int j;
        int val = (*this)[i];
        for (j = i - 1; j >= 0 && (*this)[j] > val; j--) {
            (*this)[j + 1] = (*this)[j];
            c++;
        }
        (*this)[j + 1] = val;
    }
    return c;
}

int Array::bubble_sort() {
	int c = 0;
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            if ((*this)[j - 1] > (*this)[j]) {
                int tmp = (*this)[j - 1];
                (*this)[j - 1] = (*this)[j];
                (*this)[j] = tmp;
                c++;
            }
        }
    }
    return c;
}

std::istream& operator>>(std::istream& in, Array& ar) {
    int _n;
    in >> _n;
    for (int i = 0; i < _n; i++) {
        int value;
        in >> value;
        ar.add(value);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Array& ar) {
    for (int i = 0; i < ar.n; i++) out << ar[i] << " ";
    out << "\n";
    return out;
}

Array::~Array() {
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
    Array ar;
    int value;
    std::cout << "0-exit; 1-to enter an array; 2-to print array; 3-to delete the last element; 4-to add element; 5-to sort insert; 6-to bubble sort; 7-to sort binary insert" << std::endl;
    while (true) {
        std::cout << "Enter the value: ";
        std::cin >> value;
        if (value == 0) break;
        else if (value == 1) std::cin >> ar;
        else if (value == 2) std::cout << ar;
        else if (value == 3) ar.pop();
        else if (value == 4) {
            int val;
            std::cout << "Enter the number: ";
            std::cin >> val;
            ar.add(val);
        }
        else if (value == 5) std::cout << ar.insert_sort() << std::endl;
        else if (value == 6) std::cout << ar.bubble_sort() << std::endl;
        else if (value == 7) std::cout << ar.binary_insert_sort() << std::endl;
    }
}

#include <iostream>
#include <string>
#include <vector>

class ElementT {
public:
    char ch;
    ElementT* left;
    ElementT* right;
    bool isStump();
    ElementT* leftSubtree();
    ElementT* rightSubtree();
};

bool ElementT::isStump() {
    if (left == NULL && right == NULL) return true;
    return false;
}

ElementT* ElementT::rightSubtree() {
    ElementT* el = right;
    right = NULL;
    return el;
}

ElementT* ElementT::leftSubtree() {
    ElementT* el = left;
    left = NULL;
    return el;
}




class Tree {
    std::string str;
    ElementT* head;
    //std::vector<int> v1;
    //std::vector<char> v2;
    void construct(int& i, ElementT*& el);
    void getNextSymbol(int& i, int& count1, int& count2);
    void printEl(ElementT*& el);
    void deleteEl(ElementT*& el);
    int val(ElementT* el, std::vector<int> v1, std::vector<char> v2);
public:
    Tree();
    Tree(std::string _str);
    void set(std::string _str);
    bool isEmpty();
    void print();
    //void setValues(std::vector<int> v);
    int getValue(std::vector<int> v1, std::vector<char> v2);
    std::vector<char> getLetters();
    ~Tree();
};

Tree::Tree() {
    str = "";
    head = NULL;
}

Tree::Tree(std::string _str) {
    set(_str);
}


void Tree::getNextSymbol(int& i, int& count1, int& count2) {
    char ch = str[i];
    i++;
    if (ch == '(')
        count1++;
    else if (ch == '-' || ch == '+' || ch == '*' || ch == '/') {
        count2++;
    } 
    if (count2 < count1)
        getNextSymbol(i, count1, count2);
}

void Tree::construct(int& i, ElementT*& el) {
    char ch = str[i];
    int j = i;
    i++;
    if (ch == '(') {
        int count1 = 0;
        int count2 = 0;
        getNextSymbol(j, count1, count2);
        el = new ElementT;
        el->ch = str[j-1];
        construct(i, el->left);
        construct(j, el->right);
    }
    else if (isalpha(ch)) {
        //v2.push_back(ch);
        el = new ElementT;
        el->ch = ch;
        el->left = NULL;
        el->right = NULL;
    }
    else el = NULL;
    if (i >= str.size()) el = NULL;
}

/*void Tree::setValues(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        v1.push_back(v[i]);
    }
}*/

void Tree::printEl(ElementT*& el) {
    if (el != NULL) {
        if (el->isStump()) {
            std::cout << el->ch;
        }
        else {
            std::cout << "(";
            printEl(el->left);
            std::cout << el->ch;
            printEl(el->right);
            std::cout << ")";
        }
    }
}

void Tree::deleteEl(ElementT*& el) {
    if (el != NULL) {
        if (el->isStump()) delete el;
        else {
            deleteEl(el->left);
            deleteEl(el->right);
            delete el;
        }
    }
}

void Tree::set(std::string _str) {
    str = _str;
    int i = 0;
    construct(i, head);
}

bool Tree::isEmpty() {
    return head == NULL;
}

int Tree::getValue(std::vector<int> v1, std::vector<char> v2) {
    return val(head, v1, v2);
}

void Tree::print() {
    printEl(head);
    std::cout << std::endl;
}

int Tree::val(ElementT* el, std::vector<int> v1, std::vector<char> v2) {
            if (!el->isStump()) {
                int x = val(el->left, v1, v2);
                char operation = el->ch;
                int y = val(el->right, v1, v2);
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
            else {
                for (int i = 0; i < v2.size(); i++) {
                    if (v2[i] == el->ch) {
                        return v1[i];
                    }
                }
            }
        
    return 0;
}

bool isUnique(std::vector<char> v, char symbol) {
	for (int i = 0; i < v.size(); i++) {
		int count = 0;
		if (v[i] == symbol) {
			return false;
		}
	}
	return true;
}

std::vector<char> Tree::getLetters() {
	std::vector<char> v;
	for (int i = 0; i < str.size(); i++) {
		if (isUnique(v, str[i]) && isalpha(str[i])) {
			v.push_back(str[i]);
		}
	}
	return v;
}

Tree::~Tree() {
    deleteEl(head);
}


int main()
{
    std::string s;
    std::cout << "0-to exit; 1-to convert; 2-to print" << std::endl;
    Tree t;
    int value;
    while (true) {
        std::cout << "Enter the value: ";
        std::cin >> value;
        if (value == 0) break;
        else if (value == 1) {
            std::cout << "Enter the string: ";
            std::cin >> s;
            t.set(s);
        }
        else if (value == 2) {
            int v;
            std::cout << "To calculate(0/1): ";
            std::cin >> v;
            if (v == 0) {
                t.print();
            }
            else {
                std::vector<char> v = t.getLetters();
                std::vector<int> v2;
                for (int i = 0; i < v.size(); i++) {
                    std::cout << v[i] << "=";
                    int d;
                    std::cin >> d;
                    v2.push_back(d);
                }
                std::cout << t.getValue(v2, v) << std::endl;
            }
        }
    }
    
}

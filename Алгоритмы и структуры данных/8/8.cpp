#include <iostream>
#include <vector>

struct Element {
    int value;
    Element* left;
    Element* right;
};

class Tree {
protected:
    Element* head;
    virtual void add(int val, Element*& el);
    void printEl(Element* el);
    bool isContainEl(int val, Element* el);
    void deleteEl(Element*& el);
public:
    Tree();
    Tree(std::vector<int> v);
    void set(std::vector<int> v);
    bool isContain(int val);
    void print();
    ~Tree();
};


void Tree::add(int val, Element*& el) {
    if (el == NULL) {
        el = new Element;
        el->value = val;
        el->left = NULL;
        el->right = NULL;
    } else if (val < el->value) {
        add(val, el->left);
    } else {
        add(val, el->right);
    }
}

Tree::Tree() {
    head = NULL;
}

void Tree::set(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        add(v[i], head);
    }
}

bool Tree::isContain(int val) {
    return isContainEl(val, head);
}

Tree::Tree(std::vector<int> v) {
    set(v);
}

void Tree::printEl(Element* el) { 
    if (el != NULL) {
        printEl(el->left);
        std::cout << el->value << " ";
        printEl(el->right);
    }
}

bool Tree::isContainEl(int val, Element* el) {
    if (el != NULL) {
        bool b1 = isContainEl(val, el->left);
        bool b2 = isContainEl(val, el->right);
        return el->value == val || b1 || b2;
    }
    return false;
}

void Tree::print() {
	std::cout << "head = " << head->value << std::endl;
    printEl(head);
    std::cout << std::endl;
}

void Tree::deleteEl(Element*& el) {
    if (el != NULL) {
        if (el->left == NULL && el->right == NULL) delete el;
        else {
            deleteEl(el->left);
            deleteEl(el->right);
            delete el;
        }
    }
}

Tree::~Tree() {
    deleteEl(head);
}

class BalanceTree : public Tree {
    int getHeight(Element* el);
    int getDifference(Element* el);
    void add(int val, Element*& el);
    Element* rightRightSwap(Element* el);
    Element* rightLeftSwap(Element* el);
    Element* leftLeftSwap(Element* el);
    Element* leftRightSwap(Element* el);
    void balance(Element*& el);
};

int BalanceTree::getHeight(Element* el) {
    int height = 0;
    if (el != NULL) {
        int left_height = getHeight(el->left);
        int right_height = getHeight(el->right);
        if (left_height > right_height) height = left_height;
        else height = right_height;
        height++;
    }
    return height;
}

int BalanceTree::getDifference(Element* el) {
    int left_height = getHeight(el->left);
    int right_height = getHeight(el->right);
    return left_height - right_height;
}

Element* BalanceTree::rightRightSwap(Element* el) {
    Element* el1 = el->right;
    el->right = el1->left;
    el1->left = el;
    return el1;
}

Element* BalanceTree::rightLeftSwap(Element* el) {
    Element* el1 = el->right;
    el->right = leftLeftSwap(el1);
    return rightRightSwap(el);
}

Element* BalanceTree::leftLeftSwap(Element* el) {
    Element* el1 = el->left;
    el->left = el1->right;
    el1->right = el;
    return el1;
}

Element* BalanceTree::leftRightSwap(Element* el) {
    Element* el1 = el->left;
    el->left = rightRightSwap(el1);
    return leftLeftSwap(el);
}

void BalanceTree::balance(Element*& el) {
    int parentDifference = getDifference(el);
    if (parentDifference > 1) {
        if (getDifference(el->left) > 0) el = leftLeftSwap(el);
        else el = leftRightSwap(el);
    }
    else if (parentDifference < -1) {
        if (getDifference(el->right) > 0) el = rightLeftSwap(el);
        else el = rightRightSwap(el);
    }
}

void BalanceTree::add(int val, Element*& el) {
    if (el == NULL) {
        el = new Element;
        el->value = val;
        el->left = NULL;
        el->right = NULL;
    }
    else if (val < el->value) {
        add(val, el->left);
        balance(el);
    }
    else {
        add(val, el->right);
        balance(el);
    }
}

int main()
{
    int value;
    std::cout << "0-to exit; 1-to set; 2-to print" << std::endl;
    Tree t1;
    BalanceTree t2;
    while (true) {
        std::cout << "Enter the value: ";
        std::cin >> value;
        if (value == 0) break;
        else if (value == 1) {
            std::cout << "In which tree do you want to put the array(1-to simple tree; 2-to balance tree;" << std::endl;
            int value2;
            std::cout << "Enter the value: ";
            std::cin >> value2;
            std::cout << "Enter the length of ar: ";
            int n;
            std::cin >> n;
            std::vector<int> ar(n);
            for (int i = 0; i < n; i++) {
                std::cout << "ar[" << i << "]=";
                std::cin >> ar[i];
            }
            if (value2 == 1) t1.set(ar);
            else if (value2 == 2) t2.set(ar);
        }
        else if (value == 2) { 
            std::cout << "What tree do you want to print(1-simple tree; 2-balance tree;" << std::endl;
            int value2;
            std::cout << "Enter the value: ";
            std::cin >> value2;
            if (value2 == 1) t1.print();
            else if (value2 == 2) t2.print();
        }
    }
    
}

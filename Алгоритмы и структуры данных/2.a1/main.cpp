#include <iostream>

using namespace std;

class Element {
public:
    int key;
    int value;
};

class Table {
private:
    Element dict[10];
    int currentCount;
public:
    Table();
    bool isEmpty();
    void pushStart(int key, int value);
    int findElement(int key);
    void deleteElement(int key);
    void print();
    void printElement(int index);
};

Table::Table() {
    currentCount = 0;
}

bool isEmpty() {
	return currentCount == 0;
}

void Table::pushStart(int key, int value) {
    if (currentCount < 10) {
        Element el;
        for (int i = currentCount; i >= 0; i--) {
            dict[i+1] = dict[i];
        }
        el.key = key;
        el.value = value;
        dict[0] = el;
        currentCount++;
    }
}

int Table::findElement(int key) {
    for (int i = 0; i < currentCount; i++) {
        if (dict[i].key == key) return i;
    }
    return -1;
}

void Table::deleteElement(int key) {
    int index = findElement(key);
    if (findElement(key) != -1) {
        for (int i = index+1; i < currentCount; i++) {
            dict[i-1] = dict[i];
        }
        currentCount--;
    }
}

void Table::print() {
    for (int i = 0; i < currentCount; i++) {
        cout << dict[i].key << ": " << dict[i].value << endl;
    }
}

void Table::printElement(int index) {
    cout << dict[index].key << ": " << dict[index].value << endl;
}

int main()
{
    Table t;
    cout << "0-to exit; 1-to push start; 2-to push back; 3-to delete element; 4-to find element; 5-to print elements" << endl;
    while (true) {
        cout << "Enter the number: ";
        int action;
        cin >> action;
        if (action == 0) break;
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
                int index = t.findElement(key);
                if (index != -1)
                    t.printElement(index);
                else
                    cout << "There is no current element" << endl;
            }
        } else if (action == 5) t.print();
    }
    return 0;
}

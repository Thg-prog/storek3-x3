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
    void add(int key, int value);
    int findElement(int key);
    void deleteElement(int key);
    void sortDict();
    void print();
    void printElement(int index);
};

Table::Table() {
    currentCount = 0;
}

void Table::add(int key, int value) {
    if (currentCount < 10) {
        Element el;
        el.key = key;
        el.value = value;
        dict[currentCount] = el;
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

void Table::sortDict() {
    for (int i = 0; i < currentCount-1; i++) {
        int m = dict[i].key;
        int imin = i;
        for (int j = i+1; j < currentCount; j++) {
            if (dict[j].key < m) {
                m = dict[j].key;
                imin = j;
            }
        }
        Element tmp = dict[imin];
        dict[imin] = dict[i];
        dict[i] = tmp;
    }
}

void Table::print() {
    sortDict();
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
    cout << "0-to exit; 1-to add; 2-to delete element; 3-to find element; 4-to print elements" << endl;
    while (true) {
        cout << "Enter the number: ";
        int action;
        cin >> action;
        if (action == 0) break;
        else if (action == 1) {
            cout << "Enter the key: ";
            int key;
            cin >> key;
            cout << "Enter the value: ";
            int value;
            cin >> value;
            t.add(key, value);
        } else if (action == 2 || action == 3) {
            cout << "Enter the key: ";
            int key;
            cin >> key;
            if (action == 2) t.deleteElement(key);
            if (action == 3) {
                int index = t.findElement(key);
                if (index != -1)
                    t.printElement(index);
                else
                    cout << "There is no current element" << endl;
            }
        } else if (action == 4) t.print();
    }
    return 0;
}

#include <iostream>
#include <vector>
#include "ThreadBST.h"

int main() {
    ThreadSafeBST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::vector<int> postorderResult;
    tree.postorderTraversal(postorderResult);

    for (const int& value : postorderResult) {
        std::cout << value << " ";
    }
// Вывод: 2 4 3 6 8 7 5

}

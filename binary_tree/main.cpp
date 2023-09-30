#include <iostream>
#include "binary_tree.hpp"

int main() {
    ThreadTree<int> tree {22, 10, 3, 5, 13, 26, 18, 19, 17, 2, 4, 12, 7};
    std::cout << tree;
    tree.remove(26);
    std::cout << tree;
    tree.clear();
    return 0;
} 
#include <iostream>
#include "binary_tree.hpp"

int main() {
    ThreadTree<int> tree (std::initializer_list<int>({22, 10, 3, 5, 13, 26, 18, 19, 17, 2, 4, 12}));
    std::cout << tree;
    return 0;
}
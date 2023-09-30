#include <iostream>
#include "binary_tree.hpp"

int main() {
    ThreadTree<double> tree {3.34, 5.567, 13.12, 26.98, 2.5, 4.3, 12.1, 7.78};
    ThreadTree<double> tree2(tree);
    std::cout << tree << tree2;
    bool b1 = tree == tree2;
    std::cout << b1;
    ThreadTree<double> tree3;
    tree3.add(3.2);
    tree3.add(tree);
    tree3 << 6.23;
    std::cout << tree3;
    bool b = tree3 == tree;
    std::cout << tree.findTree(5.567);
    return 0;
} 
#include <iostream>
#include "binary_tree.hpp"

int main() {
    /*
    try {
        ThreadTree<int> tree;

        tree.add(5);
        tree.add(3);
        tree.add(7);

        int value = 3;
        if (tree.find(value)) {
            std::cout << "Element " << value << " found in the tree." << std::endl;
        } else {
            std::cout << "Element " << value << " not found in the tree." << std::endl;
        }

        value = 5;
        tree.remove(value);
        value = 10;
        tree.remove(value);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    */
    ThreadTree<int> T1({10,4,2,7,42,12,54});
    std::cout<< T1 << "\n";

    ThreadTree<std::string> T3;
    ThreadTree<std::string> T2 = T3;
    return 0;
} 
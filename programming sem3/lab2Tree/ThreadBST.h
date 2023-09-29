//
// Created by Антон on 27.09.2023.
//

#ifndef LAB2TREE_THREADBST_H
#define LAB2TREE_THREADBST_H
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>

template <typename T>
class ThreadSafeBST {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;
    mutable std::mutex mtx;

public:
    // Конструкторы
    ThreadSafeBST() : root(nullptr) {}
    ThreadSafeBST(const ThreadSafeBST& other) {
        std::lock_guard<std::mutex> lock(other.mtx);
        root = cloneNode(other.root.get());
    }
    ThreadSafeBST(ThreadSafeBST&& other) noexcept : root(std::move(other.root)) {}
    ThreadSafeBST(std::initializer_list<T> initList) : root(nullptr) {
        for (const T& item : initList) {
            insert(item);
        }
    }
    template <typename InputIterator>
    ThreadSafeBST(InputIterator begin, InputIterator end) : root(nullptr) {
        for (InputIterator it = begin; it != end; ++it) {
            insert(*it);
        }
    }

    // Деструктор
    ~ThreadSafeBST() {
        clear();
    }

    // Обходы дерева
    void inorderTraversal(std::vector<T>& result) const {
        std::lock_guard<std::mutex> lock(mtx);
        inorderTraversal(root.get(), result);
    }

    void postorderTraversal(std::vector<T>& result) const {
        std::lock_guard<std::mutex> lock(mtx);
        postorderTraversal(root.get(), result);
    }

    // Добавление элемента
    void insert(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        insert(root, value);
    }
    // Добавление поддерева
    void add(const ThreadSafeBST& subtree) {
        std::lock_guard<std::mutex> lock(mtx);
        add(root, subtree.root.get());
    }
    // Поиск элемента
    bool find(const T& value) const {
        std::lock_guard<std::mutex> lock(mtx);
        return find(root.get(), value);
    }
    // Вернуть поддерево
    ThreadSafeBST findTree(const T& value) const {
        std::lock_guard<std::mutex> lock(mtx);
        ThreadSafeBST subtree;
        Node* subtreeRoot = findSubtree(root.get(), value);
        if (subtreeRoot) {
            subtree.root = cloneNode(subtreeRoot);
        }
        return subtree;
    }
    // Удаление элемента
    void remove(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        remove(root, value);
    }
    // Очистка дерева
    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        clear(root);
    }
    // Перегрузка оператора <<
    friend std::ostream& operator<<(std::ostream& os, const ThreadSafeBST& tree) {
        std::vector<T> result;
        tree.inorderTraversal(result);
        for (const T& item : result) {
            os << item << ' ';
        }
        return os;
    }
    // Операторы сравнения
    bool operator==(const ThreadSafeBST& other) const {
        std::lock_guard<std::mutex> lock1(mtx);
        std::lock_guard<std::mutex> lock2(other.mtx);
        return isEqual(root.get(), other.root.get());
    }
    bool operator!=(const ThreadSafeBST& other) const {
        return !(*this == other);
    }

private:
    // Приватные вспомогательные методы
    static std::unique_ptr<Node> cloneNode(const Node* node) {
        if (!node) {
            return nullptr;
        }
        auto newNode = std::make_unique<Node>(node->data);
        newNode->left = cloneNode(node->left.get());
        newNode->right = cloneNode(node->right.get());
        return newNode;
    }

    static void inorderTraversal(const Node* node, std::vector<T>& result) {
        if (!node) {
            return;
        }
        inorderTraversal(node->left.get(), result);
        result.push_back(node->data);
        inorderTraversal(node->right.get(), result);
    }

    void postorderTraversal(const Node* node, std::vector<T>& result) const {
        if (!node) {
            return;
        }
        postorderTraversal(node->left.get(), result);
        postorderTraversal(node->right.get(), result);
        result.push_back(node->data);
    }

    void insert(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }
        if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }
    }

    void add(std::unique_ptr<Node>& node, Node* subtreeRoot) {
        if (!subtreeRoot) {
            return;
        }
        insert(node, subtreeRoot->data);
        add(node, subtreeRoot->left.get());
        add(node, subtreeRoot->right.get());
    }

    bool find(const Node* node, const T& value) const {
        if (!node) {
            return false;
        }
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return find(node->left.get(), value);
        } else {
            return find(node->right.get(), value);
        }
    }

    Node* findSubtree(Node* node, const T& value) const {
        if (!node) {
            return nullptr;
        }
        if (value == node->data) {
            return node;
        } else if (value < node->data) {
            return findSubtree(node->left.get(), value);
        } else {
            return findSubtree(node->right.get(), value);
        }
    }

    void remove(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            return;
        }
        if (value < node->data) {
            remove(node->left, value);
        } else if (value > node->data) {
            remove(node->right, value);
        } else {
            if (!node->left) {
                node = std::move(node->right);
            } else if (!node->right) {
                node = std::move(node->left);
            } else {
                Node* minRight = findMin(node->right.get());
                node->data = minRight->data;
                remove(node->right, minRight->data);
            }
        }
    }

    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left.get();
        }
        return node;
    }

    void clear(std::unique_ptr<Node>& node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        node.reset();
    }

    bool isEqual(const Node* node1, const Node* node2) const {
        if (!node1 && !node2) {
            return true;
        } else if (node1 && node2) {
            return (node1->data == node2->data) &&
                   isEqual(node1->left.get(), node2->left.get()) &&
                   isEqual(node1->right.get(), node2->right.get());
        } else {
            return false;
        }
    }
};



#endif //LAB2TREE_THREADBST_H

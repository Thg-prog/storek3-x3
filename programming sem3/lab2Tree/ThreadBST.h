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

    std::unique_ptr<Node> m_root;
    mutable std::mutex m_mtx;

public:
    // Конструкторы
    ThreadSafeBST() : m_root(nullptr) {}
    ThreadSafeBST(const ThreadSafeBST& other);
    ThreadSafeBST(ThreadSafeBST&& other) noexcept : m_root(std::move(other.m_root)) {}
    ThreadSafeBST(std::initializer_list<T> initList);
    template <typename InputIterator>
    ThreadSafeBST(InputIterator begin, InputIterator end);
    ThreadSafeBST& operator=(const ThreadSafeBST& tree);
    ThreadSafeBST& operator=(ThreadSafeBST&& tree)noexcept;

    // Деструктор
    ~ThreadSafeBST();

    // Обходы дерева
    void inorderTraversal(std::vector<T>& result) const;

    void postorderTraversal(std::vector<T>& result) const;

    // Добавление элемента
    void insert(const T& value) ;
    // Добавление поддерева
    void add(const ThreadSafeBST& subtree) ;
    // Поиск элемента
    bool find(const T& value) const noexcept;
    // Вернуть поддерево
    ThreadSafeBST findTree(const T& value) const;
    // Удаление элемента
    void remove(const T& value) ;
    // Очистка дерева
    void clear() noexcept;
    // Перегрузка оператора <<
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const ThreadSafeBST<U>& tree);
    // Операторы сравнения
    bool operator==(const ThreadSafeBST& other) const noexcept;
    bool operator!=(const ThreadSafeBST& other) const noexcept;

    ThreadSafeBST& operator<<(ThreadSafeBST& tree);
    ThreadSafeBST& operator<<(T& value);

private:
    // Приватные вспомогательные методы
    static std::unique_ptr<Node> cloneNode(const Node* node);

    static void inorderTraversal(const Node* node, std::vector<T>& result);

    void postorderTraversal(const Node* node, std::vector<T>& result) const ;

    void insert(std::unique_ptr<Node>& node, const T& value);

    void add(std::unique_ptr<Node>& node, Node* subtree_root);

    bool find(const Node* node, const T& value) const ;

    Node* findSubtree(Node* node, const T& value) const ;

    void remove(std::unique_ptr<Node>& node, const T& value);

    Node* findMin(Node* node) ;

    void clear(std::unique_ptr<Node>& node) ;

    bool isEqual(const Node* node1, const Node* node2) const;
};

template<typename T>
ThreadSafeBST<T> &ThreadSafeBST<T>::operator=(ThreadSafeBST<T> &&tree) noexcept{
    std::lock_guard<std::recursive_mutex> lock1(tree.m_mtx);
    std::lock_guard<std::mutex> lock2(m_mtx);
    if(this != &tree){
        if(m_root != nullptr){
            m_root->clearNode();
            m_root = nullptr;
        }
        if(tree.m_root != nullptr){
            m_root = new Node(tree.root->info);
            m_root = cloneNode(tree.m_root);
            tree.root->clearNode();
            delete m_root;
        }
    }
    return *this;
}

template<typename T>
ThreadSafeBST<T> &ThreadSafeBST<T>::operator=(const ThreadSafeBST<T> &tree) {
    std::lock_guard<std::recursive_mutex> lock1(tree.m_mtx);
    std::lock_guard<std::mutex> lock2(m_mtx);
    if(this != *tree){
        if(m_root != nullptr){
            m_root->clearNode();
            delete m_root;
        }
        m_root = new Node(tree.m_root->info);
        m_root = cloneNode(tree.m_root);
    }
    return *this;
}

///приватные методы
template<typename T>
std::unique_ptr<typename ThreadSafeBST<T>::Node> ThreadSafeBST<T>::cloneNode(const ThreadSafeBST::Node *node) {
    if (!node) {
        return nullptr;
    }
    auto newNode = std::make_unique<Node>(node->data);
    newNode->left = cloneNode(node->left.get());
    newNode->right = cloneNode(node->right.get());
    return newNode;
}

template<typename T>
void ThreadSafeBST<T>::inorderTraversal(const ThreadSafeBST::Node *node, std::vector<T> &result) {
    if (!node) {
        return;
    }
    inorderTraversal(node->left.get(), result);
    result.push_back(node->data);
    inorderTraversal(node->right.get(), result);
}

template<typename T>
void ThreadSafeBST<T>::postorderTraversal(const ThreadSafeBST::Node *node, std::vector<T> &result) const {
    if (!node) {
        return;
    }
    postorderTraversal(node->left.get(), result);
    postorderTraversal(node->right.get(), result);
    result.push_back(node->data);
}

template<typename T>
void ThreadSafeBST<T>::insert(std::unique_ptr<Node> &node, const T &value) {
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

template<typename T>
void ThreadSafeBST<T>::add(std::unique_ptr<Node> &node, ThreadSafeBST::Node *subtree_root) {
    if (!subtree_root) {
        return;
    }
    insert(node, subtree_root->data);
    add(node, subtree_root->left.get());
    add(node, subtree_root->right.get());
}

template<typename T>
bool ThreadSafeBST<T>::find(const ThreadSafeBST::Node *node, const T &value) const {
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

template<typename T>
typename ThreadSafeBST<T>::Node *ThreadSafeBST<T>::findSubtree(ThreadSafeBST::Node *node, const T &value) const {
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

template<typename T>
void ThreadSafeBST<T>::remove(std::unique_ptr<Node> &node, const T &value) {
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

template<typename T>
typename ThreadSafeBST<T>::Node *ThreadSafeBST<T>::findMin(ThreadSafeBST::Node *node) {
    while (node->left) {
        node = node->left.get();
    }
    return node;
}

template<typename T>
void ThreadSafeBST<T>::clear(std::unique_ptr<Node> &node) {
    if (!node) {
        return;
    }
    clear(node->left);
    clear(node->right);
    node.reset();
}

template<typename T>
bool ThreadSafeBST<T>::isEqual(const ThreadSafeBST::Node *node1, const ThreadSafeBST::Node *node2) const {
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

/// публичные методы класса
template<typename T>
bool ThreadSafeBST<T>::operator==(const ThreadSafeBST &other) const noexcept{
    std::lock_guard<std::mutex> lock1(m_mtx);
    std::lock_guard<std::mutex> lock2(other.m_mtx);
    return isEqual(m_root.get(), other.m_root.get());
}

template<typename T>
bool ThreadSafeBST<T>::operator!=(const ThreadSafeBST &other) const noexcept{
    return !(*this == other);
}

template<typename T>
ThreadSafeBST<T> &ThreadSafeBST<T>::operator<<(ThreadSafeBST &tree) {
    add(tree);
    return *this;
}

template<typename T>
ThreadSafeBST<T> &ThreadSafeBST<T>::operator<<(T &value) {
    insert(value);
    return *this;
}

template<typename T>
ThreadSafeBST<T>::ThreadSafeBST(const ThreadSafeBST &other)  {
    std::lock_guard<std::mutex> lock(other.m_mtx);
    m_root = cloneNode(other.m_root.get());
}

template<typename T>
ThreadSafeBST<T>::ThreadSafeBST(std::initializer_list<T> initList) {
    m_root = nullptr;
    for (const T& item : initList) {
        insert(item);
    }
}

template<typename T>
template<typename InputIterator>
ThreadSafeBST<T>::ThreadSafeBST(InputIterator begin, InputIterator end) {
    m_root =nullptr;
    for (InputIterator it = begin; it != end; ++it) {
        insert(*it);
    }
}

template<typename T>
ThreadSafeBST<T>::~ThreadSafeBST() {
    clear();
}

template<typename T>
void ThreadSafeBST<T>::inorderTraversal(std::vector<T> &result) const {
    std::lock_guard<std::mutex> lock(m_mtx);
    inorderTraversal(m_root.get(), result);
}

template<typename T>
void ThreadSafeBST<T>::postorderTraversal(std::vector<T> &result) const {
    std::lock_guard<std::mutex> lock(m_mtx);
    postorderTraversal(m_root.get(), result);
}

template<typename T>
void ThreadSafeBST<T>::insert(const T &value) {
    std::lock_guard<std::mutex> lock(m_mtx);
    insert(m_root, value);
}

template<typename T>
void ThreadSafeBST<T>::add(const ThreadSafeBST &subtree) {
    std::lock_guard<std::mutex> lock(m_mtx);
    add(m_root, subtree.m_root.get());
}

template<typename T>
bool ThreadSafeBST<T>::find(const T &value) const noexcept {
    std::lock_guard<std::mutex> lock(m_mtx);
    return find(m_root.get(), value);
}

template<typename T>
ThreadSafeBST<T> ThreadSafeBST<T>::findTree(const T &value) const {
    std::lock_guard<std::mutex> lock(m_mtx);
    ThreadSafeBST subtree;
    Node* subtreem_root = findSubtree(m_root.get(), value);
    if (subtreem_root) {
        subtree.m_root = cloneNode(subtreem_root);
    }
    return subtree;
}

template<typename T>
void ThreadSafeBST<T>::remove(const T &value) {
    std::lock_guard<std::mutex> lock(m_mtx);
    remove(m_root, value);
}

template<typename T>
void ThreadSafeBST<T>::clear() noexcept {
    std::lock_guard<std::mutex> lock(m_mtx);
    clear(m_root);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const ThreadSafeBST<U> &tree) {
    std::vector<U> result;
    tree.inorderTraversal(result);
    for (const U& item : result) {
        os << item << ' ';
    }
    return os;
}

#endif //LAB2TREE_THREADBST_H

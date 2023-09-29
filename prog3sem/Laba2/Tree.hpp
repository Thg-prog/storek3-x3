#include "Tree.h"
#include <iostream>

namespace laba2{

    template <typename T>
    Tree<T>::Tree(){
        root = nullptr;
    }

    template <typename T>
    Tree<T>::Tree(T value){
        root = new Node(value);
    }

    template <typename T>
    Tree<T>::Tree(std::initializer_list<T> values) : root(nullptr) {
        for (const T& value : values) {
            add(value);
        }
    }

    template <typename T>
    Tree<T>::Tree(const Tree<T> &tree){
        std::lock_guard<std::recursive_mutex> lock(tree._mtx);
        root = new Node(tree.root->info);
        root = cloneSubtree(tree.root);
    }

    template <typename T>
    Tree<T>::Tree(Tree &&tree) noexcept{
        std::lock_guard<std::recursive_mutex> lock(tree._mtx);
        if(root != nullptr){
            root->clearNode();
            root = nullptr;
        }
        if(tree.root != nullptr){
            root = new Node(tree.root->info);
            root = cloneSubtree(tree.root);
            tree.root->clearNode();
            delete root;
        }
    }

    template <typename T>
    template <typename Iterator>
    Tree<T>::Tree(Iterator begin, Iterator end) : root(nullptr) {
        for (Iterator it = begin; it != end; ++it) {
            insert(*it);
        }
    }

    template <typename T>
    Tree<T>::~Tree(){
        clear();
    }

    template <typename T>
    Tree<T>& Tree<T>::operator=(const Tree &tree){
        std::lock_guard<std::recursive_mutex> lock1(tree._mtx);
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        if(this != *tree){
            if(root != nullptr){
            root->clearNode();
            delete root;
        }
        root = new Node(tree.root->info);
        root = cloneSubtree(tree.root);
        }
        return *this;
    }

    template <typename T>
    Tree<T>& Tree<T>::operator=(Tree &&tree) noexcept{
        std::lock_guard<std::recursive_mutex> lock(tree._mtx);
        std::lock_guard<std::recursive_mutex> lockm(_mtx);
        if(this != *tree){
            if(root != nullptr){
                root->clearNode();
                root = nullptr;
            }
            if(tree.root != nullptr){
                root = new Node(tree.root->info);
                root = cloneSubtree(tree.root);
                tree.root->clearNode();
                delete root;
            }
        }
        return *this;
    }

    template <typename T>
    typename Tree<T>::Node* Tree<T>::insertNode(Tree<T>::Node* node, const T& value) {
        if (node == nullptr) {
            return new Tree<T>::Node(value);
        }

        if (value <= node->info) {
            node->left = insertNode(node->left, value);
        } else if (value > node->info) {
            node->right = insertNode(node->right, value);
        }

        return node;
    }

    template <typename T>
    typename Tree<T>::Node* Tree<T>::insertSubtree(Tree<T>::Node* node, Tree<T>::Node* subtreeRoot) {
        if (subtreeRoot == nullptr) {
            return node;
        }

        node = insertNode(node, subtreeRoot->info);
        node = insertSubtree(node, subtreeRoot->left);
        node = insertSubtree(node, subtreeRoot->right);

        return node;
    }

    template <typename T>
    void Tree<T>::add(const T &value) noexcept{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        root = insertNode(root, value); 
    }

    template <typename T>
    void Tree<T>::add(const Tree &tree) noexcept{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        root = insertSubtree(root, tree.root);
    }

    template <typename T>
    bool Tree<T>::searchNode(const Tree<T>::Node* node, const T& value) const{
        if (root == nullptr) return false;

        if (value == node->info) return true;
        else if (value < node->info) return searchNode(node->left, value);
        else return searchNode(node->right, value);
    }

    template <typename T>
    typename Tree<T>::Node* Tree<T>::cloneSubtree(const Tree<T>::Node* node) const {
            if (node == nullptr) return nullptr;

            Node* newNode = new Node(node->info);
            newNode->left = cloneSubtree(node->left);
            newNode->right = cloneSubtree(node->right);
            return newNode;
    }

    template <typename T>
    typename Tree<T>::Node* Tree<T>::findSubtree(const Tree<T>::Node* node, const T& rootValue) const {
        if (node == nullptr)return nullptr;
        if (node->info == rootValue) return cloneSubtree(node);
        Node* leftSubtree = findSubtree(node->left, rootValue);
        if (leftSubtree != nullptr)return cloneSubtree(leftSubtree);
        Node* rightSubtree = findSubtree(node->right, rootValue);
        if (rightSubtree != nullptr)return cloneSubtree(rightSubtree);
        return nullptr;
    }

    template <typename T>
    bool Tree<T>::find(const T& value) const{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        return searchNode(root, value);
    }

    template <typename T>
    Tree<T>& Tree<T>::findTree(const T& value)const{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        Node* subtreeRoot = findSubtree(root, value);
        Tree<T> subtree;
        subtree.root = subtreeRoot;
        return subtree;
    }

    template <typename T>
    void Tree<T>::clear() noexcept{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        if(root != nullptr)root->clearNode();
        root = nullptr;
    }

    template <typename T>
    void Tree<T>::inorder(const Tree<T>::Node* node, std::vector<T>& result) const {
        if (node == nullptr) {
        return;
        }
        inorder(node->left, result);
        result.push_back(node->info);
        inorder(node->right, result);
    }

    template <typename T>
    void Tree<T>::preorder(const Tree<T>::Node* node, std::vector<T>& result) const {
        if (node == nullptr) {
            return;
        }
        result.push_back(node->info);
        preorder(node->left, result);
        preorder(node->right, result);
    }

    template <typename T>
    void Tree<T>::postorder(const Tree<T>::Node* node, std::vector<T>& result) const {
        if (node == nullptr) {
            return;
        }
        postorder(node->left, result);
        postorder(node->right, result);
        result.push_back(node->info);
    }

    template <typename T>
    std::vector<T> Tree<T>::LKP() const noexcept{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        std::vector<T> result;
        inorder(root, result);
        return result;
    }

    template <typename T>
    std::vector<T> Tree<T>::LPK() const noexcept{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        std::vector<T> result;
        preorder(root, result);
        return result;
    }

    template <typename T>
    std::vector<T> Tree<T>::KLP() const noexcept{
        std::lock_guard<std::recursive_mutex> lock(_mtx);
        std::vector<T> result;
        postorder(root, result);
        return result;
    }

    template <typename T>
    bool Tree<T>::isEqual(const Tree<T>::Node* node1, const Tree<T>::Node* node2) const {
        if (node1 == nullptr && node2 == nullptr)return true;

        if (node1 == nullptr || node2 == nullptr)return false;

        return (node1->info == node2->info) &&
            isEqual(node1->left, node2->left) &&
            isEqual(node1->right, node2->right);
        }

    template <typename T>
    bool Tree<T>::operator==(const Tree<T>& tree1)const{
        std::lock_guard<std::recursive_mutex> lock1(_mtx);
        std::lock_guard<std::recursive_mutex> lock(tree1._mtx);
        return isEqual(root, tree1.root);
    }

    template <typename T>
    bool Tree<T>::operator!=(const Tree<T>& tree1)const{
        std::lock_guard<std::recursive_mutex> lock1(_mtx);
        std::lock_guard<std::recursive_mutex> lock(tree1._mtx);
        return !isEqual(root, tree1.root);
    }

    template <typename T>
    Tree<T>& Tree<T>::operator<<(Tree<T>& tree){
        add(tree);
        return *this;
    }

    template <typename T>
    Tree<T>& Tree<T>::operator<<(T& value){
        add(value);
        return *this;
    }

    template<typename T>
    typename Tree<T>::Node* Tree<T>::getNodeWithMinimalValue(Tree<T>::Node* node)
    {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    template <typename T>
    typename Tree<T>::Node* Tree<T>::deleteNodeRecursive(Tree<T>::Node* node, const T& value){
        if (node == nullptr) return node;

        if (value < node->info) {
            node ->left = deleteNodeRecursive(node->left, value);
        } else if (value > node->info) {
            node->right = deleteNodeRecursive(node->right, value);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                Node* temp = getNodeWithMinimalValue(node->right);
                root->info = temp->info;
                node->right = this->deleteNodeRecursive(node->right, temp->info);
            }
        }

        return node;
    }

    template <typename T>
    void Tree<T>::deleteNode(T& value){
        std::lock_guard<std::recursive_mutex> lock1(_mtx);
        root = deleteNodeRecursive(root, value);
    }

    template <typename TT>
    std::ostream& operator<<(std::ostream& os, const Tree<TT>& tree){
        std::vector<TT> tmp = tree.LKP();
        for(auto i = tmp.begin(); i != tmp.end(); i++){
            os << *i << " ";
        }
        return os;
    }




}

# pragma once

#include <iostream>
#include <mutex>
#include <vector>

template <typename T>
class ThreadTree {
    struct Element {
        Element* left;
        Element* right;
        T value;
        Element(): left(nullptr), right(nullptr) {}
        Element(const T& val): value(val), left(nullptr), right(nullptr) {}
    };

    Element* head;
    mutable std::mutex mutex;

    // приватные обходы 
    void lkp_recursion(std::vector<T>& v, const Element* element) const;
    void pkl_recursion(std::vector<T>& v, const Element* element) const;
    void klp_recursion(std::vector<T>& v, const Element* element) const;
    void kpl_recursion(std::vector<T>& v, const Element* element) const;
    void lpk_recursion(std::vector<T>& v, const Element* element) const;
    void plk_recursion(std::vector<T>& v, const Element* element) const;

    void copyTree(Element*& nativeElement, const Element* otherElement);
    void insert(const T& val, Element*& el);
    void insert(Element*& subtreeElement, Element*& el);

    // для деструктора
    void deleteEl(Element*& element);

    void clearEl(Element*& element);
    bool findEl(const T& val, const Element* element) const noexcept;
    const Element* findTreeEl(const T& val, const Element* element) const noexcept;
    void removeElement(const T& value, Element*& element);
    Element* findMin(Element*& element) const noexcept;
    bool checkEqualEl(const Element* nativeElement, const Element* otherElement) const noexcept;

    public:
    ThreadTree() noexcept;
    ThreadTree(const ThreadTree& tree);
    ThreadTree(ThreadTree&& tree) noexcept;
    ThreadTree(std::initializer_list<T> list);
    template <typename Iterator>
    ThreadTree(Iterator begin, Iterator end);
    ~ThreadTree();

    // обходы
    std::vector<T> lkp() const;
    std::vector<T> pkl() const;
    std::vector<T> klp() const;
    std::vector<T> kpl() const;
    std::vector<T> lpk() const;
    std::vector<T> plk() const;

    // добавления
    void add(const T& element);
    void add(const ThreadTree& element);
    ThreadTree& operator<<(const T& element);
    ThreadTree& operator<<(const ThreadTree& element);

    // поиск
    bool find(const T& val) const noexcept;
    ThreadTree findTree(const T& value) const;

    template <typename N> 
    friend std::ostream& operator<<(std::ostream& out, const ThreadTree<N>& tree) noexcept;

    void remove(const T& value);
    void clear();

    template <typename N>
    friend bool operator==(const ThreadTree<N>& tree1, const ThreadTree<N>& tree2) noexcept;
    template <typename N>
    friend bool operator!=(const ThreadTree<N>& tree1, const ThreadTree<N>& tree2) noexcept;
};

// публичные методы

template <typename T>
ThreadTree<T>::ThreadTree() noexcept {
    head = nullptr;
}

template <typename T>
ThreadTree<T>::ThreadTree(const ThreadTree& tree) {
    head = nullptr;
    std::lock_guard<std::mutex> lock(tree.mutex);
    copyTree(head, tree.head);
}

template <typename T>
ThreadTree<T>::ThreadTree(ThreadTree&& tree) noexcept {
    std::lock_guard<std::mutex> lock(tree.mutex);
    head = tree.head;
    tree.head = nullptr;
}

template <typename T>
ThreadTree<T>::ThreadTree(std::initializer_list<T> list) {
    head = nullptr;
    for (const auto& value: list) {
        add(value);
    }
}

template <typename T>
template <typename Iterator>
ThreadTree<T>::ThreadTree(Iterator begin, Iterator end) {
    head = nullptr;
    int size = std::distance(begin, end);
    for (auto it = begin; it != end; it++) {
        add(*it);
    }
}

template <typename T>
ThreadTree<T>::~ThreadTree() {
    deleteEl(head);
}

template <typename T>
std::vector<T> ThreadTree<T>::lkp() const {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<T> v;
    lkp_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::kpl() const {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<T> v;
    kpl_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::klp() const {
    std::vector<T> v;
    klp_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::pkl() const {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<T> v;
    pkl_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::lpk() const {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<T> v;
    lpk_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::plk() const {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<T> v;
    plk_recursion(v, head);
    return v;
}

template <typename T>
void ThreadTree<T>::add(const T& element) {
    std::lock_guard<std::mutex> lock(mutex);
    insert(element, head);
}

template <typename T>
void ThreadTree<T>::add(const ThreadTree& element) {
    std::lock_guard<std::mutex> lock(mutex);
    ThreadTree<T> tree(element);
    insert(tree.head, head);
}

template <typename T>
ThreadTree<T>& ThreadTree<T>::operator<<(const T& element) {
    add(element);
    return *this;
}

template <typename T>
ThreadTree<T>& ThreadTree<T>::operator<<(const ThreadTree& element) {
    add(element);
    return *this;
}

template <typename T>
bool ThreadTree<T>::find(const T& val) const noexcept {
    std::lock_guard<std::mutex> lock(mutex);
    return findEl(val, head);
}

template <typename T>
ThreadTree<T> ThreadTree<T>::findTree(const T& value) const {
    std::lock_guard<std::mutex> lock(mutex);
    ThreadTree<T> subtree;
    const Element* el = findTreeEl(value, head);
    subtree.copyTree(subtree.head, el);
    return subtree;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ThreadTree<T>& tree) noexcept {
    std::vector<T> v = tree.lkp();
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        out << v[i] << " ";
    }
    out << "\n";
    return out;
}

template <typename T>
void ThreadTree<T>::remove(const T& value) {
    std::lock_guard<std::mutex> lock(mutex);
    removeElement(value, head);
}

template <typename T>
void ThreadTree<T>::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    clearEl(head);
}

template <typename T>
bool operator==(const ThreadTree<T>& tree1, const ThreadTree<T>& tree2) noexcept {
    std::lock_guard<std::mutex> lock1(tree1.mutex);
    std::lock_guard<std::mutex> lock2(tree2.mutex);
    return tree1.checkEqualEl(tree1.head, tree2.head);
}

template <typename T>
bool operator!=(const ThreadTree<T>& tree1, const ThreadTree<T>& tree2) noexcept {
    return !(tree1 == tree2);
}


// приватные методы


template <typename T>
void ThreadTree<T>::lkp_recursion(std::vector<T>& v, const Element* element) const {
    if (element == nullptr) return;
    if (element->left != nullptr) lkp_recursion(v, element->left);
    v.push_back(element->value);
    if (element->right != nullptr) lkp_recursion(v, element->right);
}

template <typename T>
void ThreadTree<T>::pkl_recursion(std::vector<T>& v, const Element* element) const {
    if (element == nullptr) return;
    if (element->right != nullptr) pkl_recursion(v, element->right);
    v.push_back(element->value);
    if (element->left != nullptr) pkl_recursion(v, element->left);
}

template <typename T>
void ThreadTree<T>::klp_recursion(std::vector<T>& v, const Element* element) const {
    if (element == nullptr) return;
    v.push_back(element->value);
    if (element->left != nullptr) klp_recursion(v, element->left);
    if (element->right != nullptr) klp_recursion(v, element->right);
}

template <typename T>
void ThreadTree<T>::kpl_recursion(std::vector<T>& v, const Element* element) const {
    if (element == nullptr) return;
    v.push_back(element->value);
    if (element->right != nullptr) kpl_recursion(v, element->right);
    if (element->left != nullptr) kpl_recursion(v, element->left);
}

template <typename T>
void ThreadTree<T>::lpk_recursion(std::vector<T>& v, const Element* element) const {
    if (element == nullptr) return;
    if (element->left != nullptr) lpk_recursion(v, element->left);
    if (element->right != nullptr) lpk_recursion(v, element->right);
    v.push_back(element->value);
}

template <typename T>
void ThreadTree<T>::plk_recursion(std::vector<T>& v, const Element* element) const {
    if (element == nullptr) return;
    if (element->right != nullptr) plk_recursion(v, element->right);
    if (element->left != nullptr) plk_recursion(v, element->left);
    v.push_back(element->value);
}

template <typename T>
void ThreadTree<T>::copyTree(Element*& nativeElement, const Element* otherElement) {
    if (otherElement != nullptr) {
        nativeElement = new Element(otherElement->value);
        if (otherElement->left != nullptr) copyTree(nativeElement->left, otherElement->left);
        if (otherElement->right != nullptr) copyTree(nativeElement->right, otherElement->right);
    }
}

template <typename T>
void ThreadTree<T>::insert(const T& val, Element*& el) {
    if (el == nullptr) {
        el = new Element(val);
    } else if (val < el->value) {
        insert(val, el->left);
    } else {
        insert(val, el->right);
    }
}

template <typename T>
void ThreadTree<T>::insert(Element*& treeElement, Element*& el) {
    if (treeElement == nullptr || el == nullptr) return;
    insert(treeElement->value, el);
    insert(treeElement->left, el);
    insert(treeElement->right, el);
}

template <typename T>
void ThreadTree<T>::deleteEl(Element*& element) {
    if (element != nullptr) {
        if (element->left != nullptr) deleteEl(element->left);
        if (element->right != nullptr) deleteEl(element->right);
        delete element;
    }
}

template <typename T>
void ThreadTree<T>::clearEl(Element*& element) {
    if (element != nullptr) {
        if (element->left != nullptr) deleteEl(element->left);
        if (element->right != nullptr) deleteEl(element->right);
        element = nullptr;
    }
}

template <typename T>
bool ThreadTree<T>::findEl(const T& val, const Element* el) const noexcept {
    if (el != nullptr) {
        bool b1 = findEl(val, el->left);
        bool b2 = findEl(val, el->right);
        return (el->value == val) || b1 || b2;
    }
    return false;
}

template <typename T>
const typename ThreadTree<T>::Element* ThreadTree<T>::findTreeEl(const T& val, const Element* el) const noexcept {
    if (el == nullptr) {
        return nullptr;
    }
    if (val == el->value) {
        return el;
    } else if (val < el->value) {
        return findTreeEl(val, el->left);
    } else {
        return findTreeEl(val, el->right);
    }
}

template <typename T>
void ThreadTree<T>::removeElement(const T& value, Element*& element) {
    if (element == nullptr) {
        return;
    }
    if (value < element->value) {
        removeElement(value, element->left);
    } else if (value > element->value) {
        removeElement(value, element->right);
    } else {
        if (element->left == nullptr && element->right == nullptr) {
            delete element;
            element = nullptr;
        } else if (element->left == nullptr) {
            Element* temp = element;
            element = element->right;
            delete temp;
        } else if (element->right == nullptr) {
            Element* temp = element;
            element = element->left;
            delete temp;
        } else {
            Element* min = findMin(element->right);
            element->value = min->value;
            removeElement(min->value, element->right);
        }
    }
}

template <typename T>
typename ThreadTree<T>::Element* ThreadTree<T>::findMin(Element*& element) const noexcept {
    while (element->left) {
        element = element->left;
    }
    return element;
}

template <typename T>
bool ThreadTree<T>::checkEqualEl(const Element* nativeElement, const Element* otherElement) const noexcept {
    if (nativeElement == nullptr && otherElement == nullptr) {
        return true;
    } else if (!(nativeElement != nullptr) != !(otherElement != nullptr)) {
        return false;
    } else if (nativeElement->value == otherElement->value) {
        return (nativeElement->value == otherElement->value) && checkEqualEl(nativeElement->left, otherElement->left) &&
               checkEqualEl(nativeElement->right, otherElement->right);
    }
    return false;
}

#include <iostream>
#include <mutex>
#include <vector>

template <typename T>
class ThreadTree {
    struct Element {
        Element* left;
        Element* right;
        T value;
        Element() { left=nullptr; right=nullptr; }
        Element(const T& val) {
            value = val;
            left = nullptr;
            right = nullptr;
        }
    };

    Element* head;
    std::mutex mutex;

    void lkp_recursion(std::vector<T>& v, const Element* element) const;
    void pkl_recursion(std::vector<T>& v, const Element* element) const;
    void klp_recursion(std::vector<T>& v, const Element* element) const;
    void kpl_recursion(std::vector<T>& v, const Element* element) const;
    void lpk_recursion(std::vector<T>& v, const Element* element) const;
    void plk_recursion(std::vector<T>& v, const Element* element) const;
    void copyTree(Element*& nativeElement, const Element* otherElement);
    void moveTree(Element*& nativeElement, Element*& otherElement);
    void insert(const T& val, Element*& el);
    void insert(const ThreadTree& val, Element*& el);
    void deleteEl(Element*& element);
    public:
    ThreadTree();
    ThreadTree(const ThreadTree& tree);
    ThreadTree(ThreadTree&& tree) noexcept;
    ThreadTree(std::initializer_list<T> list);
    template <typename Iterator>
    ThreadTree(Iterator begin, Iterator end);
    ~ThreadTree();
    std::vector<T> lkp() const noexcept;
    std::vector<T> pkl() const noexcept;
    std::vector<T> klp() const noexcept;
    std::vector<T> kpl() const noexcept;
    std::vector<T> lpk() const noexcept;
    std::vector<T> plk() const noexcept;
    void add(const T& element);
    void add(const ThreadTree& element);
    // ThreadTree& operator<<(const Element& element);
    // bool find(const T& val) const noexcept;
    // ThreadTree findTree(const T& value) const noexcept;
    template <typename N> 
    friend std::ostream& operator<<(std::ostream& out, const ThreadTree<N>& stack) noexcept; 
    // void delete(const T& value);
    // void clear();
    // bool operator==(const Stack& stack) const noexcept;
    // bool operator!=(const Stack& stack) const noexcept;
};

template <typename T>
ThreadTree<T>::ThreadTree() {
    head = nullptr;
}

template <typename T>
ThreadTree<T>::ThreadTree(const ThreadTree<T>& tree) {
    copyTree(head, tree.head);
}

template <typename T>
ThreadTree<T>::ThreadTree(ThreadTree<T>&& tree) noexcept {
    moveTree(head, tree.head);
    tree.head = nullptr;
}

template <typename T>
ThreadTree<T>::ThreadTree(std::initializer_list<T> list) {
    head = nullptr;
    for (const T* p = list.begin(); p != list.end(); p++) {
        add(*p);
    }
}

template <typename T>
template <typename Iterator>
ThreadTree<T>::ThreadTree(Iterator begin, Iterator end) {
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
std::vector<T> ThreadTree<T>::lkp() const noexcept {
    std::vector<T> v;
    lkp_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::kpl() const noexcept {
    std::vector<T> v;
    kpl_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::klp() const noexcept {
    std::vector<T> v;
    klp_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::pkl() const noexcept {
    std::vector<T> v;
    pkl_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::lpk() const noexcept {
    std::vector<T> v;
    lpk_recursion(v, head);
    return v;
}

template <typename T>
std::vector<T> ThreadTree<T>::plk() const noexcept {
    std::vector<T> v;
    plk_recursion(v, head);
    return v;
}

template <typename T>
void ThreadTree<T>::add(const T& element) {
    insert(element, head);
}

template <typename T>
void ThreadTree<T>::add(const ThreadTree<T>& element) {
    insert(element, head);
}

template <typename T>
void ThreadTree<T>::lkp_recursion(std::vector<T>& v, const Element* element) const {
    if (element->left != nullptr) lkp_recursion(v, element->left);
    v.push_back(element->value);
    if (element->right != nullptr) lkp_recursion(v, element->right);
}

template <typename T>
void ThreadTree<T>::pkl_recursion(std::vector<T>& v, const Element* element) const {
    if (element->right != nullptr) pkl_recursion(v, element->right);
    v.push_back(element->value);
    if (element->left != nullptr) pkl_recursion(v, element->left);
}

template <typename T>
void ThreadTree<T>::klp_recursion(std::vector<T>& v, const Element* element) const {
    v.push_back(element->value);
    if (element->left != nullptr) klp_recursion(v, element->left);
    if (element->right != nullptr) klp_recursion(v, element->right);
}

template <typename T>
void ThreadTree<T>::kpl_recursion(std::vector<T>& v, const Element* element) const {
    v.push_back(element->value);
    if (element->right != nullptr) kpl_recursion(v, element->right);
    if (element->left != nullptr) kpl_recursion(v, element->left);
}

template <typename T>
void ThreadTree<T>::lpk_recursion(std::vector<T>& v, const Element* element) const {
    if (element->left != nullptr) lpk_recursion(v, element->left);
    if (element->right != nullptr) lpk_recursion(v, element->right);
    v.push_back(element->value);
}

template <typename T>
void ThreadTree<T>::plk_recursion(std::vector<T>& v, const Element* element) const {
    if (element->right != nullptr) plk_recursion(v, element->right);
    if (element->left != nullptr) plk_recursion(v, element->left);
    v.push_back(element->value);
}

template <typename T>
void ThreadTree<T>::copyTree(Element*& nativeElement, const Element* otherElement) {
    nativeElement = new Element(otherElement->value);
    if (otherElement->left != nullptr) copyTree(nativeElement->left, otherElement->left);
    if (otherElement->right != nullptr) copyTree(nativeElement->right, otherElement->right);
}

template <typename T>
void ThreadTree<T>::moveTree(Element*& nativeElement, Element*& otherElement) {
    nativeElement = new Element(otherElement->value);
    if (otherElement->left != nullptr) moveTree(nativeElement->left, otherElement->left);
    if (otherElement->right != nullptr) moveTree(nativeElement->right, otherElement->right);
    otherElement = nullptr;
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
void ThreadTree<T>::insert(const ThreadTree& val, Element*& el) {
    if (el == nullptr) {
        copyTree(el, val.head);
    } else if (val < el->value) {
        insert(val, el->left);
    } else {
        insert(val, el->right);
    }
}

template <typename T>
void ThreadTree<T>::deleteEl(Element*& element) {
    if (element->left != nullptr) deleteEl(element->left);
    if (element->right != nullptr) deleteEl(element->left);
    delete element;
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
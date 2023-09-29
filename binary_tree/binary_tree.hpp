#include <iostream>
#include <mutex>

template <typename T>
class ThreadTree {
    public:
    ThreadTree();
    ThreadTree(const ThreadTree& tree);
    ThreadTree(ThreadTree&& tree) noexcept;
    ThreadTree(std::initializer_list<T> list);
    template <typename Iterator>
    ThreadTree(Iterator begin, Iterator end);
    ~ThreadTree();
};

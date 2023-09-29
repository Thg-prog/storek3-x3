#include <mutex>
#include <vector>

namespace laba2{
    template <typename T>
    class Tree{
        private:
            class Node{
                public:
                    T info;
                    Node* right;
                    Node* left;

                    explicit Node(T value) : info(value){
                        right = nullptr;
                        left = nullptr;
                    }

                    void clearNode(){
                        if(right != nullptr){
                            right->clearNode();
                            delete right;
                            right = nullptr;
                        }
                        if(left != nullptr){
                            left->clearNode();
                            delete left;
                            left = nullptr;
                        }
                        info = 0;
                    }
            };

            Node* root;

            mutable std::recursive_mutex _mtx;

            Node* insertNode(Node* node, const T& value);

            Node* insertSubtree(Node* node, Node* subtreeRoot);

            bool searchNode(const Node* node, const T& value) const;

            Node* findSubtree(const Node* node, const T& rootValue) const;

            Node* cloneSubtree(const Node* node) const;

            Node* deleteNodeRecursive(Node* node, const T& value);
 
            void inorder(const Node* node, std::vector<T>& result) const;

            void preorder(const Node* node, std::vector<T>& result) const;

            void postorder(const Node* node, std::vector<T>& result) const;

            bool isEqual(const Node* node1, const Node* node2) const;

            Node* getNodeWithMinimalValue(Node* node);

        public:
            Tree();
            Tree(T value);
            Tree(const Tree &tree);
            Tree& operator=(const Tree &tree);
            Tree(Tree &&tree) noexcept;
            Tree& operator=(Tree &&tree) noexcept;
            Tree(std::initializer_list<T> list);
            template <typename Iterator>
            Tree(Iterator begin, Iterator end);
            ~Tree();


            void add(const T &value) noexcept;
            void add(const Tree &tree) noexcept;

            bool find(const T& value)const;
            Tree& findTree(const T& value)const;

            std::vector<T> LKP() const noexcept;
            std::vector<T> LPK() const noexcept;
            std::vector<T> KLP() const noexcept;

            void deleteNode(T& value);
            void clear() noexcept;

            bool operator==(const Tree& tree1)const;
            bool operator!=(const Tree& tree1)const;

            Tree& operator<<(Tree& tree);
            Tree& operator<<(T& value);

            template <typename TT>friend std::ostream& operator<<(std::ostream& os, const Tree<TT>& tree);


    };
};
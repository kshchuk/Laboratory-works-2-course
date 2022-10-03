#pragma once 


#include <random>
#include <list>

 // For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif

/// @brief Class to store comparative values
/// @tparam T 
template<typename T>
class AVLTree
{
private:
    struct Node
    {
        T data;;
        Node* left = nullptr;
        Node* right = nullptr;
        int height;

        Node(T data)
            : data(data), height(1) {}
    };

    Node* root = nullptr;

    int height(Node* node) const
    {
        if (!node)
            return 0;
        return node->height;
    }

    /// @brief Right rotates subtree rooted with y
    /// @param y Subtree to rotate
    /// @return Link to the root of the rotated subtree
    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    };

    /// @brief Left rotates subtree rooted with y
    /// @param x Subtree to rotate
    /// @return Link to the root of the rotated subtree
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left),
            height(x->right)) + 1;
        y->height = std::max(height(y->left),
            height(y->right)) + 1;

        return y;
    }

    /// @brief Checks balance of the subtree
    /// @param node Node to check
    /// @return Difference between heights of the node's childrens
    int getBalance(Node* node) const
    {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    /// @brief Recursive function to insert a key in the subtree
    /// @param node Subtree root
    /// @param data Value to insert
    /// @return The new root of the subtree
    Node* insert(Node* node, T data)
    {
        if (!node)
            return new Node(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));


        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) const
    {
        Node* current = node;
        while (current->left != nullptr)
        current = current->left;
 
        return current;
    }

    /// @brief Removes node with the specified value, recursively
    /// @param node Current subtree node
    /// @param data Value to remove
    /// @return New subtree root
    Node* deleteNode(Node* node, T data)
    {
        if (!node)
            return node;

        if (data < node->data)
            node->left = deleteNode(node->left, data);

        else if (data > node->data)
            node->right = deleteNode(node->right, data);

        else
        {
            // node with only one child or no child
            if (!(node->left) || !(node->right))
            {
                Node* temp = node->left ?
                    node->left :
                    node->right;

                // No child case
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else // One child case
                    *node = *temp;
                delete temp;
            }
            else
            {
                // node with two children
                // successor (smallest in the right subtree)
                Node* temp = minValueNode(node->right);

                node->data = temp->data;

                // Delete the inorder successor
                node->right = deleteNode(node->right, temp->data);
            }
        }

        // If the tree had only one node
        if (!node)
            return node;

        // Updating height
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Checking if balanced
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 &&
            getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    /// @brief Searches specified value recursively
    /// @param node Current subtree root
    /// @param data Value to find
    /// @return New subtree root
    Node* search(Node* node, T data) const
    {
        if (node == nullptr || node->data == data)
            return node;

        if (node->data < data)
            return search(node->right, data);

        return search(node->left, data);
    }

    /// @brief Searching data by elements range recursively
    /// @param node Current subtree node
    /// @param interval Storage to save found values
    /// @param min Min value
    /// @param max Max value
    void searchElementsByInterval(Node* node, std::list<T>& interval, T& min, T& max) const
    {
        if (!node)
            return;

        if (min < node->data)
            searchElementsByInterval(node->left, interval, min, max);

        if (min <= node->data && max >= node->data)
            interval.push_back(node->data);

        searchElementsByInterval(node->right, interval, min, max);
    }

    void clearRecursive(Node* node) {
        if (!node)
            return;

        clearRecursive(node->left);
        clearRecursive(node->right);

        delete node;
    }

    /// @brief Respresents tree as array, recursively
    /// @param elements Container to save elements
    /// @param node Current node
    void InOrder(std::vector<T>& elements, Node* node = nullptr) const
    {
        if (!node)
            node = root;
        if (!root)
            return;

        if (node->left)
            InOrder(elements, node->left);
        elements.push_back(node->data);
        if (node->right)
            InOrder(elements, node->right);
    }

public:

    /// @brief Inserts value to the tree
    /// @param data Value to insert
    /// @param node Current subtree node
    void append(T data, AVLTree<T>::Node* node = nullptr)
    {
        root = insert(this->root, data); // appending recursively
    }

    /// @brief Removes tree element with the specified value
    /// @param data Value to remove
    void remove(T data)
    {
        this->root = deleteNode(this->root, data);
    }

    bool GetElem(T data) const{
        return search(this->root, data);
    }

    std::list<T> GetElementsByInterval(T min, T max) const
    {
        std::list<T> interval;
        searchElementsByInterval(this->root, interval, min, max);
        return interval;
    }

    void print(Node* node = nullptr) const
    {
        if (!node)
            node = root;
        if (!root)
            return;

        if (node->left)
            print(node->left);
        std::cout << node->data << std::endl;
        if (node->right)
            print(node->right);
    }

    void IncrementElemByOne(Node* node = nullptr) {
        if (!node)
            node = root;
        if (!root)
            return;

        if (node->left)
            IncrementElemByOne(node->left);
        ++(node->data);
        if (node->right)
            IncrementElemByOne(node->right);
    }

    void clear() {
        if (!root)
            return;

        clearRecursive(this->root);

        root = nullptr;
    }

    void FillRandom(size_t size) {
        for (size_t i = 0; i < size; i++) {
            T elem;
            elem.random();
            this->append(elem);
        }
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    /// @brief Gets maximum tree element 
    /// @return Maximum element
    T GetMax() const
    {
        Node* cur = root;
        while (cur->right != nullptr)
        {
            cur = cur->right;
        }
        return cur->data;
    }

    ~AVLTree()
    {
        this->clear();
    }


#ifdef BENCHMARK_BENCHMARK_H_

private:

    static void append_AVLTree_BM(benchmark::State& state)
    {
        AVLTree avl;
        avl.FillRandom(state.range(0));

        for (auto _ : state) {
            T data;
            data.random();
            avl.append(data);
        }

        avl.clear();
    }

    static void get_element_AVLTree_BM(benchmark::State& state)
    {
        AVLTree avl;
        avl.FillRandom(state.range(0));

        std::vector<T> elements;
        avl.InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        for (auto _ : state) {
            avl.GetElem(elements[mersenne() % elements.size()]);
        }

        avl.clear();
    }

    static void get_elements_interval_AVLTree_BM(benchmark::State& state)
    {
        AVLTree avl;
        avl.FillRandom(state.range(0));

        std::vector<T> elements;
        avl.InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        size_t start, end;

        for (auto _ : state) {
            start = mersenne() % elements.size(); end = mersenne() % elements.size();
            if (start > end) std::swap(start, end);
            avl.GetElementsByInterval(elements[start], elements[end]);
        }

        avl.clear();
    }

    static void remove_element_AVLTree_BM(benchmark::State& state)
    {
        AVLTree avl;
        avl.FillRandom(state.range(0));

        std::vector<T> elements;
        avl.InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        for (auto _ : state) {
            avl.remove(elements[mersenne() % elements.size()]);
        }

        avl.clear();
    }

    static void increase_AVLTree_BM(benchmark::State& state)
    {
        AVLTree avl;
        avl.FillRandom(state.range(0));

        for (auto _ : state) {
            avl.IncrementElemByOne();
        }

        avl.clear();
    }

    static void fill_random_AVLTree_BM(benchmark::State& state)
    {
        AVLTree avl;

        for (auto _ : state) {
            avl.FillRandom(state.range(0));
        }

        avl.clear();
    }

    static void fill_random_ascending_order_AVLTree_BM(benchmark::State& state)
    {
        AVLTree tree;

        T elem; elem.random();

        for (auto _ : state) {
            for (size_t i = 0; i < state.range(0); i++) {
                tree.append(++elem);
            }
        }
        tree.clear();
    }

    static void fill_random_descending_order_AVLTree_BM(benchmark::State& state)
    {
        AVLTree tree;

        T elem; elem.random();

        for (auto _ : state) {
            for (size_t i = 0; i < state.range(0); i++) {
                tree.append(--elem);
            }
        }
        tree.clear();
    }


public:

    // Appends benchmarking function to the benchmarking queue
    void append_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(append_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void GetElem_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(get_element_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void GetElementsByInterval_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(get_elements_interval_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void remove_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(remove_element_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void IncreaseByOne_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(increase_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandom_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandomAscendingOrder_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_ascending_order_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandomDescendingOrder_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_descending_order_AVLTree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }

#endif

};


#undef private
#undef protected
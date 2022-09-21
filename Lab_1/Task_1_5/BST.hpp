#pragma once

#include <list>

template<typename T>
class BST
{
private:
    struct Node {
        T data;
        Node* left = nullptr, * right = nullptr;

        Node(T data)
            : data(data) {}
    };

    Node* root = nullptr;


    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    // Deleting node recursively
    Node* deleteNode(Node* node, T data)
    {
        if (node == nullptr)
            return node;

        if (data < node->data)
            node->left = deleteNode(node->left, data);

        else if (data > node->data)
            node->right = deleteNode(node->right, data);

        else {
            if (node->left == nullptr && node->right == nullptr)
                return nullptr;

            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);

            node->data = temp->data;

            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Searching node recursively
    Node* search(Node* node, T data) {
        if (node == nullptr || node->data == data)
            return node;

        if (node->data < data)
            return search(node->right, data);

        return search(node->left, data);
    }

    // Searching nodes by elements range recursively
    void searchElementsByInterval(Node* node, std::list<T>& interval, T& min, T& max) {
        if (!node)
            return;

        if (min < node->data)
            searchElementsByInterval(node->left, interval, min, max);

        if (min <= node->data && max >= node->data)
            interval.push_back(node->data);

        searchElementsByInterval(node->right, interval, min, max);
    }

    void InOrder(std::vector<T>& elements, Node* node = nullptr) {
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

    void clearRecursive(Node* node) {
        if (!node)
            return;

        clearRecursive(node->left);
        clearRecursive(node->right);

        delete node;
    }

public:
    // Default constructor exists

    bool isEmpty()
    {
        return root == nullptr;
    }

    void append(T data, BST<T>::Node* node = nullptr) {
        if (!root) {
            root = new Node(data);
            return;
        }
        if (!node)
            node = root;

        if (data < node->data)
        {
            if (!node->left) {
                node->left = new Node(data);
                return;
            }
            else
                append(data, node->left);
        }

        if (data > node->data)
        {
            if (!node->right) {
                node->right = new Node(data);
                return;
            }
            else
                append(data, node->right);
        }
    }

    void remove(T data) {
        this->root = deleteNode(this->root, data);
    }

    bool GetElem(T data) {
        return (search(this->root, data) != nullptr);
    }

    std::list<T> GetElementsByInterval(T min, T max) {
        std::list<T> interval;
        searchElementsByInterval(this->root, interval, min, max);
        return interval;
    }

    void print(Node* node = nullptr) {
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

    void FillRandom(size_t size) {
        for (size_t i = 0; i < size; i++) {
            T elem;
            elem.random();
            this->append(elem);
        }
    }

    void clear() {
        if (!root)
            return;

        clearRecursive(this->root);

        root = nullptr;
    }

    T GetMax()
    {
        Node* cur = root;
        while (cur != nullptr)
        {
            cur = cur->right
        }
        return cur->data;
    }

#ifdef BENCHMARK_BENCHMARK_H_

private:

    static void append_BST_BM(benchmark::State& state)
    {
        BST bst;
        bst.FillRandom(state.range(0));

        for (auto _ : state) {
            T data;
            data.random();
            bst.append(data);
        }

        bst.clear();
    }

    static void get_element_BST_BM(benchmark::State& state)
    {
        BST bst;
        bst.FillRandom(state.range(0));

        std::vector<T> elements;
        bst.InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        for (auto _ : state) {
            bst.GetElem(elements[mersenne() % elements.size()]);
        }

        bst.clear();
    }

    static void get_elements_interval_BST_BM(benchmark::State& state)
    {
        BST bst;
        bst.FillRandom(state.range(0));

        std::vector<T> elements;
        bst.InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        size_t start, end;

        for (auto _ : state) {
            start = mersenne() % elements.size(); end = mersenne() % elements.size();
            if (start > end) std::swap(start, end);
            bst.GetElementsByInterval(elements[start], elements[end]);
        }

        bst.clear();
    }

    static void remove_element_BST_BM(benchmark::State& state)
    {
        BST bst;
        bst.FillRandom(state.range(0));

        std::vector<T> elements;
        bst.InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        for (auto _ : state) {
            bst.remove(elements[mersenne() % elements.size()]);
        }

        bst.clear();
    }

    static void increase_BST_BM(benchmark::State& state)
    {
        BST bst;
        bst.FillRandom(state.range(0));

        for (auto _ : state) {
            bst.IncrementElemByOne();
        }

        bst.clear();
    }

    static void fill_random_BST_BM(benchmark::State& state)
    {
        BST bst;

        for (auto _ : state) {
            bst.FillRandom(state.range(0));
        }

        bst.clear();
    }

    static void fill_random_ascending_order_BST_BM(benchmark::State& state)
    {
        BST bst;

        T elem; elem.random();

        for (auto _ : state) {
            for (size_t i = 0; i < state.range(0); i++) {
                bst.append(++elem);
            }
        }
        //bst.clear();
    }

    static void fill_random_descending_order_BST_BM(benchmark::State& state)
    {
        BST bst;

        T elem; elem.random();

        for (auto _ : state) {
            for (size_t i = 0; i < state.range(0); i++) {
                bst.append(--elem);
            }
        }
        bst.clear();
    }

public:

    // Appends benchmarking function to the benchmarking queue
    void append_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(append_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void GetElem_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(get_element_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void GetElementsByInterval_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(get_elements_interval_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void remove_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(remove_element_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void IncreaseByOne_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(increase_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandom_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandomAscendingOrder_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_ascending_order_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandomDescendingOrder_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_descending_order_BST_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }

    void BenchmarkTheQueue() {
        ::benchmark::RegisterMemoryManager;
        ::benchmark::RunSpecifiedBenchmarks();
    }


#endif

};
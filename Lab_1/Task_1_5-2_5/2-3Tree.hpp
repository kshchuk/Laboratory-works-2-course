#pragma once

#include <cassert>
#include <list>

// For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif

/// @brief Extra class for 2-3Tre
/// @tparam T 
template <typename T>
struct TreeNode {
    T data[2];
    int size; // number of data items
    TreeNode* children[3];
    TreeNode* parent; //TODO: can be removed


    TreeNode(T data1, TreeNode* parent = nullptr) {
        this->data[0] = data1;
        this->size = 1;
        children[0] = children[1] = children[2] = nullptr;
        this->parent = parent;
    }

    TreeNode(T data1, T data2, TreeNode* parent = nullptr) {
        this->data[0] = data1;
        this->data[1] = data2;
        this->size = 2;
        children[0] = children[1] = children[2] = nullptr;
        this->parent = parent;
    }

    TreeNode(T data1, T data2, T data3, TreeNode* parent = nullptr) {
        //assert(data1 <= data2);
        //assert(data2 <= data3);

        this->data[0] = data2;
        this->size = 1;
        this->children[0] = new TreeNode(data1, this);
        this->children[1] = new TreeNode(data3, this);
        this->children[2] = nullptr;

        this->parent = parent;
    }

    void add_single_data(T data) {
        assert(size == 1);
        if (data > this->data[0]) {
            this->data[1] = data;
            size = 2;
        }
        else {
            this->data[1] = this->data[0];
            this->data[0] = data;
            size = 2;
        }
    }

    /// @brief Adds element to the TreeNode
    /// @param new_data Value to insert
    /// @return Nullptr if added, else "4-node" (2-node with both children as 2-nodes)
    TreeNode* add_and_split(T new_data) {
        if (children[0] == nullptr) {
            if (size == 1) {
                add_single_data(new_data);
                return nullptr;
            }
            else {
                if (new_data < data[0]) {
                    return new TreeNode(new_data, data[0], data[1]);
                }
                else if (new_data < data[1]) {
                    return new TreeNode(data[0], new_data, data[1]);
                }
                else {
                    return new TreeNode(data[0], data[1], new_data);
                }
            }
        }
        TreeNode* extra = nullptr;
        if (size == 1) {
            if (new_data < data[0]) {
                extra = children[0]->add_and_split(new_data);
                if (!extra) { return nullptr; }
                data[1] = data[0];
                data[0] = extra->data[0];
                children[2] = children[1];
                children[0] = extra->children[0];
                children[1] = extra->children[1];
                size = 2;
                return nullptr;
            }
            else {
                extra = children[1]->add_and_split(new_data);
                if (!extra) { return nullptr; }
                data[1] = extra->data[0];
                children[1] = extra->children[0];
                children[2] = extra->children[1];
                size = 2;
                return nullptr;
            }
        }
        else {
            if (new_data < data[0]) {
                extra = children[0]->add_and_split(new_data);
                if (!extra) { return nullptr; }
                TreeNode* result = new TreeNode(extra->data[0], data[0], data[1]);
                result->children[0]->children[0] = extra->children[0];
                result->children[0]->children[1] = extra->children[1];
                result->children[1]->children[0] = children[1];
                result->children[1]->children[1] = children[2];
                return result;
            }
            else if (new_data < data[1]) {
                extra = children[1]->add_and_split(new_data);
                if (!extra) { return nullptr; }
                TreeNode* result = new TreeNode(data[0], extra->data[0], data[1]);
                result->children[0]->children[0] = children[0];
                result->children[0]->children[1] = extra->children[0];
                result->children[1]->children[0] = extra->children[1];
                result->children[1]->children[1] = children[2];
                return result;
            }
            else {
                extra = children[2]->add_and_split(new_data);
                if (!extra) { return nullptr; }
                TreeNode* result = new TreeNode(data[0], data[1], extra->data[0]);
                result->children[0]->children[0] = children[0];
                result->children[0]->children[1] = children[1];
                result->children[1]->children[0] = extra->children[0];
                result->children[1]->children[1] = extra->children[1];
                return result;
            }
        }
    }


    TreeNode* find_max_subtree()
    {
        if (children[2]) {
            assert(size == 2);
            return children[2]->find_max_subtree();
        }
        if (children[1]) {
            assert(size == 1);
            return children[1]->find_max_subtree();
        }
        assert(children[0] == nullptr);
        return this; // no children
    }

    T get_max_data() const
    {
        if (size == 2) {
            return data[1];
        }
        else {
            return data[0];
        }
    }
    enum RemoveResult { Removed, NotFound, NeedParentRemove };

    /// @brief Reabalance subtree
    /// @param index_current_child 
    /// @return True if rebalance complete - no need to rebalance parent
    bool rebalance(int index_current_child) {
        assert(index_current_child < size + 1);
        TreeNode* current_child = children[index_current_child];
        assert(current_child);
        assert(current_child->size == 0);
        TreeNode* left_child = nullptr;
        if (index_current_child > 0) { left_child = children[index_current_child - 1]; }
        TreeNode* right_child = (index_current_child < size) ?
            children[index_current_child + 1] :
            nullptr;
        assert(left_child != nullptr || right_child != nullptr);

        if (left_child && left_child->size == 2) {
            current_child->data[0] = this->data[index_current_child - 1];
            this->data[index_current_child - 1] = left_child->data[1];

            current_child->children[1] = current_child->children[0];
            current_child->children[0] = left_child->children[2];

            current_child->size = 1;
            left_child->size = 1;
            return true;
        }

        if (right_child && right_child->size == 2) {
            current_child->data[0] = this->data[index_current_child + 1];
            this->data[index_current_child + 1] = right_child->data[0];
            right_child->data[0] = right_child->data[1];

            current_child->children[1] = right_child->children[0];
            right_child->children[0] = right_child->children[1];
            right_child->children[1] = right_child->children[2];
            right_child->children[2] = nullptr;

            current_child->size = 1;
            right_child->size = 1;
            return true;
        }

        if (left_child) {
            assert(left_child->size == 1);

            left_child->data[1] = this->data[index_current_child - 1];

            left_child->children[2] = current_child->children[0];

            left_child->size = 2;
            this->size--;

            if (this->size == 1 && index_current_child == 1) {
                this->data[0] = this->data[1];
                this->children[1] = this->children[2];
                return true;
            }
            if (this->size == 0) {
                return false;
            }
            else {
                return true;
            }
        }
        assert(right_child != nullptr);
        assert(right_child->size == 1);

        right_child->data[1] = right_child->data[0];
        right_child->data[0] = this->data[index_current_child + 1];

        right_child->children[2] = right_child->children[1];
        right_child->children[1] = right_child->children[0];
        right_child->children[0] = current_child->children[0];

        right_child->size = 2;
        this->size--;

        if (this->size == 1 && index_current_child == 0) {
            this->data[0] = this->data[1];
            this->children[1] = this->children[2];
        }

        if (this->size == 0) {
            this->children[0] = this->children[1];
            return false;
        }
        else {
            return true;
        }

    }

    /// @brief Removes specified element. Can set size to 0, this means parent needs to fix it
    /// @param data_to_remove 
    /// @return 
    RemoveResult remove(T data_to_remove) 
    {
        if (children[0] == nullptr) {
            if (size == 1) {
                if (data[0] == data_to_remove) {
                    size = 0;
                    return NeedParentRemove;
                }
                else {
                    return NotFound;
                }
            }
            else { // size == 2
                if (data[0] == data_to_remove) {
                    data[0] = data[1];
                    size = 1;
                    return Removed;
                }
                else if (data[1] == data_to_remove) {
                    size = 1;
                    return Removed;
                }
                else {
                    return NotFound;
                }
            }
        }
        if (size == 1) {
            if (data_to_remove < data[0]) {
                RemoveResult result = children[0]->remove(data_to_remove);
                if (result == NeedParentRemove) {
                    rebalance(0);
                    if (this->size == 0) { return NeedParentRemove; }
                    else { return Removed; }
                }
                else {
                    return result;
                }
            }
            else if (data_to_remove > data[0]) {
                RemoveResult result = children[1]->remove(data_to_remove);
                if (result == NeedParentRemove) {
                    rebalance(1);
                    if (this->size == 0) { return NeedParentRemove; }
                    else { return Removed; }
                }
                else {
                    return result;
                }
            }
            else { // removing our only data
                TreeNode* prev = children[0]->find_max_subtree();
                assert(prev->children[0] == nullptr);
                T prev_data = prev->get_max_data();
                data[0] = prev_data;
                //prev->remove(prev_data, parent???)
                RemoveResult result = this->children[0]->remove(prev_data); // because we know prev, but don't know full sequence of parents
                //assert(result != NotFound);
                if (result == Removed) { return Removed; }
                rebalance(0);
                if (this->size == 0) { return NeedParentRemove; }
                else { return Removed; }
            }
        }
        if (size == 2) {
            if (data_to_remove < data[0]) {
                RemoveResult result = children[0]->remove(data_to_remove);
                if (result == NeedParentRemove) {
                    rebalance(0);
                    assert(this->size > 0);
                    return Removed;
                }
                else {
                    return result;
                }
            }
            else if (data_to_remove == data[0]) {
                TreeNode* prev = children[0]->find_max_subtree();
                assert(prev->children[0] == nullptr);
                T prev_data = prev->get_max_data();
                data[0] = prev_data;
                RemoveResult result = this->children[0]->remove(prev_data); // because we know prev, but don't know full sequence of parents
                assert(result != NotFound);
                if (result == Removed) { return Removed; }
                rebalance(0);
                assert(this->size > 0);
                return Removed;
            }
            else if (data_to_remove < data[1]) {
                RemoveResult result = children[1]->remove(data_to_remove);
                if (result == NeedParentRemove) {
                    rebalance(1);
                    assert(this->size > 0);
                    return Removed;
                }
                else {
                    return result;
                }
            }
            else if (data_to_remove == data[1]) {
                TreeNode* prev = children[1]->find_max_subtree();
                assert(prev->children[0] == nullptr);
                T prev_data = prev->get_max_data();
                data[1] = prev_data;
                RemoveResult result = this->children[1]->remove(prev_data); // because we know prev, but don't know full sequence of parents
                //assert(result != NotFound);
                if (result == Removed) { return Removed; }
                rebalance(1);
                assert(this->size > 0);
                return Removed;
            }
            else { // data_to_remove > data[1]
                RemoveResult result = children[2]->remove(data_to_remove);
                if (result == NeedParentRemove) {
                    rebalance(2);
                    assert(this->size > 0);
                    return Removed;
                }
                else {
                    return result;
                }
            }
        }

    }

    /// @brief Represents tree as array
    /// @param elements Container to save
    void InOrder(std::vector<T>& elements) const {
        if (!this)
            return;
        if (children[0]) {
            children[0]->InOrder(elements);
        }
        elements.push_back(data[0]);
        if (children[1]) {
            children[1]->InOrder(elements);
        }
        if (size == 2) {
            elements.push_back(data[1]);
            if (children[2]) {
                children[2]->InOrder(elements);
            }
        }
    }
};

/// @brief Class to store comparative values
/// @tparam T 
template<typename T>
class B23Tree {

private:

    TreeNode<T>* root = nullptr;

    /// @brief Gets node with the specified data, recursively
    /// @param data Value to find
    /// @param node Current node
    /// @return Node that contains the data, else nullptr 
    TreeNode<T>* getNode(T data, TreeNode<T>* node) const{
        if (!node)
            return nullptr;

        if (data == node->data[0])
            return node;
        else if (node->size == 2)
            if (data == node->data[1])
                return node;
            else {
                if (data < node->data[0])
                    return getNode(data, node->children[0]);
                else if (node->size == 2)
                    if (data > node->data[0] && data < node->data[1])
                        return getNode(data, node->children[1]);
                if (data > node->data[1])
                    return getNode(data, node->children[2]);
            }

        return nullptr;
    }

    void getElementsByInterval(std::list<T>& elements, TreeNode<T>* node, T min, T max) const{
        if (!node)
            return;

        if (min < node->data[0])
            getElementsByInterval(elements, node->children[0], min, max);

        if (min <= node->data[0] && max >= node->data[0])
            elements.push_back(node->data[0]);

        getElementsByInterval(elements, node->children[1], min, max);

        if (node->size == 2) {
            elements.push_back(node->data[1]);
            if (node->data[1] < max)
                getElementsByInterval(elements, node->children[2], min, max);
        }
        else
            getElementsByInterval(elements, node->children[2], min, max);
    }

    void clearRecursive(TreeNode<T>* node) {
        if (!node)
            return;

        clearRecursive(node->children[0]);
        clearRecursive(node->children[1]);
        clearRecursive(node->children[2]);

        delete node;      
    }

public:

    /// @brief Inserts the specified value into the tree
    /// @param data Value to insert
    void append(T data) {
        if (!root) {
            root = new TreeNode<T>(data);
        }
        else {
            TreeNode<T>* extra = root->add_and_split(data);
            if (extra) {
                root = extra;
            }
        }
    }

    /// @brief Removes the specified value from the tree
    /// @param data Value to insert
    void remove(T data) 
    {
        if (root->size == 1 && root->data[0] == data &&
            root->children[0] == nullptr && root->children[1] == nullptr)
        {
            delete root;
            root = nullptr;
            return;
        }

        typename TreeNode<T>::RemoveResult result = root->remove(data);
        if (result == TreeNode<T>::NotFound) { return; }
        if (result == TreeNode<T>::Removed) { return; }
        if (result == TreeNode<T>::NeedParentRemove && root->children[0]) {
            root = root->children[0];
            return;
        }
    }

    bool GetElem(T data) const{
        TreeNode<T>* node = getNode(data, root);

        if (node) {
            if (node->data[0] == data)
                return true;
            else if (node->data[1] == data)
                return true;
        }
        else {
             return false;
        }
    }

    std::list<T> GetElementsByInterval(T min, T max) const{
        std::list<T> elements;
        getElementsByInterval(elements, this->root, min, max);
        return elements;
    }

    void print() const{
        std::vector<T> elements;
        root->InOrder(elements);
        for (T& elem : elements)
            std::cout << elem << '\n';
    }

    void FillRandom(size_t size) {
        for (size_t i = 0; i < size; i++) {
            T elem;
            elem.random();
            this->append(elem);
        }
    }


    void IncrementElemByOne(TreeNode<T>* node = nullptr) {
        if (!node)
            node = root;
        if (!root)
            return;

        if (node->children[0]) IncrementElemByOne(node->children[0]);
        if (node->children[1]) IncrementElemByOne(node->children[1]);
        if (node->children[2]) IncrementElemByOne(node->children[2]);

        ++(node->data[0]);
        if (node->size == 2);
            ++(node->data[1]);
    }

    void clear() {
        if (!root) 
            return;

        clearRecursive(this->root);

        root = nullptr;
    }

    /// @brief Gets maximum element of the tree
    /// @return Maximum element of the tree
    T GetMax() const
    {
        TreeNode<T>* cur = root, *prev = root;
        while (cur != nullptr)
        {
            prev = cur;
            cur = cur->children[cur->size];
            //if (cur->size == 1)
            //    cur = cur->children[1];
            //else if (cur->size == 2)
            //    cur = cur->children[2];
        }
        return prev->get_max_data();
    }

    bool IsEmpty() const
    {
        return root == nullptr;
    }

    ~B23Tree()
    {
        this->clear();
    }

#ifdef BENCHMARK_BENCHMARK_H_

private:

    static void append_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;
        tree.FillRandom(state.range(0));

        for (auto _ : state) {
            T data;
            data.random();
            tree.append(data);
        }
        tree.clear();
    }

    static void get_element_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;
        tree.FillRandom(state.range(0));

        std::vector<Time> elements;
        tree.root->InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        for (auto _ : state) {
            tree.GetElem(elements[mersenne() % elements.size()]);
        }
        tree.clear();

    }

    static void get_elements_interval_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;
        tree.FillRandom(state.range(0));

        std::vector<Time> elements;
        tree.root->InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        size_t start, end;

        for (auto _ : state) {
            start = mersenne() % elements.size(); end = mersenne() % elements.size();
            if (start > end) std::swap(start, end);
            tree.GetElementsByInterval(elements[start], elements[end]);
        }
        tree.clear();

    }

    static void remove_element_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;
        tree.FillRandom(state.range(0));

        std::vector<Time> elements;
        tree.root->InOrder(elements);

        std::random_device rd;
        std::mt19937 mersenne(rd());

        for (auto _ : state) {
            tree.remove(elements[mersenne() % elements.size()]);
        }
        tree.clear();

    }

    static void increase_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;
        tree.FillRandom(state.range(0));

        for (auto _ : state) {
            tree.IncrementElemByOne();
        }
        tree.clear();

    }

    static void fill_random_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;

        for (auto _ : state) {
            tree.FillRandom(state.range(0));
        }
        tree.clear();

    }

    static void fill_random_ascending_order_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;

        T elem; elem.random();

        for (auto _ : state) {
            for (size_t i = 0; i < state.range(0); i++) {
                tree.append(++elem);
            }
        }
        tree.clear();
    }

    static void fill_random_descending_order_B23Tree_BM(benchmark::State& state)
    {
        B23Tree tree;

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
        BENCHMARK(append_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void GetElem_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(get_element_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void GetElementsByInterval_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(get_elements_interval_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void remove_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(remove_element_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void IncreaseByOne_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(increase_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandom_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandomAscendingOrder_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_ascending_order_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }
    // Appends benchmarking function to the benchmarking queue
    void FillRandomDescendingOrder_BM(size_t maxElems, size_t iterations) {
        BENCHMARK(fill_random_descending_order_B23Tree_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(1, maxElems)->Iterations(iterations);
    }

    void BenchmarkTheQueue() {
        benchmark::RunSpecifiedBenchmarks();
        benchmark::RegisterMemoryManager(nullptr);
    }

#endif // BENCHMARK_BENCHMARK_H_

};

#undef private
#undef protected
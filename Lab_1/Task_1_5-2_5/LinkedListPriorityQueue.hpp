#pragma once

#include <stdexcept>

#include "priority_queue.h"
#include "doctest.h"


// For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif


template <typename T>
class LinkedListPriorityQueue :
    public PriorityQueue<T>        
{
private:
    struct Node
    {
    public:
        Node(T data, int priority, Node* next = nullptr)
            : data(data), priority(priority), next(next) {}

        T get_data() const { return data; };
        int get_priority() const { return priority; };
        void set_next(Node* next) { this->next = next; };
        Node* get_next() const { return next; }

        // postfix
        Node* operator++() {
            this = this->next;
            return this;
        }
        // prefix
        Node* operator++(int) {
            Node* temp = this;
            this = this->next;
            return temp;
        }

    private:
        T data;
        int priority;
        Node* next;
    };

public:
    /// <inheritdoc />
    T Peek() const override;
    /// <inheritdoc />
    T Pop() override;
    /// <inheritdoc />
    void Insert(T data, int priority) override;

    ~LinkedListPriorityQueue();
    

private:
    Node* head;

    bool isEmpty() const override;
};

#undef private
#undef protected


template<typename T>
inline bool LinkedListPriorityQueue<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
T LinkedListPriorityQueue<T>::Peek() const
{
    if (this->isEmpty())
        throw std::underflow_error("The queue is empty");
    else
        return head->get_data();
}

template<typename T>
inline T LinkedListPriorityQueue<T>::Pop()
{
    if (this->isEmpty())
        throw std::underflow_error("The queue is empty");
    else {
        Node* temp = head;
        T data = temp->get_data();
        head = head->get_next();
        delete temp;
        return data;
    }
}

template<typename T>
inline void LinkedListPriorityQueue<T>::Insert(T data, int priority)
{
    if (this->isEmpty())
        head = new Node(data, priority, nullptr);
    else if (head->get_priority() < priority) {
        head = new Node(data, priority, head);
    }
    else 
    {
        Node* cur = head;
        while (cur->get_next() != nullptr && 
            cur->get_next()->get_priority() > priority)
        {
            cur = cur->get_next();
        }
        cur->set_next(new Node(data, priority, cur->get_next()));
    }
}

template<typename T>
inline LinkedListPriorityQueue<T>::~LinkedListPriorityQueue()
{
    Node* cur = head;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->get_next();
        delete temp;
    }
}

#ifdef _DEBUG
TEST_CASE("Insert")
{
    LinkedListPriorityQueue<int> q;

    q.Insert(1111, 1);
    CHECK(q.head->get_data() == 1111);

    q.Insert(2222, 10);
    CHECK(q.head->get_data() == 2222);
    CHECK(q.head->get_next()->get_data() == 1111);

    q.Insert(3333, 5);
    CHECK(q.head->next->get_data() == 3333);
}

TEST_CASE("Peek")
{
    LinkedListPriorityQueue<int> q;

    CHECK_THROWS_AS(q.Peek(), const std::underflow_error&);

    q.Insert(1111, 1);
    q.Insert(2222, 10);
    q.Insert(3333, 5);

    CHECK(q.Peek() == 2222);
}

TEST_CASE("Pop")
{
    LinkedListPriorityQueue<int> q;

    CHECK_THROWS_AS(q.Pop(), const std::underflow_error&);

    q.Insert(1111, 1);
    q.Insert(2222, 10);
    q.Insert(3333, 5);

    CHECK(q.Pop() == 2222);
    CHECK(q.Pop() == 3333);
    CHECK(q.Pop() == 1111);

    CHECK_THROWS_AS(q.Pop(), const std::underflow_error&);
}

#endif

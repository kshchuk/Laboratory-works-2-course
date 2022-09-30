#pragma once

#include <stdexcept>

#include "PriorityQueue.h"


template <typename T>
class LinkedListPriorityQueue :
    public PriorityQueue<T>        
{
private:
    struct Node
    {
    public:
        Node(T data, int priority, Node* next = nullptr)
            : data(data), next(next), priority(priority) {}

        T get_data() const { return data; };
        int get_priority() const { return priority; };
        void set_next(Node* next) { this->next = next; };
        Node* get_next() const { return next; }

        Node* operator++() {
            this = this->next;
            return this;
        }
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
    T Peek() override;
    T Pop() override;
    void Insert(T data, int priority) override;
    
    ~LinkedListPriorityQueue();

private:
    Node* head;

    bool isEmpty() override;
};

template<typename T>
inline bool LinkedListPriorityQueue<T>::isEmpty()
{
    return head == nullptr;
}

template <typename T>
T LinkedListPriorityQueue<T>::Peek()
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
        T data = temp.get_data();
        head++;
        delete temp;
        return data;
    }
}

template<typename T>
inline void LinkedListPriorityQueue<T>::Insert(T data, int priority)
{
    if (this->isEmpty() || head->get_priority() < priority) {
        head = new Node(data, priority, head->get_next);
    }
    else 
    {
        Node* cur = head;
        while (cur->get_next() != nullptr &&
            cur->get_next()->get_priority() > priority) 
        {
            cur++;
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
        cur++;
        delete temp;
    }
}

#pragma once

#include <vector>
#include <stdexcept>

#include "PriorityQueue.h"

template<typename T>
class ArrayPriorityQueue 
	: public PriorityQueue<T>
{
private:
    struct Item
    {
        T get_value() const { return value; };
        int get_priority() const { return priority; };

        Item(T value, int priority)
            : value(value), priority(priority) {}

    private:
        T value;
        int priority;
    };

public:
    T Peek() override;
    T Pop() override;
    void Insert(T data, int priority) override;

private:
    std::vector<Item> arr;

    bool isEmpty() override;
};


template<typename T>
inline T ArrayPriorityQueue<T>::Peek()
{
    if (this->isEmpty())
        throw std::underflow_error("The queue is empty");
    else 
    {
        int max_priority;
        int max_priority_index;

        max_priority = arr[0].get_priority();

        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i].get_priority() > max_priority) {
                max_priority = arr[i].get_priority();
                max_priority_index = i;
            }
        }
        return arr[max_priority_index].get_value();
    }
}

template<typename T>
inline T ArrayPriorityQueue<T>::Pop()
{
    if (this->isEmpty())
        throw std::underflow_error("The queue is empty");
    else
    {
        int max_priority = arr[0].get_priority();
        int max_priority_index;

        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i].get_priority() > max_priority) {
                max_priority = arr[i].get_priority();
                max_priority_index = i;
            }
        }

        T value = arr[max_priority_index].get_value();
        arr.erase(arr.begin() + max_priority_index);
        return value;
    }
}

template<typename T>
inline void ArrayPriorityQueue<T>::Insert(T data, int priority)
{
    arr.push_back(Item(T, priority));
}

template<typename T>
inline bool ArrayPriorityQueue<T>::isEmpty()
{
    return arr.empty();
}

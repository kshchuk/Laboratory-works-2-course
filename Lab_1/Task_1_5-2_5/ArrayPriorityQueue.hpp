/*
*
 *  ArrayPriorityQueue.hpp
 *
 *  Created on: Sep 30, 2022
 *
 *  Author:  Yaroslav Kishchuk
 *  Contact: Kshchuk@gmail.com
 *
 */


#pragma once

#include <vector>
#include <stdexcept>

#include "priority_queue.h"
#include "doctest.h"


 // For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif


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
    /// <inheritdoc />
    T Peek() const override;
    /// <inheritdoc />
    T Pop() override;
    /// <inheritdoc />
    void Insert(T data, int priority) override;

private:
    std::vector<Item> arr;

    /// <inheritdoc />
    bool isEmpty() const override;
};


#undef private
#undef protected


template<typename T>
inline T ArrayPriorityQueue<T>::Peek() const
{
    if (this->isEmpty())
        throw std::underflow_error("The queue is empty");
    else 
    {
        int max_priority;
        int max_priority_index = 0;
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
        int max_priority_index = 0;

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
    arr.push_back(Item(data, priority));
}

template<typename T>
inline bool ArrayPriorityQueue<T>::isEmpty() const
{
    return arr.empty();
}


#ifdef _DEBUG
TEST_CASE("Insert")
{
    ArrayPriorityQueue<int> q;

    q.Insert(1111, 1);
    CHECK(q.arr[0].get_value() == 1111);

    q.Insert(2222, 10);
    CHECK(q.arr[1].get_value() == 2222);
}

TEST_CASE("Peek")
{
    ArrayPriorityQueue<int> q;

    CHECK_THROWS_AS(q.Peek(), const std::underflow_error&);

    q.Insert(1111, 1);
    q.Insert(2222, 10);
    q.Insert(3333, 5);

    CHECK(q.Peek() == 2222);
}

TEST_CASE("Pop")
{
    ArrayPriorityQueue<int> q;

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
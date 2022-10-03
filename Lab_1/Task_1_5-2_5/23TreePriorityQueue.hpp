#pragma once

#include <stdexcept>

#include "item.h"
#include "2-3Tree.hpp"
#include "priority_queue.h"

#include "doctest.h"

// For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif


template<typename T>
class B23TreePriorityQueue : public PriorityQueue<T>
{
public:
    T Peek() const override;
    T Pop() override;
    void Insert(T data, int priority) override;

private:
    B23Tree<Item<T>> tree;

    bool isEmpty() const override;
};

#undef private
#undef protected

template<typename T>
inline T B23TreePriorityQueue<T>::Peek() const
{
	if (this->isEmpty())
		throw std::underflow_error("Queue is empty");
	else {
		return tree.GetMax().data;
	}
}

template<typename T>
inline T B23TreePriorityQueue<T>::Pop()
{
	if (this->isEmpty())
		throw std::underflow_error("Queue is empty");
	else {
		Item<T> item = tree.GetMax();
		tree.remove(item);
		return item.data;
	}
}

template<typename T>
inline void B23TreePriorityQueue<T>::Insert(T data, int priority)
{
	tree.append(Item<T>(data, priority));
}

template<typename T>
inline bool B23TreePriorityQueue<T>::isEmpty() const
{
	return tree.IsEmpty();
}

#ifdef _DEBUG
TEST_CASE("Insert")
{
	B23TreePriorityQueue<int> q;

	q.Insert(1111, 1);
	CHECK(q.tree.root->data[0].data == 1111);

	q.Insert(2222, 10);
    CHECK(q.tree.root->data[0].data == 1111);
	CHECK(q.tree.root->data[1].data == 2222);

	q.Insert(3333, 5);
    CHECK(q.tree.root->data[0].data == 3333);
    CHECK(q.tree.root->children[0]->data[0].data == 1111);
	CHECK(q.tree.root->children[1]->data[0].data == 2222);
}

TEST_CASE("Peek")
{
	B23TreePriorityQueue<int> q;

	CHECK_THROWS_AS(q.Peek(), const std::underflow_error&);

	q.Insert(1111, 1);
	q.Insert(2222, 10);
	q.Insert(3333, 5);

	CHECK(q.Peek() == 2222);
}

TEST_CASE("Pop")
{
	B23TreePriorityQueue<int> q;

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
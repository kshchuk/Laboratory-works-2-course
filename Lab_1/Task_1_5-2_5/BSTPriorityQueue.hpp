#pragma once

#include <stdexcept>

#include "BST.hpp"
#include "priority_queue.h"
#include "doctest.h"

// For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif

/// <summary>
/// Extra class to store and compare queue elements. 
/// BST must have comparative elements
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct Item
{
	T data;
	int priority;

	bool operator<(Item item)
	{
		return (this->priority < item.priority);
	}
	bool operator>(Item item)
	{
		return (this->priority > item.priority);
	}
	bool operator==(Item item)
	{
		return (this->priority == item.priority);
	}
	bool operator<=(Item item)
	{
		return (this->priority <= item.priority);
	}
	bool operator>=(Item item)
	{
		return (this->priority >= item.priority);
	}

	Item(T data, int priority)
		: data(data), priority(priority) {}
};

template<typename T>
class BSTPriorityQueue 
	: public PriorityQueue<T>, private BST<Item<T>>
{
public:
	/// <inheritdoc />
	T Peek() const override;
	/// <inheritdoc />
	T Pop() override;
	/// <inheritdoc />
	void Insert(T data, int priority) override;

private:
	BST<Item<T>> tree;

	bool isEmpty() const override;
};

#undef private
#undef protected

template<typename T>
inline T BSTPriorityQueue<T>::Peek() const
{
	if (this->isEmpty())
		throw std::underflow_error("Queue is empty");
	else {
		return tree.GetMax().data;
	}
}

template<typename T>
inline T BSTPriorityQueue<T>::Pop()
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
inline void BSTPriorityQueue<T>::Insert(T data, int priority)
{
	tree.append(Item<T>(data, priority));
}

template<typename T>
inline bool BSTPriorityQueue<T>::isEmpty() const
{
	return tree.isEmpty();
}


#ifdef _DEBUG
TEST_CASE("Insert")
{
	BSTPriorityQueue<int> q;

	q.Insert(1111, 1);
	CHECK(q.tree.root->data.data == 1111);


	q.Insert(2222, 10);
	CHECK(q.tree.root->right->data.data == 2222);
	CHECK(q.tree.root->data.data == 1111);

	q.Insert(3333, 5);
	CHECK(q.tree.root->right->left->data.data == 3333);
}

TEST_CASE("Peek")
{
	BSTPriorityQueue<int> q;

	CHECK_THROWS_AS(q.Peek(), const std::underflow_error&);

	q.Insert(1111, 1);
	q.Insert(2222, 10);
	q.Insert(3333, 5);

	CHECK(q.Peek() == 2222);
}

TEST_CASE("Pop")
{
	BSTPriorityQueue<int> q;

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

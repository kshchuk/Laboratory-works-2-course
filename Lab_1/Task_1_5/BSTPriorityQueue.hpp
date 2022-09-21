#pragma once

#include <stdexcept>

#include "BST.hpp"
#include "PriorityQueue.h"


template<typename T>
struct Item
{
	T data;
	int priority;

	bool operator<(Item item1, Item item2)
	{
		return (item1.priority < item2.priority);
	}
	bool operator>(Item item1, Item item2)
	{
		return (item1.priority > item2.priority);
	}
	bool operator==(Item item1, Item item2)
	{
		return (item1.priority == item2.priority);
	}
	bool operator<=(Item item1, Item item2)
	{
		return (item1.priority <= item2.priority);
	}
	bool operator>=(Item item1, Item item2)
	{
		return (item1.priority >= item2.priority);
	}

	Item(T data, int priority)
		: data(data), priority(priority) {}
};


template<typename T>
class BSTPriorityQueue 
	: public PriorityQueue<T>, private BST<Item<T>>
{
public:
	T Peek() override;
	T Pop() override;
	void Insert(T data, int priority) override;

private:
	BST<Item> tree;

	bool isEmpty() override;
};

template<typename T>
inline T BSTPriorityQueue<T>::Peek()
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
	tree.append(Item(data, priority));
}

template<typename T>
inline bool BSTPriorityQueue<T>::isEmpty()
{
	return tree.isEmpty();
}

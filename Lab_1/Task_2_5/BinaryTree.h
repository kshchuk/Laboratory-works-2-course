#pragma once

#include <map>
#include <cmath>


template <typename T>
class BinaryTree
{
protected:
	struct Node
	{
		T data;
		Node* left, *right;

		Node() : left(nullptr), right(nullptr) {}
		Node(T data) : Node(), data(data) {}
	};

	Node* root;

	BinaryTree() : root(nullptr) {}
	void DeleteNode(Node* parent, Node* node, Node* child);
	Node* Copy(Node* node)
	{
		if (!node)
			return nullptr;

		Node* new_node = new Node(node->data));

		new_node->left = copy(node->left);
		new_node->right = copy(node->right);

		return new_node;
	} // Copies all elements of tree

public:
	void Add(T data);

	// Clears tree nodes exept root
	void Clear(Node* root = nullptr);

};

#include "BinaryTree.ipp"
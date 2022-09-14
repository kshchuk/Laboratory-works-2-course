#pragma once

#include <map>
#include <cmath>

namespace expr
{

	template <typename T>
	class BinaryTree
	{
	protected:
		struct Node
		{
			T data;
			Node* left, * right;

			Node() : left(nullptr), right(nullptr) {}
			Node(T data) : data(data), left(nullptr), right(nullptr) {}
		};

		Node* root;

		BinaryTree() : root(nullptr) {}
		void DeleteNode(Node* parent, Node* node, Node* child);
		Node* Copy(Node* node)
		{
			if (!node)
				return nullptr;

			Node* new_node = new Node(node->data);

			new_node->left = Copy(node->left);
			new_node->right = Copy(node->right);

			return new_node;
		} // Copies all elements of tree

	public:
		// Brackets representation
		void Print(Node* node = nullptr);

		// Clears tree nodes except root
		void Clear(Node* root = nullptr);

	};
}
#include "BinaryTree.ipp"
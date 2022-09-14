#include "BinaryTree.h"


template<typename T>
inline void BinaryTree<T>::Add(T data)
{
	if (root == nullptr) {
		root = new Node(data); return;
	}

	Node* parent_node = root, * child_node = root;
	int difference;
	while (child_node) {
		parent_node = child_node;
		difference = *data - *parent_node->data;
		if (difference < 0)
			child_node = parent_node->left;
		else if (difference > 0)
			child_node = parent_node->right;
		else
			return;
	}
	if (difference < 0)
		parent_node->left = new Node(data);
	else
		parent_node->right = new Node(data);
}

template<typename T>
inline void BinaryTree<T>::Clear(Node* node)
{
	if (node == nullptr)
		node == root;

	if (node->left != nullptr)
	{
		clear(node->left);
		delete node->left;
		node->left = nullptr;
	}
	if (node->right != nullptr)
	{
		clear(node->right);
		delete node->right;
		node->right = nullptr;
	}
}

template<typename T>
inline void BinaryTree<T>::DeleteNode(Node* parent, Node* node, Node* child)
{
	if (parent == nullptr)
	{
		this->root = child;
		delete node;
	}
	else if (parent->left == node) {
		Node* temp = child;
		delete node;
		parent->left = temp;
	}
	else {
		Node* temp = child;
		delete node;
		parent->right = temp;
	}
}
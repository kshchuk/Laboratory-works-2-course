#include "BinaryTree.h"

namespace expr
{
	//template<typename T>
	//inline void BinaryTree<T>::Print(Node* node)
	//{
	//	if (root == nullptr)
	//		return;
	//	if (node == nullptr)
	//		node = root;

	//	if (node) {
	//		std::cout << node->data << ' ';

	//		if (node->left == nullptr && node->right == nullptr)
	//			return;
	//		std::cout << "(";
	//		if (node->left != nullptr)
	//			Print(node->left);
	//		if (node->right != nullptr)
	//			Print(node->right);
	//		std::cout << ")";
	//	}
	//}

	template<typename T>
	inline void BinaryTree<T>::Clear(Node* node)
	{
		if (node == nullptr)
			node = root;
		if (root == nullptr)
			return;

		if (node->left != nullptr)
		{
			Clear(node->left);
			delete node->left;
			node->left = nullptr;
		}
		if (node->right != nullptr)
		{
			Clear(node->right);
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
}
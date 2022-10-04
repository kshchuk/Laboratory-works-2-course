/*
*
 *  BinaryTree.ipp
 *
 *  Created on: Sep 30, 2022
 *
 *  Author:  Yaroslav Kishchuk
 *  Contact: Kshchuk@gmail.com
 *
 */

#include "BinaryTree.h"

#include "doctest.h"


namespace expr
{
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

#ifdef _DEBUG

	TEST_CASE("Delete node") {
		BinaryTree<int> b1;
		b1.root = new BinaryTree<int>::Node(1);
		b1.root->left = new BinaryTree<int>::Node(11);
		b1.root->right = new BinaryTree<int>::Node(12);
		b1.root->left->left = new BinaryTree<int>::Node(111);
		b1.root->left->right = new BinaryTree<int>::Node(112);

		b1.DeleteNode(b1.root, b1.root->left, b1.root->left->right);

		CHECK(b1.root->left->data == 112);
	}

	TEST_CASE("Copy tree")
	{
		BinaryTree<int> b1;
		b1.root = new BinaryTree<int>::Node(1);
		b1.root->left = new BinaryTree<int>::Node(11);
		b1.root->right = new BinaryTree<int>::Node(12);
		b1.root->left->left = new BinaryTree<int>::Node(111);
		b1.root->left->right = new BinaryTree<int>::Node(112);

		BinaryTree<int> b2;
		b2.root = b1.Copy(b1.root);

		CHECK(b1.root->data == b2.root->data);
		CHECK(b1.root->left->data == b2.root->left->data);
		CHECK(b1.root->right->data == b2.root->right->data);
		CHECK(b1.root->left->left->data == b2.root->left->left->data);
		CHECK(b1.root->left->right->data == b2.root->left->right->data);
	}

	TEST_CASE("Clear the tree")
	{
		BinaryTree<int> b1;
		b1.root = new BinaryTree<int>::Node(1);
		b1.root->left = new BinaryTree<int>::Node(11);
		b1.root->right = new BinaryTree<int>::Node(12);
		b1.root->left->left = new BinaryTree<int>::Node(111);
		b1.root->left->right = new BinaryTree<int>::Node(112);

		b1.Clear();

		CHECK(b1.root->left == nullptr);
		CHECK(b1.root->right == nullptr);
	}
#endif // _DEBUG
}
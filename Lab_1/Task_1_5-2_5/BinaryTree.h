/*
* 
 *  BinaryTree.h
 *
 *  Created on: Sep 30, 2022
 * 
 *  Author:  Yaroslav Kishchuk
 *  Contact: Kshchuk@gmail.com
 * 
 */


#pragma once

#include <map>

 // For unit testing of private methods
#ifdef _DEBUG
#define private public
#define protected public
#endif


namespace expr
{
	/// @brief Class for storing and processing data in binary tree structure
	/// @tparam T 
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

		/// @brief Deletes selected node. In order not to break the connectivity of the tree,
		///  connects node's parent node with node's child node.
		/// @param parent Node's parent
		/// @param node Node to delete
		/// @param child Node's child to reconnect parent to
		void DeleteNode(Node* parent, Node* node, Node* child);

		/// @brief Copies all data of subtree into new tree
		/// @param node Source subtree root
		/// @return Root of the new tree 
		Node* Copy(const Node* node) const
		{
			if (!node)
				return nullptr;

			Node* new_node = new Node(node->data);

			new_node->left = Copy(node->left);
			new_node->right = Copy(node->right);

			return new_node;
		}

	public:

		/// @brief Deletes all nodes of the tree except the tree's root
		/// @param root Root of the tree to delete 
		void Clear(Node* root = nullptr);
	};
}


#undef private
#undef protected

#include "BinaryTree.ipp"
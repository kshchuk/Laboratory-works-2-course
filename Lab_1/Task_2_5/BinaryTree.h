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
#include <cmath>

namespace expr
{
	/// <summary>
	/// Class for storing and processing data in binary tree structure
	/// </summary>
	/// <typeparam name="T"></typeparam>
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
		/// <summary>
		/// Deletes selected node. In order not to break the connectivity of the tree,
		///  connects node's parent node with node's child node.
		/// </summary>
		/// <param name="node"> - Node to delete </param>
		/// <param name="parent"> - node's parent </param>
		/// <param name="child"> - node's child </param>
		/// <returns></returns>
		void DeleteNode(Node* parent, Node* node, Node* child);
		/// <summary>
		/// Copies all data of subtree into new tree
		/// </summary>
		/// <param name="node"> - Old subtree root </param>
		/// <returns> - Root of the new tree </returns>
		Node* Copy(Node* node)
		{
			if (!node)
				return nullptr;

			Node* new_node = new Node(node->data);

			new_node->left = Copy(node->left);
			new_node->right = Copy(node->right);

			return new_node;
		}

	public:

		/// <summary>
		/// Deletes all nodes of the tree except the tree's root
		/// </summary>
		/// <param name="root"> - Root of the tree to delete </param>
		/// <returns></returns>
		void Clear(Node* root = nullptr);

	};
}
#include "BinaryTree.ipp"
/*
*
 *  Expression.h
 *
 *  Created on: Sep 30, 2022
 *
 *  Author:  Yaroslav Kishchuk
 *  Contact: Kshchuk@gmail.com
 *
 */


#pragma once

#include <iostream>
#include <vector>
#include <stack>

#include "BinaryTree.h"


namespace expr
{
	/// <summary>
	/// Class to store, calculate differtiate and simplify var-included expressions
	/// </summary>
	class Expression : public BinaryTree<std::string>
	{
	public:
		Expression() : BinaryTree() {};

		/// <summary>
		/// Creates binary tree based on expression
		/// </summary>
		/// <param name="expression"></param>
		Expression(std::string expression);
		/// <summary>
		/// Load expression into Expression class
		/// </summary>
		/// <param name="expression"></param>
		void LoadExpression(std::string expression);
		/// <summary>
		/// Prints all vars presented in the expression
		/// </summary>
		void PrintVarList();
		/// <summary>
		/// Simplifies expression
		/// </summary>
		/// <param name="node"> - Starting node </param>
		/// <param name="parent"> - Parent of the starting node </param>
		void Simplify(Node* node = nullptr, Node* parent = nullptr);
		/// <summary>
		/// Differentiates expression by a specified variable
		/// </summary>
		/// <param name="var"> - Variable to differenciate by </param>
		/// <param name="node"> - Binary tree node to differentiate </param>
		/// <returns> Link to </returns>
		Node* Differentiate(std::string var, Node* node = nullptr);
		/// <summary>
		/// Calculate expression if possible
		/// </summary>
		/// <param name="values_of_variables"> - Variables and values </param>
		/// <returns></returns>
		double CalculateExpression(std::map<std::string, double> values_of_variables = 
			std::map<std::string, double>());
		std::string to_string(Node* node = nullptr);

	private:
		Expression(Node*);

		const std::map<std::string, int> kFunctionsPriorities =
		{ {"sin", 1}, {"cos", 1}, {"tg", 1}, {"log", 2}, {"ln", 1}, {"^", 3},
			{"*", 4}, {"/", 4}, {"+", 5}, {"-", 5}, {"(", 6} };
		std::vector<std::string> vars;

		void ProcessOperation(std::string operation, std::stack<std::string>& operators,
			std::vector<std::string>& rpn); // rpn - reverse polish notation
		std::vector<std::string> GenRpn(std::string expression);
		void GenSubTree(Node** root, std::vector<std::string>::iterator& start);
		void ConvertVarsToNumbers(std::map<std::string, double> values, Node* node);
		void SimplifyBinaryFunction(Node* node = nullptr, Node* parent = nullptr);
		void SimplifyUnaryFunction(Node* node = nullptr, Node* parent = nullptr);
		bool isNumber(std::string str);
		bool isFunction(std::string str);
		bool isUnaryFunction(std::string str);
		void CheckVar(std::string var);
		double CalculateFunction(std::string function, double arg_1, double arg_2 = NULL);
		bool Compare(Node* root_1, Node* root_2);

		void dSin(std::string var, Node*& sin_node);
		void dCos(std::string var, Node*& cos_node);
		void dTg(std::string var, Node*& tg_node);
		void dLn(std::string var, Node*& ln_node);
		void dLog(std::string var, Node*& log_node);
		void dPow(std::string var, Node*& pow_node);
		void dMult(std::string var, Node*& mult_node);
		void dDiv(std::string var, Node*& div_node);
	};
}
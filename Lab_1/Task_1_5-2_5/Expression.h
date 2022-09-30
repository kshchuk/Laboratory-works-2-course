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
#include <map>

#include "BinaryTree.h"


 // For private methods unit testing
#ifdef _DEBUG
#define private public
#define protected public
#endif


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
		void PrintVarList() const;
		/// <summary>
		/// Simplifies expression
		/// </summary>
		/// <param name="node"> - Starting node </param>
		/// <param name="parent"> - Parent of the starting node </param>
		void Simplify(Node* node = nullptr, Node* parent = nullptr);
		/// <summary>
		/// Differentiates expression by a specified variable
		/// </summary>
		/// <param name="var"> - variable to differenciate by </param>
		/// <param name="node"> - expression tree node to differentiate </param>
		/// <returns> Link to the differentieated node </returns>
		Node* Differentiate(std::string var, Node* node = nullptr);
		/// <summary>
		/// Calculate expression if possible
		/// </summary>
		/// <param name="values_of_variables"> - map of variables and their values </param>
		/// <returns></returns>
		double CalculateExpression(std::map<std::string, double> values_of_variables = 
			std::map<std::string, double>()) const;
		/// <summary>
		/// Returns expression as string
		/// </summary>
		/// <param name="node"> - current node of the expression tree</param>
		/// <returns></returns>
		std::string to_string(Node* node = nullptr) const; 

	private:
		Expression(Node*);

		const std::map<std::string, int> kFunctionsPriorities =
		{ {"sin", 1}, {"cos", 1}, {"tg", 1}, {"log", 2}, {"ln", 1}, {"^", 3},
			{"*", 4}, {"/", 4}, {"+", 5}, {"-", 5}, {"(", 6} };
		std::vector<std::string> vars;

		/// <summary>
		/// Compares function's priority with precending function's priority
		/// int the stack. Depending on the result forms the RPN
		/// </summary>
		/// <param name="operation"> - current function to handle </param>
		/// <param name="operators"> - previous functions int the stack </param>
		/// <param name="rpn"> - polish notation </param>
		void ProcessOperation(std::string operation, std::stack<std::string>& operators,
			std::vector<std::string>& rpn) const;
		/// <summary>
		/// Respresents expression in polish notation
		/// </summary>
		/// <param name="expression"></param>
		/// <exception cref="std::runtime_error"> Thrown when there is invalid input in the expression </exception>
		/// <returns> Polish notation </returns>
		std::vector<std::string> GenRpn(std::string expression) const;
		/// <summary>
		/// Converts RPN into binary tree
		/// </summary>
		/// <param name="root"> - root of the tree</param>
		/// <param name="start"> - current RPN element </param>
		void GenSubTree(Node** root, std::vector<std::string>::iterator& start);
		/// <summary>
		/// Changes variables in the expression tree into numbers
		/// </summary>
		/// <param name="values"> - values of variables </param>
		/// <param name="node"> - current node of the expression tree </param>
		void ConvertVarsToNumbers(std::map<std::string, double> values, Node* node);
		/// <summary>
		/// Checks node's and it's childrens' values. If possible, simplifies it.
		/// </summary>
		/// <param name="node"> - current node</param>
		/// <param name="parent"> - current node's parent</param>
		/// <exception cref="std::overflow_error"> Thrown when there is invalid operation 
		/// like dividing by zero, log(1,x) etc. 
		/// </exception>
		void SimplifyBinaryFunction(Node* node = nullptr, Node* parent = nullptr);
		/// <summary>
		/// If possible simplifies unary functions
		/// </summary>
		/// <param name="node"> - current node</param>
		/// <param name="parent"> - current node's parent</param>
		/// <exception cref="std::overflow_error"> Thrown when there is invalid operation 
		/// like ln(-1) etc. 
		/// </exception>
		void SimplifyUnaryFunction(Node* node = nullptr, Node* parent = nullptr);
		/// <summary>
		/// Check whether the variable is in the list. If not - inserts it
		/// </summary>
		/// <param name="var"></param>
		void CheckVar(std::string var);
		/// <summary>
		/// Calculates function with number arguments.
		/// If function is unary - uses only first argument
		/// </summary>
		/// <param name="function"></param>
		/// <param name="arg_1"></param>
		/// <param name="arg_2"></param>
		/// <exception cref="std::overflow_error"> Thrown when there is invalid math operation
		/// </exception>
		/// <returns></returns>
		double CalculateFunction(std::string function, double arg_1, double arg_2 = NULL) const;
		/// <summary>
		/// Compares data of two Expression trees
		/// </summary>
		/// <param name="root_1"></param>
		/// <param name="root_2"></param>
		/// <returns></returns>
		bool Compare(Node* root_1, Node* root_2) const;

		bool isNumber(std::string str) const;
		bool isFunction(std::string str) const;
		bool isUnaryFunction(std::string str) const;

		// Some functions for differentiation

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


#undef private
#undef protected
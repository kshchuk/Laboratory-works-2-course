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
	/// @brief Class to store, calculate differtiate and simplify var-included expressions
	class Expression
	{
	public:
		using ENode = BinaryTree<std::string>::Node;

		/// @exception std::runtime_error Thrown when there is invalid input in the expression
		Expression() {};
		Expression(const Expression&);

		/// @brief Creates the expression based on the binary tree
		/// @param expression 
		Expression(std::string expression);

		/// @brief Load expression into Expression class 
		/// @param expression 
		void LoadExpression(std::string expression);

		/// @brief Simplifies expression
		/// @param node Starting node
		/// @param parent Starting node parent
		void Simplify(ENode* node = nullptr, ENode* parent = nullptr);

		/// @brief Differentiates expression by a specified variable
		/// @param var Variable to differenciate by
		/// @param node Expression tree node to differentiate
		/// @return Link to the differentiated node
		ENode* Differentiate(std::string var, ENode* node = nullptr);

		/// @brief Calculate expression if possible
		/// @param values_of_variables Variables and their values
		/// @return Expression value
		double CalculateExpression(std::map<std::string, double> values_of_variables = 
			std::map<std::string, double>()) const;
		
		/// @brief Returns expression as string
		/// @param node Current node of the expression tree<
		/// @return Expression as string
		std::string to_string(ENode* node = nullptr) const; 

		std::vector<std::string> get_vars() const;

		Expression& operator=(const Expression &expr);

	private:

		BinaryTree<std::string> tree;

		Expression(ENode*);

		const std::map<std::string, int> kFunctionsPriorities =
		{ {"sin", 1}, {"cos", 1}, {"tg", 1}, {"log", 2}, {"ln", 1}, {"^", 3},
			{"*", 4}, {"/", 4}, {"+", 5}, {"-", 5}, {"(", 6} };
		std::vector<std::string> vars;

		/// @brief Compares function's priority with precending function's priority
		/// int the stack. Depending on the result forms the RPN
		/// @param operation Current function to handle
		/// @param operators Previous functions int the stack
		/// @param rpn Polish notation
		void ProcessOperation(std::string operation, std::stack<std::string>& operators,
			std::vector<std::string>& rpn) const;

		/// @brief Respresents expression in polish notation
		/// @param expression Expression to convert
		/// @exception std::runtime_error Thrown when there is invalid input in the expression
		/// @return Polish notation of the expression
		std::vector<std::string> GenRpn(std::string expression) const;

		/// @brief Converts RPN into binary tree
		/// @param root Root of the tree
		/// @param start Starting RPN element
		void GenSubTree(ENode** root, std::vector<std::string>::iterator& start);

		/// @brief Changes variables in the expression tree into numbers
		/// @param values Values of the variables
		/// @param node Current node of the expression tree
		void ConvertVarsToNumbers(std::map<std::string, double> values, ENode* node);

		/// @brief Checks node's and it's childrens' values. If possible, simplifies it.
		/// @param node Current node
		/// @param parent Current node's parent
		/// @exception std::overflow_error Thrown when there is invalid operation 
		/// like dividing by zero, log(1,x) etc.
		void SimplifyBinaryFunction(ENode* node = nullptr, ENode* parent = nullptr);

		/// @brief If possible simplifies unary functions
		/// @param node Current node
		/// @param parent Current node's parent
		/// @exception std::overflow_error Thrown when there is invalid operation 
		/// like ln(-1) etc. 
		void SimplifyUnaryFunction(ENode* node = nullptr, ENode* parent = nullptr);

		/// @brief Checks whether the variable is in the list. If not - inserts it
		/// @param var Var to handle
		void CheckVar(std::string var);

		/// @brief Calculates function with number arguments.
		/// If function is unary - uses only first argument
		/// @param function Function or operator
		/// @param arg_1 
		/// @param arg_2 
		/// @return Function value
		double CalculateFunction(std::string function, double arg_1, double arg_2 = NULL) const;

		/// @brief Compares data of two Expression trees
		/// @param root_1 First tree's root
		/// @param root_2 Seconds tree's root
		/// @return True if the same data in the trees
		bool Compare(ENode* root_1, ENode* root_2) const;
		
		bool isNumber(std::string str) const;
		bool isFunction(std::string str) const;
		bool isUnaryFunction(std::string str) const;

		// Some functions for differentiation

		void dSin(std::string var, ENode*& sin_node);
		void dCos(std::string var, ENode*& cos_node);
		void dTg(std::string var, ENode*& tg_node);
		void dLn(std::string var, ENode*& ln_node);
		void dLog(std::string var, ENode*& log_node);
		void dPow(std::string var, ENode*& pow_node);
		void dMult(std::string var, ENode*& mult_node);
		void dDiv(std::string var, ENode*& div_node);
	};

}


#undef private
#undef protected
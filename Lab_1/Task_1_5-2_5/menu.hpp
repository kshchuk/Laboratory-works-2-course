#include <iostream>
#include <vector>
#include <map>
#include <exception>

#include "Expression.h"
#include "ArrayPriorityQueue.hpp"
#include "LinkedListPriorityQueue.hpp"
#include "BSTPriorityQueue.hpp"
#include "AVLPriorityQueue.hpp"
#include "23TreePriorityQueue.hpp"



void ExpressionMenu(expr::Expression expression)
{
	enum ExpressionMenu
	{
		kPrint = 1,
		kSimplify,
		kDifferentiate,
		kCalculate,
		kExit = 0
	};

	while (true)
	{
		ExpressionMenu em;
		std::cout << std::endl << std::endl <<
			"    1 - Print\n" <<
			"    2 - Simplify\n" <<
			"    3 - Differentiate\n" <<
			"    4 - Calculate\n" <<
			"    0 - Exit\n\n";
		int ans;
		std::cin >> ans; em = (ExpressionMenu)ans;

		switch (em)
		{
		case kPrint:
			std::cout << expression.to_string();
			break;
		case kSimplify:
			expression.Simplify();
			break;
		case kDifferentiate:
		{
			std::vector<std::string> vars = expression.get_vars();
			std::cout << "Variables: ";
			for (auto var : vars)
				std::cout << var << "  ";

			std::string var;
			std::cout << "\nType variable to differentiate by:  ";
			std::cin >> var;
			expression.Differentiate(var);
			break;
		}
		case kCalculate:
		{
			std::vector<std::string> vars = expression.get_vars();
			std::cout << "Variables: ";
			for (auto var : vars)
				std::cout << var << "  ";

			std::map<std::string, double> values;
			std::cout << "\nType values of the variables:\n";
			std::string name; double value;
			for (auto _ : vars)
			{
				std::cout << "\nVar name:  "; std::cin >> name;
				std::cout << "\nVar value:  "; std::cin >> value;
				values.insert({ name, value });
			}
			std::cout << "\n\nExpression value: " << expression.CalculateExpression(values);
			break;
		}
			break;
		case kExit:
			return;
		default:
			continue;
		}
	}
}

void PriorityQueueMenu(PriorityQueue<expr::Expression>* pqueue)
{
	enum PriorityQueueMenu
	{
		kPeek = 1,
		kPop,
		kInsert,
		kIsEmpty,
		kExit = 0
	};

	while (true)
	{
		PriorityQueueMenu pm;
		std::cout << std::endl << std::endl <<
			"    1 - Peek\n" <<
			"    2 - Pop\n" <<
			"    3 - Insert\n" <<
			"    0 - Exit\n\n";

		int ans;
		std::cin >> ans; pm = (PriorityQueueMenu)ans;
		
		switch (pm)
		{
		case kPeek:
		{
			try {
				ExpressionMenu(pqueue->Peek());
			}
			catch (std::underflow_error& e)
			{
				std::cout << "Underflow error: " << e.what() << std::endl;
			}
			break;
		}
		case kPop:
		{
			try {
				ExpressionMenu(pqueue->Pop());
			}
			catch (std::underflow_error& e)
			{
				std::cout << "Underflow error: " << e.what() << std::endl;
			}
			break;
		}
		case kInsert:
		{
			std::string sexpr;
			std::cout << "Type expression: ";
			std::cin >> sexpr;
			int priority;
			std::cout << "Type priority: ";
			std::cin >> priority;
			try {
				pqueue->Insert(expr::Expression(sexpr), priority);
			}
			catch (std::runtime_error& e) 
			{
				std::cout << "Insertion failed" << std::endl;
			}
			break;
		}
		case kExit:
			return;
		default:
			continue;
		}
	}
}

void MainMenu()
{
	enum QueueType
	{
		kArray = 1,
		kLinkedList,
		kBST,
		kAVL,
		k23,
		kExit = 0
	};

	PriorityQueue<expr::Expression>* queue;

	while (true)
	{
		QueueType qt;
		std::cout << std::endl << std::endl <<
			"Choose queue type: \n" <<
			"    1 - Array based priority queue\n" <<
			"    2 - Linked list based priority queue\n" <<
			"    3 - BST based priority queue\n" <<
			"    4 - AVL based priority queue\n" <<
			"    5 - 2-3Tree based priority queue\n" <<
			"    0 - Exit\n\n";

		int ans;
		std::cin >> ans; qt = (QueueType)ans;

		switch (qt)
		{
		case kArray:
			queue = new ArrayPriorityQueue<expr::Expression>();
			PriorityQueueMenu(queue);
			break;
		case kLinkedList:
			queue = new LinkedListPriorityQueue<expr::Expression>();
			PriorityQueueMenu(queue);
			break;
		case kBST:
			queue = new BSTPriorityQueue<expr::Expression>();
			PriorityQueueMenu(queue);
			break;
		case kAVL:
			queue = new AVLPriorityQueue<expr::Expression>();
			PriorityQueueMenu(queue);
			break;
		case k23:
			queue = new B23TreePriorityQueue<expr::Expression>();
			PriorityQueueMenu(queue);
			break;
		case kExit:
			return;
		default:
			continue;
		}
	}
}
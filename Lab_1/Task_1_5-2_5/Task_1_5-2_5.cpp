// Task_1_5-2_5.cpp : This file contains the 'main' function. Program execution begins and ends there.


#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "menu.hpp"


int main(int argc, char* argv[])
{
	

	// Unit tests
#ifdef _DEBUG

	doctest::Context context;

	context.applyCommandLine(argc, argv);

	int res = context.run();

	if (context.shouldExit()) {
		return res;
	}

#endif // _DEBUG

	MainMenu();

}
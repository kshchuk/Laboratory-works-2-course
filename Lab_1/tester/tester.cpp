#include <iostream>

#include <Windows.h>

#include <Expression.h>

void ImplicitCallTest()
{
	expr::Expression* ex = new expr::Expression();
	ex->LoadExpression("x+15*y-10/(100*54^x/ln(10000))");
	std::cout << ex->to_string() << std::endl;
	ex->Simplify();
	std::map<std::string, double> values = { {"x", 4}, {"y", 18} };
	std::cout << ex->CalculateExpression(values) << std::endl;
	std::cout << ex->to_string();
}

typedef expr::Expression* (__cdecl* ExpressionFactory)();

void ExplicitCallTest()
{
	HMODULE dll = LoadLibrary(L"Task_2_5.dll");
	if (!dll)
	{
		std::cout << "Fail load library" << std::endl;
		return;
	}
	ExpressionFactory factory = reinterpret_cast<ExpressionFactory>(GetProcAddress(dll, "CreateExpression"));

	if (!factory) {
		std::cerr << "Unable to load CreateLogarithmicMath from DLL!\n";
		FreeLibrary(dll);
		return;
	}
	expr::Expression* instance = factory();
	instance->LoadExpression("x+15*y-10/(100*54^x/ln(10000))");
	std::map<std::string, double> values = { {"x", 4}, {"y", 18} };
	std::cout << std::endl << instance->CalculateExpression(values);

	delete instance;
	FreeLibrary(dll);
}

int main()
{
	ImplicitCallTest();
	ExplicitCallTest();
}

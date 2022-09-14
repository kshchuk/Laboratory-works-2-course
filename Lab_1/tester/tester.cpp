#include <iostream>

#include <Expression.h>


int main()
{
	expr::Expression* ex = new expr::Expression("tg(10)^15*y*x+35*sin(-3.14)/x");
	ex->Print();
	ex->Simplify();
	std::cout << std::endl;
	ex->Print();
}

#include "pch.h"
#include "Factory.h"

TASK25_API expr::Expression* __cdecl CreateExpression()
{
    return new expr::Expression();
}

#include "dool.h"

dool::dool(): x{false}, y{false}
{}

dool::dool(bool a): x{a}, y{a}
{}

dool::dool(bool a, bool b): x{a}, y{a}
{}

bool dool::_and()
{
	return x && y;
}

bool dool::_or()
{
	return x || y;
}

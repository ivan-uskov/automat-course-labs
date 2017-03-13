#include "stdafx.h"
#include "Value.h"

std::ostream & operator << (std::ostream & out, const Value & v)
{
	std::visit([&out](auto && arg) {
		out << arg;
	}, v);

	return out;
}
#include "Check.h"

Check::Check() {};
Check::~Check() {};

bool Check::PlayerCount(int input) const
{
	if (input < 2 || input > 6)
	{
		return false;
	}
	else
	{
		return true;
	}
}
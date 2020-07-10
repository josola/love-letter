#include "input_check.h"

bool InputCheck::CheckTargetPlayer(int input)
{
	if (input >= 1 && input <= 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputCheck::CheckStartingPlayerCount(int input)
{
	if (input >= 2 && input <= 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputCheck::CheckCard(int input)
{
	if (input >= 0 && input <= 9)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
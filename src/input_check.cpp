#include "input_check.h"

const bool InputCheck::CheckTargetPlayer(const int input)
{
	if (input >= 1 && input <= 6)
		return true;
	else
		return false;
}

const bool InputCheck::CheckStartingPlayerCount(const int input)
{
	if (input >= 2 && input <= 9)
		return true;
	else
		return false;
}

const bool InputCheck::CheckCard(const int input)
{
	if (input >= 0 && input <= 9)
		return true;
	else
		return false;
}
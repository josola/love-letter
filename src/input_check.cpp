#include "input_check.h"
#include "game_state.h"

#include <iostream>

using std::cin;
using std::cout;

const bool InputCheck::CheckTarget(int input, GameState &state)
{
	while (input < 1 || input > state.players_.size())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		cout << "Number must be between 1 and " << state.players_.size() << '\n';
		cin >> input;
	}
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
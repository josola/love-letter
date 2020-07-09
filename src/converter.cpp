#include "converter.h"

#include <cassert>

Player* Converter::NumPlayer(int num, GameState& state)
{
	assert(num >= 1 && num <= 6);
	assert(!state.players_.empty());

	Player* output = nullptr;

	for (Player& iPlayer : state.players_)
	{
		if (iPlayer.GetValue() == num)
		{
			output = &iPlayer;
		}
	}
	return output;
}
#include "converter.h"
#include "player.h"
#include "game_state.h"

#include <cassert>

Player* Converter::NumPlayer(int num, GameState& state)
{
	assert(num >= 1 && num <= 6);

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
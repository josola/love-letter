#include "converter.h"
#include "player.h"
#include "game_state.h"

Player* Converter::NumPlayer(int num, GameState& state)
{
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
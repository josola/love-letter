#include "game_state.h"
#include "reference.h"
#include "player.h"

#include <cassert>

using std::to_string;

void GameState::InsertPlayer(Player player)
{
	players_.push_back(player);
}

void GameState::SetPlayers(int count)
{
    Reference reference;

    switch (count)
    {
        case 2:
        {
            for (int i = 0; i < 2; i++)
            {
                string name = "PLAYER[" + to_string(i + 1) + "]";
                InsertPlayer(Player(name, i + 1, reference));
            }
            winning_token_count_ = 6;
            break;
        }
        case 3:
        {
            for (int i = 0; i < 3; i++)
            {
                string name = "PLAYER[" + to_string(i + 1) + "]";
                InsertPlayer(Player(name, i + 1, reference));
            }
            winning_token_count_ = 5;
            break;
        }
        case 4:
        {
            for (int i = 0; i < 4; i++)
            {
                string name = "PLAYER[" + to_string(i + 1) + "]";
                InsertPlayer(Player(name, i + 1, reference));
            }
            winning_token_count_ = 4;
            break;
        }
        case 5:
        {
            for (int i = 0; i < 5; i++)
            {
                string name = "PLAYER[" + to_string(i + 1) + "]";
                InsertPlayer(Player(name, i + 1, reference));
            }
            winning_token_count_ = 3;
            break;
        }
        case 6:
        {
            for (int i = 0; i < 6; i++)
            {
                string name = "PLAYER[" + to_string(i + 1) + "]";
                InsertPlayer(Player(name, i + 1, reference));
            }
            winning_token_count_ = 3;
            break;
        }
    }
}
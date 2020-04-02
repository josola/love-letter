/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "game_util.h"
#include "console_in_util.h"
#include "console_out_util.h"

GameUtil::GameUtil(Game game) : game(game){};

int GameUtil::RoundCount()
{
    return game.round_count;

}

void GameUtil::GetPlayerCount()
{
    int count = ConsoleInUtil::GetIntInput();
    if (!CorrectPlayerCount(count))
    {
        FixPlayerCount();
    }
    else
    {
        game.player_count = SetPlayerCount(count);
        game.original_player_count = SetOriginalPlayerCount(count);
    }
    
}

bool GameUtil::CorrectPlayerCount(int input)
{
    if (input >= 2 && input <= 6)
    {
        return true;
    }
    else
    {
        ConsoleOutUtil::PrintInvalidInput(1);
        return false;
    }

}

void GameUtil::FixPlayerCount()
{
    ConsoleInUtil::ClearInput();
    GetPlayerCount();

}

int GameUtil::SetPlayerCount(int input)
{
    int count = input;
    return count;

}

int GameUtil::SetOriginalPlayerCount(int input)
{
    int count = input;
    return count;

}
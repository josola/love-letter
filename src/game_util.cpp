/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "game_util.h"
#include "console_in_util.h"
#include "console_out_util.h"

GameUtil::GameUtil(Game game) : game(game){};

void GameUtil::GetPlayerCount()
{
    ConsoleOutUtil::PrintStartingPlayerPrompt();
    int count = ConsoleInUtil::GetIntInput();
    if (!CorrectPlayerCount(count))
    {
        count = FixPlayerCount(count);
    }
    else
    {
        game.PlayerCount = SetPlayerCount(count);
        game.OriginalPlayerCount = SetOriginalPlayerCount(count);
    }
    
}

bool GameUtil::CorrectPlayerCount(int input)
{
    int count = input;
    if (count >= 2 && count <= 6)
    {
        return true;
    }
    else
    {
        ConsoleOutUtil::PrintInvalidInput(1);
        return false;
    }

}

int GameUtil::FixPlayerCount(int input)
{
    int count = input;
    bool correct = false;
    while (!correct)
    {
        count = ConsoleInUtil::GetIntInput();
        if (CorrectPlayerCount(count))
        {
            correct = true;
        }
        else
        {
            ConsoleInUtil::ClearInput();
        }
        
    }
    return count;

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
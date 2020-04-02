/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "game_util.h"
#include "console_in_util.h"
#include "console_out_util.h"

GameUtil::GameUtil(Game game) : game(game) {};

void GameUtil::GetPlayerCount()
{
    int count = ConsoleInUtil::GetIntInput();
    if (CheckPlayerCount(count))
    {
        SetPlayerCount(count);
        SetOriginalPlayerCount(count);
    }
    else
    {
        count = CorrectInput(count);
    }
    
}

bool GameUtil::CheckPlayerCount(int input)
{
    int count = input;
    if (count >= 2 || count <= 6)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

int GameUtil::CorrectInput(int input)
{
    int count = input;
    bool correct = false;
    while (!correct)
    {
        if (!CheckPlayerCount(count))
        {
            ConsoleOutUtil::PrintInvalidInput(0);
            ConsoleInUtil::ClearInput();
            count = ConsoleInUtil::GetIntInput();
        }
        else
        {
            correct = true;
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
/*
 * Holds information about the game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include <iostream>
#include "game_manager.h"
#include "player.h"
#include "console.h"

using std::cin;

GameController::GameController(GameState &state, Console &console) : state(state), console(console){};

int GameState::GetRoundCount() { return round_count; }
int GameState::GetPlayerCount() { return player_count; }
int GameState::GetStartingPlayerCount() { return starting_player_count; }
int GameState::GetWinningTokenCount() { return winning_token_count; }

void GameState::SetPlayerCount(int value)
{
    initial_log.push_back("player_count before setter: " + player_count);
    player_count = value;
}

void GameState::SetStartingPlayerCount(int value)
{
    initial_log.push_back("starting_player_count before setter: " + starting_player_count);
    starting_player_count = value;
}

void GameState::SetWinningTokenCount(int value)
{
    initial_log.push_back("winning_token_count before setter: " + winning_token_count);
    winning_token_count = value;
}

int GameController::SetPlayerCount(int output)
{
    bool correct_input = false;
    //check that input is within bounds
    while (!correct_input)
    {
        if (output >= 2 && output <= 6 && cin)
        {
            correct_input = true;
        }
        else
        {
            //reset cin fail, clear input buffer
            cin.clear();
            cin.ignore();
            console.PrintInvalidInput(1);
            output = console.ReceiveNumInput();
        }
    }
    return output;
}

int GameController::SetWinningTokenCount(int count)
{
    int output = 0;
    switch (count)
    {
    case 2:
        output = 6;
        break;
    case 3:
        output = 5;
        break;
    case 4:
        output = 4;
        break;
    case 5:
        output = 3;
        break;
    case 6:
        output = 3;
        break;
    }
    return output;
}
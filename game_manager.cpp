/*
 * Holds information about the game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include <iostream>
#include "game_manager.h"
#include "player.h"

using std::cin;

GameController::GameController(GameState &state, Console &console) : state(state), console(console){};

int GameState::GetRoundCount() { return round_count; }
int GameState::GetPlayerCount() { return player_count; }
vector<Player> GameState::GetPlayerContainer() { return player_container; }

void GameState::SetPlayerCount(int value)
{
    initial_log.push_back("player_count before setter: " + player_count);
    player_count = value;
}

void GameState::SetPlayerContainer(int count)
{
    switch (count)
    {
    case 2:
    {
        player_container.push_back(Player("PLAYER[1]", 1));
        player_container.push_back(Player("PLAYER[2]", 2));
        break;
    }
    case 3:
    {
        player_container.push_back(Player("PLAYER[1]", 1));
        player_container.push_back(Player("PLAYER[2]", 2));
        player_container.push_back(Player("PLAYER[3]", 3));
        break;
    }
    case 4:
    {
        player_container.push_back(Player("PLAYER[1]", 1));
        player_container.push_back(Player("PLAYER[2]", 2));
        player_container.push_back(Player("PLAYER[3]", 3));
        player_container.push_back(Player("PLAYER[4]", 4));
        break;
    }
    case 5:
    {
        player_container.push_back(Player("PLAYER[1]", 1));
        player_container.push_back(Player("PLAYER[2]", 2));
        player_container.push_back(Player("PLAYER[3]", 3));
        player_container.push_back(Player("PLAYER[4]", 4));
        player_container.push_back(Player("PLAYER[5]", 5));
        break;
    }
    case 6:
    {
        player_container.push_back(Player("PLAYER[1]", 1));
        player_container.push_back(Player("PLAYER[2]", 2));
        player_container.push_back(Player("PLAYER[3]", 3));
        player_container.push_back(Player("PLAYER[4]", 4));
        player_container.push_back(Player("PLAYER[5]", 5));
        player_container.push_back(Player("PLAYER[6]", 6));
        break;
    }
    }
}

void GameController::ReceivePlayerCount(int output)
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
    state.SetPlayerCount(output);
}
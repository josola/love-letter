/*
 * Holds information about the game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include <iostream>
#include "game_manager.h"
#include "player.h"

using std::cin;

Manager::Manager(GameState &state, Console &console) : state(state), console(console){};

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

//startup tasks for new games
void Manager::InitialSetup()
{
    if (state.GetRoundCount() == 1)
    {
        //prints startup prompt
        console.PrintStartup();

        //correct input setup
        int player_count_input = 0;
        bool correct_input = false;

        //check that input is between 2 and 6 and is an integer
        while (!correct_input)
        {
            cin >> player_count_input;
            if (player_count_input >= 2 && player_count_input <= 6 && cin)
            {
                correct_input = true;
            }
            else
            {
                //reset cin fail, clear input buffer
                cin.clear();
                cin.ignore();

                console.PrintInvalidInput(0);
                correct_input = false;
            }
        }

        //upon successful input
        state.SetPlayerCount(player_count_input);

        //add player objects to container
        state.SetPlayerContainer(player_count_input);
    }
    else
    {
        return;
    }
}
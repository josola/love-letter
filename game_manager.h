/*
 * Holds information about the game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include "console.h"
#include "player.h"

using std::string;
using std::vector;

class GameState
{
public:
    int GetRoundCount();
    int GetPlayerCount();
    vector<Player> GetPlayerContainer(); //container full of player objects
    void SetPlayerCount(int value);
    void SetPlayerContainer(int count);

private:
    vector<string> initial_log;
    vector<Player> player_container;
    int round_count = 1;
    int player_count = 0;
};

class GameController
{
public:
    GameController(GameState &state, Console &console);
    void ReceivePlayerCount(int output);

private:
    GameState &state;
    Console &console;
};

#endif
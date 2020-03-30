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
    int GetStartingPlayerCount();
    int GetWinningTokenCount();
    
    void SetPlayerCount(int value);
    void SetStartingPlayerCount(int value);
    void SetWinningTokenCount(int value);

private:
    vector<string> initial_log;
    int round_count = 1;
    int player_count = 0;
    int starting_player_count = 0;
    int winning_token_count = 0;
};

class GameController
{
public:
    GameController(GameState &state, Console &console);
    int SetPlayerCount(int value);
    int SetWinningTokenCount(int count);

private:
    GameState &state;
    Console &console;
};

#endif
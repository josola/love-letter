/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include <utility>
#include "game.h"
#include "player.h"

using std::pair;

class GameUtil
{
public:
    GameUtil(Game game);

    int RoundCount();
    void GetPlayerCount();
    bool CorrectPlayerCount(int input);
    void FixPlayerCount();
    void SetPlayerCount(int output);
    void SetOriginalPlayerCount(int output);
    void SetPlayers();
    vector<PlayerUtil> PlayerBuilder(int output);
    void SetWinningTokenCount();
    int PlayerCount();
    void BuildStartingPlayer();
    int GenerateNumberWithinRange(int range);
    int GetPlayerGuess();
    bool CorrectGuessInput(int output);
    void FixGuessInput();
    vector<PlayerUtil> Players();

private:
    Game game;

};

#endif
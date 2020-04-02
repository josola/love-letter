/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include "game.h"

class GameUtil
{
public:
    GameUtil(Game game);

    void GetPlayerCount();
    bool CorrectPlayerCount(int input);
    int FixPlayerCount(int input);
    int SetPlayerCount(int input);
    int SetOriginalPlayerCount(int input);

private:
    Game game;

};

#endif
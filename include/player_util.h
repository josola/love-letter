/*
 * Helper utility for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PLAYER_UTIL_h
#define PLAYER_UTIL_h

#include "player.h"

class PlayerUtil
{
public:
    PlayerUtil(Player player);

    void SetCurrent();
    string Name();
    void SetWinner(int output);
    bool Winner();
    void SetGuess(int output);
    int Guess();

private:
    Player player;
};

#endif
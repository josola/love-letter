/*
 * Helper utility for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PLAYER_UTIL_H
#define PLAYER_UTIL_H

#include "player.h"

class PlayerUtil
{
public:
    PlayerUtil(Player player);

    void SetCurrent();
    string Name();

private:
    Player player;
};

#endif
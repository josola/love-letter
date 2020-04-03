/*
 * Helper utility for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player_util.h"

PlayerUtil::PlayerUtil(Player player) : player(player) {};

void PlayerUtil::SetCurrent()
{
    player.current = true;
}

string PlayerUtil::Name()
{
    return player.name;
}
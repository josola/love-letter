/*
 * Determines game state information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_h
#define GAME_h

#include <vector>
#include "player_util.h"

using std::vector;

struct Game
{
    int player_count = 0;
    int original_player_count = 0;
    int round_count = 1;
    vector<PlayerUtil> players;
    int winning_token_count = 0;
};

#endif
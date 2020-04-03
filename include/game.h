/*
 * Determines game state information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player_util.h"

using std::vector;

struct Game
{
    Game game() {};
    int player_count = 0;
    int original_player_count = 0;
    int round_count = 1;
    vector<PlayerUtil> players;
    int winning_token_count = 0;

};

#endif
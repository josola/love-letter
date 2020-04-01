/*
 * Determines player information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "card.h"
#include "console.h"

using std::string;
using std::vector;

struct Player
{

};

class PlayerUtil
{
public:
    PlayerUtil(Player &player);

private:
    Player &player;
};

#endif
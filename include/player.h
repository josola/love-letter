/*
 * Determines information for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PLAYER_h
#define PLAYER_h

#include <string>

using std::string;

struct Player
{
    Player(string name = "", int value = 0) : name(name), value(value){};

    string name = "";
    int value = 0;
    bool current = false;
};

#endif
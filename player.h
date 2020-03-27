/*
 * Determines player information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "card.h"

using std::string;
using std::vector;

class Player
{
public:
    Player(string name, int value);
    string GetName();
    int GetValue();
    bool GetCurrentStatus();
    vector<Card> GetHand();
    void SetCurrent();

private:
    vector<string> initial_log;
    string name;
    int value;
    bool current_player;
    vector<Card> hand;
};

class PlayerController
{
public:
    PlayerController(Player &player);

private:
    Player &player;
};

#endif
/*
 * Determines player information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include <string>
#include <vector>
#include "player.h"
#include "console.h"

using std::string;
using std::vector;

Player::Player(string name, int value) : name(name), value(value){};

PlayerController::PlayerController(Player player, Console &console) : player(player), console(console){};

string Player::GetName() { return name; }
int Player::GetValue() { return value; }
bool Player::GetCurrentStatus() { return current_player; }
vector<Card> Player::GetHand() { return hand; }

void Player::SetCurrent()
{
    initial_log.push_back("current_player before setter: " + current_player);
    if (current_player)
    {
        current_player = false;
    }
    else
    {
        current_player = true;
    }
}

Player PlayerController::GetPlayer() { return player; }

Player PlayerController::SetPlayer(int output)
{
    if (output == 1)
    {
        Player p1("PLAYER[1]", 1);
        return p1;
    }
    else
    {
        Player p0("PLAYER[2]", 2);
        return p0;
    }
    
}
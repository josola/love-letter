/*
 * Helper utility for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player_util.h"

PlayerUtil::PlayerUtil(Player player) : player(player){};

void PlayerUtil::SetCurrent()
{
    player.current = true;
}

string PlayerUtil::Name()
{
    return player.name;
}

void PlayerUtil::SetWinner(int output)
{
    switch (output)
    {
    case 0:
        player.winner = false;
        break;
    case 1:
        player.winner = true;
        break;
    }
}

bool PlayerUtil::Winner()
{
    return player.winner;
}

void PlayerUtil::SetGuess(int output)
{
    player.guess = output;
}

int PlayerUtil::Guess()
{
    return player.guess;
}
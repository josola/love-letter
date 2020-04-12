/*
 * Helper utility for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player.h"

string const PlyrUtl::Name() { return name; }
int const PlyrUtl::Value() { return value; }
int const PlyrUtl::Guess() { return guess; }
bool const PlyrUtl::Current() { return current; }
bool const PlyrUtl::Spy() { return spy; }
bool const PlyrUtl::Winner() { return winner; }

void PlyrUtl::SetCurrent() { current = true; }
void PlyrUtl::SetWinner(int output)
{
    switch (output)
    {
    case 0:
        winner = false;
        break;
    case 1:
        winner = true;
        break;
    }
}
void PlyrUtl::SetGuess(int output) { guess = output; }

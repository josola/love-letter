/*
 * Determines deck information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DECK_H
#define DECK_H

#include "card_util.h"
#include <vector>

using std::vector;

struct Deck
{
    vector<CardUtil> deck;
};

#endif
/*
 * Determines deck information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

using std::vector;

struct Deck
{

};

class DeckUtil
{
public:
    DeckUtil(Deck &deck);

private:
    Deck &deck;
};

#endif
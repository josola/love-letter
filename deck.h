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

class Deck
{
public:
    vector<Card> GetDeck();

private:
    vector<Card> deck;
};

class DeckController
{
public:
    DeckController(Deck &deck);

private:
    Deck &deck;
};

#endif
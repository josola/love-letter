/*
 * Helper utility for deck.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DECK_UTIL_h
#define DECK_UTIL_h

#include <vector>
#include "deck.h"
#include "card_util.h"

using std::vector;

class DeckUtil
{
public:
    DeckUtil(Deck deck);

    vector<CardUtil> DeckBuilder();
    void SetDeck();
    vector<CardUtil> GetDeck();
    void ShuffleDeck();
    CardUtil GetCardFromDeck(int pos);
    void RemoveCardFromDeck(int pos);

private:
    Deck deck;
};

#endif
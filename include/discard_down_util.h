/*
 * Helper utility for down pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DISCARD_DOWN_UTIL_h
#define DISCARD_DOWN_UTIL_h

#include "discard_down.h"
#include "deck_util.h"

class DiscardDownUtil
{
public:
    DiscardDownUtil(DiscardDown& downPile);

    void SetDownPile(DeckUtil& deckUtil);
    vector<CardUtil> GetDownPile();

private:
    DiscardDown& discardDown;
};

#endif
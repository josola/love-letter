/*
 * Helper utility for up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef UP_PILE_UTIL_H
#define UP_PILE_UTIL_H

#include <vector>
#include "up_pile.h"
#include "card_util.h"
#include "deck_util.h"

using std::vector;

class UpPileUtil
{
public:
    UpPileUtil(UpPile upPile;

    vector<CardUtil> BuildUpPileTwoPlayer(DeckUtil deckUtil);
    void SetUpPile(vector<CardUtil> output);

private:
    UpPile upPile;
};

#endif
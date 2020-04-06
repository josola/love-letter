/*
 * Helper utility for down pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DOWN_PILE_H
#define DOWN_PILE_H

#include <vector>
#include "down_pile.h"
#include "deck_util.h"

using std::vector;

class DownPileUtil
{
public:
    DownPileUtil(DownPile downPile);

    void SetDownPile(DeckUtil deckUtil);

private:
    DownPile downPile;
};

#endif
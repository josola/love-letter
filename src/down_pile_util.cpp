/*
 * Helper utility for down pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <vector>
#include "down_pile_util.h"
#include "card_util.h"
#include "card_util.h"

using std::vector;

DownPileUtil::DownPileUtil(DownPile downPile) : downPile(downPile){};

void DownPileUtil::SetDownPile(DeckUtil deckUtil)
{
    downPile.down_pile.push_back(deckUtil.GetDeck()[0]);
    deckUtil.RemoveCardFromDeck(0);
}

vector<CardUtil> DownPileUtil::GetDownPile()
{
    return downPile.down_pile;
}
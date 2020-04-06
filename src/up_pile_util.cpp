/*
 * Helper utility for the up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <vector>
#include "up_pile_util.h"
#include "card_util.h"
#include "deck_util.h"

using std::vector;

UpPileUtil::UpPileUtil(UpPile upPile) : upPile(upPile){};

vector<CardUtil> UpPileUtil::BuildUpPileTwoPlayer(DeckUtil deckUtil)
{
    vector<CardUtil> output;
    for (int i = 0; i < 2; i++)
    {
        output.push_back(deckUtil.GetCardFromDeck(0));
        deckUtil.RemoveCardFromDeck(0);
    }
    return output;
}

void UpPileUtil::SetUpPile(vector<CardUtil> output)
{
    upPile.up_pile = output;
}
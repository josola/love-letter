/*
 * Helper utility for up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "discard_util.h"

UpPileUtil::UpPileUtil(Discard discard) : discard(discard){};

vector<CardUtil> UpPileUtil::UpPile()
{
    return discard.discard_pile;
}
/*
 * Helper utility for up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "discard_up_util.h"

DiscardUpUtil::DiscardUpUtil(DiscardUp& discardUp) : discardUp(discardUp){};

vector<CardUtil> DiscardUpUtil::UpPile()
{
    return discardUp.up_pile;
}
/*
 * Helper utility for up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DISCARD_UP_UTIL_h
#define DISCARD_UP_UTIL_h

#include "discard_up.h"

class DiscardUpUtil
{
public:
    DiscardUpUtil(DiscardUp& discardUp);
    vector<CardUtil> UpPile();
private:
    DiscardUp& discardUp;
};

#endif
/*
 * Helper utility for up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DISCARD_UTIL_h
#define DISCARD_UTIL_h

#include <vector>
#include "discard.h"

using std::vector;

class UpPileUtil
{
public:
    UpPileUtil(Discard discard);
    vector<CardUtil> UpPile();
private:
    Discard discard;
};

#endif
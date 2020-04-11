/*
 * Helper utility for up pile.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DISCARD_UTIL_h
#define DISCARD_UTIL_h

#include <vector>
#include "discard_up.h"

using std::vector;

class DiscardUpUtil
{
public:
    DiscardUpUtil(DiscardUp& discardUp);
    vector<CardUtil> UpPile();
private:
    DiscardUp& discardUp;
};

#endif
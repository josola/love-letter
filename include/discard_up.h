/*
 * Determines up pile information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DISCARD_h
#define DISCARD_h

#include <vector>
#include "card_util.h"

using std::vector;

struct DiscardUp
{
    vector<CardUtil> up_pile;
};

#endif
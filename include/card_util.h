/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_UTIL_h
#define CARD_UTIL_h

#include "card.h"

class CardUtil
{
public:
    CardUtil(Card card);

    string GetName();
    int GetValue();
    CardUtil CardUtilBuilder(int input);

private:
    Card card;
};

#endif
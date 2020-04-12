/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "card.h"

string CardInterface::Name() { return name; }
int CardInterface::Value() { return value; }

void CardInterface::SetName(string input) { name = input; }
void CardInterface::SetValue(int input) { value = input; }

CardUtl CardUtl::Builder(int input)
{
    switch (input)
    {
    case 0:
    {
        CardUtl spyUtil("SPY[0]", 0);
        return spyUtil;
        break;
    }
    case 1:
    {
        CardUtl guardUtil("GUARD[1]", 1);
        return guardUtil;
        break;
    }
    case 2:
    {
        CardUtl priestUtil("PRIEST[2]", 2);
        return priestUtil;
        break;
    }
    case 3:
    {
        CardUtl baronUtil("BARON[3]", 3);
        return baronUtil;
        break;
    }
    case 4:
    {
        CardUtl handmaidUtil("HANDMAID[4]", 4);
        return handmaidUtil;
        break;
    }
    case 5:
    {
        CardUtl princeUtil("PRINCE[5]", 5);
        return princeUtil;
        break;
    }
    case 6:
    {
        CardUtl chancellorUtil("CHANCELLOR[6]", 6);
        return chancellorUtil;
        break;
    }
    case 7:
    {
        CardUtl kingUtil("KING[7]", 7);
        return kingUtil;
        break;
    }
    case 8:
    {
        CardUtl countessUtil("COUNTESS[8]", 8);
        return countessUtil;
        break;
    }
    case 9:
    {
        CardUtl princessUtil("PRINCESS[9]", 9);
        return princessUtil;
        break;
    }
    default:
        CardUtl ghostUtil("", 10);
        return ghostUtil;
        break;
    }
}
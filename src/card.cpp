/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "card.h"

/* Card Interface */

//getters
string CardInterface::Name() { return name; }
int CardInterface::Value() { return value; }

//setters
void CardInterface::SetName(string input) { name = input; }
void CardInterface::SetValue(int input) { value = input; }

/* Card Controller */

CardController CardController::Builder(int input)
{
    switch (input)
    {
    case 0:
    {
        CardController spyUtil("SPY[0]", 0);
        return spyUtil;
        break;
    }
    case 1:
    {
        CardController guardUtil("GUARD[1]", 1);
        return guardUtil;
        break;
    }
    case 2:
    {
        CardController priestUtil("PRIEST[2]", 2);
        return priestUtil;
        break;
    }
    case 3:
    {
        CardController baronUtil("BARON[3]", 3);
        return baronUtil;
        break;
    }
    case 4:
    {
        CardController handmaidUtil("HANDMAID[4]", 4);
        return handmaidUtil;
        break;
    }
    case 5:
    {
        CardController princeUtil("PRINCE[5]", 5);
        return princeUtil;
        break;
    }
    case 6:
    {
        CardController chancellorUtil("CHANCELLOR[6]", 6);
        return chancellorUtil;
        break;
    }
    case 7:
    {
        CardController kingUtil("KING[7]", 7);
        return kingUtil;
        break;
    }
    case 8:
    {
        CardController countessUtil("COUNTESS[8]", 8);
        return countessUtil;
        break;
    }
    case 9:
    {
        CardController princessUtil("PRINCESS[9]", 9);
        return princessUtil;
        break;
    }
    default:
        CardController ghostUtil("", 10);
        return ghostUtil;
        break;
    }
}
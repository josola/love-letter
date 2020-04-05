/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "card_util.h"

CardUtil::CardUtil(Card card) : card(card){};

string CardUtil::GetName()
{
    return card.name;
}

int CardUtil::GetValue()
{
    return card.value;
}

CardUtil CardUtil::CardUtilBuilder(int input)
{
    switch (input)
    {
    case 0:
    {
        CardUtil spyUtil(Card("SPY[0]", 0));
        return spyUtil;
        break;
    }
    case 1:
    {
        CardUtil guardUtil(Card("GUARD[1]", 1));
        return guardUtil;
        break;
    }
    case 2:
    {
        CardUtil priestUtil(Card("PRIEST[2]", 2));
        return priestUtil;
        break;
    }
    case 3:
    {
        CardUtil baronUtil(Card("BARON[3]", 3));
        return baronUtil;
        break;
    }
    case 4:
    {
        CardUtil handmaidUtil(Card("HANDMAID[4]", 4));
        return handmaidUtil;
        break;
    }
    case 5:
    {
        CardUtil princeUtil(Card("PRINCE[5]", 5));
        return princeUtil;
        break;
    }
    case 6:
    {
        CardUtil chancellorUtil(Card("CHANCELLOR[6]", 6));
        return chancellorUtil;
        break;
    }
    case 7:
    {
        CardUtil kingUtil(Card("KING[7]", 7));
        return kingUtil;
        break;
    }
    case 8:
    {
        CardUtil countessUtil(Card("COUNTESS[8]", 8));
        return countessUtil;
        break;
    }
    case 9:
    {
        CardUtil princessUtil(Card("PRINCESS[9]", 9));
        return princessUtil;
        break;
    }
    default:
        CardUtil ghostUtil(Card("", 10));
        return ghostUtil;
        break;
    }
}
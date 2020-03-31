/*
 * Determines card information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_H
#define CARD_H

#include <string>

using std::string;

class Card
{
public:
    Card(string nam, int value);
    string GetName();
    int GetValue();

private:
    string name;
    int value;
};

class CardController
{
public:
    CardController(Card card);

private:
    Card card;
};

#endif
/*
 * Determines card information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_h
#define CARD_h

#include <string>

using std::string;

struct Card
{
    Card(string name = "", int value = 0) : name(name), value(value){};

    string name;
    int value;
};

#endif
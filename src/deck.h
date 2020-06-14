/*
 * deck.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

using std::vector;

class Deck
{
public:
    void Clear();
    const int Size();
    void Insert(Card card);

protected:
    vector<Card> pile_;

};

#endif

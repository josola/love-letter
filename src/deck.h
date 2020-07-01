/*
 * deck.h
 * (C) Jordan Sola 2019/2020 - MIT License
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
    void Print();
    void Set();
    void Shuffle();
    Card GetCard(const int position);

protected:
    vector<Card> pile_;
};

#endif

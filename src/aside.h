/*
 * aside.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef ASIDE_H
#define ASIDE_H

#include "card.h"
#include "deck.h"
#include <vector>

using std::vector;

class Aside : public Deck
{
public:
    int Size();
    void Insert(Card card);
    void Clear();

private:
    vector<Card> pile_;
    
};

#endif

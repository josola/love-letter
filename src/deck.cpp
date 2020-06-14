/*
 * deck.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "deck.h"
#include <stdexcept>

using std::logic_error;

void Deck::Clear()
{
    (pile_.empty()) ? (throw logic_error("Pile is empty!")) : (pile_.erase(pile_.begin(), pile_.end()));
    (!pile_.empty()) ? (throw logic_error("Erase didn't work!")) : (NULL);
}
const int Deck::Size()
{
    return pile_.size();
}
void Deck::Insert(Card card)
{
    pile_.push_back(card);
}
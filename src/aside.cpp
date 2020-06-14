/*
 * aside.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "aside.h"
#include <stdexcept>

using std::logic_error;

int Aside::Size()
{
    return pile_.size();
}
void Aside::Insert(Card card)
{
    pile_.push_back(card);
}
void Aside::Clear()
{
    if (pile_.empty())
    {
        throw logic_error("Pile is empty!");
    }
    else
    {
        pile_.erase(pile_.begin(), pile_.end());
        (!pile_.empty()) ? throw logic_error("Erase didn't work!") : (NULL);
    }
}
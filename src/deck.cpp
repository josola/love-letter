/*
 * deck.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "deck.h"
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
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
void Deck::Print()
{
    if (pile_.empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        if (pile_.size() == 1)
        {
            cout << pile_.at(0).GetName() << endl;
        }
        else
        {
            for (size_t i = 0; i < pile_.size(); i++)
            {
                if (i < pile_.size() - 1)
                {
                    cout << pile_.at(i).GetName() << ", ";
                }
                else
                {
                    cout << pile_.at(i).GetName() << endl;
                }
            }
        }
    }
}
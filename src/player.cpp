/*
 * Determines player information and utility.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player.h"

//getters
string const PlyrUtl::Name() { return name; }
int const PlyrUtl::Value() { return value; }
int const PlyrUtl::Guess() { return guess; }
bool const PlyrUtl::Current() { return current; }
bool const PlyrUtl::Spy() { return spy; }
bool const PlyrUtl::Winner() { return winner; }
vector<CardUtl> const PlyrUtl::Hand() { return hand; }

//setters
void PlyrUtl::IsCurrent() { current = true; }
void PlyrUtl::NotCurrent() { current = false; }
void PlyrUtl::IsWinner() { winner = true;}
void PlyrUtl::NotWinner() { winner = false; }
void PlyrUtl::SetGuess(int output) { guess = output; }

//actions
template<typename Object>
CardUtl PlyrUtl::DrawCard(Object &obj)
{
    CardUtl top_card = obj.Card(0);
    return top_card;
}
void PlyrUtl::InsertCardIntoHand(CardUtl card) { hand.push_back(card); }

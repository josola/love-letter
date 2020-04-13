/*
 * Determines player information and utility.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player.h"

//getters
string const PlyrITF::Name() { return name; }
int const PlyrITF::Value() { return value; }
int const PlyrITF::Guess() { return guess; }
bool const PlyrITF::Current() { return current; }
bool const PlyrITF::Spy() { return spy; }
bool const PlyrITF::Winner() { return winner; }
vector<CardUtl> const PlyrITF::Hand() { return hand; }

//setters
void PlyrITF::SetName(string input) { name = input; }
void PlyrITF::SetValue(int input) { value = input; }
void PlyrITF::IsCurrent() { current = true; }
void PlyrITF::NotCurrent() { current = false; }
void PlyrITF::IsWinner() { winner = true;}
void PlyrITF::NotWinner() { winner = false; }
void PlyrITF::SetGuess(int output) { guess = output; }

//actions
template<typename Object>
CardUtl PlyrCNTLR::DrawCard(Object &obj)
{
    CardUtl top_card = obj.Card(0);
    return top_card;
}
void PlyrCNTLR::InsertCardIntoHand(CardUtl card) { hand.push_back(card); }

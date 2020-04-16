/*
 * Determines player information and utility.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player.h"

//getters
const string PlyrITF::Name() { return name; }
const int PlyrITF::Value() { return value; }
const int PlyrITF::Guess() { return guess; }
const bool PlyrITF::Current() { return current; }
const bool PlyrITF::Spy() { return spy; }
const bool PlyrITF::Winner() { return winner; }
vector<CardUtl> const PlyrITF::Hand() { return hand; }
constexpr bool const PlyrITF::Playing() { return playing; }
const int PlyrITF::Tokens() { return token_count; }

//setters
void PlyrITF::SetName(string input) { name = input; }
void PlyrITF::SetValue(int input) { value = input; }
void PlyrITF::IsCurrent() { current = true; }
void PlyrITF::NotCurrent() { current = false; }
void PlyrITF::IsWinner() { winner = true;}
void PlyrITF::NotWinner() { winner = false; }
void PlyrITF::SetGuess(int output) { guess = output; }
void PlyrITF::IsPlaying() { playing = true; }
void PlyrITF::NotPlaying() { playing = false; }

//actions
template<typename Object>
CardUtl PlyrCNTLR::DrawCard(Object &obj)
{
    CardUtl top_card = obj.Card(0);
    return top_card;
}
void PlyrCNTLR::InsertCardIntoHand(CardUtl card) { hand.push_back(card); }

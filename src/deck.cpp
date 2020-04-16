/*
 * Helper utility for deck.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <algorithm>
#include "deck.h"

using std::random_shuffle;
using std::srand;
using std::time;

//getters
vector<CardController> DeckInterface::Deck() { return deck; }
CardController DeckInterface::Card(int pos)
{
    CardController card = deck.at(pos);
    RemoveCard(pos);
    return card;
}

//setters
void DeckInterface::InsertCard(CardController card) { deck.push_back(card); }

//actions
void DeckInterface::Shuffle()
{
    srand(time(NULL));
    random_shuffle(deck.begin(), deck.end());
}
void DeckInterface::RemoveCard(int pos) { deck.erase(deck.begin() + pos); }


//builds deck
void DeckController::Builder()
{
    CardController cardUtl("", 10);
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardUtl.Builder(0));
    }
    for (int i = 0; i < 6; i++)
    {
        InsertCard(cardUtl.Builder(1));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardUtl.Builder(2));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardUtl.Builder(3));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardUtl.Builder(4));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardUtl.Builder(5));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardUtl.Builder(6));
    }
    InsertCard(cardUtl.Builder(7));
    InsertCard(cardUtl.Builder(8));
    InsertCard(cardUtl.Builder(9));
}

//builds up pile (for 2 player games)
void UpController::Builder(DeckController deck) { for (int i = 0; i < 3; i++) { InsertCard(deck.Card(0)); } }
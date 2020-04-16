/*
 * Helper utility for deck.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DECK_h
#define DECK_h

#include <vector>
#include "card.h"

using std::vector;

class DeckModel
{
protected:
    vector<CardController> deck;
};

class DeckInterface : public DeckModel
{
public:
    DeckInterface() : DeckModel{} {};

    //getters
    vector<CardController> Deck();
    CardController Card(int pos);

    //setters
    void InsertCard(CardController card);

    //actions
    void Shuffle();
    void RemoveCard(int pos);
};

class DeckController : virtual public DeckInterface
{
public:
    DeckController() : DeckInterface{} {};

    virtual void Builder();
};

class UpController : virtual public DeckInterface
{
public:
    UpController() : DeckInterface{} {};

    virtual void Builder(DeckController deck);
};

class DownController : virtual public DeckInterface
{
public:
    DownController() : DeckInterface{} {};
};

#endif
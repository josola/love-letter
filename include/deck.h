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

class DeckMdl
{
protected:
    vector<CardUtl> deck;
};

class DeckInterface : public DeckMdl
{
public:
    DeckInterface() : DeckMdl{} {};

    //getters
    vector<CardUtl> Deck();
    CardUtl Card(int pos);

    //setters
    void InsertCard(CardUtl card);

    //actions
    void Shuffle();
    void RemoveCard(int pos);
};

class DeckUtl : virtual public DeckInterface
{
public:
    DeckUtl() : DeckInterface{} {};

    virtual void Builder();
};

class UpUtl : virtual public DeckInterface
{
public:
    UpUtl() : DeckInterface{} {};

    virtual void Builder(DeckUtl deck);
};

class DwnUtl : virtual public DeckInterface
{
public:
    DwnUtl() : DeckInterface{} {};
};

#endif
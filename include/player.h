/*
 * Helper utility for player.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PLAYER_h
#define PLAYER_h

#include <string>
#include <vector>
#include "card.h"

using std::string;
using std::vector;

class PlyrMdl
{
public:
    PlyrMdl(string name = "", int value = 0) : name(name), value(value) {};

protected:
    const string name = "";
    const int value = 0;
    bool current = false;
    bool winner = false;
    int guess = 0;
    bool spy = false;
    vector<CardUtl> hand;
};

class PlyrUtl : public PlyrMdl
{
public:
    PlyrUtl(string name, int value) : PlyrMdl{ name, value } {};

    //getters
    string const Name();
    int const Value();
    bool const Winner();
    bool const Current();
    bool const Spy();
    int const Guess();
    vector<CardUtl> const Hand();

    //setters
    void IsCurrent();
    void NotCurrent();
    void IsWinner();
    void NotWinner();
    void SetGuess(int output);

    //actions
    template<typename Object>
    CardUtl DrawCard(Object &obj);
    void InsertCardIntoHand(CardUtl card);
};

#endif
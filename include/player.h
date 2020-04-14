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

class PlyrM
{
protected:
    string name = "";
    int value = 0;
    bool current = false;
    bool winner = false;
    int guess = 0;
    bool spy = false;
    vector<CardUtl> hand;
    bool playing = true;
};

class PlyrITF : public PlyrM
{
public:
    PlyrITF(string name, int value) : PlyrM{} { SetName(name), SetValue(value); };

    //getters
    string const Name();
    int const Value();
    bool const Winner();
    bool const Current();
    bool const Spy();
    int const Guess();
    vector<CardUtl> const Hand();
    constexpr bool const Playing();

    //setters
    void SetName(string input);
    void SetValue(int input);
    void IsCurrent();
    void NotCurrent();
    void IsWinner();
    void NotWinner();
    void SetGuess(int output);
    void IsPlaying();
    void NotPlaying();
};

class PlyrCNTLR : public PlyrITF
{
public:
    PlyrCNTLR(string name = "", int value = 0) : PlyrITF{ name, value } {};

    //actions
    template<typename Object>
    CardUtl DrawCard(Object &obj);
    void InsertCardIntoHand(CardUtl card);
};

#endif
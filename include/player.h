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

class PlayerModel
{
protected:
    string name = "";
    int value = 0;
    bool current = false;
    bool winner = false;
    int guess = 0;
    bool spy = false;
    vector<CardController> hand;
    bool playing = true;
    int token_count = 0;
};

class PlayerInterface : public PlayerModel
{
public:
    PlayerInterface(string player_name, int player_value) : PlayerModel{} { SetName(player_name), SetValue(player_value); };

    //getters
    const string Name();
    const int Value();
    const bool Winner();
    const bool Current();
    const bool Spy();
    const int Guess();
    vector<CardController> const Hand();
    constexpr bool const Playing();
    const int Tokens();

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

class PlayerController : public PlayerInterface
{
public:
    PlayerController(string name = "", int value = 0) : PlayerInterface{ name, value } {};

    //actions
    template<typename Object>
    CardController DrawCard(Object &obj);
    void InsertCardIntoHand(CardController card);
};

#endif
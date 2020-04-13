/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_h
#define GAME_h

#include "player.h"
#include "deck.h"

class GameM
{
protected:
    int player_count = 0;
    int original_player_count = 0;
    int round_count = 1;
    vector<PlyrCNTLR> players;
    int winning_token_count = 0;
};

class GameITF : public GameM
{
public:
    GameITF() : GameM{} {};

    //getters
    const int PCount();
    const int Round();
    const int OPCount();
    const int WinningTokenCount();
    vector<PlyrCNTLR> Plyrs();

    //setters
    void SetPCount(int input);
    void SetOPCount(int input);
    void SetPlyrs(vector<PlyrCNTLR> input);
    void SetWinningTokenCount();
    void SetStrtngPlyr(int output);
};

class GameCNTLR : public GameITF
{
public:
    GameCNTLR() : GameITF{} {};

    void PCountIn();
    void PlayerBuilder();
    bool CorrectPlayerCount(int input);
    void FixPlayerCount();
    void BuildStartingPlayer();
    int GenerateNumberWithinRange(int range);
    int GetPlayerGuess();
    bool CorrectGuessInput(int output);
    void FixGuessInput(int input);
    bool DuplicateGuess(vector<int> guess_container, int guess);
    int GetCurrent();
    void DealStartingHand(DeckUtl &deck);
};

#endif
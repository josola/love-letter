/*
 * Helper utility for console out.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_OUT_UTIL_h
#define CONSOLE_OUT_UTIL_h

#include <string>
#include <vector>
#include "card_util.h"
#include "player_util.h"
#include "deck_util.h"
#include "game_util.h"

using std::string;
using std::vector;

class ConsoleOutUtil
{
public:
    static void PrintWelcome();
    static void PrintStartingPlayerPrompt();
    static void PrintInvalidInput(int output);
    static void PrintExitPrompt();
    static void PrintPlayerGuessPrompt(int output);
    static void PrintNameGuess(string name);
    static void PrintCorrectGuessPrompt(string name);
    static void PrintRound(int output);
    static void PrintPlayerTurn(int output);
    static void PrintString(string output);
    static void PrintUpPile(vector<CardUtil> up_pile);
    static void PrintDownPile(vector<CardUtil> down_pile);
    static void PrintMultipleWinners(vector<PlayerUtil> players, int range);
    static void PrintClosestGuess(int target, PlayerUtil player);
    static void PrintDeckTotal(DeckUtil deckUtil);
    static void PrintRivalPlayers(GameUtil gameUtil);

private:
};

#endif
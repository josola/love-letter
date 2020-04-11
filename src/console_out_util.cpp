/*
 * Helper utility for console out.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include "console_out_util.h"

using std::cout;

void ConsoleOutUtil::PrintWelcome()
{
    cout << "-- Welcome to Love Letter --\n";
}

void ConsoleOutUtil::PrintStartingPlayerPrompt()
{
    cout << "How many players will be playing?\n";
}

void ConsoleOutUtil::PrintInvalidInput(int output)
{
    switch (output)
    {
    case 0:
        cout << "Invalid input. Please enter an integer.\n";
        break;
    case 1:
        cout << "Invalid input. Please enter a number between 1 and 6.\n";
        break;
    case 2:
        cout << "Invalid input. Please enter a number between 1 and the max number of players: \n";
        break;
    case 3:
        cout << "Invalid input. Number already guessed.\n";
        break;
    default:
        cout << "Invalid input.\n";
        break;
    }
}

void ConsoleOutUtil::PrintExitPrompt()
{
    cout << "Type 'E' to exit:\n";
}

void ConsoleOutUtil::PrintPlayerGuessPrompt(int output)
{
    cout << "Guess any number between 1 and " << output << ".\n";
}

void ConsoleOutUtil::PrintNameGuess(string name)
{
    cout << name << " guess: \n";
}

void ConsoleOutUtil::PrintCorrectGuessPrompt(string name)
{
    cout << name << " got it! " << name << " goes first!\n";
}

void ConsoleOutUtil::PrintRound(int output)
{
    cout << "-- ROUND " << output << " --\n";
}

void ConsoleOutUtil::PrintDealingHand()
{
    cout << "Dealing out starting hand.\n";
}

void ConsoleOutUtil::PrintString(string output)
{
    cout << output << '\n';
}

void ConsoleOutUtil::PrintUpPile()
{
    cout << "Up pile:\n";
    cout << '\n';
}

void ConsoleOutUtil::PrintDownPile(vector<CardUtil> down_pile)
{
    cout << "Down pile:\n";
    for (CardUtil iCUtil : down_pile)
    {
        cout << ' ' << iCUtil.GetName();
    }
    cout << '\n';
}

void ConsoleOutUtil::PrintMultipleWinners(vector<PlayerUtil> players, int range)
{
    cout << "There were multiple winners last round.\n";
    for (PlayerUtil iPUtil : players)
    {
        cout << ' ' << iPUtil.Name();
    }
    cout << " please guess a number between 1 and " << range << '\n';
}

void ConsoleOutUtil::PrintClosestGuess(int target, PlayerUtil player)
{
    cout << player.Name() << " has the closest guess to target[" << target << "]! They get to go first this round!\n";
}
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

void ConsoleOutUtil::PrintPlayerTurn(int output)
{
    switch (output)
    {
    case 1:
        cout << "-- PLAYER[1] turn --\n";
        break;
    case 2:
        cout << "-- PLAYER[2] turn --\n";
        break;
    case 3:
        cout << "-- PLAYER[3] turn --\n";
        break;
    case 4:
        cout << "-- PLAYER[4] turn --\n";
        break;
    case 5:
        cout << "-- PLAYER[5] turn --\n";
        break;
    case 6:
        cout << "-- PLAYER[6] turn --\n";
        break;
    }
}

void ConsoleOutUtil::PrintString(string output)
{
    cout << output << '\n';
}

void ConsoleOutUtil::PrintUpPile(vector<CardUtl> up_pile)
{
    cout << "Up pile:\n";
    for (CardUtl iCUtil : up_pile)
    {
        cout << ' ' << iCUtil.Name();
    }
    cout << '\n';
}

void ConsoleOutUtil::PrintDownPile(vector<CardUtl> down_pile)
{
    cout << "Down pile:\n";
    for (CardUtl iCUtil : down_pile)
    {
        cout << ' ' << iCUtil.Name();
    }
    cout << '\n';
}

void ConsoleOutUtil::PrintMultipleWinners(vector<PlyrCNTLR> players, int range)
{
    cout << "There were multiple winners last round.\n";
    for (PlyrCNTLR iPUtil : players)
    {
        cout << ' ' << iPUtil.Name();
    }
    cout << " please guess a number between 1 and " << range << '\n';
}

void ConsoleOutUtil::PrintClosestGuess(int target, PlyrCNTLR player)
{
    cout << player.Name() << " has the closest guess to target[" << target << "]! They get to go first this round!\n";
}

void ConsoleOutUtil::PrintDeckTotal(DeckUtl deckUtil)
{
    int size = deckUtil.Deck().size();
    cout << "Total cards in deck: " << size << '\n';
}

void ConsoleOutUtil::PrintRivalPlayers(GameCNTLR gameUtil)
{
    if (gameUtil.PCount() == 2)
    {
        cout << "Rival player: \n";
        for (PlyrCNTLR iPUtil : gameUtil.Plyrs())
        {
            if (!iPUtil.Current())
            {
                cout << ' ' << iPUtil.Name();
            }
        }
        cout << '\n';
    }
    else
    {
        cout << "Rival players: \n";
        for (PlyrCNTLR iPUtil : gameUtil.Plyrs())
        {
            if (!iPUtil.Current())
            {
                cout << ' ' << iPUtil.Name();
            }
        }
        cout << '\n';
    }
}

void ConsoleOutUtil::PrintRivalsWithSpy(GameCNTLR gameUtil)
{
    int spy_count(0);
    for (PlyrCNTLR iPUtil : gameUtil.Plyrs())
    {
        if (iPUtil.Spy())
        {
            spy_count++;
        }
    }
    if (spy_count > 0)
    {
        cout << "Rivals with Spy: \n";
        for (PlyrCNTLR iPUtil : gameUtil.Plyrs())
        {
            if (iPUtil.Spy())
            {
                cout << ' ' << iPUtil.Name();
            }
        }
        cout << '\n';
    }
}

void ConsoleOutUtil::PrintPlayerHand(PlyrCNTLR PlyrCNTLR)
{
    cout << "Player hand: \n";
    for (CardUtl iCUtil : PlyrCNTLR.Hand())
    {
        cout << ' ' << iCUtil.Name();
    }
    cout << '\n';
}
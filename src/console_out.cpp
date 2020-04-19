/*
 * Helper utility for console out.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include "console_out.h"

using std::cout;

void ConsoleOut::PrintWelcome() { cout << "-- Welcome to Love Letter --\n"; }
void ConsoleOut::PrintStartingPlayerPrompt() { cout << "How many players will be playing?\n"; }
void ConsoleOut::PrintInvalidInput(int output)
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
void ConsoleOut::PrintExitPrompt() { cout << "Type 'E' to exit:\n"; }
void ConsoleOut::PrintPlayerGuessPrompt(int output) { cout << "Guess any number between 1 and " << output << ".\n"; }
void ConsoleOut::PrintNameGuess(string name) { cout << name << " guess: \n"; }
void ConsoleOut::PrintCorrectGuessPrompt(string name) { cout << name << " got it! " << name << " goes first!\n"; }
void ConsoleOut::PrintRound(int output) { cout << "-- ROUND " << output << " --\n"; }
void ConsoleOut::PrintPlayerTurn(int output)
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
void ConsoleOut::PrintString(string output) { cout << output << '\n'; }
void ConsoleOut::PrintUpPile(vector<CardController> up_pile)
{
    cout << "Up pile:\n";
    for (CardController iCUtil : up_pile)
    {
        cout << ' ' << iCUtil.Name();
    }
    cout << '\n';
}
void ConsoleOut::PrintDownPile(vector<CardController> down_pile)
{
    cout << "Down pile:\n";
    for (CardController iCUtil : down_pile)
    {
        cout << ' ' << iCUtil.Name();
    }
    cout << '\n';
}
void ConsoleOut::PrintMultipleWinners(vector<PlayerController> players, int range)
{
    cout << "There were multiple winners last round.\n";
    for (PlayerController iPUtil : players)
    {
        cout << ' ' << iPUtil.Name();
    }
    cout << " please guess a number between 1 and " << range << '\n';
}
void ConsoleOut::PrintClosestGuess(int target, PlayerController player)
{
    cout << player.Name() << " has the closest guess to target[" << target << "]! They get to go first this round!\n";
}
void ConsoleOut::PrintDeckTotal(DeckController deckUtil)
{
    int size = deckUtil.Deck().size();
    cout << "Total cards in deck: " << size << '\n';
}
void ConsoleOut::PrintRivalPlayers(GameController gameUtil)
{
    if (gameUtil.PCount() == 2)
    {
        cout << "Rival player: \n";
        for (PlayerController iPUtil : gameUtil.Players())
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
        for (PlayerController iPUtil : gameUtil.Players())
        {
            if (!iPUtil.Current())
            {
                cout << ' ' << iPUtil.Name();
            }
        }
        cout << '\n';
    }
}
void ConsoleOut::PrintRivalsWithSpy(GameController gameUtil)
{
    int spy_count(0);
    for (PlayerController iPUtil : gameUtil.Players())
    {
        if (iPUtil.Spy())
        {
            spy_count++;
        }
    }
    if (spy_count > 0)
    {
        cout << "Rivals with Spy: \n";
        for (PlayerController iPUtil : gameUtil.Players())
        {
            if (iPUtil.Spy())
            {
                cout << ' ' << iPUtil.Name();
            }
        }
        cout << '\n';
    }
}
void ConsoleOut::PrintPlayerHand(PlayerController PlyrCNTLR)
{
    cout << "Player hand: \n";
    for (CardController iCUtil : PlyrCNTLR.Hand())
    {
        cout << ' ' << iCUtil.Name();
    }
    cout << '\n';
}
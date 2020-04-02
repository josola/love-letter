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
    default:
        cout << "Invalid input.\n";
        break;
    }

}

void ConsoleOutUtil::PrintExitPrompt()
{
    cout << "Type 'E' to exit:\n";

}
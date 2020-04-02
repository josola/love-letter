/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include "console_in_util.h"
#include "console_out_util.h"

using std::cin;

int ConsoleInUtil::GetIntInput()
{
    int input = 0;
    cin >> input;
    if (!CorrectInput(input))
    {
        FixIntInput();
    }
    else
    {
        return input;
    }

}

bool ConsoleInUtil::CorrectInput(int input)
{
    if (!cin)
    {
        ConsoleOutUtil::PrintInvalidInput(0);
        return false;
    }
    else
    {
        return true;
    }

}

void ConsoleInUtil::FixIntInput()
{
    ClearInput();
    GetIntInput();

}

void ConsoleInUtil::ClearInput()
{
    cin.clear();
    cin.ignore();

}
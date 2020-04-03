/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include <numeric>
#include "console_in_util.h"
#include "console_out_util.h"

using std::cin;
using std::numeric_limits;
using std::streamsize;

int ConsoleInUtil::GetIntInput()
{
    int input;
    cin >> input;
    switch (CorrectInput(input))
    {
    case 0:
        FixIntInput();
        break;
    case 1:
        return input;
        break;
    default:
        return 0;
        break;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}
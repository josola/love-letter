/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include <limits>
#include "console_in_util.h"
#include "console_out_util.h"

using std::cin;
using std::numeric_limits;
using std::streamsize;

int ConsoleInUtil::GetIntInput()
{
    int input;
    cin >> input;
    
    if (!CorrectInput(input))
    {
        int fixed = 0;
        fixed = FixIntInput(input);
        return fixed;
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

int ConsoleInUtil::FixIntInput(int input)
{
    bool correct = false;
    int fixed = 0;
    while (!correct)
    {
        ClearInput();
        cin >> fixed;
        if (cin)
        {
            correct = true;
        }
    }
    return fixed;

}

void ConsoleInUtil::ClearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}
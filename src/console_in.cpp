/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include <limits>
#include "console_in.h"
#include "console_out.h"

using std::cin;
using std::numeric_limits;
using std::streamsize;

int ConsoleIn::GetIntInput()
{
    int input;
    cin >> input;

    if (!CorrectIntInput(input))
    {
        int fixed = 0;
        fixed = FixIntInput();
        return fixed;
    }
    else
    {
        return input;
    }
}
bool ConsoleIn::CorrectIntInput(int input)
{
    if (!cin)
    {
        ConsoleOut::PrintInvalidInput(0);
        return false;
    }
    else
    {
        return true;
    }
}
int ConsoleIn::FixIntInput()
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
void ConsoleIn::ClearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
char ConsoleIn::GatCharInput()
{
    char output;
    cin >> output;
    if (!CorrectCharInput(output))
    {
        output = FixCharInput();
    }
    return output;
}
bool ConsoleIn::CorrectCharInput(char input)
{
    if (!cin)
    {
        ConsoleOut::PrintInvalidInput(6);
        return false;
    }
    else
    {
        return true;
    }
}
char ConsoleIn::FixCharInput()
{
    bool correct = false;
    char fixed;
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
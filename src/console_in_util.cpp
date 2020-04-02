/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include "console_in_util.h"

using std::cin;

int ConsoleInUtil::GetIntInput()
{
    int input = 0;
    cin >> input;
    return input;

}

void ConsoleInUtil::ClearInput()
{
    cin.clear();
    cin.ignore();
}
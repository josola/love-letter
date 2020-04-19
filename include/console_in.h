/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_IN_h
#define CONSOLE_IN_h

#include <string>

using std::string;

class ConsoleIn
{
public:
    static int GetIntInput();
    static bool CorrectIntInput(int input);
    static int FixIntInput();
    static void ClearInput();
    static string GetStringInput();
    static bool CorrectStringInput(string input);
    static string FixStringInput();
};

#endif
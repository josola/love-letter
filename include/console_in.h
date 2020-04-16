/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_IN_UTIL_h
#define CONSOLE_IN_UTIL_h

class ConsoleIn
{
public:
    static int GetIntInput();
    static bool CorrectInput(int input);
    static int FixIntInput(int input);
    static void ClearInput();

private:
};

#endif
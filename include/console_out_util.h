/*
 * Helper utility for console out.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_OUT_UTIL_H
#define CONSOLE_OUT_UTIL_H

class ConsoleOutUtil
{
public:
    static void PrintWelcome();
    static void PrintStartingPlayerPrompt();
    static void PrintInvalidInput(int output);
    static void PrintExitPrompt();

private:

};

#endif
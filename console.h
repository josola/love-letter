/*
 * Determines input and outputs correctly to the console.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_H
#define CONSOLE_H

struct Console
{
    Console();
    static int ReceiveNumInput();
    static void PrintWelcomeMessage();
    static void PrintBeginningPlayerPrompt(int player_count);
    static void PrintInvalidInput(int type);
};

#endif
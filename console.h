/*
 * Determines input and outputs correctly to the console.
 * This program uses the MIT license.
 * Written by Jordan Sola 2020
 */

#ifndef CONSOLE_H
#define CONSOLE_H

struct Console
{
    void PrintStartup();
    void PrintInvalidInput(int type);
};

#endif
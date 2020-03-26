/*
 * Executes the program.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include "console.h"
#include "game_manager.h"

int main()
{
    Console console;
    GameState state;
    Manager manager(state, console);
    manager.InitialSetup();
    return 0;
}
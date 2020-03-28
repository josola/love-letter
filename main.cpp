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
    GameController gameController(state, console);
    if (state.GetRoundCount() == 1)
    {
        console.PrintWelcomeMessage();
        gameController.SetPlayerCount(console.ReceiveNumInput());
        gameController.SetPlayerContainer(state.GetPlayerCount());
        gameController.SetWinningTokenCount(state.GetPlayerCount());
        gameController.SetStartingPlayer();
    }
    else
    {
        /* code */
    }
    
    return 0;
}
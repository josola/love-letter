/*
 * Executes the program.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "console.h"
#include "game_manager.h"

int main()
{
    Console console;
    GameState state;
    GameController gameController(state);
    if (state.GetRoundCount() == 1)
    {
        Console::PrintWelcomeMessage();
        state.SetPlayerCount(gameController.SetPlayerCount(Console::ReceiveNumInput()));
        state.SetPlayerControllerContainer(gameController.SetPlayerControllerContainer(state.GetPlayerCount()));
        state.SetWinningTokenCount(gameController.SetWinningTokenCount(state.GetPlayerCount()));
    }
    else
    {
        /* code */
    }

    return 0;
}
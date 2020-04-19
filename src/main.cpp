/*
 * Executes the program.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "console_out.h"
#include "console_in.h"
#include "game.h"
#include "deck.h"

int main()
{
    bool initial_setup = true;
    bool begin_round = true;
    bool player_turn = true;
    bool game_over = false;

    while (!game_over)
    {
        GameController gameController;
        DeckController deckController;
        DownController downController;
        UpController upController;

        while (initial_setup && !game_over)
        {
            if (gameController.Round() > 1 || game_over)
            {
                initial_setup = false;
                break;
            }
            ConsoleOut::PrintWelcome();
            ConsoleOut::PrintStartingPlayerPrompt();
            gameController.BuildPCount();
            gameController.BuildPContainer();
            gameController.BuildWinningTokenCount();
            ConsoleOut::PrintPlayerGuessPrompt(gameController.PCount());
            gameController.BuildStartingPlyr();
            initial_setup = false;
        }

        while (begin_round && !game_over)
        {
            for (PlayerController iPCNTLR : gameController.Players())
            {
                if (iPCNTLR.Tokens() > gameController.WinningTokenCount())
                {
                    game_over = true;
                    begin_round = false;
                    break;
                }
            }
            gameController.SetStrtngPlyr(gameController.FindWinner());
            gameController.ClearWinner();
            gameController.ClearPlaying();
            ConsoleOut::PrintRound(gameController.Round());
            ConsoleOut::PrintPlayerTurn(gameController.PCurrent());

            deckController.Builder();
            deckController.Shuffle();

            //discard one card face down
            downController.InsertCard(deckController.Card(0));

            if (gameController.PCount() == 2)
            {
                upController.Builder(deckController);
            }

            gameController.DealStartingHand(deckController);

            ConsoleOut::PrintDeckTotal(deckController);

            if (!upController.Deck().empty())
            {
                ConsoleOut::PrintUpPile(upController.Deck());
            }

            ConsoleOut::PrintRivalPlayers(gameController);
            ConsoleOut::PrintRivalsWithSpy(gameController);
            begin_round = false;
        }

        while (player_turn && !game_over)
        {
            ConsoleOut::PrintPlayerHand(gameController.Players().at(gameController.PCurrent()));
            player_turn = false;
        }
    }
    return 0;
}
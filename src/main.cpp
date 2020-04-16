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
        GameController gameCNTLR;

        while (initial_setup && !game_over)
        {
            if (gameCNTLR.Round() > 1 || game_over)
            {
                initial_setup = false;
                break;
            }
            ConsoleOut::PrintWelcome();
            ConsoleOut::PrintStartingPlayerPrompt();
            gameCNTLR.BuildPCount();
            gameCNTLR.BuildPContainer();
            gameCNTLR.BuildWinningTokenCount();
            ConsoleOut::PrintPlayerGuessPrompt(gameCNTLR.PCount());
            gameCNTLR.BuildStartingPlyr();
            initial_setup = false;
        }

        while (begin_round && !game_over)
        {
            for (PlayerController iPCNTLR : gameCNTLR.Plyrs())
            {
                if (iPCNTLR.Tokens() > gameCNTLR.WinningTokenCount())
                {
                    game_over = true;
                    begin_round = false;
                    break;
                }
            }
            gameCNTLR.SetStrtngPlyr(gameCNTLR.FindWinner());
            gameCNTLR.ClearWinner();
            gameCNTLR.ClearPlaying();
            ConsoleOut::PrintRound(gameCNTLR.Round());
            ConsoleOut::PrintPlayerTurn(gameCNTLR.PCurrent());

            DeckController deckUtl;

            deckUtl.Builder();
            deckUtl.Shuffle();

            DownController dwnUtl;

            //discard one card face down
            dwnUtl.InsertCard(deckUtl.Card(0));

            UpController upUtl;

            if (gameCNTLR.PCount() == 2)
            {
                upUtl.Builder(deckUtl);
            }

            gameCNTLR.DealStartingHand(deckUtl);

            ConsoleOut::PrintDeckTotal(deckUtl);

            if (!upUtl.Deck().empty())
            {
                ConsoleOut::PrintUpPile(upUtl.Deck());
            }

            ConsoleOut::PrintRivalPlayers(gameCNTLR);
            ConsoleOut::PrintRivalsWithSpy(gameCNTLR);
            begin_round = false;
        }

        while (player_turn && !game_over)
        {

        }
    }
    return 0;
}
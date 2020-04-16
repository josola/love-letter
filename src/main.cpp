/*
 * Executes the program.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "console_out_util.h"
#include "console_in_util.h"
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
        GameCNTLR gameCNTLR;

        while (initial_setup && !game_over)
        {
            if (gameCNTLR.Round() > 1 || game_over)
            {
                initial_setup = false;
                break;
            }
            ConsoleOutUtil::PrintWelcome();
            ConsoleOutUtil::PrintStartingPlayerPrompt();
            gameCNTLR.BuildPCount();
            gameCNTLR.BuildPContainer();
            gameCNTLR.BuildWinningTokenCount();
            ConsoleOutUtil::PrintPlayerGuessPrompt(gameCNTLR.PCount());
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
            ConsoleOutUtil::PrintRound(gameCNTLR.Round());
            ConsoleOutUtil::PrintPlayerTurn(gameCNTLR.PCurrent());

            DeckUtl deckUtl;

            deckUtl.Builder();
            deckUtl.Shuffle();

            DwnUtl dwnUtl;

            //discard one card face down
            dwnUtl.InsertCard(deckUtl.Card(0));

            UpUtl upUtl;

            if (gameCNTLR.PCount() == 2)
            {
                upUtl.Builder(deckUtl);
            }

            gameCNTLR.DealStartingHand(deckUtl);

            ConsoleOutUtil::PrintDeckTotal(deckUtl);

            if (!upUtl.Deck().empty())
            {
                ConsoleOutUtil::PrintUpPile(upUtl.Deck());
            }

            ConsoleOutUtil::PrintRivalPlayers(gameCNTLR);
            ConsoleOutUtil::PrintRivalsWithSpy(gameCNTLR);
            begin_round = false;
        }

        while (player_turn && !game_over)
        {

        }
    }
    return 0;
}
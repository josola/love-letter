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
    GameCNTLR gameCNTLR;

    if (gameCNTLR.Round() == 1)
    {
        ConsoleOutUtil::PrintWelcome();
        ConsoleOutUtil::PrintStartingPlayerPrompt();
        gameCNTLR.BuildPCount();
        gameCNTLR.BuildPContainer();
        gameCNTLR.BuildWinningTokenCount();
        ConsoleOutUtil::PrintPlayerGuessPrompt(gameCNTLR.PCount());
        gameCNTLR.BuildStartingPlyr();
    }
    else if (gameCNTLR.Round() >= 2)
    {
        gameCNTLR.SetStrtngPlyr(gameCNTLR.FindWinner());
        gameCNTLR.ClearWinner();
        gameCNTLR.ClearPlaying();
    }

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

    system("pause");
    return 0;
}
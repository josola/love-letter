/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include "game_util.h"
#include "console_in_util.h"
#include "console_out_util.h"

GameUtl::GameUtl(Game& game) : game(game) {};

int GameUtl::RoundCount()
{
    return game.round_count;
}

void GameUtl::GetPlayerCount()
{
    int count(ConsoleInUtil::GetIntInput());
    if (!CorrectPlayerCount(count))
    {
        FixPlayerCount();
    }
    else
    {
        SetPlayerCount(count);
        SetOriginalPlayerCount(count);
    }
}

bool GameUtl::CorrectPlayerCount(int input)
{
    if (input >= 2 && input <= 6)
    {
        return true;
    }
    else
    {
        ConsoleOutUtil::PrintInvalidInput(1);
        return false;
    }
}

void GameUtl::FixPlayerCount()
{
    ConsoleInUtil::ClearInput();
    GetPlayerCount();
}

void GameUtl::SetPlayerCount(int output)
{
    game.player_count = output;
}

void GameUtl::SetOriginalPlayerCount(int output)
{
    game.original_player_count = output;
}

void GameUtl::SetPlayers()
{
    switch (game.original_player_count)
    {
    case 2:
        game.players = PlayerBuilder(2);
        break;
    case 3:
        game.players = PlayerBuilder(3);
        break;
    case 4:
        game.players = PlayerBuilder(4);
        break;
    case 5:
        game.players = PlayerBuilder(5);
        break;
    case 6:
        game.players = PlayerBuilder(6);
        break;
    }
}

vector<PlyrUtl> GameUtl::PlayerBuilder(int output)
{
    vector<PlyrUtl> player_container{};
    switch (output)
    {
    case 2:
    {
        PlyrUtl p1Util("PLAYER[1]", 1);
        PlyrUtl p2Util("PLAYER[2]", 2);
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        return player_container;
        break;
    }
    case 3:
    {
        PlyrUtl p1Util("PLAYER[1]", 1);
        PlyrUtl p2Util("PLAYER[2]", 2);
        PlyrUtl p3Util("PLAYER[3]", 3);
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        player_container.push_back(p3Util);
        return player_container;
        break;
    }
    case 4:
    {
        PlyrUtl p1Util("PLAYER[1]", 1);
        PlyrUtl p2Util("PLAYER[2]", 2);
        PlyrUtl p3Util("PLAYER[3]", 3);
        PlyrUtl p4Util("PLAYER[4]", 4);
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        player_container.push_back(p3Util);
        player_container.push_back(p4Util);
        return player_container;
        break;
    }
    case 5:
    {
        PlyrUtl p1Util("PLAYER[1]", 1);
        PlyrUtl p2Util("PLAYER[2]", 2);
        PlyrUtl p3Util("PLAYER[3]", 3);
        PlyrUtl p4Util("PLAYER[4]", 4);
        PlyrUtl p5Util("PLAYER[5]", 5);
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        player_container.push_back(p3Util);
        player_container.push_back(p4Util);
        player_container.push_back(p5Util);
        return player_container;
        break;
    }
    case 6:
    {
        PlyrUtl p1Util("PLAYER[1]", 1);
        PlyrUtl p2Util("PLAYER[2]", 2);
        PlyrUtl p3Util("PLAYER[3]", 3);
        PlyrUtl p4Util("PLAYER[4]", 4);
        PlyrUtl p5Util("PLAYER[5]", 5);
        PlyrUtl p6Util("PLAYER[6]", 6);
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        player_container.push_back(p3Util);
        player_container.push_back(p4Util);
        player_container.push_back(p5Util);
        player_container.push_back(p6Util);
        return player_container;
        break;
    }
    default:
    {
        PlyrUtl p0Util("PLAYER[0]", 0);
        player_container.push_back(p0Util);
        return player_container;
        break;
    }
    }
}

void GameUtl::SetWinningTokenCount()
{
    switch (game.player_count)
    {
    case 2:
        game.winning_token_count = 6;
        break;
    case 3:
        game.winning_token_count = 5;
        break;
    case 4:
        game.winning_token_count = 4;
        break;
    case 5:
        game.winning_token_count = 3;
        break;
    case 6:
        game.winning_token_count = 3;
        break;
    }
}

int GameUtl::PlayerCount()
{
    return game.player_count;
}

void GameUtl::SetStartingPlayer(int output)
{
    output--;
    switch (output)
    {
    case 0:
        game.players.at(0).IsCurrent();
        break;
    case 1:
        game.players.at(1).IsCurrent();
        break;
    case 2:
        game.players.at(2).IsCurrent();
        break;
    case 3:
        game.players.at(3).IsCurrent();
        break;
    case 4:
        game.players.at(4).IsCurrent();
        break;
    case 5:
        game.players.at(5).IsCurrent();
        break;
    }
}

int GameUtl::BuildStartingPlayer()
{
    int target(GenerateNumberWithinRange(game.player_count));
    vector<int> duplicate_guess{};
    int player(0);
    for (PlyrUtl iPUtil : game.players)
    {
        ConsoleOutUtil::PrintNameGuess(iPUtil.Name());
        int guess(GetPlayerGuess());
        while (DuplicateGuess(duplicate_guess, guess))
        {
            guess = GetPlayerGuess();
        }
        if (guess == target)
        {
            ConsoleOutUtil::PrintCorrectGuessPrompt(iPUtil.Name());
            duplicate_guess.erase(duplicate_guess.begin(), duplicate_guess.end());
            player = iPUtil.Value();
            break;
        }
        else
        {
            duplicate_guess.push_back(guess);
        }
    }
    return player;
}

int GameUtl::GenerateNumberWithinRange(int range)
{
    srand(time(NULL));
    int output(rand() % range + 1);
    return output;
}

int GameUtl::GetPlayerGuess()
{
    int output(ConsoleInUtil::GetIntInput());
    if (!CorrectGuessInput(output))
    {
        FixGuessInput(output);
    }
    return output;
}

bool GameUtl::CorrectGuessInput(int output)
{
    if (output >= 1 && output <= game.player_count)
    {
        return true;
    }
    else
    {
        ConsoleOutUtil::PrintInvalidInput(2);
        return false;
    }
}

void GameUtl::FixGuessInput(int input)
{
    ConsoleInUtil::ClearInput();
    input = GetPlayerGuess();
}

bool GameUtl::DuplicateGuess(vector<int> guess_container, int guess)
{
    for (int iInt : guess_container)
    {
        if (iInt == guess)
        {
            ConsoleOutUtil::PrintInvalidInput(3);
            return true;
        }
    }
    return false;
}

vector<PlyrUtl> GameUtl::Players()
{
    return game.players;
}

int GameUtl::GetCurrent()
{
    int output(0);
    for (PlyrUtl iPUtil : game.players)
    {
        if (iPUtil.Current())
        {
            output = iPUtil.Value();
        }
    }
    return output;
}

void GameUtl::DealStartingHand(DeckUtl &deck)
{
    for (PlyrUtl &iPUtl : game.players)
    {
        iPUtl.InsertCardIntoHand(deck.Card(0));
    }
}
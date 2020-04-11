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

GameUtil::GameUtil(Game game) : game(game) {};

int GameUtil::RoundCount()
{
    return game.round_count;
}

void GameUtil::GetPlayerCount()
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

bool GameUtil::CorrectPlayerCount(int input)
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

void GameUtil::FixPlayerCount()
{
    ConsoleInUtil::ClearInput();
    GetPlayerCount();
}

void GameUtil::SetPlayerCount(int output)
{
    game.player_count = output;
}

void GameUtil::SetOriginalPlayerCount(int output)
{
    game.original_player_count = output;
}

void GameUtil::SetPlayers()
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

vector<PlayerUtil> GameUtil::PlayerBuilder(int output)
{
    vector<PlayerUtil> player_container{};
    switch (output)
    {
    case 2:
    {
        PlayerUtil p1Util(Player("PLAYER[1]", 1));
        PlayerUtil p2Util(Player("PLAYER[2]", 2));
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        return player_container;
        break;
    }
    case 3:
    {
        PlayerUtil p1Util(Player("PLAYER[1]", 1));
        PlayerUtil p2Util(Player("PLAYER[2]", 2));
        PlayerUtil p3Util(Player("PLAYER[3]", 3));
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        player_container.push_back(p3Util);
        return player_container;
        break;
    }
    case 4:
    {
        PlayerUtil p1Util(Player("PLAYER[1]", 1));
        PlayerUtil p2Util(Player("PLAYER[2]", 2));
        PlayerUtil p3Util(Player("PLAYER[3]", 3));
        PlayerUtil p4Util(Player("PLAYER[4]", 4));
        player_container.push_back(p1Util);
        player_container.push_back(p2Util);
        player_container.push_back(p3Util);
        player_container.push_back(p4Util);
        return player_container;
        break;
    }
    case 5:
    {
        PlayerUtil p1Util(Player("PLAYER[1]", 1));
        PlayerUtil p2Util(Player("PLAYER[2]", 2));
        PlayerUtil p3Util(Player("PLAYER[3]", 3));
        PlayerUtil p4Util(Player("PLAYER[4]", 4));
        PlayerUtil p5Util(Player("PLAYER[5]", 5));
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
        PlayerUtil p1Util(Player("PLAYER[1]", 1));
        PlayerUtil p2Util(Player("PLAYER[2]", 2));
        PlayerUtil p3Util(Player("PLAYER[3]", 3));
        PlayerUtil p4Util(Player("PLAYER[4]", 4));
        PlayerUtil p5Util(Player("PLAYER[5]", 5));
        PlayerUtil p6Util(Player("PLAYER[6]", 6));
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
        PlayerUtil p0Util(Player("PLAYER[0]", 0));
        player_container.push_back(p0Util);
        return player_container;
        break;
    }
    }
}

void GameUtil::SetWinningTokenCount()
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

int GameUtil::PlayerCount()
{
    return game.player_count;
}

void GameUtil::BuildStartingPlayer()
{
    int target(GenerateNumberWithinRange(game.player_count));
    vector<int> duplicate_guess{};
    for (PlayerUtil iPUtil : game.players)
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
            iPUtil.SetCurrent();
            duplicate_guess.erase(duplicate_guess.begin(), duplicate_guess.end());
            break;
        }
        else
        {
            duplicate_guess.push_back(guess);
        }
    }
}

int GameUtil::GenerateNumberWithinRange(int range)
{
    srand(time(NULL));
    int output(rand() % range + 1);
    return output;
}

int GameUtil::GetPlayerGuess()
{
    int output(ConsoleInUtil::GetIntInput());
    if (!CorrectGuessInput(output))
    {
        FixGuessInput(output);
    }
    return output;
}

bool GameUtil::CorrectGuessInput(int output)
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

void GameUtil::FixGuessInput(int input)
{
    ConsoleInUtil::ClearInput();
    input = GetPlayerGuess();
}

bool GameUtil::DuplicateGuess(vector<int> guess_container, int guess)
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

vector<PlayerUtil> GameUtil::Players()
{
    return game.players;
}
/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <iterator>
#include "game.h"
#include "console_in_util.h"
#include "console_out_util.h"

using std::find;
using std::distance;

const int GameITF::PCount(){ return player_count; }
const int GameITF::Round() { return round_count; }
const int GameITF::OPCount() { return original_player_count; }
const int GameITF::WinningTokenCount() { return winning_token_count; }
vector<PlyrCNTLR> GameITF::Plyrs() { return players; }
int GameITF::PCurrent()
{
    int output(0);
    for (PlyrCNTLR iPUtil : players)
    {
        if (iPUtil.Current())
        {
            output = iPUtil.Value();
        }
    }
    return output;
}
int GameITF::FindWinner()
{
    int index(0);
    for (int i = 0; i < players.size(); i++)
    {
        if (players.at(i).Winner())
        {
            index = i;
        }
    }
    return index;
}
void GameITF::SetPCount(int input) { player_count = input; }
void GameITF::SetOPCount(int input) { original_player_count = input; }
void GameITF::SetPlyrs(vector<PlyrCNTLR> input) { players = input; }
void GameITF::SetWinningTokenCount(int input) { winning_token_count = input; }
void GameITF::SetStrtngPlyr(int output)
{
    output--;
    switch (output)
    {
    case 0:
        players.at(0).IsCurrent();
        break;
    case 1:
        players.at(1).IsCurrent();
        break;
    case 2:
        players.at(2).IsCurrent();
        break;
    case 3:
        players.at(3).IsCurrent();
        break;
    case 4:
        players.at(4).IsCurrent();
        break;
    case 5:
        players.at(5).IsCurrent();
        break;
    }
}
void GameCNTLR::BuildPCount()
{
    int count(ConsoleInUtil::GetIntInput());
    if (!PCountCorrect(count))
    {
        FixPCount();
    }
    else
    {
        SetPCount(count);
        SetOPCount(count);
    }
}
bool GameCNTLR::PCountCorrect(int input)
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
void GameCNTLR::FixPCount()
{
    ConsoleInUtil::ClearInput();
    BuildPCount();
}
void GameCNTLR::BuildPContainer()
{
    vector<PlyrCNTLR> plyrs;
    switch (player_count)
    {
    case 2:
    {
        PlyrCNTLR p1Util("PLAYER[1]", 1);
        PlyrCNTLR p2Util("PLAYER[2]", 2);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        SetPlyrs(plyrs);
        break;
    }
    case 3:
    {
        PlyrCNTLR p1Util("PLAYER[1]", 1);
        PlyrCNTLR p2Util("PLAYER[2]", 2);
        PlyrCNTLR p3Util("PLAYER[3]", 3);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        plyrs.push_back(p3Util);
        SetPlyrs(plyrs);
        break;
    }
    case 4:
    {
        PlyrCNTLR p1Util("PLAYER[1]", 1);
        PlyrCNTLR p2Util("PLAYER[2]", 2);
        PlyrCNTLR p3Util("PLAYER[3]", 3);
        PlyrCNTLR p4Util("PLAYER[4]", 4);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        plyrs.push_back(p3Util);
        plyrs.push_back(p4Util);
        SetPlyrs(plyrs);
        break;
    }
    case 5:
    {
        PlyrCNTLR p1Util("PLAYER[1]", 1);
        PlyrCNTLR p2Util("PLAYER[2]", 2);
        PlyrCNTLR p3Util("PLAYER[3]", 3);
        PlyrCNTLR p4Util("PLAYER[4]", 4);
        PlyrCNTLR p5Util("PLAYER[5]", 5);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        plyrs.push_back(p3Util);
        plyrs.push_back(p4Util);
        plyrs.push_back(p5Util);
        SetPlyrs(plyrs);
        break;
    }
    case 6:
    {
        PlyrCNTLR p1Util("PLAYER[1]", 1);
        PlyrCNTLR p2Util("PLAYER[2]", 2);
        PlyrCNTLR p3Util("PLAYER[3]", 3);
        PlyrCNTLR p4Util("PLAYER[4]", 4);
        PlyrCNTLR p5Util("PLAYER[5]", 5);
        PlyrCNTLR p6Util("PLAYER[6]", 6);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        plyrs.push_back(p3Util);
        plyrs.push_back(p4Util);
        plyrs.push_back(p5Util);
        plyrs.push_back(p6Util);
        SetPlyrs(plyrs);
        break;
    }
    default:
    {
        PlyrCNTLR p0Util("PLAYER[0]", 0);
        plyrs.push_back(p0Util);
        SetPlyrs(plyrs);
        break;
    }
    }
}
void GameCNTLR::BuildWinningTokenCount()
{
    switch (player_count)
    {
    case 2:
        SetWinningTokenCount(6);
        break;
    case 3:
        SetWinningTokenCount(5);
        break;
    case 4:
        SetWinningTokenCount(4);
        break;
    case 5:
        SetWinningTokenCount(3);
        break;
    case 6:
        SetWinningTokenCount(3);
        break;
    }
}
void GameCNTLR::BuildStartingPlyr()
{
    int target(GenerateNumberWithinRange(player_count));
    vector<int> duplicate_guess{};
    int player(0);
    for (PlyrCNTLR iPUtil : players)
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
    SetStrtngPlyr(player);
}
int GameCNTLR::GenerateNumberWithinRange(int range)
{
    srand(time(NULL));
    int output(rand() % range + 1);
    return output;
}
int GameCNTLR::GetPlayerGuess()
{
    int output(ConsoleInUtil::GetIntInput());
    if (!CorrectGuessInput(output))
    {
        FixGuessInput(output);
    }
    return output;
}
bool GameCNTLR::CorrectGuessInput(int output)
{
    if (output >= 1 && output <= player_count)
    {
        return true;
    }
    else
    {
        ConsoleOutUtil::PrintInvalidInput(2);
        return false;
    }
}
void GameCNTLR::FixGuessInput(int input)
{
    ConsoleInUtil::ClearInput();
    input = GetPlayerGuess();
}
bool GameCNTLR::DuplicateGuess(vector<int> guess_container, int guess)
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
void GameCNTLR::DealStartingHand(DeckUtl &deck)
{
    for (PlyrCNTLR &iPUtl : players)
    {
        iPUtl.InsertCardIntoHand(deck.Card(0));
    }
}
/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "game.h"
#include "console_in.h"
#include "console_out.h"

using std::any_of;
using std::distance;
using std::find;

const int GameInterface::PCount() { return player_count; }
const int GameInterface::Round() { return round_count; }
const int GameInterface::OPCount() { return original_player_count; }
const int GameInterface::WinningTokenCount() { return winning_token_count; }
vector<PlayerController> GameInterface::Players() { return players; }
PlayerController GameInterface::PCurrent()
{
    for (PlayerController iPUtil : players)
    {
        if (iPUtil.Current())
        {
            return iPUtil;
        }
    }
}
int GameInterface::FindWinner()
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
void GameInterface::SetPCount(int input) { player_count = input; }
void GameInterface::SetOPCount(int input) { original_player_count = input; }
void GameInterface::SetPlyrs(vector<PlayerController> input) { players = input; }
void GameInterface::SetWinningTokenCount(int input) { winning_token_count = input; }
void GameInterface::SetStrtngPlyr(int output)
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
void GameController::BuildPCount()
{
    int count(ConsoleIn::GetIntInput());
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
bool GameController::PCountCorrect(int input)
{
    if (input >= 2 && input <= 6)
    {
        return true;
    }
    else
    {
        ConsoleOut::PrintInvalidInput(1);
        return false;
    }
}
void GameController::FixPCount()
{
    ConsoleIn::ClearInput();
    BuildPCount();
}
void GameController::BuildPContainer()
{
    vector<PlayerController> plyrs;
    switch (player_count)
    {
    case 2:
    {
        PlayerController p1Util("PLAYER[1]", 1);
        PlayerController p2Util("PLAYER[2]", 2);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        SetPlyrs(plyrs);
        break;
    }
    case 3:
    {
        PlayerController p1Util("PLAYER[1]", 1);
        PlayerController p2Util("PLAYER[2]", 2);
        PlayerController p3Util("PLAYER[3]", 3);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        plyrs.push_back(p3Util);
        SetPlyrs(plyrs);
        break;
    }
    case 4:
    {
        PlayerController p1Util("PLAYER[1]", 1);
        PlayerController p2Util("PLAYER[2]", 2);
        PlayerController p3Util("PLAYER[3]", 3);
        PlayerController p4Util("PLAYER[4]", 4);
        plyrs.push_back(p1Util);
        plyrs.push_back(p2Util);
        plyrs.push_back(p3Util);
        plyrs.push_back(p4Util);
        SetPlyrs(plyrs);
        break;
    }
    case 5:
    {
        PlayerController p1Util("PLAYER[1]", 1);
        PlayerController p2Util("PLAYER[2]", 2);
        PlayerController p3Util("PLAYER[3]", 3);
        PlayerController p4Util("PLAYER[4]", 4);
        PlayerController p5Util("PLAYER[5]", 5);
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
        PlayerController p1Util("PLAYER[1]", 1);
        PlayerController p2Util("PLAYER[2]", 2);
        PlayerController p3Util("PLAYER[3]", 3);
        PlayerController p4Util("PLAYER[4]", 4);
        PlayerController p5Util("PLAYER[5]", 5);
        PlayerController p6Util("PLAYER[6]", 6);
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
        PlayerController p0Util("PLAYER[0]", 0);
        plyrs.push_back(p0Util);
        SetPlyrs(plyrs);
        break;
    }
    }
}
void GameController::BuildWinningTokenCount()
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
void GameController::BuildStartingPlyr()
{
    int target(GenerateNumberWithinRange(player_count));
    vector<int> duplicate_guess{};
    int player(0);
    for (PlayerController iPUtil : players)
    {
        ConsoleOut::PrintNameGuess(iPUtil.Name());
        int guess(GetPlayerGuess());
        while (DuplicateGuess(duplicate_guess, guess))
        {
            guess = GetPlayerGuess();
        }
        if (guess == target)
        {
            ConsoleOut::PrintCorrectGuessPrompt(iPUtil.Name());
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
int GameController::GenerateNumberWithinRange(int range)
{
    srand(time(NULL));
    int output(rand() % range + 1);
    return output;
}
int GameController::GetPlayerGuess()
{
    int output(ConsoleIn::GetIntInput());
    if (!CorrectGuessInput(output))
    {
        FixGuessInput(output);
    }
    return output;
}
bool GameController::CorrectGuessInput(int output)
{
    if (output >= 1 && output <= player_count)
    {
        return true;
    }
    else
    {
        ConsoleOut::PrintInvalidInput(2);
        return false;
    }
}
void GameController::FixGuessInput(int input)
{
    ConsoleIn::ClearInput();
    input = GetPlayerGuess();
}
bool GameController::DuplicateGuess(vector<int> guess_container, int guess)
{
    for (int iInt : guess_container)
    {
        if (iInt == guess)
        {
            ConsoleOut::PrintInvalidInput(3);
            return true;
        }
    }
    return false;
}
void GameController::DealStartingHand(DeckController &deck)
{
    for (PlayerController &iPUtl : players)
    {
        iPUtl.InsertCardIntoHand(deck.Card(0));
    }
}
void GameController::ClearWinner()
{
    for (PlayerController iPCNTLR : players)
    {
        iPCNTLR.NotWinner();
    }
}
void GameController::ClearPlaying()
{
    for (PlayerController iPCNTLR : players)
    {
        iPCNTLR.IsPlaying();
    }
}
void GameController::ProcessDraw(DeckController &deck)
{
    char input = DrawInput();
    if (!CorrectDrawInput(input))
    {
        input = FixDrawInput();
    }
    else
    {
        for (PlayerController &iPUtil : players)
        {
            if (iPUtil.Current())
            {
                iPUtil.InsertCardIntoHand(deck.Card(0));
            }
        }
    }
}
char GameController::DrawInput() { return ConsoleIn::GatCharInput(); }
bool GameController::CorrectDrawInput(char input)
{
    if (input == 'd')
    {
        return true;
    }
    else
    {
        ConsoleOut::PrintInvalidInput(5);
        return false;
    }
}
char GameController::FixDrawInput()
{
    ConsoleIn::ClearInput();
    char output;
    bool correct = false;
    while (!correct)
    {
        output = DrawInput();
        if (!CorrectDrawInput(output))
        {
            ConsoleIn::ClearInput();
        }
        else
        {
            correct = true;
        }
    }
    return output;
}
int GameController::ProcessCardChoice()
{
    int choice = ConsoleIn::GetIntInput();
    if (!CorrectChoiceInput(choice))
    {
        choice = FixChoiceInput();
    }
    else
    {
        for (auto iCUtil : PCurrent().Hand())
        {
            bool in_hand = false;
            while (!in_hand)
            {
                if (iCUtil.Value() == choice)
                {
                    in_hand = true;
                }
                else
                {
                    ConsoleOut::PrintInvalidInput(8);
                    choice = FixChoiceInput();
                }
            }
        }
    }
    return choice;
}
bool GameController::CorrectChoiceInput(int input)
{
    if (input < 0 && input > 9)
    {
        ConsoleOut::PrintInvalidInput(7);
        return false;
    }
    else
    {
        return true;
    }
}
int GameController::FixChoiceInput()
{
    int output = 0;
    bool correct = false;
    while (!correct)
    {
        ConsoleIn::ClearInput();
        output = ConsoleIn::GetIntInput();
        if (output >= 0 || output <= 9)
        {
            correct = true;
        }
        else
        {
            ConsoleOut::PrintInvalidInput(8);
        }
    }
    return output;
}
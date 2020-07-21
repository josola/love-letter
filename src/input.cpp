#include "card_support.h"
#include "game_state.h"
#include "player.h"

#include <cassert>
#include <iostream>

using std::cin;
using std::cout;

const bool CheckCard(const int card)
{
    if (card < 0 || card > 9 || cin.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void FixCard(int card)
{
    assert(card < 0 || card > 9);

    while (card < 0 || card > 9 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Card must be between 0 and 9.\n";
        cin >> card;
    }
}

void SanitizeCard(int target, const int originator)
{
    assert(originator >= 0 && originator <= 9);

    switch (originator)
    {
        case 1:
        {
            while (!CheckCard(target) || target == 1)
            {
                cout << "You cannot choose a Guard.\n";
                FixCard(target);
            }
        }
        default:
        {
            while (!CheckCard(target))
            {
                FixCard(target);
            }
        }
    }
}

const bool CheckTarget(const int input, const GameState &state)
{
    if (input < 1 || input > state.players_.size() || cin.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void FixTarget(int input, const GameState &state)
{
    assert(input < 1 || input > 6);

    while (input < 1 || input > state.players_.size())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
        }
        cout << "Number must be between 1 and " << state.players_.size() << '\n';
        cin >> input;
    }
}

void SanitizeTarget(int target, const GameState &state, const int card, Player &aggressor)
{
    assert(card >= 0 && card <= 9);

    if (card == 1 || card == 3)
    {
        while (!CheckTarget(target, state) || target == aggressor.GetValue())
        {
            cout << "You cannot choose yourself.\n";
            FixTarget(target, state);
        }
    }
    else
    {
        while (!CheckTarget(target, state))
        {
            FixTarget(target, state);
        }
    }
}

Player *GetTarget(Player &aggressor, GameState &state, const int card)
{
    assert(card >= 0 && card <= 9);

    Player *target_player = nullptr;

    bool protected_target = true;
    while (protected_target)
    {
        cout << aggressor.GetName() << " choose a target player: ";

        int target = 0;
        cin >> target;
        SanitizeTarget(target, state, card, aggressor);

        target_player = aggressor.GetConversion()->NumPlayer(target, state);

        if (target_player->ProtectionStatus())
        {
            cout << target_player->ProtectionStatus() << " has Handmaid protection.\n";
        }
        else
        {
            protected_target = false;
        }
    }
    return target_player;
}

const bool CheckCharacter(const char input, const char target)
{
    if (input == target)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void FixCharacter(char input, const char target)
{
    while (input != target)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Input must be '" << target << "'\n";
        cin >> input;
    }
}

void SanitizeCharacter(char input, const char target)
{
    while (!CheckCharacter(input, target))
    {
        FixCharacter(input, target);
    }
}
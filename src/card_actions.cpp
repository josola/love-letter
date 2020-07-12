#include "card_actions.h"
#include "game_state.h"
#include "player.h"
#include "deck.h"

#include <iostream>
#include <algorithm>

using std::any_of;
using std::cin;
using std::cout;
using std::sort;

// supporting functions
const bool CheckCard(const int card)
{
    if (card < 0 || card > 9 || cin.fail())
        return false;
    else
        return true;
}
void FixCard(int card)
{
    while (card < 0 || card > 9)
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
            FixCard(target);
    }
    }
}
const bool CheckTarget(const int input, const GameState &state)
{
    if (input < 1 || input > state.players_.size() || cin.fail())
        return false;
    else
        return true;
}
void FixTarget(int input, const GameState &state)
{
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
    switch (card)
    {
    case 1:
    {
        while (!CheckTarget(target, state) || target == aggressor.GetValue())
        {
            cout << "You cannot choose yourself.\n";
            FixTarget(target, state);
        }
    }
    default:
    {
        while (!CheckTarget(target, state))
            FixTarget(target, state);
    }
    }
}
Player *GetTarget(Player &aggressor, GameState &state, const int card)
{
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
            cout << target_player->ProtectionStatus() << " has Handmaid protection.\n";
        else
            protected_target = false;
    }
    return target_player;
}
const bool CheckCharacter(const char input, const char target)
{
    if (input == target)
        return true;
    else
        return false;
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
        FixCharacter(input, target);
}

// actions
void Spy(Player &player) { player.GainSpy(); }
void Guard(GameState &state, Player &aggressor, Deck &deck)
{
    Player *target = GetTarget(aggressor, state, 1);
    int card = 0;
    cout << aggressor.GetName() << " guess a card: ";
    cin >> card;
    SanitizeCard(card, 1);
    for (const Card &iCard : *target->GetHand())
    {
        if (iCard.GetValue() == card)
        {
            cout << "Match!\n";
            target->Out(deck);
            return;
        }
    }
    cout << "No match!\n";
}
void Priest(GameState &state, Player &aggressor)
{
    Player *target = GetTarget(aggressor, state, 2);
    cout << target->GetName() << "'s hand is:\n";
    target->PrintHand();
    cout << '\n';
}
void Baron(GameState &state, Player &aggressor, Deck &deck)
{
    Player *target = GetTarget(aggressor, state, 3);
    vector<Player *> players;
    players.push_back(&aggressor);
    players.push_back(target);
    sort(players.begin(), players.end());
    cout << players.at(0)->GetName() << " had the higher card!\n";
    players.at(1)->Out(deck);
}
void Handmaid(Player &player) { player.SetProtection(1); }
void Prince(GameState &state, Player &player, Deck &deck)
{
    Player *target = GetTarget(player, state, 5);
    if (target->GetValue() == player.GetValue())
    {
        cout << "You chose yourself!\n";
        cout << "Please discard your hand (d): ";
        char discard = ' ';
        cin >> discard;
        SanitizeCharacter(discard, 'd');
        vector<Card>* hand = player.GetHand();
        if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            Princess(player, deck);
        }
        else
            player.DiscardHand(deck);
    }
    else
    {
        cout << target->GetName() << " discards their hand!\n";
        vector<Card>* hand = target->GetHand();
        if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            Princess(*target, deck);
        }
        else
            target->DiscardHand(deck);
    }
}
void Chancellor(Deck &deck, Player &player) // infinite loop when drawing two cards?
{
    cout << player.GetName() << " draw two cards (d): ";
    char draw = ' ';
    cin >> draw;
    SanitizeCharacter(draw, 'd');
    for (int i = 0; i < 2; i++)
        player.Draw(deck.GetCard(0));
    player.PrintHand();
    cout << "First card to put back: ";
    int first = 0;
    cin >> first;
    SanitizeCard(first, 6);
    if (first == 9)
    {
        Princess(player, deck);
    }
    else
        player.Discard(first, deck);
    cout << "Second card to put back: ";
    int second = 0;
    cin >> second;
    SanitizeCard(second, 6);
    if (second == 9)
    {
        Princess(player, deck);
    }
    else
        player.Discard(second, deck);
}
void King(GameState &state, Player &aggressor)
{
    Player *target = GetTarget(aggressor, state, 7);
    cout << target->GetName() << " trade hands with ";
    cout << aggressor.GetName() << '\n';
    vector<Card>* instigator_hand = aggressor.GetHand();
    vector<Card>* target_hand = target->GetHand();
    swap(instigator_hand, target_hand);
    aggressor.PrintHand();
}
void Countess(Player &player) { cout << player.GetName() << " has played the Countess!\n"; }
void Princess(Player &player, Deck &deck)
{
    cout << player.GetName() << " had the Princess!\n";
    player.Out(deck);
}
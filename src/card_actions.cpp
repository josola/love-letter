#include "card_actions.h"
#include "card_support.h"
#include "game_state.h"
#include "player.h"
#include "deck.h"

#include <iostream>
#include <algorithm>
#include <cassert>

using std::any_of;
using std::cin;
using std::cout;
using std::sort;

// actions
void Spy(Player &player)
{
    assert(!player.SpyStatus());
    player.GainSpy();
}

void Guard(GameState &state, Player &aggressor, Deck &deck)
{
    Player *target = GetTarget(aggressor, state, 1);

    cout << aggressor.GetName() << " guess a card: ";

    int card = 0;
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

void Baron(GameState &state, Player &aggressor, Deck &deck) // round does not end during 2 player games
{
    Player *target = GetTarget(aggressor, state, 3);

    vector<Player *> players;
    players.push_back(&aggressor);
    players.push_back(target);

    sort(players.begin(), players.end());

    cout << players.at(0)->GetName() << " had the higher card!\n";

    players.at(1)->Out(deck);
}

void Handmaid(Player &player)
{
    assert(!player.ProtectionStatus());
    player.SetProtection(1);
}

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

        vector<Card> *hand = player.GetHand();

        if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            Princess(player, deck);
        }
        else
        {
            player.DiscardHand(deck);
        }
    }
    else
    {
        cout << target->GetName() << " discards their hand!\n";

        vector<Card> *hand = target->GetHand();

        if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            Princess(*target, deck);
        }
        else
        {
            target->DiscardHand(deck);
        }
    }
}

void Chancellor(Deck &deck, Player &player) // infinite loop when drawing two cards?
{
    cout << player.GetName() << " draw two cards (d): ";

    char draw = ' ';
    cin >> draw;
    SanitizeCharacter(draw, 'd');

    for (int i = 0; i < 2; i++)
    {
        player.Draw(deck.GetCard(0));
    }

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
    {
        player.Discard(first, deck);
    }

    cout << "Second card to put back: ";

    int second = 0;
    cin >> second;
    SanitizeCard(second, 6);

    if (second == 9)
    {
        Princess(player, deck);
    }
    else
    {
        player.Discard(second, deck);
    }
}

void King(GameState &state, Player &aggressor)
{
    Player *target = GetTarget(aggressor, state, 7);

    cout << target->GetName() << " trade hands with " << aggressor.GetName() << '\n';

    vector<Card> *instigator_hand = aggressor.GetHand();
    vector<Card> *target_hand = target->GetHand();

    swap(instigator_hand, target_hand);

    aggressor.PrintHand();
}

void Countess(Player &player)
{
    cout << player.GetName() << " has played the Countess!\n";
}

void Princess(Player &player, Deck &deck)
{
    cout << player.GetName() << " had the Princess!\n";
    player.Out(deck);
}
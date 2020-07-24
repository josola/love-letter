#include "card_actions.h"
#include "input.h"
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

void Guard(GameState &state, Player &aggressor, vector<Card> &deck)
{
    if (OpponentsProtected(aggressor, state))
    {
        cout << "All players have Handmaid protection!\n";
        return;
    }
    
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
    if (OpponentsProtected(aggressor, state))
    {
        cout << "All players have Handmaid protection!\n";
        return;
    }
    
    Player *target = GetTarget(aggressor, state, 2);

    target->PrintHand();
    cout << '\n';
}

void Baron(GameState &state, Player &aggressor, vector<Card> &deck) // round does not end during 2 player games
{
    if (OpponentsProtected(aggressor, state))
    {
        cout << "All players have Handmaid protection!\n";
        return;
    }
    
    Player *target = GetTarget(aggressor, state, 3);
    
    vector<Card>* target_hand = target->GetHand();
    vector<Card>* aggressor_hand = aggressor.GetHand();

    if (aggressor_hand->at(0).GetValue() > target_hand->at(0).GetValue())
    {
        cout << aggressor.GetName() << " had the higher card!\n";
        target->Out(deck);
    }
    else if (aggressor_hand->at(0).GetValue() == target_hand->at(0).GetValue())
    {
        cout << "Players hand the same card!\n";
    }
    else
    {
        cout << target->GetName() << " had the higher card!\n";
        aggressor.Out(deck);
    }
}

void Handmaid(Player &player)
{
    assert(!player.ProtectionStatus());
    player.SetProtection(1);
}

void Prince(GameState &state, Player &aggressor, vector<Card> &deck)
{
    if (OpponentsProtected(aggressor, state))
    {
        cout << "All players have Handmaid protection!\n";
        cout << "Prince applies to you!\n";
        
        vector<Card> *hand = aggressor.GetHand();
        
        if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            Princess(aggressor, deck);
        }
        else
        {
            aggressor.DiscardHand(deck);
        }
        return;
    }
    
    Player *target = GetTarget(aggressor, state, 5);

    if (target->GetValue() == aggressor.GetValue())
    {
        cout << "You chose yourself!\n";
        cout << "Please discard your hand (d): ";

        char discard = ' ';
        cin >> discard;
        SanitizeCharacter(discard, 'd');

        vector<Card> *hand = aggressor.GetHand();

        if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            Princess(aggressor, deck);
        }
        else
        {
            aggressor.DiscardHand(deck);
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

void Chancellor(vector<Card> &deck, Player &player) // infinite loop when drawing two cards?
{
    cout << player.GetName() << " draw two cards (d): ";

    char draw = ' ';
    cin >> draw;
    SanitizeCharacter(draw, 'd');

    for (int i = 0; i < 2; i++)
    {
        player.Draw(deck.at(0));
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
    if (OpponentsProtected(aggressor, state))
    {
        cout << "All players have Handmaid protection!\n";
        return;
    }
    
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

void Princess(Player &player, vector<Card> &deck)
{
    cout << player.GetName() << " had the Princess!\n";
    player.Out(deck);
}

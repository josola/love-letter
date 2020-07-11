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
const bool CheckTarget(const int input, GameState &state)
{
    if (input < 1 || input > state.players_.size() || cin.fail())
        return false;
    else
        return true;
}
void FixTarget(int input, GameState &state)
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
Player *ChooseTarget(Player &aggressor, GameState &state, const int card)
{
    Player *target_player = nullptr;
    bool protected_target = true;
    while (protected_target)
    {
        cout << aggressor.GetName() << " choose a target player: ";
        int target = 0;
        cin >> target;
        while (!CheckTarget(target, state) || target == aggressor.GetValue())
        {
            if (card != 5 && target == aggressor.GetValue())
                cout << "You cannot choose yourself\n";
            FixTarget(target, state);
        }
        target_player = aggressor.GetConversion()->NumPlayer(target, state);
        if (target_player->ProtectionStatus())
            cout << target_player->ProtectionStatus() << " has Handmaid protection.\n";
        else
            protected_target = false;
    }
    return target_player;
}

// actions
void Action::Spy(Player &player) { player.GainSpy(); }
void Action::Guard(GameState &state, Player &aggressor, Deck &deck)
{
    Player *target = ChooseTarget(aggressor, state, 1);
    int card = 0;
    cout << aggressor.GetName() << " guess a card: ";
    cin >> card;
    while (!CheckCard(card) || card == 1)
    {
        if (card == 1)
            cout << "You cannot choose a guard.\n";
        FixCard(card);
    }
    for (const Card &iCard : target->GetHand())
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
void Action::Priest(GameState &state, Player &aggressor)
{
    Player *target = ChooseTarget(aggressor, state, 2);
    cout << target->GetName() << "'s hand is:\n";
    target->PrintHand();
    cout << '\n';
}
void Action::Baron(GameState &state, Player &aggressor, Deck &deck)
{
    Player *target = ChooseTarget(aggressor, state, 3);
    vector<Player *> players;
    players.push_back(&aggressor);
    players.push_back(target);
    sort(players.begin(), players.end(), [](const Player iPlayer) { return iPlayer.GetHand().at(0).GetValue(); });
    cout << players.at(0)->GetName() << " had the higher card!\n";
    players.at(1)->Out(deck);
}
void Action::Handmaid(Player &player) { player.SetProtection(1); }
void Action::Prince(GameState &state, Player &player, Deck &deck)
{
    Player *target = ChooseTarget(player, state, 5);
    if (target->GetValue() == player.GetValue())
    {
        cout << "You chose yourself!\n";
        cout << "Please discard your hand (d): ";
        char discard = ' ';
        cin >> discard;
        while (discard != 'd')
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "Please enter 'd'.\n";
            cin >> discard;
        }
        vector<Card> hand = player.GetHand();
        if (any_of(hand.begin(), hand.end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            cout << "You discarded the Princess!\n";
            player.Out(deck);
        }
        else
            player.DiscardHand(deck);
    }
    else
    {
        cout << target->GetName() << " discards their hand!\n";
        vector<Card> hand = target->GetHand();
        if (any_of(hand.begin(), hand.end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
        {
            cout << target->GetName() << " discarded the Princess!\n";
            target->Out(deck);
        }
        else
            target->DiscardHand(deck);
    }
}
void Action::Chancellor(Deck *deck) // infinite loop when drawing two cards?
{
    bool draw_input = false;
    while (!draw_input)
    {
        cout << this->GetName() << " draw two cards (d): ";
        char input = ' ';
        cin >> input;
        if (input == 'd')
        {
            for (int i = 0; i < 2; i++)
            {
                this->Draw(deck->GetCard(0));
            }
        }
    }
    this->PrintHand();
    bool first_card_input = false;
    while (!first_card_input)
    {
        cout << "First card to put back: ";
        short unsigned int choice = 0;
        cin >> choice;
        if (choice >= 0 && choice <= 9 && cin)
        {
            if (choice == 9)
            {
                cout << this->GetName() << " discarded the Princess!\n";
                cout << this->GetName() << " is out!\n";
                this->Playing(0);
                this->Discard(choice);
                break;
            }
            else
            {
                this->Discard(choice);
                first_card_input = true;
            }
        }
        else
        {
            cout << "Invalid input.\n";
        }
    }
    bool second_card_input = false;
    while (!second_card_input)
    {
        cout << "Second card to put back: ";
        short unsigned int choice = 0;
        cin >> choice;
        if (choice >= 0 && choice <= 9 && cin)
        {
            if (choice == 9)
            {
                cout << this->GetName() << " discarded the Princess!\n";
                cout << this->GetName() << " is out!\n";
                this->Playing(0);
                this->Discard(choice);
                break;
            }
            else
            {
                this->Discard(choice);
                second_card_input = true;
            }
        }
        else
        {
            cout << "Invalid input.\n";
        }
    }
}
void Action::King(GameState &state, InputCheck &check)
{
    bool target_input = false;
    short unsigned int target = 0;
    while (!target_input)
    {
        cout << "Choose target player: ";
        cin >> target;
        if (check.CheckTargetPlayer(target))
        {
            target_input = true;
        }
        else
        {
            cout << "Invalid input.\n";
        }
    }
    Player *target_player = convert.NumPlayer(target, state);
    cout << target_player->GetName() << " trade hands with ";
    cout << this->GetName() << '\n';
    this->hand_.swap(target_player->hand_);
    this->PrintHand();
}
void Action::Countess()
{
    cout << this->GetName() << " has played the Countess!\n";
}
void Action::Princess() // Segmentation fault when player discards Princess?
{
    cout << this->GetName() << " has played the Princess!\n";
    cout << this->GetName() << " is out!\n";
    this->DiscardHand();
    this->Reset();
    this->Playing(0);
}
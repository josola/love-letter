/*
 * deck.cpp
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "deck.h"
#include "suits.h"
#include <stdexcept>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

using std::cout;
using std::endl;
using std::logic_error;
using std::shuffle;

void Deck::Clear()
{
    (pile_.empty()) ? (throw logic_error("Pile is empty!")) : (pile_.erase(pile_.begin(), pile_.end()));
    (!pile_.empty()) ? (throw logic_error("Erase didn't work!")) : (NULL);
}

const int Deck::Size()
{
    return pile_.size();
}

void Deck::Insert(Card card)
{
    pile_.push_back(card);
}

void Deck::Print()
{
    if (pile_.empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        if (pile_.size() == 1)
        {
            cout << pile_.at(0).GetName() << endl;
        }
        else
        {
            for (size_t i = 0; i < pile_.size(); i++)
            {
                if (i < pile_.size() - 1)
                {
                    cout << pile_.at(i).GetName() << ", ";
                }
                else
                {
                    cout << pile_.at(i).GetName() << endl;
                }
            }
        }
    }
}

void Deck::Set()
{
    vector<string> names = { "SPY", "GUARD", "PRIEST", "BARON", "HANDMAID", "PRINCE", "CHANCELLOR", "KING", "COUNTESS", "PRINCESS" };
    vector<string> descriptions = {
        "At the end of the round, if you are the only player in the round who played or discarded a Spy, gain 1 favor token.",
        "Choose another player and name a non-Guard card. If that player has that card, they are out of the round.",
        "Choose and look at another player's hand.",
        "Choose and secretly compare hands with another player. Whoever has the lower value is out of the round.",
        "Until yout next turn, other players cannot choose you for their card effects.",
        "Choose any player (including yourself). That player discards their hand and redraws.",
        "Draw 2 cards. Keep 1 card and put your other 2 on the bottom of the deck in any order.",
        "Choose and trade hands with another player.",
        "If the King or Prince is in your hand, you must play this card.",
        "If you play or discard this card, you are out of the round."
    };
    vector<Card> cards;
    for (int i = 0; i < 10; i++)
    {
        Card card(names[i], i, descriptions[i]);
        cards.push_back(card);
    }
    for (int i = 0; i < 2; i++)
    {
        pile_.push_back(cards.at(0));
    }
    for (int i = 0; i < 6; i++)
    {
        pile_.push_back(cards.at(1));
    }
    for (int i = 0; i < 2; i++)
    {
        pile_.push_back(cards.at(2));
    }
    for (int i = 0; i < 2; i++)
    {
        pile_.push_back(cards.at(3));
    }
    for (int i = 0; i < 2; i++)
    {
        pile_.push_back(cards.at(4));
    }
    for (int i = 0; i < 2; i++)
    {
        pile_.push_back(cards.at(5));
    }
    for (int i = 0; i < 2; i++)
    {
        pile_.push_back(cards.at(6));
    }
    pile_.push_back(cards.at(7));
    pile_.push_back(cards.at(8));
    pile_.push_back(cards.at(9));
}

void Deck::Shuffle()
{
    shuffle(pile_.begin(), pile_.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}

Card Deck::GetCard(const int position)
{
    Card card = pile_.at(position);
    pile_.erase(pile_.begin() + position);
    return card;
}
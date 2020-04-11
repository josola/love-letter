/*
 * Helper utility for deck.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <algorithm>
#include "deck_util.h"

using std::random_shuffle;
using std::srand;
using std::time;

DeckUtil::DeckUtil(Deck deck) : deck(deck){};

vector<CardUtil> DeckUtil::DeckBuilder()
{
    CardUtil cardUtil(Card("", 10));
    vector<CardUtil> output;
    for (int i = 0; i < 2; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(0));
    }
    for (int i = 0; i < 6; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(1));
    }
    for (int i = 0; i < 2; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(2));
    }
    for (int i = 0; i < 2; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(3));
    }
    for (int i = 0; i < 2; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(4));
    }
    for (int i = 0; i < 2; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(5));
    }
    for (int i = 0; i < 2; i++)
    {
        output.push_back(cardUtil.CardUtilBuilder(6));
    }
    output.push_back(cardUtil.CardUtilBuilder(7));
    output.push_back(cardUtil.CardUtilBuilder(8));
    output.push_back(cardUtil.CardUtilBuilder(9));
    return output;
};

void DeckUtil::SetDeck()
{
    deck.deck = DeckBuilder();
}

vector<CardUtil> DeckUtil::GetDeck()
{
    return deck.deck;
}

void DeckUtil::ShuffleDeck()
{
    srand(time(NULL));
    random_shuffle(deck.deck.begin(), deck.deck.end());
}

CardUtil DeckUtil::GetCardFromDeck(int pos)
{
    CardUtil top_card = deck.deck.at(pos);
    return top_card;
}

void DeckUtil::RemoveCardFromDeck(int pos)
{
    deck.deck.erase(deck.deck.begin() + pos);
}
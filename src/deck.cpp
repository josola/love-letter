#include "deck.h"
#include "card.h"
#include <cassert>
#include <chrono>
#include <random>

using std::shuffle;

void Build(vector<Card> &input)
{
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("SPY", 0, "REF"));
    }
    for (int i = 0; i < 6; i++)
    {
        input.push_back(Card("GUARD", 1, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("PRIEST", 2, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("BARON", 3, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("HANDMAID", 4, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("PRINCE", 5, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("CHANCELLOR", 6, "REF"));
    }
    input.push_back(Card("KING", 7, "REF"));
    input.push_back(Card("COUNTESS", 8, "REF"));
    input.push_back(Card("PRINCESS", 9, "REF"));
}

void Shuffle(vector<Card> &input)
{
    assert(!input.empty());
    shuffle(input.begin(), input.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}

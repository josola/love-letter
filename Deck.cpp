#include "Deck.h"

Deck::Deck() {};
Deck::~Deck() {};

std::vector<int> Deck::GetDeck() const { return numDeck; }
int Deck::AcquireCard(int pos)
{
    int card = 0;
    card += numDeck[pos];
    return card;
}
bool Deck::RemoveCard(int cardPosition) { return true; }
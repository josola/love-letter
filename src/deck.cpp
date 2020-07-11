#include "deck.h"
#include "card.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

using std::cout;
using std::endl;
using std::shuffle;

// getters
const int Deck::Size() const { return pile_.size(); }
const bool Deck::Empty() const { return pile_.empty(); }
Card Deck::GetCard(const int position)
{
  Card card = pile_.at(position);
  pile_.erase(pile_.begin() + position);
  return card;
}

// setters
void Deck::Clear() { pile_.erase(pile_.begin(), pile_.end()); }
void Deck::Set()
{
  for (int i = 0; i < 2; i++)
  {
    pile_.push_back(Card("SPY", 0, "REF"));
  }
  for (int i = 0; i < 6; i++)
  {
    pile_.push_back(Card("GUARD", 1, "REF"));
  }
  for (int i = 0; i < 2; i++)
  {
    pile_.push_back(Card("PRIEST", 2, "REF"));
  }
  for (int i = 0; i < 2; i++)
  {
    pile_.push_back(Card("BARON", 3, "REF"));
  }
  for (int i = 0; i < 2; i++)
  {
    pile_.push_back(Card("HANDMAID", 4, "REF"));
  }
  for (int i = 0; i < 2; i++)
  {
    pile_.push_back(Card("PRINCE", 5, "REF"));
  }
  for (int i = 0; i < 2; i++)
  {
    pile_.push_back(Card("CHANCELLOR", 6, "REF"));
  }
  pile_.push_back(Card("KING", 7, "REF"));
  pile_.push_back(Card("COUNTESS", 8, "REF"));
  pile_.push_back(Card("PRINCESS", 9, "REF"));
}

// actions
void Deck::Shuffle() { shuffle(pile_.begin(), pile_.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())); }
void Deck::Insert(Card card) { pile_.push_back(card); }
void Deck::Print() const
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
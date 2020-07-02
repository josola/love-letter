//===-- deck.h - Deck class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

using std::vector;

class Deck {
public:
  void Clear();
  const int Size();
  void Insert(Card card);
  void Print();
  void Set();
  void Shuffle();
  Card GetCard(const int position);

protected:
  vector<Card> pile_;
};

#endif

//===-- discard.h - Discard class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

#ifndef DISCARD_H
#define DISCARD_H

#include "deck.h"

class Discard : public Deck {
public:
  vector<Card> GetDeck();

protected:
};

#endif

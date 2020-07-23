//===-- deck_support.h - Deck class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of the main Deck. The "Discard" and
/// the "Aside" piles are derived from this class.
///
//===----------------------------------------------------------------------===//

#ifndef DECK_SUPPORT_h
#define DECK_SUPPORT_h

#include <vector>

using std::vector;

class Card;

void Build(vector<Card> &input);
void Shuffle(vector<Card> &input);

#endif

//===-- player.h - Player class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of a Player.
///
//===----------------------------------------------------------------------===//

#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "pile.h"
#include "reference.h"
#include "token.h"

class Player {
public:
  Player(const string name, const int value, const Reference &reference);

  // getters
  const bool ProtectionStatus() const;
  const string GetName() const;
  const vector<Card> GetHand() const;
  const bool Status() const;

  // setters
  void Draw(const Card obj);
  void GainSpy();
  void Reset();
  void SetProtection(const bool state);
  void Discard(const int choice);

  // printer
  void PrintHand() const;

private:
  string name_ = "";
  int value_ = 0;
  Reference reference_;
  vector<Card> hand_;
  vector<Token> tokens_;
  bool handmaid_ = false;
  bool spy_ = false;
  bool playing_ = true;
};

#endif

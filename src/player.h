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

class Player
{
public:
  Player(const string name, const int value, const Reference &reference);

  // getters
  const bool ProtectionStatus() const;
  const string GetName() const;
  const vector<Card> GetHand() const;
  const bool Status() const;
  const int GetValue() const;

  // setters
  void Draw(const Card obj);
  void GainSpy();
  void Reset();
  void SetProtection(const bool state);
  void Discard(const int choice);
  void DiscardHand();
  void Playing(const bool state);

  // printer
  void PrintHand() const;

  // actions
  void Spy();
  void Guard(vector<Player>* players);
  void Priest(vector<Player>* players);
  void Baron(vector<Player>* players);
  void Handmaid();
  void Prince(vector<Player>* players);
  void Chancellor();
  void King(vector<Player>* players);
  void Countess();

private:
  // information
  string name_ = "";
  int value_ = 0;

  // objects
  Reference reference_;
  vector<Card> hand_;
  vector<Token> tokens_;

  // state
  bool handmaid_ = false;
  bool spy_ = false;
  bool playing_ = true;
};

#endif

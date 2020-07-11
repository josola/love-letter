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

#include "converter.h"
#include "reference.h"

class Card;
class Reference;
class Token;
class Deck;
class InputCheck;
class Deck;
string;
vector<Card>;

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
  const int GetTokenCount() const;
  const bool SpyStatus() const;
  Converter* GetConversion();

  // setters
  void Draw(const Card obj);
  void GainSpy();
  void Reset();
  void SetProtection(const bool state);
  void Discard(const int choice, Deck &deck);
  void DiscardHand(Deck &deck);
  void Addtoken();
  void Winner(const bool state);
  void RemoveCard(const int card);
  void Out(Deck &deck);

  // printer
  void PrintHand() const;

private:
  // information
  string name_ = "";
  int value_ = 0;

  // objects
  Reference reference_;
  vector<Card> hand_;
  int token_count_ = 0;

  // state
  bool handmaid_ = false;
  bool spy_ = false;
  bool playing_ = true;
  bool winner_ = false;

  // data
  Converter convert;

};

#endif

//===-- card_actions.h - Card action definitions -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of a card action.
///
//===----------------------------------------------------------------------===//

#ifndef CARD_ACTIONS_h
#define CARD_ACTIONS_h

#include <vector>

using std::vector;

class GameState;
class InputCheck;
class Player;
class Deck;
class Card;

// actions
void Spy(Player &player);
void Guard(GameState &state, Player &aggressor, vector<Card> &deck);
void Priest(GameState &state, Player &aggressor);
void Baron(GameState &state, Player &aggressor, vector<Card> &deck);
void Handmaid(Player &player);
void Prince(GameState &state, Player &player, vector<Card> &deck);
void Chancellor(vector<Card> &deck, Player &player);
void King(GameState &state, Player &aggressor);
void Countess(Player &player);
void Princess(Player &player, vector<Card> &deck);

#endif // !CARD_ACTIONS_h

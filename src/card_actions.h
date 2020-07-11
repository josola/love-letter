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

class GameState;
class InputCheck;
class Player;
class Deck;

struct Action
{
    void Spy(Player &player);
    void Guard(GameState &state, Player &aggressor, Deck &deck);
    void Priest(GameState &state, Player &aggressor);
    void Baron(GameState &state, Player &aggressor, Deck &deck);
    void Handmaid(Player &player);
    void Prince(GameState &state, Player &player, Deck &deck);
    void Chancellor(Deck *deck);
    void King(GameState &state, InputCheck &check);
    void Countess();
    void Princess();
};

#endif // !CARD_ACTIONS_h
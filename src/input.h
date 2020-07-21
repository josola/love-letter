//===- card_support.h - Supporting definitions for card actions -*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file adds supporting functions for input operations.
///
//===----------------------------------------------------------------------===//

class GameState;
class Player;

const bool CheckCard(const int card);
void FixCard(int card);
void SanitizeCard(int target, const int originator);

const bool CheckTarget(const int input, const GameState &state);
void FixTarget(int input, const GameState &state);
void SanitizeTarget(int target, const GameState &state, const int card, Player &aggressor);

Player *GetTarget(Player &aggressor, GameState &state, const int card);

const bool CheckCharacter(const char input, const char target);
void FixCharacter(char input, const char target);
void SanitizeCharacter(char input, const char target);
//===-------- game_state.h - Holds game state data --------------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines POD class for game state.
///
//===----------------------------------------------------------------------===//

#ifndef GAME_STATE_h
#define GAME_STATE_h

#include "player.h"

#include <vector>

using std::vector;

struct GameState
{
	// methods
	void InsertPlayer(Player &player);
	void SetPlayers(int count);

	// data
	vector<Player> players_;
	int winning_token_count_ = 0;
};

#endif // !GAME_STATE_h

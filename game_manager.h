/*
 * Holds information about the game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

struct GameState
{
    
};

class GameStateUtil
{
public:
    GameStateUtil(GameState &game_state);

private:
    GameState &game_state;
};

#endif
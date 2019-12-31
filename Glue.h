#pragma once
#include "Player.h"
#include "Deck.h"
#include "Log.h"
#include "Input.h"
#include <vector>

struct Glue
{
public:
	Glue();
	~Glue();

	std::vector<Player> playerObjects;

	int GetPlayerCount();
};
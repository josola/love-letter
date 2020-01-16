#pragma once
#include "Player.h"
#include "Deck.h"
#include "Log.h"
#include "Input.h"
#include "Check.h"
#include <vector>

struct Glue
{
public:
	Glue();
	~Glue();

	int GetPlayerCount();
};
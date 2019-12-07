/*
Jordan Sola 2019
Variables and objects that are used in Functions.cpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

class Suitor
{
private:
	bool
		hasSpy = false,
		hasHandmaid = false;
	int tokenCount = 0;

public:
	void GainSpy() { hasSpy = true; }
	void RemoveSpy() { hasSpy = false; }
	bool SpyStatus() { return hasSpy; }
	void GainHandmaid() { hasHandmaid = true; }
	void RemoveHandmaid() { hasHandmaid = false; }
	bool HandmaidStatus() { return hasHandmaid; }
	int GetTokenCount() { return tokenCount; }
	void GainToken() { tokenCount++; }
};

Suitor
suitor1,
suitor2,
suitor3,
suitor4,
suitor5,
suitor6;

std::vector<Suitor> suitorObjects
{
	suitor1,
	suitor2,
	suitor3,
	suitor4,
	suitor5,
	suitor6
};

int
activeSuitorCount,
originalSuitorCount,
currentSuitor,
tokenCountToWin,
cardNum,
roundCount = 1,
tempVictor,
i,
iLength;

static const int
spy = 0,
guard = 1,
priest = 2,
baron = 3,
handmaid = 4,
prince = 5,
chancellor = 6,
king = 7,
countess = 8,
princess = 9;

std::vector<int>
tempVector,
suitors,
upPile,
downPile,
tempInput,
suitorsWithHandmaid;

std::vector<std::vector<int> > activeSuitorHands;

auto winner = 0;
unsigned int playerNum = 0;
bool gameOver = false;
char input;

std::vector<std::string> suitorNames
{
	"SUITOR 1",
	"SUITOR 2",
	"SUITOR 3",
	"SUITOR 4",
	"SUITOR 5",
	"SUITOR 6"
};

std::vector<std::string> cardNames
{
	"SPY[0]",
	"GUARD[1]",
	"PRIEST[2]",
	"BARON[3]",
	"HANDMAID[4]",
	"PRINCE[5]",
	"CHANCELLOR[6]",
	"KING[7]",
	"COUNTESS[8]",
	"PRINCESS[9]"
};

std::vector<int> deck
{
	spy,
	spy,
	guard,
	guard,
	guard,
	guard,
	guard,
	guard,
	priest,
	priest,
	baron,
	baron,
	handmaid,
	handmaid,
	prince,
	prince,
	chancellor,
	chancellor,
	king,
	countess,
	princess
};

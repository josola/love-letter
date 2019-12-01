#pragma once

#include <string>
#include <vector>

class Suitor
{
private:
	bool hasSpy = false;
	bool hasHandmaid = false;
	int tokenCount = 0;

public:
	void getSpy()
	{
		hasSpy = true;
	}
	void loseSpy()
	{
		hasSpy = false;
	}
	bool spyStatus()
	{
		return hasSpy;
	}
	void getHandmaid()
	{
		hasHandmaid = true;
	}
	void loseHandmaid()
	{
		hasHandmaid = false;
	}
	bool handmaidStatus()
	{
		return hasHandmaid;
	}
	int getTokenCount()
	{
		return tokenCount;
	}
	void upTokenCount()
	{
		tokenCount++;
	}
};

Suitor suitor1, suitor2, suitor3, suitor4, suitor5, suitor6;
std::vector<Suitor> suitorObjectContainer{ suitor1, suitor2, suitor3, suitor4, suitor5, suitor6 };

int activeSuitors, currentSuitor, cardNum, originalSuitorCount, roundCount = 1, tempVictor, totalTokensWins;
const int spy = 0, guard = 1, priest = 2, baron = 3, handmaid = 4, prince = 5, chancellor = 6, king = 7, countess = 8, princess = 9;
auto winner = 0;
unsigned int playerNum = 0;
bool gameOver = false;
char input;
std::vector<std::string> suitorNames = { "SUITOR 1", "SUITOR 2", "SUITOR 3", "SUITOR 4", "SUITOR 5", "SUITOR 6" };
std::vector<std::string> cardNames = { "SPY[0]", "GUARD[1]", "PRIEST[2]", "BARON[3]", "HANDMAID[4]", "PRINCE[5]", "CHANCELLOR[6]", "KING[7]", "COUNTESS[8]", "PRINCESS[9]" };
std::vector<unsigned int> deck = { 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9 };
std::vector<unsigned int> tempVector;
std::vector<unsigned int> suitors;
std::vector<unsigned int> upPile;
std::vector<unsigned int> downPile;
std::vector<std::vector<int> > suitor;
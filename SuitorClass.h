#pragma once

#include <vector>

class Suitor
{
private:

	bool
		hasSpy = false,
		hasHandmaid = false,
		isPlaying = true;

	int tokenCount = 0;

	std::vector<int> hand;

public:

	void GainSpy() { hasSpy = true; }
	void RemoveSpy() { hasSpy = false; }
	void GainHandmaid() { hasHandmaid = true; }
	void RemoveHandmaid() { hasHandmaid = false; }
	void GainToken() { tokenCount++; }
	//Needs to replace current dealing logic
	int insertWithinHand(int itemNum)
	{
		hand.push_back(itemNum);
	}

	int GetTokenCount() { return tokenCount; }
	
	bool HandmaidStatus() { return hasHandmaid; }
	bool SpyStatus() { return hasSpy; }
	//Integration waiting on dealing logic update
	bool cardInHand(int cardNum) const
	{
		for (int i : hand)
		{
			if (i == cardNum)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
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
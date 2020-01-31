#pragma once

#include "Resources.h"

class Suitor
{
private:

	bool
		hasSpy = false,
		hasHandmaid = false,
		isPlaying = true;

	int tokenCount = 0;

public:

	std::vector<int> hand;

	void GainSpy() { hasSpy = true; }
	void RemoveSpy() { hasSpy = false; }
	void GainHandmaid() { hasHandmaid = true; }
	void RemoveHandmaid() { hasHandmaid = false; }
	void GainToken() { tokenCount++; }
	void PlayerOut() { isPlaying = false;  }
	void PlayerIn() { isPlaying = true; }

	int GetTokenCount() const { return tokenCount; }

	bool HandmaidStatus() const { return hasHandmaid; }
	bool SpyStatus() const { return hasSpy; }
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

std::vector<Suitor> originalSuitors;
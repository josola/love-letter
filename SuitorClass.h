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
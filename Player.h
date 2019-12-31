#pragma once
#include <string>
#include <vector>

class Player
{
private:
	std::string name;
	bool isActive = false;
	bool isOut = false;
	bool hasHandmaid = false;
	bool hasSpy = false;
	int tokenCount = 0;
	std::vector<int> hand;

public:
	Player(std::string name);
	~Player();

	std::string GetName() const;
	bool GetActiveStatus() const;
	void SetActiveStatus(bool status);
	bool GetOutStatus() const;
	void SetOutStatus(bool status);
	bool GetHandmaidStatus() const;
	void SetHandmaidStatus(bool status);
	bool GetSpyStatus() const;
	void SetSpyStatus(bool status);
	int GetTokenCount() const;
	void UpTokenCount();
	std::vector<int> GetHand() const;
};

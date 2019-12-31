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

	std::string GetName() const
	{
		return name;
	}
    bool GetActiveStatus() const
    {
        return isActive;
    }
    void SetActiveStatus(bool status)
    {
        isActive = status;
    }
    bool GetOutStatus() const
    {
        return isOut;
    }
    void SetOutStatus(bool status)
    {
        isOut = status;
    }
    bool GetHandmaidStatus() const
    {
        return hasHandmaid;
    }
    void SetHandmaidStatus(bool status)
    {
        hasHandmaid = status;
    }
    bool GetSpyStatus() const
    {
        return hasSpy;
    }
    void SetSpyStatus(bool status)
    {
        hasSpy = status;
    }
    int GetTokenCount() const
    {
        return tokenCount;
    }
    void UpTokenCount()
    {
        tokenCount++;
    }
    std::vector<int> GetHand() const
    {
        return hand;
    }
};

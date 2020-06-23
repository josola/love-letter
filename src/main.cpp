#include "Functions.h"

int main()
{
	bool game_over = false;
	bool end_round = false;
	InitialSetup();
	while (!game_over)
	{
		BeginRound();
		SuitorTurn();

		/* END OF ROUND */

		//When the deck runs out.
		if (playingDeck.empty())
		{
			std::cout << "The deck is empty, suitors compare hands" << std::endl;
			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
			{
				//Print remaining Suitors.
				if (!activeSuitorHands[i].empty())
				{
					std::cout << suitorNames[i] << " hand: " << activeSuitorHands[i][0] << std::endl;
				}
			}
			//Assign Suitor with highest hand to winner.
			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
			{
				if (!activeSuitorHands[i].empty())
				{
					if (winner < activeSuitorHands[i][0])
					{
						winner = activeSuitorHands[i][0];
					}
				}
			}
			//Assign winner as a Suitor integer.
			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
			{
				if (!activeSuitorHands[i].empty() && activeSuitorHands[i][0] == winner)
				{
					winner = i;
					break;
				}
			}
			//Check for Spy bonus, give Spy bonus token, no Spies, or duplicate Spies.
			if (activeSuitorCount > 1)
			{
				for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
				{
					if (suitorObjects[i].SpyStatus())
					{
						tempVector.push_back(i);
					}
				}
				if (tempVector.size() > 1)
				{
					std::cout << "Multiple suitors had the Spy. No one gets a bonus." << std::endl;
				}
				if (tempVector.size() == 1)
				{
					std::cout << suitorNames.at(tempVector[0]) << " Has the Spy, they gain an extra favor token <3" << std::endl;
					suitorObjects.at(tempVector[0]).GainToken();
					std::cout << suitorNames.at(tempVector[0]) << " token count: " << suitorObjects.at(tempVector[0]).GetTokenCount() << std::endl;
				}
				if (tempVector.empty())
				{
					std::cout << "No one had the Spy this round." << std::endl;
				}
			}
		}
		//When there is one Suitor remaining.
		else
		{
			//Assign winner as a Suitor integer.
			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
			{
				if (!activeSuitorHands[i].empty())
				{
					winner = i;
				}
			}
			std::cout << "Round over. " << suitorNames[winner] << " is the last suitor standing." << std::endl;
			//Check for Spy bonus and give bonus token.
			if (suitorObjects[winner].SpyStatus())
			{
				std::cout << suitorNames[winner] << " has the Spy, they gain an extra favor token <3" << std::endl;
				suitorObjects[winner].GainToken();
				suitorObjects[winner].RemoveSpy();
				std::cout << suitorNames[winner] << " token count: " << suitorObjects[winner].GetTokenCount() << std::endl;
			}
		}
		//Give winner a favor token.
		suitorObjects[winner].GainToken();
		std::cout << suitorNames[winner] << " gains one[1] favor token <3" << std::endl;
		std::cout << suitorNames[winner] << " total tokens: " << suitorObjects[winner].GetTokenCount() << std::endl;
		//Prepare for next round.
		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
		{
			suitorObjects[i].RemoveHandmaid();
		}
		if (suitorObjects[winner].GetTokenCount() < tokenCountToWin)
		{
			++roundCount;
			activeSuitorHands.clear();
			suitors.clear();
			downPile.clear();
			upPile.clear();
			activeSuitorCount = 0;
			std::cout << "Moving on to the next round..." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(3));
			ClearScreen();
		}
		if (suitorObjects[winner].GetTokenCount() == tokenCountToWin)
		{
			std::cout << suitorNames[winner] << " has won the heart of the princess." << std::endl;
			std::cout << "-- GAME OVER --" << std::endl;
			activeSuitorHands.clear();
			suitors.clear();
			downPile.clear();
			upPile.clear();
			activeSuitorCount = 0;
			gameOver = true;
		}
	}
	return 0;
}

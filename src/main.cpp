#include <iostream>
#include <thread>
#include <vector>
#include "functions.h"
#include "player.h"
#include "reference.h"
#include "deck.h"
#include "discard.h"
#include "aside.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	short unsigned int suitor_count = 0;
	short unsigned int winning_token_count = 0;
	vector<Player> players;
	Reference reference;
	short unsigned int current_suitor = 0;
	short unsigned int round_count = 1;

	//Tasks that are performed at the start of every GAME.
	cout << "-- WELCOME TO LOVE LETTER --" << endl;

	bool correct_suitor_count = false;
	while (!correct_suitor_count)
	{
		cout << "How many suitors will be playing: " << endl;

		cin >> suitor_count;

		cout << "--" << endl;

		if (suitor_count >= 2 && suitor_count <= 6 && cin)
		{
			correct_suitor_count = true;
			switch (suitor_count)
			{
			case 2:
				players.push_back(Player("PLAYER[1]", 1, reference));
				players.push_back(Player("PLAYER[2]", 2, reference));
				winning_token_count = 6;
				break;
			case 3:
				players.push_back(Player("PLAYER[1]", 1, reference));
				players.push_back(Player("PLAYER[2]", 2, reference));
				players.push_back(Player("PLAYER[3]", 3, reference));
				winning_token_count = 5;
				break;
			case 4:
				players.push_back(Player("PLAYER[1]", 1, reference));
				players.push_back(Player("PLAYER[2]", 2, reference));
				players.push_back(Player("PLAYER[3]", 3, reference));
				players.push_back(Player("PLAYER[4]", 4, reference));
				winning_token_count = 4;
				break;
			case 5:
				players.push_back(Player("PLAYER[1]", 1, reference));
				players.push_back(Player("PLAYER[2]", 2, reference));
				players.push_back(Player("PLAYER[3]", 3, reference));
				players.push_back(Player("PLAYER[4]", 4, reference));
				players.push_back(Player("PLAYER[5]", 5, reference));
				winning_token_count = 3;
				break;
			case 6:
				players.push_back(Player("PLAYER[1]", 1, reference));
				players.push_back(Player("PLAYER[2]", 2, reference));
				players.push_back(Player("PLAYER[3]", 3, reference));
				players.push_back(Player("PLAYER[4]", 4, reference));
				players.push_back(Player("PLAYER[5]", 5, reference));
				players.push_back(Player("PLAYER[6]", 6, reference));
				winning_token_count = 3;
				break;
			default:
				break;
			}
		}
		else
		{
			cout << "Invalid input, please input a number of Suitors between 2 and 6." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	bool game_over = false;
	while (!game_over)
	{
		Deck deck;
		deck.Set();
		deck.Shuffle();

		Discard discard;
		Aside aside;

		cout << "-- ROUND " << round_count << " --" << endl;

		if (round_count > 1)
		{
			//Round is second round or above.
			for (Player& i : players)
			{
				i.Reset();
			}
		}

		aside.Insert(deck.GetCard(0));

		if (players.size() == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				discard.Insert(deck.GetCard(0));
			}
		}
		
		game_over = true;
	}

	/*PlayGame();*/

	return 0;
}
// 	//new structure
// 	bool game_over = false;
// 	while (!game_over)
// 	{
// 		Deck deck;
// 		deck.Set();
// 		deck.Shuffle();
// 		std::cout << "-- ROUND " << roundCount << " --" << std::endl;
// 		//Check for starting round.
// 		if (roundCount != startingRound)
// 		{
// 			//Round is second round or above.
// 			activeSuitorCount = originalSuitorCount;
// 			for (i = 1; i < activeSuitorCount + 1; ++i)
// 			{
// 				suitors.push_back(i);
// 			}
// 			for (i = 1; i < activeSuitorCount + 1; ++i)
// 			{
// 				std::vector<int> hand;
// 				activeSuitorHands.push_back(hand);
// 			}
// 			std::cout << suitorNames.at(winner) << " won the last round. " << suitorNames.at(winner) << " goes first." << std::endl;
// 			currentSuitor = winner;
// 			winner = 0;
// 		}
// 		//Check for two Suitor game.
// 		if (activeSuitorCount == minSuitorsPlaying)
// 		{
// 			downPile.push_back(playingDeck[0]);
// 			playingDeck.erase(playingDeck.begin());
// 			for (i = 0; i < 3; ++i)
// 			{
// 				upPile.push_back(playingDeck[i]);
// 				playingDeck.erase(playingDeck.begin());
// 			}
// 		}
// 		//Discard top card of deck to face down pile, no matter the activeSuitorCount.
// 		else
// 		{
// 			downPile.push_back(playingDeck[0]);
// 			playingDeck.erase(playingDeck.begin());
// 		}
// 		//Deal starting hand.
// 		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 		{
// 			activeSuitorHands.at(i).push_back(playingDeck[0]);
// 			playingDeck.erase(playingDeck.begin());
// 		}

// 		SuitorTurn();

// 		//end round
// 		if (playingDeck.empty())
// 		{
// 			cout << "The deck is empty, suitors compare hands" << endl;
// 			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 			{
// 				if (!activeSuitorHands[i].empty())
// 				{
// 					cout << suitorNames[i] << " hand: " << activeSuitorHands[i][0] << endl;
// 				}
// 			}
// 			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 			{
// 				if (!activeSuitorHands[i].empty())
// 				{
// 					if (winner < activeSuitorHands[i][0])
// 					{
// 						winner = activeSuitorHands[i][0];
// 					}
// 				}
// 			}
// 			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 			{
// 				if (!activeSuitorHands[i].empty() && activeSuitorHands[i][0] == winner)
// 				{
// 					winner = i;
// 					break;
// 				}
// 			}
// 			if (activeSuitorCount > 1)
// 			{
// 				for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 				{
// 					if (suitorObjects[i].SpyStatus())
// 					{
// 						tempVector.push_back(i);
// 					}
// 				}
// 				if (tempVector.size() > 1)
// 				{
// 					cout << "Multiple suitors had the Spy. No one gets a bonus." << endl;
// 				}
// 				if (tempVector.size() == 1)
// 				{
// 					cout << suitorNames.at(tempVector[0]) << " Has the Spy, they gain an extra favor token <3" << endl;
// 					suitorObjects.at(tempVector[0]).GainToken();
// 					cout << suitorNames.at(tempVector[0]) << " token count: " << suitorObjects.at(tempVector[0]).GetTokenCount() << endl;
// 				}
// 				if (tempVector.empty())
// 				{
// 					cout << "No one had the Spy this round." << endl;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 			{
// 				if (!activeSuitorHands[i].empty())
// 				{
// 					winner = i;
// 				}
// 			}
// 			cout << "Round over. " << suitorNames[winner] << " is the last suitor standing." << endl;
// 			if (suitorObjects[winner].SpyStatus())
// 			{
// 				cout << suitorNames[winner] << " has the Spy, they gain an extra favor token <3" << endl;
// 				suitorObjects[winner].GainToken();
// 				suitorObjects[winner].RemoveSpy();
// 				cout << suitorNames[winner] << " token count: " << suitorObjects[winner].GetTokenCount() << endl;
// 			}
// 		}
// 		suitorObjects[winner].GainToken();
// 		cout << suitorNames[winner] << " gains one[1] favor token <3" << endl;
// 		cout << suitorNames[winner] << " total tokens: " << suitorObjects[winner].GetTokenCount() << endl;
// 		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
// 		{
// 			suitorObjects[i].RemoveHandmaid();
// 		}
// 		if (suitorObjects[winner].GetTokenCount() < tokenCountToWin)
// 		{
// 			++roundCount;
// 			activeSuitorHands.clear();
// 			suitors.clear();
// 			downPile.clear();
// 			upPile.clear();
// 			activeSuitorCount = 0;
// 			cout << "Moving on to the next round..." << endl;
// 			std::this_thread::sleep_for(std::chrono::seconds(3));
// 			ClearScreen();
// 		}
// 		if (suitorObjects[winner].GetTokenCount() == tokenCountToWin)
// 		{
// 			cout << suitorNames[winner] << " has won the heart of the princess." << endl;
// 			cout << "-- GAME OVER --" << endl;
// 			activeSuitorHands.clear();
// 			suitors.clear();
// 			downPile.clear();
// 			upPile.clear();
// 			activeSuitorCount = 0;
// 			game_over = true;
// 		}
// 	}
// }

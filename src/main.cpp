#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include "functions.h"
#include "player.h"
#include "reference.h"
#include "deck.h"
#include "discard.h"
#include "aside.h"

using std::cin;
using std::cout;
using std::endl;
using std::to_string;
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

		//set players
		if (suitor_count >= 2 && suitor_count <= 6 && cin)
		{
			correct_suitor_count = true;
			switch (suitor_count)
			{
			case 2:
				for (short unsigned int i = 0; i < 2; i++)
				{
					string name = "PLAYER[" + to_string(i + 1) + "]";
					players.push_back(Player(name, i + 1, reference));
				}
				winning_token_count = 6;
				break;
			case 3:
				for (short unsigned int i = 0; i < 3; i++)
				{
					string name = "PLAYER[" + to_string(i + 1) + "]";
					players.push_back(Player(name, i + 1, reference));
				}
				winning_token_count = 5;
				break;
			case 4:
				for (short unsigned int i = 0; i < 4; i++)
				{
					string name = "PLAYER[" + to_string(i + 1) + "]";
					players.push_back(Player(name, i + 1, reference));
				}
				winning_token_count = 4;
				break;
			case 5:
				for (short unsigned int i = 0; i < 5; i++)
				{
					string name = "PLAYER[" + to_string(i + 1) + "]";
					players.push_back(Player(name, i + 1, reference));
				}
				winning_token_count = 3;
				break;
			case 6:
				for (short unsigned int i = 0; i < 6; i++)
				{
					string name = "PLAYER[" + to_string(i + 1) + "]";
					players.push_back(Player(name, i + 1, reference));
				}
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

		//second round and above: reset player stats
		if (round_count > 1)
		{
			for (Player &i : players)
			{
				i.Reset();
			}
		}

		//discard to down pile
		aside.Insert(deck.GetCard(0));

		//two player game: discard two cards
		if (players.size() == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				discard.Insert(deck.GetCard(0));
			}
		}

		//deal starting hand
		for (Player &i : players)
		{
			i.Draw(deck.GetCard(0));
		}

		if (deck.Size() == 0)
		{
			game_over = true;
			break;
		}

		for (Player &i : players)
		{
			if (i.Status())
			{
				i.ResetProtection();
				bool draw_input = false;
				while (!draw_input)
				{
					cout << i.GetName() << " draw a card (d): " << endl;
					char draw = ' ';
					cin >> draw;
					if (draw == 'd')
					{
						break;
					}
					else
					{
						cout << "Invalid input." << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}
				i.Draw(deck.GetCard(0));
				i.PrintHand();
			}
			else
			{
				break;
			}
		}

		game_over = true;
	}

	//PlayGame();

	return 0;
}
// 	//new structure
// LOOP:
// 	//More than one Suitor must be playing and the deck must not be empty.
// 	while (!playingDeck.empty())
// 	{
// 		//Remove Handmaid protection from previous turn.
// 		if (suitorObjects[currentSuitor].HandmaidStatus())
// 		{
// 			suitorObjects[currentSuitor].RemoveHandmaid();
// 			auto itD = find(suitorsWithHandmaid.begin(), suitorsWithHandmaid.end(), currentSuitor);
// 			suitorsWithHandmaid.erase(itD);
// 		}
// 		//Check for empty deck so these functions don't duplicate.
// 		if (!playingDeck.empty())
// 		{
// 			PrintDeckSize();
// 			PrintActiveSuitors();
// 			PrintUpPile();
// 			PrintSuitorsWithSpy();
// 			printHand(currentSuitor);
// 		}
// 		else
// 		{
// 			return;
// 		}
// 		//Current Suitor draws a card to their hand.
// 		std::cout << suitorNames.at(currentSuitor) << " draw a card (d): " << std::endl;
// 		std::cin >> input;
// 		PrintSeperator();
// 		if (input == 'd')
// 		{
// 			activeSuitorHands.at(currentSuitor).push_back(playingDeck[0]);
// 			playingDeck.erase(playingDeck.begin());
// 		}
// 		else
// 		{
// 			std::cout << "Invalid input, please input 'd' to draw a card." << std::endl;
// 			ClearInput();
// 			goto LOOP;
// 		}
// 	LOOPA:
// 		printHand(currentSuitor);
// 		//Current Suitor plays a card from their hand.
// 		returnSuitor(currentSuitor);
// 		std::cout << " play a card: " << std::endl;
// 		std::cin >> cardNum;
// 		PrintSeperator();
// 		if (!ProperCardInput())
// 		{
// 			ClearInput();
// 			goto LOOPA;
// 		}
// 		if (!CardInHand(currentSuitor, cardNum))
// 		{
// 			std::cout << "You do not have " << cardNames[cardNum] << " in your hand." << std::endl;
// 			goto LOOPA;
// 		}
// 		if (CountessRestriction())
// 		{
// 			ClearInput();
// 			goto LOOPA;
// 		}
// 		else
// 		{
// 			DiscardPlayedCard();
// 		}
// 		//Card resolves.
// 		if (cardNum == guard || cardNum == priest || cardNum == baron || cardNum == king)
// 		{
// 			ChooseTargetSuitor(targetNum);
// 			if (TargetHandmaidProtected() && activeSuitorCount == 2)
// 			{
// 				returnSuitor(targetNum);
// 				std::cout << " has Handmaid protection." << std::endl;
// 				PrintSeperator();
// 				SwitchSuitor();
// 				goto LOOP;
// 			}
// 			if (suitorsWithHandmaid.size() == activeSuitorCount - 1)
// 			{
// 				returnSuitor(targetNum);
// 				std::cout << " has Handmaid protection." << std::endl;
// 				std::cout << "All target Suitors have Handmaid protection." << std::endl;
// 				PrintSeperator();
// 				SwitchSuitor();
// 				goto LOOP;
// 			}
// 			else
// 			{
// 				PlayCard();
// 			}
// 		}
// 		else
// 		{
// 			PlayCard();
// 		}
// 		//Current Suitor's turn is done. Move to next active Suitor.
// 		if (activeSuitorCount > 1)
// 		{
// 			SwitchSuitor();
// 		}
// 		tempInput.clear();
// 	}
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

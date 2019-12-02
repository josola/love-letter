/*
Jordan Sola 2019
Functions used in Main.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

#include "Resources.h"

using namespace std;

//Game functions.
bool TargetHandmaidProtected()
{
	if (suitorObjectContainer[playerNum].handmaidStatus())
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PrintFaceUpPile()
{
	cout << "Cards in face up pile: " << endl;
	for (unsigned int i = 0; i < upPile.size(); i++)
	{
		cout << cardNames.at(upPile[i]) << " ";
	}
	cout << "\n--\n";
}
void PrintDeckSize()
{
	cout << "Number of cards in the deck: " << deck.size() << endl;
	cout << "--\n";
}
void PrintSuitorsWithSpy()
{
	cout << "Suitors with Spy bonus: " << endl;
	for (unsigned int i = 0; i < suitor.size(); i++)
	{
		if (suitorObjectContainer[i].spyStatus())
		{
			cout << suitorNames[i] << " ";
		}
	}
	cout << "\n--\n";
}
void ClearInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
auto CurrentSuitor()
{
	return suitorNames[currentSuitor];
}
auto TargetSuitor()
{
	return suitorNames[playerNum];
}
bool ProperCardInput()
{
	if (cardNum >= spy && cardNum <= princess && cin)
	{
		return true;
	}
	else
	{
		cout << "Invalid input, please input a card value between 0 and 9." << endl;
		return false;
	}
}
bool CardInHand()
{
	if (find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum) != suitor[currentSuitor].end())
	{
		return true;
	}
	else
	{
		cout << "You don't have " << cardNames[cardNum] << " in your hand." << endl;
		return false;
	}
}
bool CountessRestriction()
{
	if (suitor[currentSuitor][0] == 8 || suitor[currentSuitor][1] == 8 && cardNum != 8)
	{
		if (suitor[currentSuitor][0] == 5 || suitor[currentSuitor][0] == 7 || suitor[currentSuitor][1] == 5 || suitor[currentSuitor][1] == 7)
		{
			cout << "You have the " << cardNames.at(suitor[currentSuitor][0]) << " and the " << cardNames.at(suitor[currentSuitor][1]) << ". You MUST play the " << cardNames[8] << " this turn." << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool IsSuitorPlaying()
{
	if (!suitor[playerNum].empty())
	{
		return true;
	}
	else
	{
		cout << TargetSuitor() << " is out." << endl;
		return false;
	}
}
bool ProperSuitorInput()
{
	if (playerNum >= 0 && playerNum <= suitor.size() && cin)
	{
		return true;
	}
	else
	{
		cout << "Invalid input, please choose an active player by their number eg. SUITOR 1 would be 1." << endl;
		return false;
	}
}
void SwitchSuitor()
{
	if (currentSuitor == suitors[0] - 1)
	{
		for (unsigned int i = 1; i < suitor.size(); i++)
		{
			currentSuitor++;
		}
		if (!suitor[currentSuitor].empty())
		{
			return;
		}
	}
	if (suitor[currentSuitor].empty())
	{
	LOOP:
		while (suitor[currentSuitor].empty())
		{
			if (currentSuitor == suitors[0] - 1)
			{
				for (unsigned int i = 1; i < suitor.size(); i++)
				{
					currentSuitor++;
				}
			}
			if (suitor[currentSuitor].empty())
			{
				currentSuitor--;
			}
		}
		return;
	}
	else
	{
		currentSuitor--;
		if (suitor[currentSuitor].empty())
		{
			goto LOOP;
		}
	}
}
void DiscardPlayedCard()
{
	auto it = find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum);
	cout << CurrentSuitor() << " played " << cardNames[cardNum] << "\n--\n";
	upPile.push_back(cardNum);
	if (it != suitor[currentSuitor].end())
	{
		suitor[currentSuitor].erase(it);
	}
}
void PrintActiveSuitors()
{
	cout << "Rival Suitors: " << endl;
	currentSuitor++;
	for (unsigned int i = 0; i < suitor.size(); i++)
	{
		if (!suitor[i].empty() && suitors[i] != currentSuitor)
		{
			cout << suitorNames[i] << " ";
		}
	}
	currentSuitor--;
	cout << "\n--\n";
}
void PrintCurrentSuitorHand()
{
	cout << CurrentSuitor() << " hand: " << endl;
	for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
	{
		cout << cardNames.at(suitor[currentSuitor][i]) << " ";
	}
	cout << endl;
}
void PrintTargetSuitorHand()
{
	cout << TargetSuitor() << " hand: " << endl;
	for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
	{
		cout << cardNames.at(suitor[playerNum][i]) << endl;
	}
}
void ChooseTargetSuitor()
{
LOOP:
	PrintActiveSuitors();
	cout << CurrentSuitor() << " choose target suitor: " << endl;
	cin >> playerNum;
	cout << "--\n";
	playerNum--;
	if (!ProperSuitorInput() || !IsSuitorPlaying())
	{
		ClearInput();
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		if (activeSuitors == 2)
		{
			return;
		}
		else
		{
			cout << TargetSuitor() << " has Handmaid protection." << endl;
			ClearInput();
			goto LOOP;
		}
	}
	if (playerNum == currentSuitor)
	{
		if (cardNum == prince)
		{
			return;
		}
		else
		{
			cout << "You cannot choose yourself." << endl;
			ClearInput();
			goto LOOP;
		}
	}
}
void RemoveSuitor(bool effectedSuitor)
{
	if (effectedSuitor)
	{
		for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
		{
			upPile.push_back(suitor[currentSuitor][i]);
		}
		suitor[currentSuitor].clear();
		if (suitorObjectContainer[currentSuitor].spyStatus())
		{
			suitorObjectContainer[currentSuitor].loseSpy();
		}
		activeSuitors--;
	}
	if (!effectedSuitor)
	{
		for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
		{
			upPile.push_back(suitor[playerNum][i]);
		}
		suitor[playerNum].clear();
		if (suitorObjectContainer[playerNum].spyStatus())
		{
			suitorObjectContainer[playerNum].loseSpy();
		}
		activeSuitors--;
	}
}
void InitialSetup()
{
	if (roundCount == 1)
	{
		cout << "-- WELCOME TO LOVE LETTER --" << endl;
	LOOP:
		cout << "How many suitors will be playing: " << endl;
		cin >> activeSuitors;
		cout << "--\n";
		if (activeSuitors < 2 || activeSuitors > 6 || !cin)
		{
			cout << "Invalid input, please input a number of Suitors between 2 and 6." << endl;
			ClearInput();
			goto LOOP;
		}
		switch (activeSuitors)
		{
		case 2:
			totalTokensWins = 6;
			break;
		case 3:
			totalTokensWins = 5;
			break;
		case 4:
			totalTokensWins = 4;
			break;
		case 5:
			totalTokensWins = 3;
			break;
		case 6:
			totalTokensWins = 3;
			break;
		}
		originalSuitorCount = activeSuitors;
		for (int i = 1; i < activeSuitors + 1; i++)
		{
			suitors.push_back(i);
		}
		for (int i = 1; i < activeSuitors + 1; i++)
		{
			vector<int> hand;
			suitor.push_back(hand);
		}
		srand((int)time(NULL));
		int target = rand() % suitor.size() + 1;
		unsigned int guess = 0;
		cout << "I have a suitor number (1 - " << suitor.size() << ") in my head. Guess it!" << endl;
	LOOPA:
		for (unsigned int i = 0; i < suitor.size() + 1; i++)
		{
		LOOPB:
			cout << suitorNames.at(i) << " guess: " << endl;
			cin >> guess;
			if (guess <= suitor.size() && guess >= 1)
			{
				for (unsigned int i = 0; i < tempVector.size(); i++)
				{
					if (guess == tempVector.at(i))
					{
						cout << guess << " has already been guessed. Try again." << endl;
						ClearInput();
						goto LOOPB;
					}
				}
				if (guess == target)
				{
					cout << suitorNames.at(i) << " got it!\n--" << endl;
					currentSuitor = i;
					break;
				}
				tempVector.push_back(guess);
			}
			else
			{
				cout << "Invalid input, please input a guess between 1 and " << activeSuitors << '.' << endl;
				ClearInput();
				goto LOOPA;
			}
		}
		tempVector.clear();
	}
	else
	{
		deck = { 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9 };
		cout << "-- ROUND " << roundCount << " --" << endl;
		activeSuitors = originalSuitorCount;
		for (int i = 1; i < activeSuitors + 1; i++)
		{
			suitors.push_back(i);
		}
		for (int i = 1; i < activeSuitors + 1; i++)
		{
			vector<int> hand;
			suitor.push_back(hand);
		}
		cout << suitorNames.at(winner) << " won the last round. " << suitorNames.at(winner) << " goes first." << endl;
		currentSuitor = winner;
		winner = 0;
	}
	random_shuffle(deck.begin(), deck.end());
	if (activeSuitors == 2)
	{
		downPile.push_back(deck[0]);
		deck.erase(deck.begin());
		for (unsigned int i = 0; i < 3; i++)
		{
			upPile.push_back(deck[i]);
			deck.erase(deck.begin());
		}
		PrintFaceUpPile();
	}
	if (activeSuitors > 2)
	{
		downPile.push_back(deck[0]);
		deck.erase(deck.begin());
	}
	for (unsigned int i = 0; i < suitor.size(); i++)
	{
		suitor.at(i).push_back(deck[0]);
		deck.erase(deck.begin());
	}
}
void ClearScreen()
{
	cout << "\033[2J\033[1;1H";
}
void EndRound()
{
	if (deck.empty())
	{
		cout << "The deck is empty, suitors compare hands" << endl;
		for (unsigned int i = 0; i < suitor.size(); i++)
		{
			if (!suitor[i].empty())
			{
				cout << suitorNames[i] << " hand: " << suitor[i][0] << endl;
			}
		}
		for (unsigned int i = 0; i < suitor.size(); i++)
		{
			if (!suitor[i].empty())
			{
				if (winner < suitor[i][0])
				{
					winner = suitor[i][0];
				}
			}
		}
		for (unsigned int i = 0; i < suitor.size(); i++)
		{
			if (!suitor[i].empty() && suitor[i][0] == winner)
			{
				winner = i;
				break;
			}
		}
		if (activeSuitors > 1)
		{
			for (unsigned int i = 0; i < suitor.size(); i++)
			{
				if (suitorObjectContainer[i].spyStatus())
				{
					tempVector.push_back(i);
				}
			}
			if (tempVector.size() > 1)
			{
				cout << "Multiple suitors had the Spy. No one gets a bonus." << endl;
			}
			if (tempVector.size() == 1)
			{
				cout << suitorNames.at(tempVector[0]) << " Has the Spy, they gain an extra favor token <3" << endl;
				suitorObjectContainer.at(tempVector[0]).upTokenCount();
				cout << suitorNames.at(tempVector[0]) << " token count: " << suitorObjectContainer.at(tempVector[0]).getTokenCount() << endl;
			}
			if (tempVector.empty())
			{
				cout << "No one had the Spy this round." << endl;
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < suitors.size(); i++)
		{
			if (!suitor[i].empty())
			{
				winner = --suitors[i];
			}
		}
		cout << "Round over. " << suitorNames[winner] << " is the last suitor standing." << endl;
		if (suitorObjectContainer[winner].spyStatus())
		{
			cout << suitorNames[winner] << " has the Spy, they gain an extra favor token <3" << endl;
			suitorObjectContainer[winner].upTokenCount();
			suitorObjectContainer[winner].loseSpy();
			cout << suitorNames[winner] << " token count: " << suitorObjectContainer[winner].getTokenCount() << endl;
		}
	}
	suitorObjectContainer[winner].upTokenCount();
	cout << suitorNames[winner] << " gains one[1] favor token <3" << endl;
	cout << suitorNames[winner] << " total tokens: " << suitorObjectContainer[winner].getTokenCount() << endl;
	for (unsigned int i = 0; i < suitor.size(); i++)
	{
		suitorObjectContainer[i].loseHandmaid();
	}
	if (suitorObjectContainer[winner].getTokenCount() < totalTokensWins)
	{
		++roundCount;
		suitor.clear();
		suitors.clear();
		downPile.clear();
		upPile.clear();
		activeSuitors = 0;
		cout << "Moving on to the next round..." << endl;
		this_thread::sleep_for(chrono::seconds(3));
		ClearScreen();
	}
	if (suitorObjectContainer[winner].getTokenCount() == totalTokensWins)
	{
		cout << suitorNames[winner] << " has won the heart of the princess." << endl;
		cout << "-- GAME OVER --" << endl;
		suitor.clear();
		suitors.clear();
		downPile.clear();
		upPile.clear();
		activeSuitors = 0;
		gameOver = true;
	}
}

//Card functions.
void Spy()
{
	suitorObjectContainer[currentSuitor].getSpy();
}
void Guard()
{
LOOP:
	cout << CurrentSuitor() << " guess a card: " << endl;
	cin >> cardNum;
	if (!ProperCardInput())
	{
		ClearInput();
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		if (activeSuitors == 2)
		{
			return;
		}
		else
		{
			goto LOOP;
		}
	}
	if (cardNum == guard)
	{
		cout << "You can guess any card OTHER than a Guard." << endl;
		ClearInput();
		goto LOOP;
	}
	if (suitor[playerNum][0] == cardNum)
	{
		cout << "Match! " << suitorNames[playerNum] << " is out." << endl;
		RemoveSuitor(0);
	}
	else
	{
		cout << "no match" << endl;
	}
}
void Priest()
{
	PrintTargetSuitorHand();
}
void Baron()
{
	PrintCurrentSuitorHand();
	PrintTargetSuitorHand();
	if (suitor[currentSuitor][0] == suitor[playerNum][0])
	{
		cout << "Tie! Both suitors remain in the game." << endl;
		return;
	}
	else
	{
		tempVictor = max(suitor[currentSuitor][0], suitor[playerNum][0]);
		if (suitor[currentSuitor][0] == tempVictor)
		{
			cout << CurrentSuitor() << " is victorious! " << TargetSuitor() << " is out!" << endl;
			RemoveSuitor(0);
		}
		else {
			cout << TargetSuitor() << " is victorious! " << CurrentSuitor() << " is out!" << endl;
			RemoveSuitor(1);
		}
	}
}
void Handmaid()
{
	suitorObjectContainer[currentSuitor].getHandmaid();
}
void Prince()
{
LOOPB:
	ChooseTargetSuitor();
	if (TargetHandmaidProtected())
	{
		if (activeSuitors == 2)
		{
			cout << "The Prince applies only to you." << endl;
			if (find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), 9) != suitor[currentSuitor].end())
			{
				cout << "You had the Princess! You're out!" << endl;
				RemoveSuitor(1);
				return;
			}
			for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
			{
				upPile.push_back(i);
			}
			suitor[currentSuitor].clear();
			suitor[currentSuitor].push_back(deck[0]);
			deck.erase(deck.begin());
			return;
		}
		cout << suitorNames[playerNum] << " is untargetable." << endl;
		goto LOOPB;
	}
	if (find(suitor[playerNum].begin(), suitor[playerNum].end(), 9) != suitor[playerNum].end())
	{
		cout << suitorNames[playerNum] << " had the Princess! " << suitorNames[playerNum] << " is out!" << endl;
		RemoveSuitor(0);
		return;
	}
	if (deck.empty())
	{
		for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
		{
			upPile.push_back(i);
		}
		suitor[playerNum].push_back(downPile[0]);
		downPile.erase(downPile.begin(), downPile.end());
	}
	else
	{
		for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
		{
			upPile.push_back(i);
		}
		suitor[playerNum].erase(suitor[playerNum].begin(), suitor[playerNum].end());
		suitor[playerNum].push_back(deck[0]);
		deck.erase(deck.begin());
	}
}
void Chancellor()
{
	if (deck.empty())
	{
		cout << "The deck is empty. The " << cardNames[6] << " plays with no effect." << endl;
		return;
	}
	if (deck.size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			suitor[currentSuitor].push_back(deck[0]);
			deck.erase(deck.begin());
		}
		PrintCurrentSuitorHand();
	LOOP:
		cout << "First card to put back: " << endl;
		cin >> cardNum;
		auto itA = find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOP;
		}
		if (!CardInHand())
		{
			ClearInput();
			goto LOOP;
		}
		else
		{
			deck.push_back(cardNum);
			if (itA != suitor[currentSuitor].end())
			{
				suitor[currentSuitor].erase(itA);
			}
			if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[cardNum] << " you are out!" << endl;
				RemoveSuitor(1);
				return;
			}
			else
			{
				PrintCurrentSuitorHand();
			}
		}
	LOOPA:
		cout << "Second card to put back: " << endl;
		cin >> cardNum;
		auto itB = find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPA;
		}
		if (!CardInHand())
		{
			ClearInput();
			goto LOOPA;
		}
		else
		{
			deck.push_back(cardNum);
			if (itB != suitor[currentSuitor].end())
			{
				suitor[currentSuitor].erase(itB);
			}
			if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[cardNum] << " you are out!" << endl;
				RemoveSuitor(1);
				return;
			}
			else
			{
				PrintCurrentSuitorHand();
			}
		}
	}
	if (deck.size() == 1)
	{
		cout << "There is only one card in the deck." << endl;
		for (int i = 0; i < 1; i++)
		{
			suitor[currentSuitor].push_back(deck[0]);
			deck.erase(deck.begin());
		}
		PrintCurrentSuitorHand();
	LOOPB:
		cout << "Card to put back: " << endl;
		cin >> cardNum;
		auto itC = find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPB;
		}
		if (!CardInHand())
		{
			ClearInput();
			goto LOOPB;
		}
		else
		{
			deck.push_back(cardNum);
			if (itC != suitor[currentSuitor].end())
			{
				suitor[currentSuitor].erase(itC);
			}
			if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[cardNum] << " you are out!" << endl;
				RemoveSuitor(1);
				return;
			}
			else
			{
				PrintCurrentSuitorHand();
			}
		}
	}
}
void King()
{
	suitor[currentSuitor].swap(suitor[playerNum]);
	cout << CurrentSuitor() << "'s hand is now..." << endl;
	PrintCurrentSuitorHand();
	cout << TargetSuitor() << "'s hand is now..." << endl;
	PrintTargetSuitorHand();
}
void Princess()
{
	cout << suitorNames[currentSuitor] << " is out!" << endl;
	RemoveSuitor(1);
}

//Dependent game functions.
void PlayCard()
{
	switch (cardNum)
	{
	case 0:
		Spy();
		break;
	case 1:
		Guard();
		break;
	case 2:
		Priest();
		break;
	case 3:
		Baron();
		break;
	case 4:
		Handmaid();
		break;
	case 5:
		Prince();
		break;
	case 6:
		Chancellor();
		break;
	case 7:
		King();
		break;
	case 9:
		Princess();
		break;
	}
}
void SuitorTurn()
{
	while (activeSuitors > 1 && !deck.empty())
	{
		if (suitorObjectContainer[currentSuitor].handmaidStatus())
		{
			suitorObjectContainer[currentSuitor].loseHandmaid();
		}
		if (!deck.empty())
		{
			PrintDeckSize();
			PrintActiveSuitors();
			PrintFaceUpPile();
			PrintSuitorsWithSpy();
			PrintCurrentSuitorHand();
		}
		else
		{
			return;
		}
	LOOP:
		cout << suitorNames.at(currentSuitor) << " draw a card (d): " << endl;
		cin >> input;
		cout << "--\n";
		if (input == 'd')
		{
			suitor.at(currentSuitor).push_back(deck[0]);
			deck.erase(deck.begin());
		}
		else
		{
			cout << "Invalid input, please input 'd' to draw a card." << endl;
			ClearInput();
			goto LOOP;
		}
	LOOPA:
		PrintCurrentSuitorHand();
		cout << CurrentSuitor() << " play a card: " << endl;
		cin >> cardNum;
		if (!ProperCardInput() || !CardInHand())
		{
			ClearInput();
			goto LOOPA;
		}
		if (CountessRestriction())
		{
			ClearInput();
			goto LOOPA;
		}
		DiscardPlayedCard();
		if (cardNum == guard || cardNum == priest || cardNum == baron || cardNum == king)
		{
			ChooseTargetSuitor();
			if (TargetHandmaidProtected() && activeSuitors == 2)
			{
				cout << "Moving on to next active Suitor..." << endl;
				this_thread::sleep_for(chrono::seconds(3));
				ClearScreen();
				SwitchSuitor();
				return;
			}
			else
			{
				PlayCard();
			}
		}
		else
		{
			PlayCard();
		}
		if (activeSuitors > 1)
		{
			cout << "Moving on to next active Suitor..." << endl;
			this_thread::sleep_for(chrono::seconds(3));
			ClearScreen();
			SwitchSuitor();
		}
	}
}
void PlayGame()
{
	InitialSetup();
	while (!gameOver)
	{
		if (activeSuitors == 0)
		{
			InitialSetup();
		}
		SuitorTurn();
		EndRound();
	}
}

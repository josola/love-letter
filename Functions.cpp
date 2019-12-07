/*
Jordan Sola 2019
Functions used in Main.cpp
*/

#include "Resources.h"

using namespace std;

//Game functions.
bool TargetHandmaidProtected()
{
	switch (suitorObjects[playerNum].HandmaidStatus())
	{
	case 1: { return true; }
	case 0: { return false; }
	}
}
void PrintFaceUpPile()
{
	cout << "Cards in face up pile: " << endl;
	for (i = 0, iLength = upPile.size(); i < iLength; ++i)
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
	cout << "Spy bonus: " << endl;
	for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
	{
		if (!activeSuitorHands[i].empty())
		{
			if (suitorObjects[i].SpyStatus()) { cout << suitorNames[i] << endl; }
		}
	}
	cout << "--\n";
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
	if (cardNum >= spy && cardNum <= princess && cin) { return true; }
	else
	{
		cout << "Invalid input, please input a card value between 0 and 9." << endl;
		return false;
	}
}
bool CardInHand()
{
	if (find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum) != activeSuitorHands[currentSuitor].end()) { return true; }
	else
	{
		cout << "You don't have " << cardNames[cardNum] << " in your hand." << endl;
		return false;
	}
}
bool CountessRestriction()
{
	if (activeSuitorHands[currentSuitor][0] == 8 || activeSuitorHands[currentSuitor][1] == 8)
	{
		if (cardNum != 8)
		{
			if (activeSuitorHands[currentSuitor][0] == 5 || activeSuitorHands[currentSuitor][0] == 7 || activeSuitorHands[currentSuitor][1] == 5 || activeSuitorHands[currentSuitor][1] == 7)
			{
				cout << "You have the " << cardNames.at(activeSuitorHands[currentSuitor][0]) << " and the " << cardNames.at(activeSuitorHands[currentSuitor][1]) << ". You MUST play the " << cardNames[8] << " this turn." << endl;
				return true;
			}
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
}
bool IsSuitorPlaying()
{
	switch (activeSuitorHands[playerNum].empty())
	{
	case 0: { return true; }
	case 1: { cout << TargetSuitor() << " is out." << endl; return false; }
	}
}
bool ProperSuitorInput()
{
	if (playerNum >= 0 && playerNum <= activeSuitorHands.size() && cin)
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
		for (unsigned int i = 1; i < activeSuitorHands.size(); i++)
		{
			currentSuitor++;
		}
		if (!activeSuitorHands[currentSuitor].empty())
		{
			return;
		}
	}
	if (activeSuitorHands[currentSuitor].empty())
	{
	LOOP:
		while (activeSuitorHands[currentSuitor].empty())
		{
			if (currentSuitor == suitors[0] - 1)
			{
				for (unsigned int i = 1; i < activeSuitorHands.size(); i++)
				{
					currentSuitor++;
				}
			}
			if (activeSuitorHands[currentSuitor].empty())
			{
				currentSuitor--;
			}
		}
		return;
	}
	else
	{
		currentSuitor--;
		if (activeSuitorHands[currentSuitor].empty())
		{
			goto LOOP;
		}
	}
}
void DiscardPlayedCard()
{
	auto it = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
	cout << CurrentSuitor() << " played " << cardNames[cardNum] << "\n--\n";
	upPile.push_back(cardNum);
	if (it != activeSuitorHands[currentSuitor].end())
	{
		activeSuitorHands[currentSuitor].erase(it);
	}
}
void PrintActiveSuitors()
{
	cout << "Rival Suitors: " << endl;
	currentSuitor++;
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		if (!activeSuitorHands[i].empty() && suitors[i] != currentSuitor)
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
	for (unsigned int i = 0; i < activeSuitorHands[currentSuitor].size(); i++)
	{
		cout << cardNames.at(activeSuitorHands[currentSuitor][i]) << " ";
	}
	cout << endl;
}
void PrintTargetSuitorHand()
{
	cout << TargetSuitor() << " hand: " << endl;
	for (unsigned int i = 0; i < activeSuitorHands[playerNum].size(); i++)
	{
		cout << cardNames.at(activeSuitorHands[playerNum][i]) << endl;
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
	if (!tempInput.empty())
	{
		for (unsigned int i = 0; i < tempInput.size(); i++)
		{
			if (tempInput.at(i) == playerNum)
			{
				cout << "You already chose " << suitorNames.at(tempInput[i]) << " please choose a different Suitor." << endl;
				goto LOOP;
			}
		}
	}
	if (!ProperSuitorInput() || !IsSuitorPlaying())
	{
		ClearInput();
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		if (activeSuitorCount == 2)
		{
			return;
		}
		else
		{
			cout << TargetSuitor() << " has Handmaid protection." << endl;
			tempInput.push_back(playerNum);
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
		for (unsigned int i = 0; i < activeSuitorHands[currentSuitor].size(); i++)
		{
			upPile.push_back(activeSuitorHands[currentSuitor][i]);
		}
		activeSuitorHands[currentSuitor].clear();
		if (suitorObjects[currentSuitor].SpyStatus())
		{
			suitorObjects[currentSuitor].RemoveSpy();
		}
		activeSuitorCount--;
	}
	if (!effectedSuitor)
	{
		for (unsigned int i = 0; i < activeSuitorHands[playerNum].size(); i++)
		{
			upPile.push_back(activeSuitorHands[playerNum][i]);
		}
		activeSuitorHands[playerNum].clear();
		if (suitorObjects[playerNum].SpyStatus())
		{
			suitorObjects[playerNum].RemoveSpy();
		}
		activeSuitorCount--;
	}
}
void InitialSetup()
{
	if (roundCount == 1)
	{
		cout << "-- WELCOME TO LOVE LETTER --" << endl;
	LOOP:
		cout << "How many suitors will be playing: " << endl;
		cin >> activeSuitorCount;
		cout << "--\n";
		if (activeSuitorCount < 2 || activeSuitorCount > 6 || !cin)
		{
			cout << "Invalid input, please input a number of Suitors between 2 and 6." << endl;
			ClearInput();
			goto LOOP;
		}
		switch (activeSuitorCount)
		{
		case 2:
			tokenCountToWin = 6;
			break;
		case 3:
			tokenCountToWin = 5;
			break;
		case 4:
			tokenCountToWin = 4;
			break;
		case 5:
			tokenCountToWin = 3;
			break;
		case 6:
			tokenCountToWin = 3;
			break;
		}
		originalSuitorCount = activeSuitorCount;
		for (int i = 1; i < activeSuitorCount + 1; i++)
		{
			suitors.push_back(i);
		}
		for (int i = 1; i < activeSuitorCount + 1; i++)
		{
			vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		srand((int)time(NULL));
		int target = rand() % activeSuitorHands.size() + 1;
		unsigned int guess = 0;
		cout << "I have a suitor number (1 - " << activeSuitorHands.size() << ") in my head. Guess it!" << endl;
	LOOPA:
		for (unsigned int i = 0; i < activeSuitorHands.size() + 1; i++)
		{
		LOOPB:
			cout << suitorNames.at(i) << " guess: " << endl;
			cin >> guess;
			if (guess <= activeSuitorHands.size() && guess >= 1)
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
				cout << "Invalid input, please input a guess between 1 and " << activeSuitorCount << '.' << endl;
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
		activeSuitorCount = originalSuitorCount;
		for (int i = 1; i < activeSuitorCount + 1; i++)
		{
			suitors.push_back(i);
		}
		for (int i = 1; i < activeSuitorCount + 1; i++)
		{
			vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		cout << suitorNames.at(winner) << " won the last round. " << suitorNames.at(winner) << " goes first." << endl;
		currentSuitor = winner;
		winner = 0;
	}
	random_shuffle(deck.begin(), deck.end());
	if (activeSuitorCount == 2)
	{
		downPile.push_back(deck[0]);
		deck.erase(deck.begin());
		for (unsigned int i = 0; i < 3; i++)
		{
			upPile.push_back(deck[i]);
			deck.erase(deck.begin());
		}
	}
	if (activeSuitorCount > 2)
	{
		downPile.push_back(deck[0]);
		deck.erase(deck.begin());
	}
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		activeSuitorHands.at(i).push_back(deck[0]);
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
		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
		{
			if (!activeSuitorHands[i].empty())
			{
				cout << suitorNames[i] << " hand: " << activeSuitorHands[i][0] << endl;
			}
		}
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
		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
		{
			if (!activeSuitorHands[i].empty() && activeSuitorHands[i][0] == winner)
			{
				winner = i;
				break;
			}
		}
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
				cout << "Multiple suitors had the Spy. No one gets a bonus." << endl;
			}
			if (tempVector.size() == 1)
			{
				cout << suitorNames.at(tempVector[0]) << " Has the Spy, they gain an extra favor token <3" << endl;
				suitorObjects.at(tempVector[0]).GainToken();
				cout << suitorNames.at(tempVector[0]) << " token count: " << suitorObjects.at(tempVector[0]).GetTokenCount() << endl;
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
			if (!activeSuitorHands[i].empty())
			{
				winner = --suitors[i];
			}
		}
		cout << "Round over. " << suitorNames[winner] << " is the last suitor standing." << endl;
		if (suitorObjects[winner].SpyStatus())
		{
			cout << suitorNames[winner] << " has the Spy, they gain an extra favor token <3" << endl;
			suitorObjects[winner].GainToken();
			suitorObjects[winner].RemoveSpy();
			cout << suitorNames[winner] << " token count: " << suitorObjects[winner].GetTokenCount() << endl;
		}
	}
	suitorObjects[winner].GainToken();
	cout << suitorNames[winner] << " gains one[1] favor token <3" << endl;
	cout << suitorNames[winner] << " total tokens: " << suitorObjects[winner].GetTokenCount() << endl;
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
		cout << "Moving on to the next round..." << endl;
		this_thread::sleep_for(chrono::seconds(3));
		ClearScreen();
	}
	if (suitorObjects[winner].GetTokenCount() == tokenCountToWin)
	{
		cout << suitorNames[winner] << " has won the heart of the princess." << endl;
		cout << "-- GAME OVER --" << endl;
		activeSuitorHands.clear();
		suitors.clear();
		downPile.clear();
		upPile.clear();
		activeSuitorCount = 0;
		gameOver = true;
	}
}

//Card functions.
void Spy()
{
	suitorObjects[currentSuitor].GainSpy();
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
		if (activeSuitorCount == 2)
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
	if (activeSuitorHands[playerNum][0] == cardNum)
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
	if (activeSuitorHands[currentSuitor][0] == activeSuitorHands[playerNum][0])
	{
		cout << "Tie! Both suitors remain in the game." << endl;
		return;
	}
	else
	{
		tempVictor = max(activeSuitorHands[currentSuitor][0], activeSuitorHands[playerNum][0]);
		if (activeSuitorHands[currentSuitor][0] == tempVictor)
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
	suitorObjects[currentSuitor].GainHandmaid();
	suitorsWithHandmaid.push_back(currentSuitor);
}
void Prince()
{
LOOPB:
	ChooseTargetSuitor();
	if (TargetHandmaidProtected())
	{
		if (activeSuitorCount == 2)
		{
			cout << TargetSuitor() << " has Handmaid protection." << endl;
			cout << "The Prince applies to you." << endl;
			if (find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), 9) != activeSuitorHands[currentSuitor].end())
			{
				cout << "You had the Princess! You're out!" << endl;
				RemoveSuitor(1);
				return;
			}
			for (unsigned int i = 0; i < activeSuitorHands[currentSuitor].size(); i++)
			{
				upPile.push_back(i);
			}
			activeSuitorHands[currentSuitor].clear();
			activeSuitorHands[currentSuitor].push_back(deck[0]);
			deck.erase(deck.begin());
			PrintCurrentSuitorHand();
			return;
		}
		cout << suitorNames[playerNum] << " is untargetable." << endl;
		goto LOOPB;
	}
	if (find(activeSuitorHands[playerNum].begin(), activeSuitorHands[playerNum].end(), 9) != activeSuitorHands[playerNum].end())
	{
		cout << suitorNames[playerNum] << " had the Princess! " << suitorNames[playerNum] << " is out!" << endl;
		RemoveSuitor(0);
		return;
	}
	if (deck.empty())
	{
		cout << suitorNames[playerNum] << " discards their hand, then redraws." << endl;
		for (unsigned int i = 0; i < activeSuitorHands[playerNum].size(); i++)
		{
			upPile.push_back(i);
		}
		activeSuitorHands[playerNum].push_back(downPile[0]);
		downPile.erase(downPile.begin(), downPile.end());
		if (playerNum == currentSuitor)
		{
			PrintCurrentSuitorHand();
		}
	}
	else
	{
		cout << suitorNames[playerNum] << " discards their hand, then redraws." << endl;
		for (unsigned int i = 0; i < activeSuitorHands[playerNum].size(); i++)
		{
			upPile.push_back(i);
		}
		activeSuitorHands[playerNum].erase(activeSuitorHands[playerNum].begin(), activeSuitorHands[playerNum].end());
		activeSuitorHands[playerNum].push_back(deck[0]);
		deck.erase(deck.begin());
		if (playerNum == currentSuitor)
		{
			PrintCurrentSuitorHand();
		}
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
			activeSuitorHands[currentSuitor].push_back(deck[0]);
			deck.erase(deck.begin());
		}
		PrintCurrentSuitorHand();
	LOOP:
		cout << "First card to put back: " << endl;
		cin >> cardNum;
		auto itA = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
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
			if (itA != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itA);
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
		auto itB = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
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
			if (itB != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itB);
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
			activeSuitorHands[currentSuitor].push_back(deck[0]);
			deck.erase(deck.begin());
		}
		PrintCurrentSuitorHand();
	LOOPB:
		cout << "Card to put back: " << endl;
		cin >> cardNum;
		auto itC = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
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
			if (itC != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itC);
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
	activeSuitorHands[currentSuitor].swap(activeSuitorHands[playerNum]);
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
LOOP:
	while (activeSuitorCount > 1 && !deck.empty())
	{
		if (suitorObjects[currentSuitor].HandmaidStatus())
		{
			suitorObjects[currentSuitor].RemoveHandmaid();
			auto itD = find(suitorsWithHandmaid.begin(), suitorsWithHandmaid.end(), currentSuitor);
			suitorsWithHandmaid.erase(itD);
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
		cout << suitorNames.at(currentSuitor) << " draw a card (d): " << endl;
		cin >> input;
		cout << "--\n";
		if (input == 'd')
		{
			activeSuitorHands.at(currentSuitor).push_back(deck[0]);
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
			if (TargetHandmaidProtected() && activeSuitorCount == 2)
			{
				cout << TargetSuitor() << " has Handmaid protection." << endl;
				cout << "--\n";
				cout << "Moving on to next active Suitor..." << endl;
				this_thread::sleep_for(chrono::seconds(3));
				ClearScreen();
				SwitchSuitor();
				goto LOOP;
			}
			if (suitorsWithHandmaid.size() == activeSuitorCount - 1)
			{
				cout << TargetSuitor() << " has Handmaid protection." << endl;
				cout << "All target Suitors have Handmaid protection." << endl;
				cout << "--\n";
				cout << "Moving on to next active Suitor..." << endl;
				this_thread::sleep_for(chrono::seconds(3));
				ClearScreen();
				SwitchSuitor();
				goto LOOP;
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
		if (activeSuitorCount > 1)
		{
			cout << "--\n";
			cout << "Moving on to next active Suitor..." << endl;
			this_thread::sleep_for(chrono::seconds(3));
			ClearScreen();
			SwitchSuitor();
		}
		tempInput.clear();
	}
}
void PlayGame()
{
	InitialSetup();
	while (!gameOver)
	{
		if (activeSuitorCount == 0)
		{
			InitialSetup();
		}
		SuitorTurn();
		EndRound();
	}
}

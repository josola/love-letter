/*
Jordan Sola 2019
Functions used in Main.cpp
*/

#include "Resources.h"

using namespace std;

//Game functions.
void ClearScreen() { cout << "\033[2J\033[1;1H"; }
void PrintSeperator()
{
	cout << "--" << endl;
}
bool TargetHandmaidProtected()
{
	if (suitorObjects[playerNum].HandmaidStatus()) { return true; }
	else { return false; }
}
void PrintFaceUpPile()
{
	cout << "Cards in face up pile: " << endl;
	for (i = 0, iLength = upPile.size(); i < iLength; ++i)
	{
		cout << cardNames.at(upPile[i]) << " ";
	}
	cout << endl;
	PrintSeperator();
}
void PrintDeckSize()
{
	cout << "Number of cards in the deck: " << playingDeck.size() << endl;
	PrintSeperator();
}
void PrintSuitorsWithSpy()
{
	cout << "Spy bonus: " << endl;
	for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
	{
		if (!activeSuitorHands[i].empty())
		{
			if (suitorObjects[i].SpyStatus()) { cout << suitorNames[i] << " "; }
		}
	}
	cout << endl;
	PrintSeperator();
}
void ClearInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
auto CurrentSuitor() { return suitorNames[currentSuitor]; }
auto TargetSuitor() { return suitorNames[playerNum]; }
bool ProperCardInput()
{
	if (cardNum >= spy && cardNum <= princess && cin) { return true; }
	else
	{
		cout << "Invalid input, please input a card value between 0 and 9." << endl;
		return false;
	}
}
bool CardInHand(int suitor, int card)
{
	if (find(activeSuitorHands[suitor].begin(), activeSuitorHands[suitor].end(), card) != activeSuitorHands[suitor].end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
int HandPosition(int suitor, int pos)
{
	cardPosition = activeSuitorHands[suitor][pos];
	return cardPosition;
}
bool CountessRestriction()
{
	if (CardInHand(currentSuitor, countess) && cardNum != countess)
	{
		if (CardInHand(currentSuitor, prince) || CardInHand(currentSuitor, king))
		{
			cout << "You have the " << cardNames[HandPosition(currentSuitor, 0)]
				<< " and the " << cardNames[HandPosition(currentSuitor, 1)]
				<< ". You MUST play the " << cardNames[countess] << " this turn." << endl;
			return true;
		}
		else { return false; }
	}
	else { return false; }
}
bool IsSuitorPlaying()
{
	if (!activeSuitorHands[playerNum].empty()) { return true; }
	else { return false; }
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
bool ProperSuitorCount()
{
	if (activeSuitorCount >= minSuitorsPlaying && activeSuitorCount <= maxSuitorsPlaying && cin) { return true; }
	else { return false; }
}
void SwitchSuitor()
{
	cout << "Moving on to next active Suitor..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	ClearScreen();
	if (currentSuitor == suitors[0] - 1)
	{
		for (i = 1, iLength = activeSuitorHands.size(); i < iLength; ++i)
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
				for (i = 1, iLength = activeSuitorHands.size(); i < iLength; ++i)
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
	cout << CurrentSuitor() << " played " << cardNames[cardNum] << endl;
	PrintSeperator();
	upPile.push_back(cardNum);
	auto it = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
	activeSuitorHands[currentSuitor].erase(it);
}
void PrintActiveSuitors()
{
	cout << "Rival Suitors: " << endl;
	currentSuitor++;
	for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
	{
		if (!activeSuitorHands[i].empty() && suitors[i] != currentSuitor)
		{
			cout << suitorNames[i] << " ";
		}
	}
	cout << endl;
	PrintSeperator();
	currentSuitor--;
}
void PrintCurrentSuitorHand()
{
	cout << CurrentSuitor() << " hand: " << endl;
	for (i = 0, iLength = activeSuitorHands[currentSuitor].size(); i < iLength; ++i)
	{
		cout << cardNames[HandPosition(currentSuitor, i)] << " ";
	}
	cout << endl;
	PrintSeperator();
}
void PrintTargetSuitorHand()
{
	cout << TargetSuitor() << " hand: " << endl;
	for (i = 0, iLength = activeSuitorHands[playerNum].size(); i < iLength; ++i)
	{
		cout << cardNames[HandPosition(playerNum, i)] << " ";
	}
	cout << endl;
	PrintSeperator();
}
void ChooseTargetSuitor()
{
LOOP:
	PrintActiveSuitors();
	cout << CurrentSuitor() << " choose target suitor: " << endl;
	cin >> playerNum;
	PrintSeperator();
	playerNum--;
	if (!tempInput.empty())
	{
		for (i = 0, iLength = tempInput.size(); i < iLength; ++i)
		{
			if (tempInput[i] == playerNum)
			{
				cout << "You already chose " << suitorNames[tempInput[i]] << " please choose a different Suitor." << endl;
				goto LOOP;
			}
		}
	}
	if (!ProperSuitorInput())
	{
		ClearInput();
		goto LOOP;
	}
	if (!IsSuitorPlaying())
	{
		cout << TargetSuitor() << " is out." << endl;
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
void RemoveSuitor(int suitor)
{
	for (i = 0, iLength = activeSuitorHands[suitor].size(); i < iLength; i++)
	{
		upPile.push_back(activeSuitorHands[suitor][i]);
	}
	activeSuitorHands[suitor].clear();
	if (suitorObjects[suitor].SpyStatus())
	{
		suitorObjects[suitor].RemoveSpy();
	}
	activeSuitorCount--;
}
void ShuffleDeck()
{
	random_shuffle(playingDeck.begin(), playingDeck.end());
}
void ResetDeck()
{
	playingDeck.assign(baseDeck.begin(), baseDeck.end());
}

void SetWinningTokenCount()
{
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
}

//Card functions.
void Spy() { suitorObjects[currentSuitor].GainSpy(); }
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
		RemoveSuitor(playerNum);
	}
	else
	{
		cout << "no match" << endl;
	}
}
void Priest() { PrintTargetSuitorHand(); }
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
			RemoveSuitor(playerNum);
		}
		else {
			cout << TargetSuitor() << " is victorious! " << CurrentSuitor() << " is out!" << endl;
			RemoveSuitor(currentSuitor);
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
			if (find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), princess) != activeSuitorHands[currentSuitor].end())
			{
				cout << "You had the Princess! You're out!" << endl;
				RemoveSuitor(currentSuitor);
				return;
			}
			for (i = 0, iLength = activeSuitorHands[currentSuitor].size(); i < iLength; ++i)
			{
				upPile.push_back(activeSuitorHands[playerNum][i]);
			}
			activeSuitorHands[currentSuitor].clear();
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
			PrintCurrentSuitorHand();
			return;
		}
		cout << suitorNames[playerNum] << " is untargetable." << endl;
		goto LOOPB;
	}
	if (find(activeSuitorHands[playerNum].begin(), activeSuitorHands[playerNum].end(), 9) != activeSuitorHands[playerNum].end())
	{
		cout << TargetSuitor() << " had the Princess! " << TargetSuitor() << " is out!" << endl;
		RemoveSuitor(playerNum);
		return;
	}
	if (playingDeck.empty())
	{
		cout << suitorNames[playerNum] << " discards their hand, then redraws." << endl;
		for (i = 0, iLength = activeSuitorHands[playerNum].size(); i < iLength; ++i)
		{
			upPile.push_back(activeSuitorHands[playerNum][i]);
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
		for (i = 0, iLength = activeSuitorHands[playerNum].size(); i < iLength; ++i)
		{
			upPile.push_back(activeSuitorHands[playerNum][i]);
		}
		activeSuitorHands[playerNum].erase(activeSuitorHands[playerNum].begin(), activeSuitorHands[playerNum].end());
		activeSuitorHands[playerNum].push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
		if (playerNum == currentSuitor)
		{
			PrintCurrentSuitorHand();
		}
	}
}
void Chancellor()
{
	if (playingDeck.empty())
	{
		cout << "The deck is empty. The " << cardNames[6] << " plays with no effect." << endl;
		return;
	}
	if (playingDeck.size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
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
		if (!CardInHand(currentSuitor, cardNum))
		{
			ClearInput();
			goto LOOP;
		}
		else
		{
			playingDeck.push_back(cardNum);
			if (itA != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itA);
			}
			if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[cardNum] << " you are out!" << endl;
				RemoveSuitor(currentSuitor);
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
		if (!CardInHand(currentSuitor, cardNum))
		{
			ClearInput();
			goto LOOPA;
		}
		else
		{
			playingDeck.push_back(cardNum);
			if (itB != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itB);
			}
			if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[cardNum] << " you are out!" << endl;
				RemoveSuitor(currentSuitor);
				return;
			}
			else
			{
				PrintCurrentSuitorHand();
			}
		}
	}
	if (playingDeck.size() == 1)
	{
		cout << "There is only one card in the deck." << endl;
		for (int i = 0; i < 1; i++)
		{
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
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
		if (!CardInHand(currentSuitor, cardNum))
		{
			ClearInput();
			goto LOOPB;
		}
		else
		{
			playingDeck.push_back(cardNum);
			if (itC != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itC);
			}
			if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[cardNum] << " you are out!" << endl;
				RemoveSuitor(currentSuitor);
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

//Dependent on card functions.
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

//Main gameplay functions.
void InitialSetup()
{
	cout << "-- WELCOME TO LOVE LETTER --" << endl;
LOOP:
	cout << "How many suitors will be playing: " << endl;
	cin >> activeSuitorCount;
	PrintSeperator();
	if (!ProperSuitorCount())
	{
		cout << "Invalid input, please input a number of Suitors between 2 and 6." << endl;
		ClearInput();
		goto LOOP;
	}
	else
	{
		originalSuitorCount = activeSuitorCount;
		SetWinningTokenCount();
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
					ClearScreen();
					cout << suitorNames.at(i) << " got it!" << endl;
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
}
void BeginRound()
{
	ResetDeck();
	cout << "-- ROUND " << roundCount << " --" << endl;
	if (roundCount != startingRound)
	{
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
	ShuffleDeck();
	if (activeSuitorCount == minSuitorsPlaying)
	{
		downPile.push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
		for (unsigned int i = 0; i < 3; i++)
		{
			upPile.push_back(playingDeck[i]);
			playingDeck.erase(playingDeck.begin());
		}
	}
	else
	{
		downPile.push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
	}
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		activeSuitorHands.at(i).push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
	}
}
void SuitorTurn()
{
LOOP:
	while (activeSuitorCount > 1 && !playingDeck.empty())
	{
		if (suitorObjects[currentSuitor].HandmaidStatus())
		{
			suitorObjects[currentSuitor].RemoveHandmaid();
			auto itD = find(suitorsWithHandmaid.begin(), suitorsWithHandmaid.end(), currentSuitor);
			suitorsWithHandmaid.erase(itD);
		}
		if (!playingDeck.empty())
		{
			PrintDeckSize();
			PrintActiveSuitors();
			PrintFaceUpPile();
			PrintSuitorsWithSpy();
			PrintCurrentSuitorHand();
		}
		else { return; }
		cout << suitorNames.at(currentSuitor) << " draw a card (d): " << endl;
		cin >> input;
		PrintSeperator();
		if (input == 'd')
		{
			activeSuitorHands.at(currentSuitor).push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
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
		PrintSeperator();
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPA;
		}
		if (!CardInHand(currentSuitor, cardNum))
		{
			cout << "You do not have " << cardNames[cardNum] << " in your hand." << endl;
			goto LOOPA;
		}
		if (CountessRestriction())
		{
			ClearInput();
			goto LOOPA;
		}
		else { DiscardPlayedCard(); }
		if (cardNum == guard || cardNum == priest || cardNum == baron || cardNum == king)
		{
			ChooseTargetSuitor();
			if (TargetHandmaidProtected() && activeSuitorCount == 2)
			{
				cout << TargetSuitor() << " has Handmaid protection." << endl;
				PrintSeperator();
				SwitchSuitor();
				goto LOOP;
			}
			if (suitorsWithHandmaid.size() == activeSuitorCount - 1)
			{
				cout << TargetSuitor() << " has Handmaid protection." << endl;
				cout << "All target Suitors have Handmaid protection." << endl;
				PrintSeperator();
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
			SwitchSuitor();
		}
		tempInput.clear();
	}
}
void EndRound()
{
	if (playingDeck.empty())
	{
		cout << "The deck is empty, suitors compare hands" << endl;
		for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
		{
			if (!activeSuitorHands[i].empty())
			{
				cout << suitorNames[i] << " hand: " << activeSuitorHands[i][0] << endl;
			}
		}
		for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
		{
			if (!activeSuitorHands[i].empty())
			{
				if (winner < activeSuitorHands[i][0])
				{
					winner = activeSuitorHands[i][0];
				}
			}
		}
		for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
		{
			if (!activeSuitorHands[i].empty() && activeSuitorHands[i][0] == winner)
			{
				winner = i;
				break;
			}
		}
		if (activeSuitorCount > 1)
		{
			for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
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
		for (i = 0, iLength = suitors.size(); i < iLength; ++i)
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
	for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
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
void PlayGame()
{
	InitialSetup();
	while (!gameOver)
	{
		BeginRound();
		SuitorTurn();
		EndRound();
	}
}

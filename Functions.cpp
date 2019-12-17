/*
Jordan Sola 2019
Functions used in Main.cpp
*/

#include "Resources.h"

using namespace std;

//Card position functions.//

bool CardInHand(int suitor, int card)
{
	//Checks for card selection in Suitor's hand.
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
	//Return's position of card in Suitor's hand.
	cardPosition = activeSuitorHands[suitor][pos];
	return cardPosition;
}

//Output functions.//

//Prints current Suitor as "SUITOR #"
auto CurrentSuitor() { return suitorNames[currentSuitor]; }
//Prints target Suitor as "SUITOR #"
auto TargetSuitor() { return suitorNames[targetNum]; }
void ClearScreen() { cout << "\033[2J\033[1;1H"; }
void PrintSeperator()
{
	cout << "--" << endl;
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
	for (i = 0, iLength = activeSuitorHands[targetNum].size(); i < iLength; ++i)
	{
		cout << cardNames[HandPosition(targetNum, i)] << " ";
	}
	cout << endl;
	PrintSeperator();
}

//Input checks.//

void ClearInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
bool ProperCardInput()
{
	//Input numbers cannot be lower than zero or higher than nine.
	if (cardNum >= spy && cardNum <= princess && cin) { return true; }
	else
	{
		cout << "Invalid input, please input a card value between 0 and 9." << endl;
		return false;
	}
}
bool ProperSuitorInput()
{
	targetNum++;
	//Cannot input a number lower than one or a number larger than the number of active Suitors.
	if (targetNum >= 1 && targetNum <= activeSuitorHands.size() && cin)
	{
		targetNum--;
		return true;
	}
	else
	{
		cout << "Invalid input, please choose an active player by their number eg. SUITOR 1 would be 1." << endl;
		targetNum--;
		return false;
	}
}
bool ProperSuitorCount()
{
	//Min number of Suitors is two and max number of suitors is six.
	if (activeSuitorCount >= minSuitorsPlaying && activeSuitorCount <= maxSuitorsPlaying && cin) { return true; }
	else { return false; }
}

//Suitor status checks.//

bool CountessRestriction()
{
	//When Prince or King and Countess are in hand, the Countess must be played.
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
	//Active Suitor check.
	if (!activeSuitorHands[targetNum].empty()) { return true; }
	else { return false; }
}
bool TargetHandmaidProtected()
{
	//Handmaid protection check.
	if (suitorObjects[targetNum].HandmaidStatus()) { return true; }
	else { return false; }
}
void ChooseTargetSuitor()
{
	//Guard, Priest, Baron, Prince, and King are cards that target other/current Suitors.
LOOP:
	PrintActiveSuitors();
	cout << CurrentSuitor() << " choose target suitor: " << endl;
	cin >> targetNum;
	PrintSeperator();
	targetNum--;
	//Prompt duplicate Suitor selection.
	if (!tempInput.empty())
	{
		for (i = 0, iLength = tempInput.size(); i < iLength; ++i)
		{
			if (tempInput[i] == targetNum)
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
		//When there are two active Suitors and the other Suitor is protected the card either applies to the current Suitor or play moves on.
		if (activeSuitorCount == 2)
		{
			return;
		}
		else
		{
			cout << TargetSuitor() << " has Handmaid protection." << endl;
			tempInput.push_back(targetNum);
			ClearInput();
			goto LOOP;
		}
	}
	if (targetNum == currentSuitor)
	{
		//Prince can apply to current Suitor.
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

//Suitor modifiers.//

void SwitchSuitor()
{
	//Move to next active Suitor after current Suitor's turn ends.
	cout << "Moving on to next active Suitor..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	ClearScreen();
	//Move to end of Suitor line if at beginning.
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
	//Skip Suitors that are out.
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
	//Discard played card from Suitor hand to up pile.
	cout << CurrentSuitor() << " played " << cardNames[cardNum] << endl;
	PrintSeperator();
	upPile.push_back(cardNum);
	auto it = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
	activeSuitorHands[currentSuitor].erase(it);
}
void RemoveSuitor(int suitor)
{
	//Removing a Suitor from the game.
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
void SetWinningTokenCount()
{
	//Token counts change by the number of Suitors that start the game.
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

//Deck modifiers//

void ShuffleDeck()
{
	random_shuffle(playingDeck.begin(), playingDeck.end());
}
void ResetDeck()
{
	//Sets played deck cards to starting cards.
	playingDeck.assign(baseDeck.begin(), baseDeck.end());
}

//Card functions.//

void Spy() { suitorObjects[currentSuitor].GainSpy(); }
void Guard()
{
	//Current Suitor guesses what card a target Suitor has in hand. Correct guesses knock out the target Suitor.
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
	//Guards cannot guess other Guards.
	if (cardNum == guard)
	{
		cout << "You can guess any card OTHER than a Guard." << endl;
		ClearInput();
		goto LOOP;
	}
	if (activeSuitorHands[targetNum][0] == cardNum)
	{
		cout << "Match! " << suitorNames[targetNum] << " is out." << endl;
		RemoveSuitor(targetNum);
	}
	else
	{
		cout << "no match" << endl;
	}
}
void Priest() { PrintTargetSuitorHand(); }
void Baron()
{
	//Current Suitor compares hand with a target Suitor, highest hand stays in the game.
	PrintCurrentSuitorHand();
	PrintTargetSuitorHand();
	//If both hands are equal both Suitors remain and play moves on.
	if (activeSuitorHands[currentSuitor][0] == activeSuitorHands[targetNum][0])
	{
		cout << "Tie! Both suitors remain in the game." << endl;
		return;
	}
	else
	{
		tempVictor = max(activeSuitorHands[currentSuitor][0], activeSuitorHands[targetNum][0]);
		if (activeSuitorHands[currentSuitor][0] == tempVictor)
		{
			cout << CurrentSuitor() << " is victorious! " << TargetSuitor() << " is out!" << endl;
			RemoveSuitor(targetNum);
		}
		else {
			cout << TargetSuitor() << " is victorious! " << CurrentSuitor() << " is out!" << endl;
			RemoveSuitor(currentSuitor);
		}
	}
}
void Handmaid()
{
	//Suitors with Handmaid protection are untargetable until the beginning of their next turn.
	suitorObjects[currentSuitor].GainHandmaid();
	suitorsWithHandmaid.push_back(currentSuitor);
}
void Prince()
{
	//Current Suitor can discard their hand, or Target Suitor's hand, and draw a new hand.
LOOPB:
	if (currentSuitor == humanSuitor)
	{
		ChooseTargetSuitor();
	}
	if (TargetHandmaidProtected())
	{
		//When there are two active Suitors the Prince must resolve on one of the Suitors.
		if (activeSuitorCount == 2)
		{
			//When target Suitor is Handmaid protected the Prince applies to the current Suitor.
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
				upPile.push_back(activeSuitorHands[targetNum][i]);
			}
			activeSuitorHands[currentSuitor].clear();
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
			if (currentSuitor == humanSuitor)
			{
				PrintCurrentSuitorHand();
			}
			return;
		}
		cout << suitorNames[targetNum] << " is untargetable." << endl;
		goto LOOPB;
	}
	if (find(activeSuitorHands[targetNum].begin(), activeSuitorHands[targetNum].end(), princess) != activeSuitorHands[targetNum].end())
	{
		cout << TargetSuitor() << " had the Princess! " << TargetSuitor() << " is out!" << endl;
		RemoveSuitor(targetNum);
		return;
	}
	if (playingDeck.empty())
	{
		cout << suitorNames[targetNum] << " discards their hand, then redraws." << endl;
		for (i = 0, iLength = activeSuitorHands[targetNum].size(); i < iLength; ++i)
		{
			upPile.push_back(activeSuitorHands[targetNum][i]);
		}
		activeSuitorHands[targetNum].push_back(downPile[0]);
		downPile.erase(downPile.begin(), downPile.end());
		if (targetNum == currentSuitor && targetNum == humanSuitor)
		{
			PrintCurrentSuitorHand();
		}
	}
	else
	{
		cout << suitorNames[targetNum] << " discards their hand, then redraws." << endl;
		for (i = 0, iLength = activeSuitorHands[targetNum].size(); i < iLength; ++i)
		{
			upPile.push_back(activeSuitorHands[targetNum][i]);
		}
		activeSuitorHands[targetNum].erase(activeSuitorHands[targetNum].begin(), activeSuitorHands[targetNum].end());
		activeSuitorHands[targetNum].push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
		if (targetNum == currentSuitor && targetNum == humanSuitor)
		{
			PrintCurrentSuitorHand();
		}
	}
}
void Chancellor()
{
	//Current Suitor draws two cards from the top of the deck and returns two cards to the bottom of the deck.
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
			//I don't think you actually lose if you put back the Princess, you're not discarding it.
			/*if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[princess] << " you are out!" << endl;
				RemoveSuitor(currentSuitor);
				return;
			}*/
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
			//I don't think you actually lose if you put back the Princess, you're not discarding it.
			/*if (cardNum == 9)
			{
				cout << "You discarded the " << cardNames[princess] << " you are out!" << endl;
				RemoveSuitor(currentSuitor);
				return;
			}*/
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
	//Swaps current Suitor's hand with Target Suitor's hand.
	activeSuitorHands[currentSuitor].swap(activeSuitorHands[targetNum]);
	cout << CurrentSuitor() << "'s hand is now..." << endl;
	PrintCurrentSuitorHand();
	cout << TargetSuitor() << "'s hand is now..." << endl;
	PrintTargetSuitorHand();
}
void Princess()
{
	//When a Suitor discards the Princess they are out.
	cout << suitorNames[currentSuitor] << " is out!" << endl;
	RemoveSuitor(1);
}
void PlayCard()
{
	//Directs input to correct card function.
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

//Game state functions.//

void NPCTurn()
{
	//Draw card.
	activeSuitorHands.at(currentSuitor).push_back(playingDeck[0]);
	playingDeck.erase(playingDeck.begin());
	//Play card with highest value.
	if (activeSuitorHands[currentSuitor][0] >= activeSuitorHands[currentSuitor][1])
	{
		cardNum = activeSuitorHands[currentSuitor][0];
	}
	else
	{
		cardNum = activeSuitorHands[currentSuitor][1];
	}
	DiscardPlayedCard();
	//Target Suitor.
	if (cardNum == guard || cardNum == priest || cardNum == baron || cardNum == king)
	{
		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
		{
			if (i != currentSuitor && !suitorObjects[i].HandmaidStatus() && !activeSuitorHands[i].empty())
			{
				targetNum = i;
			}
		}
		if (suitorObjects[targetNum].HandmaidStatus() && activeSuitorCount == 2)
		{
			cout << TargetSuitor() << " has Handmaid protection." << endl;
			cout << "All target Suitors have Handmaid protection." << endl;
			PrintSeperator();
			SwitchSuitor();
			return;
		}
	}
	PlayCard();
}
void InitialSetup()
{
	//Tasks that are performed at the start of every GAME.
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
		//Add hand vectors to a vector container.
		for (i = 1; i < activeSuitorCount + 1; ++i)
		{
			suitors.push_back(i);
		}
		for (i = 1; i < activeSuitorCount + 1; ++i)
		{
			vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		currentSuitor = 0;
		humanSuitor = 0;
	}
		//Removed setup for individual games.
	//	//Set up the target number Suitors will need to guess correctly to go first.
	//	srand((int)time(NULL));
	//	int target = rand() % activeSuitorHands.size() + 1;
	//	//Prompt and record all Suitor guesses, check if they are correct and if they are duplicates of previous guesses.
	//	cout << "I have a suitor number (1 - " << activeSuitorHands.size() << ") in my head. Guess it!" << endl;
	//LOOPA:
	//	for (unsigned int i = 0; i < activeSuitorHands.size() + 1; ++i)
	//	{
	//	LOOPB:
	//		cout << suitorNames.at(i) << " guess: " << endl;
	//		cin >> guess;
	//		if (guess <= activeSuitorHands.size() && guess >= 1)
	//		{
	//			//Duplicate guess.
	//			for (unsigned int i = 0; i < tempVector.size(); ++i)
	//			{
	//				if (guess == tempVector.at(i))
	//				{
	//					cout << guess << " has already been guessed. Try again." << endl;
	//					ClearInput();
	//					goto LOOPB;
	//				}
	//			}
	//			//Correct guess.
	//			if (guess == target)
	//			{
	//				ClearScreen();
	//				cout << suitorNames.at(i) << " got it!" << endl;
	//				currentSuitor = i;
	//				break;
	//			}
	//			//Add previous guesses to be checked as duplicates.
	//			tempVector.push_back(guess);
	//		}
	//		else
	//		{
	//			cout << "Invalid input, please input a guess between 1 and " << activeSuitorCount << '.' << endl;
	//			ClearInput();
	//			goto LOOPA;
	//		}
	//	}
	//	tempVector.clear();
	//}
}
void BeginRound()
{
	ResetDeck();
	ShuffleDeck();
	cout << "-- ROUND " << roundCount << " --" << endl;
	//Check for starting round.
	if (roundCount != startingRound)
	{
		//Round is second round or above.
		activeSuitorCount = originalSuitorCount;
		for (i = 1; i < activeSuitorCount + 1; ++i)
		{
			suitors.push_back(i);
		}
		for (i = 1; i < activeSuitorCount + 1; ++i)
		{
			vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		cout << suitorNames.at(winner) << " won the last round. " << suitorNames.at(winner) << " goes first." << endl;
		currentSuitor = winner;
		winner = 0;
	}
	//Check for two Suitor game.
	if (activeSuitorCount == minSuitorsPlaying)
	{
		downPile.push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
		for (i = 0; i < 3; ++i)
		{
			upPile.push_back(playingDeck[i]);
			playingDeck.erase(playingDeck.begin());
		}
	}
	//Discard top card of deck to face down pile, no matter the activeSuitorCount.
	else
	{
		downPile.push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
	}
	//Deal starting hand.
	for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
	{
		activeSuitorHands.at(i).push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
	}
}
void SuitorTurn()
{
LOOP:
	//More than one Suitor must be playing and the deck must not be empty.
	while (activeSuitorCount > 1 && !playingDeck.empty())
	{
		//Remove Handmaid protection from previous turn.
		if (suitorObjects[currentSuitor].HandmaidStatus())
		{
			suitorObjects[currentSuitor].RemoveHandmaid();
			auto itD = find(suitorsWithHandmaid.begin(), suitorsWithHandmaid.end(), currentSuitor);
			suitorsWithHandmaid.erase(itD);
		}
		
		if (currentSuitor != humanSuitor)
		{
			NPCTurn();
		}
		else
		{
			//Check for empty deck so these functions don't duplicate.
			if (!playingDeck.empty())
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
			//Current Suitor draws a card to their hand.
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
			//Current Suitor plays a card from their hand.
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
			//Card resolves.
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
		}
		//Current Suitor's turn is done. Move to next active Suitor.
		if (activeSuitorCount > 1)
		{
			SwitchSuitor();
		}
		tempInput.clear();
	}
}
void EndRound()
{
	//When the deck runs out.
	if (playingDeck.empty())
	{
		cout << "The deck is empty, suitors compare hands" << endl;
		for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
		{
			//Print remaining Suitors.
			if (!activeSuitorHands[i].empty())
			{
				cout << suitorNames[i] << " hand: " << activeSuitorHands[i][0] << endl;
			}
		}
		//Assign Suitor with highest hand to winner.
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
		//Assign winner as a Suitor integer.
		for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
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
	//When there is one Suitor remaining.
	else
	{
		//Assign winner as a Suitor integer.
		for (i = 0, iLength = activeSuitorHands.size(); i < iLength; ++i)
		{
			if (!activeSuitorHands[i].empty())
			{
				winner = i;
			}
		}
		cout << "Round over. " << suitorNames[winner] << " is the last suitor standing." << endl;
		//Check for Spy bonus and give bonus token.
		if (suitorObjects[winner].SpyStatus())
		{
			cout << suitorNames[winner] << " has the Spy, they gain an extra favor token <3" << endl;
			suitorObjects[winner].GainToken();
			suitorObjects[winner].RemoveSpy();
			cout << suitorNames[winner] << " token count: " << suitorObjects[winner].GetTokenCount() << endl;
		}
	}
	//Give winner a favor token.
	suitorObjects[winner].GainToken();
	cout << suitorNames[winner] << " gains one[1] favor token <3" << endl;
	cout << suitorNames[winner] << " total tokens: " << suitorObjects[winner].GetTokenCount() << endl;
	//Prepare for next round.
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

//Game state.//

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

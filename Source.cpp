#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

int suitorCount, currentSuitor, cardNum, originalSuitorCount, roundCount = 1, tempVictor, totalTokensWins;
auto winner = 0;
unsigned int playerNum;
bool gameOver = false;
char input;
vector<string> suitorNames = { "SUITOR 1", "SUITOR 2", "SUITOR 3", "SUITOR 4", "SUITOR 5", "SUITOR 6" };
vector<string> cardNames = { "SPY[0]", "GUARD[1]", "PRIEST[2]", "BARON[3]", "HANDMAID[4]", "PRINCE[5]", "CHANCELLOR[6]", "KING[7]", "COUNTESS[8]", "PRINCESS[9]" };
vector<unsigned int> deck = { 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9 };
vector<unsigned int> tempVector;
vector<unsigned int> suitors;
vector<unsigned int> upPile;
vector<unsigned int> downPile;
vector<vector<int> > suitor;

class Suitor
{
private:
	bool hasSpy = false;
	bool hasHandmaid = false;
	int tokenCount = 0;

public:
	void getSpy()
	{
		hasSpy = true;
	}
	void loseSpy()
	{
		hasSpy = false;
	}
	bool spyStatus()
	{
		return hasSpy;
	}
	void getHandmaid()
	{
		hasHandmaid = true;
	}
	void loseHandmaid()
	{
		hasHandmaid = false;
	}
	bool handmaidStatus()
	{
		return hasHandmaid;
	}
	int getTokenCount()
	{
		return tokenCount;
	}
	void upTokenCount()
	{
		tokenCount++;
	}
};

Suitor suitor1, suitor2, suitor3, suitor4, suitor5, suitor6;
vector<Suitor> suitorObjectContainer{ suitor1, suitor2, suitor3, suitor4, suitor5, suitor6 };

void invalidInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "invalid input" << endl;
}

void switchPlayer()
{
	//Check if current suitor is at begining of vector.
	if (currentSuitor == suitors[0] - 1)
	{
		for (unsigned int i = 1; i < suitor.size(); i++)
		{
			currentSuitor++;
		}
	}
	else
	{
		currentSuitor--;
	}
	//Skip suitors marked as out[0].
	while (suitors[currentSuitor] == 0)
	{
		if (currentSuitor == suitors[0])
		{
			for (unsigned int i = 1; i < suitor.size(); i++)
			{
				currentSuitor++;
			}
		}
		if (suitors[currentSuitor] == 0)
		{
			currentSuitor--;
		}
	}
}

void discardPlayedCard()
{
	//Expression to aquire input number from within vectors.
	auto it = find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum);
	cout << suitorNames[currentSuitor] << " played " << cardNames[cardNum] << endl;
	//Discard played card from current suitor hand to up pile.
	upPile.push_back(cardNum);
	if (it != suitor[currentSuitor].end())
	{
		suitor[currentSuitor].erase(it);
	}
}

void printActiveSuitors()
{
	cout << "Suitors fighting for the Princess: " << endl;
	//Up current suitor to conform to vector rules (begin at 0).
	currentSuitor++;
	//Check if suitor is out (suitor hand is empty). Do not print current suitor name.
	for (unsigned int i = 0; i < suitor.size(); i++)
	{
		if (!suitor[i].empty() && suitors[i] != currentSuitor)
		{
			cout << suitorNames[i] << " ";
		}
	}
	//Decrement current suitor to conform to human readability (start at 1). 
	currentSuitor--;
	cout << endl;
}

void targetSuitor()
{
LOOP:
	printActiveSuitors();
	//Prompt current suitor to target suitor.
	cout << suitorNames[currentSuitor] << " target suitor: " << endl;
	cin >> playerNum;
	//Decrement playerNum to conform to vector rules (begin at 0).
	playerNum--;
	//Check for valid input.
	if (playerNum < 0 || playerNum > suitors.size() - 1 || !cin)
	{
		invalidInput();
		goto LOOP;
	}
	//Check if target suitor is out.
	if (suitors[playerNum] == 0)
	{
		cout << suitorNames[playerNum] << " is out." << endl;
		goto LOOP;
	}
	//Check if target suitor input is current suitor.
	if (playerNum == currentSuitor)
	{
		if (cardNum == 5)
		{
			return;
		}
		else
		{
			cout << "You cannot choose yourself." << endl;
			goto LOOP;
		}
	}
	//Check for Handmaid protection.
	if (suitorObjectContainer[playerNum].handmaidStatus())
	{
		cout << suitorNames[playerNum] << " is untargetable." << endl;
		if (suitorCount == 2)
		{
			return;
		}
		else
		{
			goto LOOP;
		}
	}
}

void playCard()
{
	switch (cardNum)
	{
	case 0:
		discardPlayedCard();
		//Current suitor object gains spy bonus.
		suitorObjectContainer[currentSuitor].getSpy();
		break;
	case 1:
		discardPlayedCard();
		targetSuitor();
		//LOOPB:
		//	//Prompt current suitor for card guess.
		//	cout << suitorNames[currentSuitor] << " card guess: " << endl;
		//	for (unsigned int i = 0; i < suitor.at(playerNum).size(); i++)
		//	{
		//		cout << cardNames.at(suitor[playerNum][i]) << " ";
		//	}
		//	cout << endl;
		//	cin >> cardNum;
		//	//Check for valid input.
		//	if (cardNum >= 0 && cardNum <= 9 && cin)
		//	{
		//		//Check for correct card guess.
		//		if (suitor[playerNum][0] == cardNum)
		//		{
		//			cout << "Match! " << suitorNames[playerNum] << " is out." << endl;
		//			//Discard target suitor hand to up pile.
		//			for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
		//			{
		//				upPile.push_back(suitor[playerNum][i]);
		//			}
		//			suitor[playerNum].erase(suitor[playerNum].begin(), suitor[playerNum].end());
		//			//Remove target suitor from game.
		//			if (suitorObjectContainer[playerNum].spyStatus())
		//			{
		//				suitorObjectContainer[playerNum].loseSpy();
		//			}
		//			suitors[playerNum] = 0;
		//			suitorCount--;
		//		}
		//		else
		//		{
		//			cout << "no match" << endl;
		//			break;
		//		}
		//	}
		//	else
		//	{
		//		invalidInput();
		//		goto LOOPB;
		//	}
		break;
	case 2:
		discardPlayedCard();
		targetSuitor();
		/*cout << suitorNames[playerNum] << " hand: " << endl;
		for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
		{
			cout << cardNames.at(suitor[playerNum][i]) << endl;
		}*/
		break;
	case 3:
		discardPlayedCard();
		targetSuitor();
		////Print target suitor hand along with current suitor hand.
		//cout << suitorNames[currentSuitor] << " hand: " << endl;
		//cout << cardNames.at(suitor[currentSuitor][0]) << endl;
		//cout << suitorNames[playerNum] << " hand: " << endl;
		//cout << cardNames.at(suitor[playerNum][0]) << endl;
		////Check for equal hand value.
		//if (suitor[currentSuitor][0] == suitor[playerNum][0])
		//{
		//	cout << "Tie! Both suitors remain in the game." << endl;
		//	break;
		//}
		//else
		//{
		//	//Assign highest value card to a temporary value.
		//	tempVictor = max(suitor[currentSuitor][0], suitor[playerNum][0]);
		//	//Check current suitor hand value against temporary highest value.
		//	if (suitor[currentSuitor][0] == tempVictor)
		//	{
		//		cout << suitorNames[currentSuitor] << " is victorious! " << suitorNames[playerNum] << " is out!" << endl;
		//		//Discard target suitor hand to up pile.
		//		for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
		//		{
		//			upPile.push_back(suitor[playerNum][i]);
		//		}
		//		suitor[playerNum].erase(suitor[playerNum].begin(), suitor[playerNum].end());
		//		//Remove target suitor from game.
		//		if (suitorObjectContainer[playerNum].spyStatus())
		//		{
		//			suitorObjectContainer[playerNum].loseSpy();
		//		}
		//		suitors[playerNum] = 0;
		//		suitorCount--;
		//	}
		//	//Check target suitor hand value against temporary highest value.
		//	else {
		//		cout << suitorNames[playerNum] << " is victorious! " << suitorNames[currentSuitor] << " is out!" << endl;
		//		//Discard current suitor hand to up pile.
		//		for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
		//		{
		//			upPile.push_back(suitor[currentSuitor][i]);
		//		}
		//		suitor[currentSuitor].erase(suitor[currentSuitor].begin(), suitor[currentSuitor].end());
		//		//Remove current suitor from game.
		//		if (suitorObjectContainer[currentSuitor].spyStatus())
		//		{
		//			suitorObjectContainer[currentSuitor].loseSpy();
		//		}
		//		suitors[currentSuitor] = 0;
		//		suitorCount--;
		//	}
		//}
		break;
	case 4:
		discardPlayedCard();
		////Current suitor object gains Handmaid protection.
		//suitorObjectContainer[currentSuitor].getHandmaid();
		break;
	case 5:
		discardPlayedCard();
	LOOPE:
		targetSuitor();
		//Check for Handmaid protection (Prince requires more checks than standard Handmaid check).
		if (suitorObjectContainer[playerNum].handmaidStatus())
		{
			if (suitorCount == 2)
			{
				//Prince must be played on current suitor if only other active suitor has handmaid protection.
				cout << "The Prince applies only to you." << endl;
				//Check for Princess in current suitor hand.
				if (find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), 9) != suitor[currentSuitor].end())
				{
					cout << "You had the Princess! You're out!" << endl;
					//Discard current suitor hand to up pile.
					for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
					{
						upPile.push_back(i);
					}
					suitor[currentSuitor].erase(suitor[currentSuitor].begin(), suitor[currentSuitor].end());
					//Remove current suitor from game.
					if (suitorObjectContainer[currentSuitor].spyStatus())
					{
						suitorObjectContainer[currentSuitor].loseSpy();
					}
					suitors[currentSuitor] = 0;
					suitorCount--;
					break;
				}
				//Discard current suitor hand when there are more than two active suitors and the other active suitor has handmaid protection.
				for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
				{
					upPile.push_back(i);
				}
				suitor[currentSuitor].erase(suitor[currentSuitor].begin(), suitor[currentSuitor].end());
				//Draw into current suitor hand from deck.
				suitor[currentSuitor].push_back(deck[0]);
				deck.erase(deck.begin());
				break;
			}
			cout << suitorNames[playerNum] << " is untargetable." << endl;
			goto LOOPE;
		}
		//Check for Princess in target suitor hand.
		if (find(suitor[playerNum].begin(), suitor[playerNum].end(), 9) != suitor[playerNum].end())
		{
			cout << suitorNames[playerNum] << " had the Princess! " << suitorNames[playerNum] << " is out!" << endl;
			//Discard target suitor hand to up pile.
			for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
			{
				upPile.push_back(i);
			}
			suitor[playerNum].erase(suitor[playerNum].begin(), suitor[playerNum].end());
			//Remove target suitor from game.
			if (suitorObjectContainer[playerNum].spyStatus())
			{
				suitorObjectContainer[playerNum].loseSpy();
			}
			suitors[playerNum] = 0;
			suitorCount--;
			break;
		}
		//When the deck is empty, the target suitor must discard their hand and draw the card in the face down pile to their hand.
		if (deck.empty())
		{
			//Discard target suitor hand.
			for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
			{
				upPile.push_back(i);
			}
			//Draw into target suitor hand from face down pile.
			suitor[playerNum].push_back(downPile[0]);
			downPile.erase(downPile.begin(), downPile.end());
		}
		//Perform basic Prince function.
		else
		{
			//Discard target suitor hand to up pile.
			for (unsigned int i = 0; i < suitor[playerNum].size(); i++)
			{
				upPile.push_back(i);
			}
			//Draw into target suitor hand from deck.
			suitor[playerNum].erase(suitor[playerNum].begin(), suitor[playerNum].end());
			suitor[playerNum].push_back(deck[0]);
			deck.erase(deck.begin());
		}
		break;
	case 6:
		discardPlayedCard();
		//	//Draw two cards.
		//	for (int i = 0; i < 2; i++)
		//	{
		//		suitor[--currentSuitor].push_back(deck[0]);
		//		deck.erase(deck.begin());
		//	}
		//	//Print current suitor hand.
		//	cout << suitorNames[currentSuitor] << " hand: " << endl;
		//	for (unsigned int i = 0; i < suitor[currentSuitor].size(); i++)
		//	{
		//		cout << cardNames[i] << " ";
		//	}
		//	cout << endl;
		//LOOPF:
		//	cout << "First card to put back: " << endl;
		//	cin >> inputNum;
		//	//Check for proper input.
		//	if (inputNum < 0 || inputNum > 9 || !cin)
		//	{
		//		invalidInput();
		//		goto LOOPF;
		//	}
		//	//Check if input card is not in hand.
		//	if (!(find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), inputNum) != suitor[currentSuitor].end()))
		//	{
		//		cout << cardNames[inputNum] << " is not in your hand." << endl;
		//		goto LOOPF;
		//	}
		//	//Discard input card to bottom of deck.
		//	else
		//	{
		//		deck.push_back(inputNum);
		//		if (it != suitor[currentSuitor].end())
		//		{
		//			suitor[currentSuitor].erase(it);
		//		}
		//	}
		//	cout << endl;
		//LOOPG:
		//	cout << "Second card to put back: " << endl;
		//	cin >> inputNum;
		//	//Check for proper input.
		//	if (inputNum < 0 || inputNum > 9 || !cin)
		//	{
		//		invalidInput();
		//		goto LOOPG;
		//	}
		//	//Check if input card is not in hand.
		//	if (!(find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), inputNum) != suitor[currentSuitor].end()))
		//	{
		//		cout << cardNames[inputNum] << " is not in your hand." << endl;
		//		goto LOOPG;
		//	}
		//	//Discard input card to bottom of deck.
		//	else
		//	{
		//		deck.push_back(inputNum);
		//		if (it != suitor[currentSuitor].end())
		//		{
		//			suitor[currentSuitor].erase(it);
		//		}
		//		cout << endl;
		//	}
		break;
	case 7:
		discardPlayedCard();
		targetSuitor();
		break;
	case 8:
		discardPlayedCard();
		break;
	case 9:
		discardPlayedCard();
		break;
	}
}

void initialSetup()
{
	//Begin initial round.
	if (roundCount == 1)
	{
		cout << "-- WELCOME TO LOVE LETTER --" << endl;
		//Determine how many suitors will be playing.
	LOOPA:
		cout << "How many suitors will be playing: " << endl;
		cin >> suitorCount;
		//Check for valid input.
		if (suitorCount < 2 || suitorCount > 6 || !cin)
		{
			invalidInput();
			goto LOOPA;
		}
		//Set number of favor tokens to win based off of number of suitors playing.
		switch (suitorCount)
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
		//Set suitorCount to go back to after round end.
		originalSuitorCount = suitorCount;
		//Fill to number of suitors in-game;
		for (int i = 1; i < suitorCount + 1; i++)
		{
			suitors.push_back(i);
		}
		for (int i = 1; i < suitorCount + 1; i++)
		{
			vector<int> hand;
			suitor.push_back(hand);
		}
		//Determine which suitor will start the game.
		srand((int)time(NULL));
		int target = rand() % suitor.size() + 1;
		unsigned int guess;
		cout << "I have a suitor number (1 - " << suitor.size() << ") in my head. Guess it!" << endl;
		cout << target << endl;
	LOOP:
		for (unsigned int i = 0; i < suitor.size() + 1; i++)
		{
			cout << suitorNames.at(i) << " guess: " << endl;
			cin >> guess;
			if (guess <= suitor.size() && guess >= 1)
			{
				if (guess == target)
				{
					cout << suitorNames.at(i) << " got it!" << endl;
					currentSuitor = i;
					break;
				}
			}
			else
			{
				cout << suitorNames.at(i) << " messed it up, everyone try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				goto LOOP;
			}
		}
	}
	//Begin next round.
	else
	{
		deck = { 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9 };
		cout << "-- ROUND " << roundCount << " --" << endl;
		suitorCount = originalSuitorCount;
		for (int i = 1; i < suitorCount + 1; i++)
		{
			suitors.push_back(i);
		}
		for (int i = 1; i < suitorCount + 1; i++)
		{
			vector<int> hand;
			suitor.push_back(hand);
		}
		cout << suitorNames.at(winner) << " won the last round. " << suitorNames.at(winner) << " goes first." << endl;
		currentSuitor = winner;
		winner = 0;
	}
	//Shuffle deck, discard one card face down and possibly three cards face up.
	random_shuffle(deck.begin(), deck.end());
	if (suitorCount == 2)
	{
		//Discard one card to down pile.
		downPile.push_back(deck[0]);
		deck.erase(deck.begin());
		for (unsigned int i = 0; i < 3; i++)
		{
			upPile.push_back(deck[i]);
			deck.erase(deck.begin());
		}
		//Discard three cards to up pile.
		cout << "Up pile: " << endl;
		for (unsigned int i = 0; i < upPile.size(); i++)
		{
			cout << cardNames.at(upPile[i]) << " ";
		}
		cout << endl;
	}
	if (suitorCount > 2)
	{
		downPile.push_back(deck[0]);
		deck.erase(deck.begin());
	}
	//Deal starting hand.
	for (unsigned int i = 0; i < suitor.size(); i++)
	{
		suitor.at(i).push_back(deck[0]);
		deck.erase(deck.begin());
	}
}

void playerTurn()
{
	while (suitorCount > 1 && !deck.empty())
	{
		if (suitorObjectContainer[currentSuitor].handmaidStatus())
		{
			suitorObjectContainer[currentSuitor].loseHandmaid();
		}
		//Draw card to player hand.
		cout << suitorNames.at(currentSuitor) << " hand: ";
		for (unsigned int i = 0; i < suitor.at(currentSuitor).size(); i++)
		{
			cout << cardNames.at(suitor[currentSuitor][i]) << " ";
		}
		cout << endl;
	LOOP:
		cout << suitorNames.at(currentSuitor) << " draw a card (d): " << endl;
		cin >> input;
		if (input == 'd')
		{
			suitor.at(currentSuitor).push_back(deck[0]);
			deck.erase(deck.begin());
		}
		else
		{
			invalidInput();
			goto LOOP;
		}
		//Play card.
	LOOPB:
		cout << suitorNames.at(currentSuitor) << " hand: " << endl;
		for (unsigned int i = 0; i < suitor.at(currentSuitor).size(); i++)
		{
			cout << cardNames.at(suitor[currentSuitor][i]) << " ";
		}
		cout << endl;
		cout << suitorNames.at(currentSuitor) << " play a card: " << endl;
		cin >> cardNum;
		if (!(find(suitor[currentSuitor].begin(), suitor[currentSuitor].end(), cardNum) != suitor[currentSuitor].end()))
		{
			cout << "You don't have " << cardNames[cardNum] << " in your hand." << endl;
			goto LOOPB;
		}
		if (cardNum >= 0 && cardNum <= 9 && cin)
		{
			playCard();
		}
		else
		{
			invalidInput();
			goto LOOPB;
		}
		if (suitorCount > 1)
		{
			switchPlayer();
		}
	}
}

void endRound()
{
	//When the deck is empty, remaining suitors compare hands. The highest hand between remaining suitors wins the round.
	if (deck.empty())
	{
		//Print remaining suitor hands.
		cout << "The deck is empty, suitors compare hands" << endl;
		for (unsigned int i = 0; i < suitor.size(); i++)
		{
			cout << suitorNames[i] << " hand: " << suitor[i][0] << endl;
		}
		//Assign highest suitor hand value as winner.
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
		//Assign vector position of highest hand value as winner.
		for (unsigned int i = 0; i < suitor.size(); i++)
		{
			if (suitor[i][0] == winner)
			{
				winner = i;
				break;
			}
		}
		if (suitorCount > 1)
		{
			//Check remaining suitors for duplicate Spy bonus.
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
	//When there are no more than one active suitors.
	else
	{
		//Designate remaining suitor as winner.
		for (unsigned int i = 0; i < suitors.size(); i++)
		{
			if (suitors[i] > 0)
			{
				winner = --suitors[i];
			}
		}
		cout << "Round over. " << suitorNames[winner] << " is the last suitor standing." << endl;
		//Check remaining suitor for Spy bonus.
		if (suitorObjectContainer[winner].spyStatus())
		{
			cout << suitorNames[winner] << " has the Spy, they gain an extra favor token <3" << endl;
			suitorObjectContainer[winner].upTokenCount();
			cout << suitorNames[winner] << " token count: " << suitorObjectContainer[winner].getTokenCount() << endl;
		}
	}
	//Give winner a favor token.
	suitorObjectContainer[winner].upTokenCount();
	cout << suitorNames[winner] << " gains one[1] favor token <3" << endl;
	cout << suitorNames[winner] << " total tokens: " << suitorObjectContainer[winner].getTokenCount() << endl;
	//Check if winner has enough tokens to win game.
	if (suitorObjectContainer[winner].getTokenCount() < totalTokensWins)
	{
		//Suitor does not have required number of favor tokens to win, start new round.
		++roundCount;
		//Clear suitor, suitors, downPile, and upPile vectors.
		suitor.clear();
		suitors.clear();
		downPile.clear();
		upPile.clear();
		suitorCount = 0;
	}
	if (suitorObjectContainer[winner].getTokenCount() == totalTokensWins)
	{
		//Suitor has enough favor tokens to win the game, game over.
		cout << suitorNames[winner] << " has won the heart of the princess." << endl;
		cout << "-- GAME OVER --" << endl;
		//Clear suitor, suitors, downPile, and upPile vectors.
		suitor.clear();
		suitors.clear();
		downPile.clear();
		upPile.clear();
		suitorCount = 0;
		gameOver = true;
	}
}

int main()
{
	initialSetup();
	while (!gameOver)
	{
		if (suitorCount == 0)
		{
			initialSetup();
		}
		playerTurn();
		endRound();
	}
	return 0;
}

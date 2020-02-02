/*
MIT License

Copyright (c) 2020 Jordan Sola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Functions.h"
#include "SuitorClass.h"
#include "Resources.h"
#include <iostream>

//Output functions.//

void returnSuitor(int suitor)
{
	std::cout << "SUITOR[" << suitor << ']';
}
void ClearScreen()
{
	//Windows tested, untested on unix.
	std::cout << "\033[2J\033[1;1H";
}
void PrintSeperator()
{
	std::cout << "--" << std::endl;
}
void PrintUpPile()
{
	std::cout << "cards in up pile: " << std::endl;
	for (int i : up_pile)
	{
		std::cout << card_names[i] + ' ';
	}
	std::cout << std::endl;
	PrintSeperator();
}
void PrintDeckSize()
{
	std::cout << "Number of cards in the deck: " << playing_deck.size() << std::endl;
	PrintSeperator();
}
void PrintSuitorsWithSpy()
{
	std::cout << "Spy bonus: " << std::endl;
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		if (!activeSuitorHands[i].empty())
		{
			if (suitorObjects[i].SpyStatus())
			{
				returnSuitor(i);
			}
		}
	}
	std::cout << std::endl;
	PrintSeperator();
}
void PrintActiveSuitors()
{
	std::cout << "Rival Suitors: " << std::endl;
	current_suitor++;
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		if (!activeSuitorHands[i].empty() && suitors[i] != current_suitor)
		{
			returnSuitor(i);
		}
	}
	std::cout << std::endl;
	PrintSeperator();
	current_suitor--;
}
void printHand(int suitor)
{
	std::vector<std::string> cardNames
	{
		"SPY[0]", "GUARD[1]", "PRIEST[2]", "BARON[3]", "HANDMAID[4]", "PRINCE[5]", "CHANCELLOR[6]", "KING[7]", "COUNTESS[8]", "PRINCESS[9]"
	};

	returnSuitor(suitor);
	std::cout << " hand: " << std::endl;

	for (unsigned int i = 0; i < activeSuitorHands[suitor].size(); i++)
	{
		std::cout << cardNames[HandPosition(suitor, i)] << " ";
	}
	std::cout << std::endl;
	PrintSeperator();
}

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
	car_position = activeSuitorHands[suitor][pos];
	return car_position;
}

//Input checks.//

void ClearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool ProperCardInput()
{
	//Input numbers cannot be lower than zero or higher than nine.
	if (card_num >= spy && card_num <= princess && std::cin) { return true; }
	else
	{
		std::cout << "Invalid input, please input a card value between 0 and 9." << std::endl;
		return false;
	}
}
bool ProperSuitorInput()
{
	target_hum++;
	//Cannot input a number lower than one or a number larger than the number of active Suitors.
	if (target_hum >= 1 && target_hum <= activeSuitorHands.size() && std::cin)
	{
		target_hum--;
		return true;
	}
	else
	{
		std::cout << "Invalid input, please choose an active player by their number eg. SUITOR 1 would be 1." << std::endl;
		target_hum--;
		return false;
	}
}
bool ProperSuitorCount()
{
	//Min number of Suitors is two and max number of suitors is six.
	if (active_suitor_count >= minSuitorsPlaying && active_suitor_count <= maxSuitorsPlaying && std::cin) { return true; }
	else { return false; }
}

//Suitor status checks.//

bool CountessRestriction()
{
	//When Prince or King and Countess are in hand, the Countess must be played.
	if (CardInHand(current_suitor, countess) && card_num != countess)
	{
		if (CardInHand(current_suitor, prince) || CardInHand(current_suitor, king))
		{
			std::cout << "You have the " << card_names[HandPosition(current_suitor, 0)]
				<< " and the " << card_names[HandPosition(current_suitor, 1)]
				<< ". You MUST play the " << card_names[countess] << " this turn." << std::endl;
			return true;
		}
		else { return false; }
	}
	else { return false; }
}
bool IsSuitorPlaying()
{
	//Active Suitor check.
	if (!activeSuitorHands[target_hum].empty()) { return true; }
	else { return false; }
}
bool TargetHandmaidProtected()
{
	//Handmaid protection check.
	if (suitorObjects[target_hum].HandmaidStatus()) { return true; }
	else { return false; }
}
void ChooseTargetSuitor(int target)
{
	//Guard, Priest, Baron, Prince, and King are cards that target other/current Suitors.
LOOP:
	PrintActiveSuitors();
	returnSuitor(current_suitor);
	std::cout << " choose target suitor: " << std::endl;
	std::cin >> target;
	PrintSeperator();
	//Prompt duplicate Suitor selection.
	if (!temp_input.empty())
	{
		for (unsigned int i = 0; i < temp_input.size(); i++)
		{
			if (temp_input[i] == target)
			{
				std::cout << "You already chose ";
				returnSuitor(temp_input[i]);
				std::cout << "] please choose a different Suitor." << std::endl;
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
		returnSuitor(target_hum);
		std::cout << " is out." << std::endl;
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		//When there are two active Suitors and the other Suitor is protected the card either applies to the current Suitor or play moves on.
		if (active_suitor_count == 2)
		{
			return;
		}
		else
		{
			returnSuitor(target_hum);
			std::cout << " has Handmaid protection." << std::endl;
			temp_input.push_back(target);
			ClearInput();
			goto LOOP;
		}
	}
	if (target == current_suitor)
	{
		//Prince can apply to current Suitor.
		if (card_num == prince)
		{
			return;
		}
		else
		{
			std::cout << "You cannot choose yourself." << std::endl;
			ClearInput();
			goto LOOP;
		}
	}
}

//Suitor modifiers.//

void SwitchSuitor()
{
	//Move to next active Suitor after current Suitor's turn ends.
	std::cout << "Moving on to next active Suitor..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	ClearScreen();
	//Move to end of Suitor line if at beginning.
	if (current_suitor == suitors[0] - 1)
	{
		for (unsigned int i = 1; i < activeSuitorHands.size(); i++)
		{
			current_suitor++;
		}
		if (!activeSuitorHands[current_suitor].empty())
		{
			return;
		}
	}
	//Skip Suitors that are out.
	if (activeSuitorHands[current_suitor].empty())
	{
	LOOP:
		while (activeSuitorHands[current_suitor].empty())
		{
			if (current_suitor == suitors[0] - 1)
			{
				for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
				{
					current_suitor++;
				}
			}
			if (activeSuitorHands[current_suitor].empty())
			{
				current_suitor--;
			}
		}
		return;
	}
	else
	{
		current_suitor--;
		if (activeSuitorHands[current_suitor].empty())
		{
			goto LOOP;
		}
	}
}
void DiscardPlayedCard()
{
	//Discard played card from Suitor hand to up pile.
	returnSuitor(current_suitor);
	std::cout << " played " << card_names[card_num] << std::endl;
	PrintSeperator();
	up_pile.push_back(card_num);
	auto it = find(activeSuitorHands[current_suitor].begin(), activeSuitorHands[current_suitor].end(), card_num);
	activeSuitorHands[current_suitor].erase(it);
}
void RemoveSuitor(int suitor)
{
	//Removing a Suitor from the game.
	for (unsigned int i = 0; i < activeSuitorHands[suitor].size(); i++)
	{
		up_pile.push_back(activeSuitorHands[suitor][i]);
	}
	activeSuitorHands[suitor].clear();
	if (suitorObjects[suitor].SpyStatus())
	{
		suitorObjects[suitor].RemoveSpy();
	}
	active_suitor_count--;
}
void SetWinningTokenCount()
{
	//Token counts change by the number of Suitors that start the game.
	switch (active_suitor_count)
	{
	case 2:
		token_count_to_win = 6;
		break;
	case 3:
		token_count_to_win = 5;
		break;
	case 4:
		token_count_to_win = 4;
		break;
	case 5:
		token_count_to_win = 3;
		break;
	case 6:
		token_count_to_win = 3;
		break;
	}
}

//Deck modifiers//

void ShuffleDeck()
{
	random_shuffle(playing_deck.begin(), playing_deck.end());
}
void ResetDeck()
{
	//Sets played deck cards to starting cards.
	playing_deck.assign(base_deck.begin(), base_deck.end());
}

//Card functions.//

void Spy()
{
	suitorObjects[current_suitor].GainSpy();
}
void Guard()
{
	//Current Suitor guesses what card a target Suitor has in hand. Correct guesses knock out the target Suitor.
LOOP:
	returnSuitor(current_suitor);
	std::cout << " guess a card: " << std::endl;
	std::cin >> card_num;
	if (!ProperCardInput())
	{
		ClearInput();
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		if (active_suitor_count == 2)
		{
			return;
		}
		else
		{
			goto LOOP;
		}
	}
	//Guards cannot guess other Guards.
	if (card_num == guard)
	{
		std::cout << "You can guess any card OTHER than a Guard." << std::endl;
		ClearInput();
		goto LOOP;
	}
	if (activeSuitorHands[target_hum][0] == card_num)
	{
		std::cout << "Match! " << suitor_names[target_hum] << " is out." << std::endl;
		RemoveSuitor(target_hum);
	}
	else
	{
		std::cout << "no match" << std::endl;
	}
}
void Priest()
{
	printHand(target_hum);
}
void Baron()
{
	//Current Suitor compares hand with a target Suitor, highest hand stays in the game.
	printHand(current_suitor);
	printHand(target_hum);
	//If both hands are equal both Suitors remain and play moves on.
	if (activeSuitorHands[current_suitor][0] == activeSuitorHands[target_hum][0])
	{
		std::cout << "Tie! Both suitors remain in the game." << std::endl;
		return;
	}
	else
	{
		temp_victor = std::max(activeSuitorHands[current_suitor][0], activeSuitorHands[target_hum][0]);
		if (activeSuitorHands[current_suitor][0] == temp_victor)
		{
			returnSuitor(current_suitor);
			std::cout << " is victorious! ";
			returnSuitor(target_hum);
			std::cout << " is out!" << std::endl;
			RemoveSuitor(target_hum);
		}
		else {
			returnSuitor(current_suitor);
			std::cout << " is victorious! ";
			returnSuitor(current_suitor);
			std::cout << " is out!" << std::endl;
			RemoveSuitor(current_suitor);
		}
	}
}
void Handmaid()
{
	//Suitors with Handmaid protection are untargetable until the beginning of their next turn.
	suitorObjects[current_suitor].GainHandmaid();
	suitors_with_handmaid.push_back(current_suitor);
}
void Prince()
{
	//Current Suitor can discard their hand, or Target Suitor's hand, and draw a new hand.
LOOPB:
	if (current_suitor == human_suitor)
	{
		ChooseTargetSuitor(target_hum);
	}
	if (TargetHandmaidProtected())
	{
		//When there are two active Suitors the Prince must resolve on one of the Suitors.
		if (active_suitor_count == 2)
		{
			//When target Suitor is Handmaid protected the Prince applies to the current Suitor.
			returnSuitor(target_hum);
			std::cout << " has Handmaid protection." << std::endl;
			std::cout << "The Prince applies to you." << std::endl;
			if (find(activeSuitorHands[current_suitor].begin(), activeSuitorHands[current_suitor].end(), princess) != activeSuitorHands[current_suitor].end())
			{
				std::cout << "You had the Princess! You're out!" << std::endl;
				RemoveSuitor(current_suitor);
				return;
			}
			for (unsigned int i = 0; i < activeSuitorHands[current_suitor].size(); i++)
			{
				up_pile.push_back(activeSuitorHands[target_hum][i]);
			}
			activeSuitorHands[current_suitor].clear();
			activeSuitorHands[current_suitor].push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
			if (current_suitor == human_suitor)
			{
				printHand(current_suitor);
			}
			return;
		}
		std::cout << suitor_names[target_hum] << " is untargetable." << std::endl;
		goto LOOPB;
	}
	if (find(activeSuitorHands[target_hum].begin(), activeSuitorHands[target_hum].end(), princess) != activeSuitorHands[target_hum].end())
	{
		returnSuitor(target_hum);
		std::cout << " had the Princess! ";
		returnSuitor(target_hum);
		std::cout << " is out!" << std::endl;
		RemoveSuitor(target_hum);
		return;
	}
	if (playing_deck.empty())
	{
		std::cout << suitor_names[target_hum] << " discards their hand, then redraws." << std::endl;
		for (unsigned int i = 0; i < activeSuitorHands[target_hum].size(); i++)
		{
			up_pile.push_back(activeSuitorHands[target_hum][i]);
		}
		activeSuitorHands[target_hum].push_back(down_pile[0]);
		down_pile.erase(down_pile.begin(), down_pile.end());
		if (target_hum == current_suitor && target_hum == human_suitor)
		{
			printHand(current_suitor);
		}
	}
	else
	{
		std::cout << suitor_names[target_hum] << " discards their hand, then redraws." << std::endl;
		for (unsigned int i = 0; i < activeSuitorHands[target_hum].size(); i++)
		{
			up_pile.push_back(activeSuitorHands[target_hum][i]);
		}
		activeSuitorHands[target_hum].erase(activeSuitorHands[target_hum].begin(), activeSuitorHands[target_hum].end());
		activeSuitorHands[target_hum].push_back(playing_deck[0]);
		playing_deck.erase(playing_deck.begin());
		if (target_hum == current_suitor && target_hum == human_suitor)
		{
			printHand(current_suitor);
		}
	}
}
void Chancellor()
{
	//Current Suitor draws two cards from the top of the deck and returns two cards to the bottom of the deck.
	if (playing_deck.empty())
	{
		std::cout << "The deck is empty. The " << card_names[6] << " plays with no effect." << std::endl;
		return;
	}
	if (playing_deck.size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			activeSuitorHands[current_suitor].push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
		}
		printHand(current_suitor);
	LOOP:
		std::cout << "First card to put back: " << std::endl;
		std::cin >> card_num;
		auto itA = find(activeSuitorHands[current_suitor].begin(), activeSuitorHands[current_suitor].end(), card_num);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOP;
		}
		if (!CardInHand(current_suitor, card_num))
		{
			ClearInput();
			goto LOOP;
		}
		else
		{
			playing_deck.push_back(card_num);
			if (itA != activeSuitorHands[current_suitor].end())
			{
				activeSuitorHands[current_suitor].erase(itA);
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
				printHand(current_suitor);
			}
		}
	LOOPA:
		std::cout << "Second card to put back: " << std::endl;
		std::cin >> card_num;
		auto itB = find(activeSuitorHands[current_suitor].begin(), activeSuitorHands[current_suitor].end(), card_num);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPA;
		}
		if (!CardInHand(current_suitor, card_num))
		{
			ClearInput();
			goto LOOPA;
		}
		else
		{
			playing_deck.push_back(card_num);
			if (itB != activeSuitorHands[current_suitor].end())
			{
				activeSuitorHands[current_suitor].erase(itB);
			}
			else
			{
				printHand(current_suitor);
			}
		}
	}
	if (playing_deck.size() == 1)
	{
		std::cout << "There is only one card in the deck." << std::endl;
		for (int i = 0; i < 1; i++)
		{
			activeSuitorHands[current_suitor].push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
		}
		printHand(current_suitor);
	LOOPB:
		std::cout << "Card to put back: " << std::endl;
		std::cin >> card_num;
		auto itC = find(activeSuitorHands[current_suitor].begin(), activeSuitorHands[current_suitor].end(), card_num);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPB;
		}
		if (!CardInHand(current_suitor, card_num))
		{
			ClearInput();
			goto LOOPB;
		}
		else
		{
			playing_deck.push_back(card_num);
			if (itC != activeSuitorHands[current_suitor].end())
			{
				activeSuitorHands[current_suitor].erase(itC);
			}
			if (card_num == 9)
			{
				std::cout << "You discarded the " << card_names[card_num] << " you are out!" << std::endl;
				RemoveSuitor(current_suitor);
				return;
			}
			else
			{
				printHand(current_suitor);
			}
		}
	}
}
void King(int agressor, int victim)
{
	//Swaps current Suitor's hand with Target Suitor's hand.
	activeSuitorHands[agressor].swap(activeSuitorHands[victim]);
	returnSuitor(agressor);
	std::cout << " 's hand is now..." << std::endl;
	printHand(agressor);
	returnSuitor(victim);
	std::cout << " 's hand is now..." << std::endl;
	printHand(victim);
}
void Princess()
{
	//When a Suitor discards the Princess they are out.
	std::cout << suitor_names[current_suitor] << " is out!" << std::endl;
	RemoveSuitor(1);
}
void PlayCard()
{
	//Directs input to correct card function.
	switch (card_num)
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
		King(current_suitor, target_hum);
		break;
	case 9:
		Princess();
		break;
	}
}

//Game state functions.//

void InitialSetup()
{
	//Tasks that are performed at the start of every GAME.
	std::cout << "-- WELCOME TO LOVE LETTER --" << std::endl;
LOOP:
	std::cout << "How many suitors will be playing: " << std::endl;
	std::cin >> active_suitor_count;
	PrintSeperator();
	if (ProperSuitorCount())
	{
		original_suitor_count = active_suitor_count;
		SetWinningTokenCount();
		//Add hand vectors to a vector container.
		for (i = 1; i < active_suitor_count + 1; ++i)
		{
			suitors.push_back(i);
		}
		for (i = 1; i < active_suitor_count + 1; ++i)
		{
			std::vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		current_suitor = 0;
		human_suitor = 0;
	}
	else
	{
		std::cout << "Invalid input, please input a number of Suitors between 2 and 6." << std::endl;
		ClearInput();
		goto LOOP;
	}
	//Set up the target number Suitors will need to guess correctly to go first.
	srand((int)time(NULL));
	int target = rand() % activeSuitorHands.size() + 1;
	//Prompt and record all Suitor guesses, check if they are correct and if they are duplicates of previous guesses.
	std::cout << "I have a suitor number (1 - " << activeSuitorHands.size() << ") in my head. Guess it!" << std::endl;
LOOPA:
	for (unsigned int i = 0; i < activeSuitorHands.size() + 1; ++i)
	{
	LOOPB:
		std::cout << suitor_names.at(i) << " guess: " << std::endl;
		std::cin >> guess;
		if (guess <= activeSuitorHands.size() && guess >= 1)
		{
			//Duplicate guess.
			for (unsigned int i = 0; i < temp_vector.size(); ++i)
			{
				if (guess == temp_vector.at(i))
				{
					std::cout << guess << " has already been guessed. Try again." << std::endl;
					ClearInput();
					goto LOOPB;
				}
			}
			//Correct guess.
			if (guess == target)
			{
				ClearScreen();
				std::cout << suitor_names.at(i) << " got it!" << std::endl;
				current_suitor = i;
				break;
			}
			//Add previous guesses to be checked as duplicates.
			temp_vector.push_back(guess);
		}
		else
		{
			std::cout << "Invalid input, please input a guess between 1 and " << active_suitor_count << '.' << std::endl;
			ClearInput();
			goto LOOPA;
		}
	}
	temp_vector.clear();
}
void BeginRound()
{
	ResetDeck();
	ShuffleDeck();
	std::cout << "-- ROUND " << round_count << " --" << std::endl;
	//Check for starting round.
	if (round_count != starting_round)
	{
		//Round is second round or above.
		active_suitor_count = original_suitor_count;
		for (i = 1; i < active_suitor_count + 1; ++i)
		{
			suitors.push_back(i);
		}
		for (i = 1; i < active_suitor_count + 1; ++i)
		{
			std::vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		std::cout << suitor_names.at(winner) << " won the last round. " << suitor_names.at(winner) << " goes first." << std::endl;
		current_suitor = winner;
		winner = 0;
	}
	//Check for two Suitor game.
	if (active_suitor_count == minSuitorsPlaying)
	{
		down_pile.push_back(playing_deck[0]);
		playing_deck.erase(playing_deck.begin());
		for (i = 0; i < 3; ++i)
		{
			up_pile.push_back(playing_deck[i]);
			playing_deck.erase(playing_deck.begin());
		}
	}
	//Discard top card of deck to face down pile, no matter the activeSuitorCount.
	else
	{
		down_pile.push_back(playing_deck[0]);
		playing_deck.erase(playing_deck.begin());
	}
	//Deal starting hand.
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		activeSuitorHands.at(i).push_back(playing_deck[0]);
		playing_deck.erase(playing_deck.begin());
	}
}
void SuitorTurn()
{
LOOP:
	//More than one Suitor must be playing and the deck must not be empty.
	while (active_suitor_count > 1 && !playing_deck.empty())
	{
		//Remove Handmaid protection from previous turn.
		if (suitorObjects[current_suitor].HandmaidStatus())
		{
			suitorObjects[current_suitor].RemoveHandmaid();
			auto itD = find(suitors_with_handmaid.begin(), suitors_with_handmaid.end(), current_suitor);
			suitors_with_handmaid.erase(itD);
		}
		//Check for empty deck so these functions don't duplicate.
		if (!playing_deck.empty())
		{
			PrintDeckSize();
			PrintActiveSuitors();
			PrintUpPile();
			PrintSuitorsWithSpy();
			printHand(current_suitor);
		}
		else
		{
			return;
		}
		//Current Suitor draws a card to their hand.
		std::cout << suitor_names.at(current_suitor) << " draw a card (d): " << std::endl;
		std::cin >> input;
		PrintSeperator();
		if (input == 'd')
		{
			activeSuitorHands.at(current_suitor).push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
		}
		else
		{
			std::cout << "Invalid input, please input 'd' to draw a card." << std::endl;
			ClearInput();
			goto LOOP;
		}
	LOOPA:
		printHand(current_suitor);
		//Current Suitor plays a card from their hand.
		returnSuitor(current_suitor);
		std::cout << " play a card: " << std::endl;
		std::cin >> card_num;
		PrintSeperator();
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPA;
		}
		if (!CardInHand(current_suitor, card_num))
		{
			std::cout << "You do not have " << card_names[card_num] << " in your hand." << std::endl;
			goto LOOPA;
		}
		if (CountessRestriction())
		{
			ClearInput();
			goto LOOPA;
		}
		else { DiscardPlayedCard(); }
		//Card resolves.
		if (card_num == guard || card_num == priest || card_num == baron || card_num == king)
		{
			ChooseTargetSuitor(target_hum);
			if (TargetHandmaidProtected() && active_suitor_count == 2)
			{
				returnSuitor(target_hum);
				std::cout << " has Handmaid protection." << std::endl;
				PrintSeperator();
				SwitchSuitor();
				goto LOOP;
			}
			if (suitors_with_handmaid.size() == active_suitor_count - 1)
			{
				returnSuitor(target_hum);
				std::cout << " has Handmaid protection." << std::endl;
				std::cout << "All target Suitors have Handmaid protection." << std::endl;
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
		//Current Suitor's turn is done. Move to next active Suitor.
		if (active_suitor_count > 1)
		{
			SwitchSuitor();
		}
		temp_input.clear();
	}
}
void EndRound()
{
	//When the deck runs out.
	if (playing_deck.empty())
	{
		std::cout << "The deck is empty, suitors compare hands" << std::endl;
		for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
		{
			//Print remaining Suitors.
			if (!activeSuitorHands[i].empty())
			{
				std::cout << suitor_names[i] << " hand: " << activeSuitorHands[i][0] << std::endl;
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
		if (active_suitor_count > 1)
		{
			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
			{
				if (suitorObjects[i].SpyStatus())
				{
					temp_vector.push_back(i);
				}
			}
			if (temp_vector.size() > 1)
			{
				std::cout << "Multiple suitors had the Spy. No one gets a bonus." << std::endl;
			}
			if (temp_vector.size() == 1)
			{
				std::cout << suitor_names.at(temp_vector[0]) << " Has the Spy, they gain an extra favor token <3" << std::endl;
				suitorObjects.at(temp_vector[0]).GainToken();
				std::cout << suitor_names.at(temp_vector[0]) << " token count: " << suitorObjects.at(temp_vector[0]).GetTokenCount() << std::endl;
			}
			if (temp_vector.empty())
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
		std::cout << "Round over. " << suitor_names[winner] << " is the last suitor standing." << std::endl;
		//Check for Spy bonus and give bonus token.
		if (suitorObjects[winner].SpyStatus())
		{
			std::cout << suitor_names[winner] << " has the Spy, they gain an extra favor token <3" << std::endl;
			suitorObjects[winner].GainToken();
			suitorObjects[winner].RemoveSpy();
			std::cout << suitor_names[winner] << " token count: " << suitorObjects[winner].GetTokenCount() << std::endl;
		}
	}
	//Give winner a favor token.
	suitorObjects[winner].GainToken();
	std::cout << suitor_names[winner] << " gains one[1] favor token <3" << std::endl;
	std::cout << suitor_names[winner] << " total tokens: " << suitorObjects[winner].GetTokenCount() << std::endl;
	//Prepare for next round.
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		suitorObjects[i].RemoveHandmaid();
	}
	if (suitorObjects[winner].GetTokenCount() < token_count_to_win)
	{
		++round_count;
		activeSuitorHands.clear();
		suitors.clear();
		down_pile.clear();
		up_pile.clear();
		active_suitor_count = 0;
		std::cout << "Moving on to the next round..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		ClearScreen();
	}
	if (suitorObjects[winner].GetTokenCount() == token_count_to_win)
	{
		std::cout << suitor_names[winner] << " has won the heart of the princess." << std::endl;
		std::cout << "-- GAME OVER --" << std::endl;
		activeSuitorHands.clear();
		suitors.clear();
		down_pile.clear();
		up_pile.clear();
		active_suitor_count = 0;
		game_over = true;
	}
}

//Game state.//

void PlayGame()
{
	InitialSetup();
	while (!game_over)
	{
		BeginRound();
		SuitorTurn();
		EndRound();
	}
}

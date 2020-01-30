/*
Jordan Sola 2019
Functions used in Main.cpp

TODO:
Continue cleaning up logic. 1/29/20 10:35PM CST
Test i++ L781, L785 instead of current ++i 1/30/20 8:13AM CST
Update vector member functions from vect.func() to func(vec) 1/30/20 8:16AM CST
*/

#include "Functions.h"
#include "SuitorClass.h"
#include "Resources.h"
#include <iostream>

//output functions

void print_player_name(int suitor)
{
	std::cout << "SUITOR[" << suitor << ']';
}
void clear_output_window()
{
	//Windows tested, untested on unix.
	std::cout << "\033[2J\033[1;1H";
}
void print_line_seperator()
{
	std::cout << "--" << std::endl;
}
void print_up_pile_cards()
{
	std::cout << "cards in up pile: " << std::endl;
	for (int i : upPile)
	{
		std::cout << cardNames[i] + ' ';
	}
	std::cout << std::endl;
	print_line_seperator();
}
void print_deck_size()
{
	std::cout << "Number of cards in the deck: " << playingDeck.size() << std::endl;
	print_line_seperator();
}
void print_players_with_spy_bonus()
{
	std::cout << "Spy bonus: " << std::endl;
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		if (!activeSuitorHands[i].empty())
		{
			if (suitorObjects[i].SpyStatus())
			{
				print_player_name(i);
			}
		}
	}
	std::cout << std::endl;
	print_line_seperator();
}
void print_active_players()
{
	std::cout << "Rival Suitors: " << std::endl;
	currentSuitor++;
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		if (!activeSuitorHands[i].empty() && suitors[i] != currentSuitor)
		{
			print_player_name(i);
		}
	}
	std::cout << std::endl;
	print_line_seperator();
	currentSuitor--;
}
void print_cards_in_hand(int suitor)
{
	std::vector<std::string> cardNames
	{
		"SPY[0]", "GUARD[1]", "PRIEST[2]", "BARON[3]", "HANDMAID[4]", "PRINCE[5]", "CHANCELLOR[6]", "KING[7]", "COUNTESS[8]", "PRINCESS[9]"
	};

	print_player_name(suitor);
	std::cout << " hand: " << std::endl;

	for (unsigned int i = 0; i < activeSuitorHands[suitor].size(); i++)
	{
		std::cout << cardNames[find_card_position_within_hand(suitor, i)] << " ";
	}
	std::cout << std::endl;
	print_line_seperator();
}

//card position functions

bool find_card_in_hand(int suitor, int card)
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
int find_card_position_within_hand(int suitor, int pos)
{
	//Return's position of card in Suitor's hand.
	cardPosition = activeSuitorHands[suitor][pos];
	return cardPosition;
}

//input checks

void clear_input()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool check_proper_card_input()
{
	//Input numbers cannot be lower than zero or higher than nine.
	if (cardNum >= spy && cardNum <= princess && std::cin) { return true; }
	else
	{
		std::cout << "Invalid input, please input a card value between 0 and 9." << std::endl;
		return false;
	}
}
bool check_proper_player_input()
{
	targetNum++;
	//Cannot input a number lower than one or a number larger than the number of active Suitors.
	if (targetNum >= 1 && targetNum <= activeSuitorHands.size() && std::cin)
	{
		targetNum--;
		return true;
	}
	else
	{
		std::cout << "Invalid input, please choose an active player by their number eg. SUITOR 1 would be 1." << std::endl;
		targetNum--;
		return false;
	}
}
bool check_proper_player_count()
{
	//Min number of Suitors is two and max number of suitors is six.
	if (activeSuitorCount >= minSuitorsPlaying && activeSuitorCount <= maxSuitorsPlaying && std::cin) { return true; }
	else { return false; }
}

//suitor status checks

bool check_countess_restriction()
{
	//When Prince or King and Countess are in hand, the Countess must be played.
	if (find_card_in_hand(currentSuitor, countess) && cardNum != countess)
	{
		if (find_card_in_hand(currentSuitor, prince) || find_card_in_hand(currentSuitor, king))
		{
			std::cout << "You have the " << cardNames[find_card_position_within_hand(currentSuitor, 0)]
				<< " and the " << cardNames[find_card_position_within_hand(currentSuitor, 1)]
				<< ". You MUST play the " << cardNames[countess] << " this turn." << std::endl;
			return true;
		}
		else { return false; }
	}
	else { return false; }
}
bool check_player_active()
{
	//Active Suitor check.
	if (!activeSuitorHands[targetNum].empty()) { return true; }
	else { return false; }
}
bool check_target_handmaid_protection()
{
	//Handmaid protection check.
	if (suitorObjects[targetNum].HandmaidStatus()) { return true; }
	else { return false; }
}
void choose_target_player(int target)
{
	//Guard, Priest, Baron, Prince, and King are cards that target other/current Suitors.
LOOP:
	print_active_players();
	print_player_name(currentSuitor);
	std::cout << " choose target suitor: " << std::endl;
	std::cin >> target;
	print_line_seperator();
	//Prompt duplicate Suitor selection.
	if (!tempInput.empty())
	{
		for (unsigned int i = 0; i < tempInput.size(); i++)
		{
			if (tempInput[i] == target)
			{
				std::cout << "You already chose ";
				print_player_name(tempInput[i]);
				std::cout << "] please choose a different Suitor." << std::endl;
				goto LOOP;
			}
		}
	}
	if (!check_proper_player_input())
	{
		clear_input();
		goto LOOP;
	}
	if (!check_player_active())
	{
		print_player_name(targetNum);
		std::cout << " is out." << std::endl;
		goto LOOP;
	}
	if (check_target_handmaid_protection())
	{
		//When there are two active Suitors and the other Suitor is protected the card either applies to the current Suitor or play moves on.
		if (activeSuitorCount == 2)
		{
			return;
		}
		else
		{
			print_player_name(targetNum);
			std::cout << " has Handmaid protection." << std::endl;
			tempInput.push_back(target);
			clear_input();
			goto LOOP;
		}
	}
	if (target == currentSuitor)
	{
		//Prince can apply to current Suitor.
		if (cardNum == prince)
		{
			return;
		}
		else
		{
			std::cout << "You cannot choose yourself." << std::endl;
			clear_input();
			goto LOOP;
		}
	}
}

//suitor modifiers

void switch_player_turn()
{
	//Move to next active Suitor after current Suitor's turn ends.
	std::cout << "Moving on to next active Suitor..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	clear_output_window();
	//Move to end of Suitor line if at beginning.
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
	//Skip Suitors that are out.
	if (activeSuitorHands[currentSuitor].empty())
	{
	LOOP:
		while (activeSuitorHands[currentSuitor].empty())
		{
			if (currentSuitor == suitors[0] - 1)
			{
				for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
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
void discard()
{
	//Discard played card from Suitor hand to up pile.
	print_player_name(currentSuitor);
	std::cout << " played " << cardNames[cardNum] << std::endl;
	print_line_seperator();
	upPile.push_back(cardNum);
	auto it = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
	activeSuitorHands[currentSuitor].erase(it);
}
void remove_player_from_play(int suitor)
{
	//Removing a Suitor from the game.
	for (unsigned int i = 0; i < activeSuitorHands[suitor].size(); i++)
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
void set_winning_token_count()
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

//deck modifiers

void shuffle_deck()
{
	random_shuffle(playingDeck.begin(), playingDeck.end());
}
void reset_deck()
{
	//Sets played deck cards to starting cards.
	playingDeck.assign(baseDeck.begin(), baseDeck.end());
}

//card functions

void Spy()
{
	suitorObjects[currentSuitor].GainSpy();
}
void Guard()
{
	//Current Suitor guesses what card a target Suitor has in hand. Correct guesses knock out the target Suitor.
LOOP:
	print_player_name(currentSuitor);
	std::cout << " guess a card: " << std::endl;
	std::cin >> cardNum;
	if (!check_proper_card_input())
	{
		clear_input();
		goto LOOP;
	}
	if (check_target_handmaid_protection())
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
		std::cout << "You can guess any card OTHER than a Guard." << std::endl;
		clear_input();
		goto LOOP;
	}
	if (activeSuitorHands[targetNum][0] == cardNum)
	{
		std::cout << "Match! " << suitorNames[targetNum] << " is out." << std::endl;
		remove_player_from_play(targetNum);
	}
	else
	{
		std::cout << "no match" << std::endl;
	}
}
void Priest()
{
	print_cards_in_hand(targetNum);
}
void Baron()
{
	//Current Suitor compares hand with a target Suitor, highest hand stays in the game.
	print_cards_in_hand(currentSuitor);
	print_cards_in_hand(targetNum);
	//If both hands are equal both Suitors remain and play moves on.
	if (activeSuitorHands[currentSuitor][0] == activeSuitorHands[targetNum][0])
	{
		std::cout << "Tie! Both suitors remain in the game." << std::endl;
		return;
	}
	else
	{
		tempVictor = std::max(activeSuitorHands[currentSuitor][0], activeSuitorHands[targetNum][0]);
		if (activeSuitorHands[currentSuitor][0] == tempVictor)
		{
			print_player_name(currentSuitor);
			std::cout << " is victorious! ";
			print_player_name(targetNum);
			std::cout << " is out!" << std::endl;
			remove_player_from_play(targetNum);
		}
		else {
			print_player_name(currentSuitor);
			std::cout << " is victorious! ";
			print_player_name(currentSuitor);
			std::cout << " is out!" << std::endl;
			remove_player_from_play(currentSuitor);
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
		choose_target_player(targetNum);
	}
	if (check_target_handmaid_protection())
	{
		//When there are two active Suitors the Prince must resolve on one of the Suitors.
		if (activeSuitorCount == 2)
		{
			//When target Suitor is Handmaid protected the Prince applies to the current Suitor.
			print_player_name(targetNum);
			std::cout << " has Handmaid protection." << std::endl;
			std::cout << "The Prince applies to you." << std::endl;
			if (find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), princess) != activeSuitorHands[currentSuitor].end())
			{
				std::cout << "You had the Princess! You're out!" << std::endl;
				remove_player_from_play(currentSuitor);
				return;
			}
			for (unsigned int i = 0; i < activeSuitorHands[currentSuitor].size(); i++)
			{
				upPile.push_back(activeSuitorHands[targetNum][i]);
			}
			activeSuitorHands[currentSuitor].clear();
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
			if (currentSuitor == humanSuitor)
			{
				print_cards_in_hand(currentSuitor);
			}
			return;
		}
		std::cout << suitorNames[targetNum] << " is untargetable." << std::endl;
		goto LOOPB;
	}
	if (find(activeSuitorHands[targetNum].begin(), activeSuitorHands[targetNum].end(), princess) != activeSuitorHands[targetNum].end())
	{
		print_player_name(targetNum);
		std::cout << " had the Princess! ";
		print_player_name(targetNum);
		std::cout << " is out!" << std::endl;
		remove_player_from_play(targetNum);
		return;
	}
	if (playingDeck.empty())
	{
		std::cout << suitorNames[targetNum] << " discards their hand, then redraws." << std::endl;
		for (unsigned int i = 0; i < activeSuitorHands[targetNum].size(); i++)
		{
			upPile.push_back(activeSuitorHands[targetNum][i]);
		}
		activeSuitorHands[targetNum].push_back(downPile[0]);
		downPile.erase(downPile.begin(), downPile.end());
		if (targetNum == currentSuitor && targetNum == humanSuitor)
		{
			print_cards_in_hand(currentSuitor);
		}
	}
	else
	{
		std::cout << suitorNames[targetNum] << " discards their hand, then redraws." << std::endl;
		for (unsigned int i = 0; i < activeSuitorHands[targetNum].size(); i++)
		{
			upPile.push_back(activeSuitorHands[targetNum][i]);
		}
		activeSuitorHands[targetNum].erase(activeSuitorHands[targetNum].begin(), activeSuitorHands[targetNum].end());
		activeSuitorHands[targetNum].push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
		if (targetNum == currentSuitor && targetNum == humanSuitor)
		{
			print_cards_in_hand(currentSuitor);
		}
	}
}
void Chancellor()
{
	//Current Suitor draws two cards from the top of the deck and returns two cards to the bottom of the deck.
	if (playingDeck.empty())
	{
		std::cout << "The deck is empty. The " << cardNames[6] << " plays with no effect." << std::endl;
		return;
	}
	if (playingDeck.size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
		}
		print_cards_in_hand(currentSuitor);
	LOOP:
		std::cout << "First card to put back: " << std::endl;
		std::cin >> cardNum;
		auto itA = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
		if (!check_proper_card_input())
		{
			clear_input();
			goto LOOP;
		}
		if (!find_card_in_hand(currentSuitor, cardNum))
		{
			clear_input();
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
				print_cards_in_hand(currentSuitor);
			}
		}
	LOOPA:
		std::cout << "Second card to put back: " << std::endl;
		std::cin >> cardNum;
		auto itB = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
		if (!check_proper_card_input())
		{
			clear_input();
			goto LOOPA;
		}
		if (!find_card_in_hand(currentSuitor, cardNum))
		{
			clear_input();
			goto LOOPA;
		}
		else
		{
			playingDeck.push_back(cardNum);
			if (itB != activeSuitorHands[currentSuitor].end())
			{
				activeSuitorHands[currentSuitor].erase(itB);
			}
			else
			{
				print_cards_in_hand(currentSuitor);
			}
		}
	}
	if (playingDeck.size() == 1)
	{
		std::cout << "There is only one card in the deck." << std::endl;
		for (int i = 0; i < 1; i++)
		{
			activeSuitorHands[currentSuitor].push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
		}
		print_cards_in_hand(currentSuitor);
	LOOPB:
		std::cout << "Card to put back: " << std::endl;
		std::cin >> cardNum;
		auto itC = find(activeSuitorHands[currentSuitor].begin(), activeSuitorHands[currentSuitor].end(), cardNum);
		if (!check_proper_card_input())
		{
			clear_input();
			goto LOOPB;
		}
		if (!find_card_in_hand(currentSuitor, cardNum))
		{
			clear_input();
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
				std::cout << "You discarded the " << cardNames[cardNum] << " you are out!" << std::endl;
				remove_player_from_play(currentSuitor);
				return;
			}
			else
			{
				print_cards_in_hand(currentSuitor);
			}
		}
	}
}
void King(int agressor, int victim)
{
	//Swaps current Suitor's hand with Target Suitor's hand.
	activeSuitorHands[agressor].swap(activeSuitorHands[victim]);
	print_player_name(agressor);
	std::cout << " 's hand is now..." << std::endl;
	print_cards_in_hand(agressor);
	print_player_name(victim);
	std::cout << " 's hand is now..." << std::endl;
	print_cards_in_hand(victim);
}
void Princess()
{
	//When a Suitor discards the Princess they are out.
	std::cout << suitorNames[currentSuitor] << " is out!" << std::endl;
	remove_player_from_play(1);
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
		King(currentSuitor, targetNum);
		break;
	case 9:
		Princess();
		break;
	}
}

//game state functions

void initial_game_setup()
{
	//Tasks that are performed at the start of every GAME.
	std::cout << "-- WELCOME TO LOVE LETTER --" << std::endl;
LOOP:
	std::cout << "How many suitors will be playing: " << std::endl;
	std::cin >> activeSuitorCount;
	print_line_seperator();
	if (check_proper_player_count())
	{
		originalSuitorCount = activeSuitorCount;
		set_winning_token_count();
		//Add hand vectors to a vector container.
		for (i = 1; i < activeSuitorCount + 1; ++i)
		{
			suitors.push_back(i);
		}
		for (i = 1; i < activeSuitorCount + 1; ++i)
		{
			std::vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		currentSuitor = 0;
		humanSuitor = 0;
	}
	else
	{
		std::cout << "Invalid input, please input a number of Suitors between 2 and 6." << std::endl;
		clear_input();
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
		std::cout << suitorNames.at(i) << " guess: " << std::endl;
		std::cin >> guess;
		if (guess <= activeSuitorHands.size() && guess >= 1)
		{
			//Duplicate guess.
			for (unsigned int i = 0; i < tempVector.size(); ++i)
			{
				if (guess == tempVector.at(i))
				{
					std::cout << guess << " has already been guessed. Try again." << std::endl;
					clear_input();
					goto LOOPB;
				}
			}
			//Correct guess.
			if (guess == target)
			{
				clear_output_window();
				std::cout << suitorNames.at(i) << " got it!" << std::endl;
				currentSuitor = i;
				break;
			}
			//Add previous guesses to be checked as duplicates.
			tempVector.push_back(guess);
		}
		else
		{
			std::cout << "Invalid input, please input a guess between 1 and " << activeSuitorCount << '.' << std::endl;
			clear_input();
			goto LOOPA;
		}
	}
	tempVector.clear();
}
void begin_game_round()
{
	reset_deck();
	shuffle_deck();
	std::cout << "-- ROUND " << roundCount << " --" << std::endl;
	//check for starting round
	if (roundCount != startingRound)
	{
		//round is > first round
		activeSuitorCount = originalSuitorCount;
		for (i = 1; i < activeSuitorCount + 1; ++i) //test i++ instead
		{
			suitors.push_back(i);
		}
		for (i = 1; i < activeSuitorCount + 1; ++i) //test i++ instead
		{
			std::vector<int> hand;
			activeSuitorHands.push_back(hand);
		}
		std::cout << suitorNames.at(winner) << " won the last round. " << suitorNames.at(winner) << " goes first." << std::endl;
		currentSuitor = winner;
		winner = 0;
	}
	//Check for two Suitor game.
	if (activeSuitorCount == minSuitorsPlaying)
	{
		downPile.push_back(playingDeck[0]);
		playingDeck.erase(begin(playingDeck));
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
	for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
	{
		activeSuitorHands.at(i).push_back(playingDeck[0]);
		playingDeck.erase(playingDeck.begin());
	}
}
void player_turn()
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
		//Check for empty deck so these functions don't duplicate.
		if (!playingDeck.empty())
		{
			print_deck_size();
			print_active_players();
			print_up_pile_cards();
			print_players_with_spy_bonus();
			print_cards_in_hand(currentSuitor);
		}
		else
		{
			return;
		}
		//Current Suitor draws a card to their hand.
		std::cout << suitorNames.at(currentSuitor) << " draw a card (d): " << std::endl;
		std::cin >> input;
		print_line_seperator();
		if (input == 'd')
		{
			activeSuitorHands.at(currentSuitor).push_back(playingDeck[0]);
			playingDeck.erase(playingDeck.begin());
		}
		else
		{
			std::cout << "Invalid input, please input 'd' to draw a card." << std::endl;
			clear_input();
			goto LOOP;
		}
	LOOPA:
		print_cards_in_hand(currentSuitor);
		//Current Suitor plays a card from their hand.
		print_player_name(currentSuitor);
		std::cout << " play a card: " << std::endl;
		std::cin >> cardNum;
		print_line_seperator();
		if (!check_proper_card_input())
		{
			clear_input();
			goto LOOPA;
		}
		if (!find_card_in_hand(currentSuitor, cardNum))
		{
			std::cout << "You do not have " << cardNames[cardNum] << " in your hand." << std::endl;
			goto LOOPA;
		}
		if (check_countess_restriction())
		{
			clear_input();
			goto LOOPA;
		}
		else { discard(); }
		//Card resolves.
		if (cardNum == guard || cardNum == priest || cardNum == baron || cardNum == king)
		{
			choose_target_player(targetNum);
			if (check_target_handmaid_protection() && activeSuitorCount == 2)
			{
				print_player_name(targetNum);
				std::cout << " has Handmaid protection." << std::endl;
				print_line_seperator();
				switch_player_turn();
				goto LOOP;
			}
			if (suitorsWithHandmaid.size() == activeSuitorCount--)
			{
				print_player_name(targetNum);
				std::cout << " has Handmaid protection." << std::endl;
				std::cout << "All target Suitors have Handmaid protection." << std::endl;
				print_line_seperator();
				switch_player_turn();
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
		if (activeSuitorCount > 1)
		{
			switch_player_turn();
		}
		tempInput.clear();
	}
}
void end_game_round()
{
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
		clear_output_window();
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

//game state

void play_game()
{
	initial_game_setup();
	while (!gameOver)
	{
		begin_game_round();
		player_turn();
		end_game_round();
	}
}

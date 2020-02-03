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

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include "global_resources.h"
#include "player_class.h"

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::vector;
using std::string;

Suitor suitor1, suitor2, suitor3, suitor4, suitor5, suitor6;

vector<Suitor> suitor_objects
	{ suitor1, suitor2, suitor3, suitor4, suitor5, suitor6 };

//input

void ClearInput()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool ProperCardInput()
{
	//Input numbers cannot be lower than zero or higher than nine.
	if (card_num >= spy && card_num <= princess && cin) { return true; }
	else
	{
		cout << "Invalid input, please input a card value between 0 and 9." << endl;
		return false;
	}
}
bool ProperPlayerInput()
{
	target_hum++;
	//Cannot input a number lower than one or a number larger than the number of active Suitors.
	if (target_hum >= 1 && target_hum <= active_player_hands.size() && cin)
	{
		target_hum--;
		return true;
	}
	else
	{
		cout << "Invalid input, please choose an active player by their number eg. SUITOR 1 would be 1." << endl;
		target_hum--;
		return false;
	}
}
bool ProperPlayerCount()
{
	//Min number of Suitors is two and max number of suitors is six.
	if (active_player_count >= min_players && active_player_count <= max_players && cin) { return true; }
	else { return false; }
}
int TakePlayerCount()
{
	int count;
	cout << "How many suitors will be playing: " << endl;
	cin >> count;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "invalid input..." << endl;
		cout << "please enter an integer" << endl;
		cout << "How many suitors will be playing: " << endl;
		cin >> count;
	}
	return count;
	//Does not account for float input.
}
int CheckPlayerCount(int input)
{
	while (input < 2 || input > 6)
	{
		cout << "invalid input..." << endl;
		cout << "minimum # of players: 2 - maximum # of players: 6 - your input: " << input << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		input = TakePlayerCount();
	}
	return input;
}
int GivePlayerCount()
{
	int raw_count = TakePlayerCount();
	int processed_count = CheckPlayerCount(raw_count);
	return processed_count;
}

//card position

bool CardInHand(int suitor, int card)
{
	//Checks for card selection in Suitor's hand.
	if (find(active_player_hands[suitor].begin(), active_player_hands[suitor].end(), card) != active_player_hands[suitor].end())
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
	car_position = active_player_hands[suitor][pos];
	return car_position;
}

//output

void ReturnPlayer(int suitor)
{
	cout << "SUITOR[" << suitor << ']';
}
void ClearScreen()
{
	//Windows tested, untested on unix.
	cout << "\033[2J\033[1;1H";
}
void PrintSeperator()
{
	cout << "--" << endl;
}
void PrintUpPile()
{
	cout << "cards in up pile: " << endl;
	for (int i : up_pile)
	{
		cout << card_names[i] + ' ';
	}
	cout << endl;
	PrintSeperator();
}
void PrintDeckSize()
{
	cout << "Number of cards in the deck: " << playing_deck.size() << endl;
	PrintSeperator();
}
void PrintPlayersWithSpy()
{
	cout << "Spy bonus: " << endl;
	for (unsigned int i = 0; i < active_player_hands.size(); i++)
	{
		if (!active_player_hands[i].empty())
		{
			if (suitor_objects[i].SpyStatus())
			{
				ReturnPlayer(i);
			}
		}
	}
	cout << endl;
	PrintSeperator();
}
void PrintActivePlayers()
{
	cout << "Rival Suitors: " << endl;
	current_player++;
	for (unsigned int i = 0; i < active_player_hands.size(); i++)
	{
		if (!active_player_hands[i].empty() && players[i] != current_player)
		{
			ReturnPlayer(i);
		}
	}
	cout << endl;
	PrintSeperator();
	current_player--;
}
void PrintHand(int suitor)
{
	vector<string> cardNames
	{
		"SPY[0]", "GUARD[1]", "PRIEST[2]", "BARON[3]", "HANDMAID[4]", "PRINCE[5]", "CHANCELLOR[6]", "KING[7]", "COUNTESS[8]", "PRINCESS[9]"
	};

	ReturnPlayer(suitor);
	cout << " hand: " << endl;

	for (unsigned int i = 0; i < active_player_hands[suitor].size(); i++)
	{
		cout << cardNames[HandPosition(suitor, i)] << " ";
	}
	cout << endl;
	PrintSeperator();
}

//suitor status

bool CountessRestriction()
{
	//When Prince or King and Countess are in hand, the Countess must be played.
	if (CardInHand(current_player, countess) && card_num != countess)
	{
		if (CardInHand(current_player, prince) || CardInHand(current_player, king))
		{
			cout << "You have the " << card_names[HandPosition(current_player, 0)]
				<< " and the " << card_names[HandPosition(current_player, 1)]
				<< ". You MUST play the " << card_names[countess] << " this turn." << endl;
			return true;
		}
		else { return false; }
	}
	else { return false; }
}
bool IsPlayerPlaying()
{
	//Active Suitor check.
	if (!active_player_hands[target_hum].empty()) { return true; }
	else { return false; }
}
bool TargetHandmaidProtected()
{
	//Handmaid protection check.
	if (suitor_objects[target_hum].HandmaidStatus()) { return true; }
	else { return false; }
}
void ChooseTargetPlayer(int target)
{
	//Guard, Priest, Baron, Prince, and King are cards that target other/current Suitors.
LOOP:
	PrintActivePlayers();
	ReturnPlayer(current_player);
	cout << " choose target suitor: " << endl;
	cin >> target;
	PrintSeperator();
	//Prompt duplicate Suitor selection.
	if (!temp_input.empty())
	{
		for (unsigned int i = 0; i < temp_input.size(); i++)
		{
			if (temp_input[i] == target)
			{
				cout << "You already chose ";
				ReturnPlayer(temp_input[i]);
				cout << "] please choose a different Suitor." << endl;
				goto LOOP;
			}
		}
	}
	if (!ProperPlayerInput())
	{
		ClearInput();
		goto LOOP;
	}
	if (!IsPlayerPlaying())
	{
		ReturnPlayer(target_hum);
		cout << " is out." << endl;
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		//When there are two active Suitors and the other Suitor is protected the card either applies to the current Suitor or play moves on.
		if (active_player_count == 2)
		{
			return;
		}
		else
		{
			ReturnPlayer(target_hum);
			cout << " has Handmaid protection." << endl;
			temp_input.push_back(target);
			ClearInput();
			goto LOOP;
		}
	}
	if (target == current_player)
	{
		//Prince can apply to current Suitor.
		if (card_num == prince)
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

//suitor modifiers

void SwitchPlayer()
{
	//Move to next active Suitor after current Suitor's turn ends.
	cout << "Moving on to next active Suitor..." << endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	ClearScreen();
	//Move to end of Suitor line if at beginning.
	if (current_player == players[0] - 1)
	{
		for (unsigned int i = 1; i < active_player_hands.size(); i++)
		{
			current_player++;
		}
		if (!active_player_hands[current_player].empty())
		{
			return;
		}
	}
	//Skip Suitors that are out.
	if (active_player_hands[current_player].empty())
	{
	LOOP:
		while (active_player_hands[current_player].empty())
		{
			if (current_player == players[0] - 1)
			{
				for (unsigned int i = 0; i < active_player_hands.size(); i++)
				{
					current_player++;
				}
			}
			if (active_player_hands[current_player].empty())
			{
				current_player--;
			}
		}
		return;
	}
	else
	{
		current_player--;
		if (active_player_hands[current_player].empty())
		{
			goto LOOP;
		}
	}
}
void DiscardPlayedCard()
{
	//Discard played card from Suitor hand to up pile.
	ReturnPlayer(current_player);
	cout << " played " << card_names[card_num] << endl;
	PrintSeperator();
	up_pile.push_back(card_num);
	auto it = find(active_player_hands[current_player].begin(), active_player_hands[current_player].end(), card_num);
	active_player_hands[current_player].erase(it);
}
void RemovePlayer(int suitor)
{
	//Removing a Suitor from the game.
	for (unsigned int i = 0; i < active_player_hands[suitor].size(); i++)
	{
		up_pile.push_back(active_player_hands[suitor][i]);
	}
	active_player_hands[suitor].clear();
	if (suitor_objects[suitor].SpyStatus())
	{
		suitor_objects[suitor].RemoveSpy();
	}
	active_player_count--;
}
void SetWinningTokenCount()
{
	//Token counts change by the number of Suitors that start the game.
	switch (active_player_count)
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

//deck modifiers

void ShuffleDeck()
{
	random_shuffle(playing_deck.begin(), playing_deck.end());
}
void ResetDeck()
{
	//Sets played deck cards to starting cards.
	playing_deck.assign(base_deck.begin(), base_deck.end());
}

//card actions

void Spy()
{
	suitor_objects[current_player].GainSpy();
}
void Guard()
{
	//Current Suitor guesses what card a target Suitor has in hand. Correct guesses knock out the target Suitor.
LOOP:
	ReturnPlayer(current_player);
	cout << " guess a card: " << endl;
	cin >> card_num;
	if (!ProperCardInput())
	{
		ClearInput();
		goto LOOP;
	}
	if (TargetHandmaidProtected())
	{
		if (active_player_count == 2)
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
		cout << "You can guess any card OTHER than a Guard." << endl;
		ClearInput();
		goto LOOP;
	}
	if (active_player_hands[target_hum][0] == card_num)
	{
		cout << "Match! " << player_names[target_hum] << " is out." << endl;
		RemovePlayer(target_hum);
	}
	else
	{
		cout << "no match" << endl;
	}
}
void Priest()
{
	PrintHand(target_hum);
}
void Baron()
{
	//Current Suitor compares hand with a target Suitor, highest hand stays in the game.
	PrintHand(current_player);
	PrintHand(target_hum);
	//If both hands are equal both Suitors remain and play moves on.
	if (active_player_hands[current_player][0] == active_player_hands[target_hum][0])
	{
		cout << "Tie! Both suitors remain in the game." << endl;
		return;
	}
	else
	{
		temp_victor = max(active_player_hands[current_player][0], active_player_hands[target_hum][0]);
		if (active_player_hands[current_player][0] == temp_victor)
		{
			ReturnPlayer(current_player);
			cout << " is victorious! ";
			ReturnPlayer(target_hum);
			cout << " is out!" << endl;
			RemovePlayer(target_hum);
		}
		else {
			ReturnPlayer(current_player);
			cout << " is victorious! ";
			ReturnPlayer(current_player);
			cout << " is out!" << endl;
			RemovePlayer(current_player);
		}
	}
}
void Handmaid()
{
	//Suitors with Handmaid protection are untargetable until the beginning of their next turn.
	suitor_objects[current_player].GainHandmaid();
	players_with_handmaid.push_back(current_player);
}
void Prince()
{
	//Current Suitor can discard their hand, or Target Suitor's hand, and draw a new hand.
LOOPB:
	if (current_player == human_player)
	{
		ChooseTargetPlayer(target_hum);
	}
	if (TargetHandmaidProtected())
	{
		//When there are two active Suitors the Prince must resolve on one of the Suitors.
		if (active_player_count == 2)
		{
			//When target Suitor is Handmaid protected the Prince applies to the current Suitor.
			ReturnPlayer(target_hum);
			cout << " has Handmaid protection." << endl;
			cout << "The Prince applies to you." << endl;
			if (find(active_player_hands[current_player].begin(), active_player_hands[current_player].end(), princess) != active_player_hands[current_player].end())
			{
				cout << "You had the Princess! You're out!" << endl;
				RemovePlayer(current_player);
				return;
			}
			for (unsigned int i = 0; i < active_player_hands[current_player].size(); i++)
			{
				up_pile.push_back(active_player_hands[target_hum][i]);
			}
			active_player_hands[current_player].clear();
			active_player_hands[current_player].push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
			if (current_player == human_player)
			{
				PrintHand(current_player);
			}
			return;
		}
		cout << player_names[target_hum] << " is untargetable." << endl;
		goto LOOPB;
	}
	if (find(active_player_hands[target_hum].begin(), active_player_hands[target_hum].end(), princess) != active_player_hands[target_hum].end())
	{
		ReturnPlayer(target_hum);
		cout << " had the Princess! ";
		ReturnPlayer(target_hum);
		cout << " is out!" << endl;
		RemovePlayer(target_hum);
		return;
	}
	if (playing_deck.empty())
	{
		cout << player_names[target_hum] << " discards their hand, then redraws." << endl;
		for (unsigned int i = 0; i < active_player_hands[target_hum].size(); i++)
		{
			up_pile.push_back(active_player_hands[target_hum][i]);
		}
		active_player_hands[target_hum].push_back(down_pile[0]);
		down_pile.erase(down_pile.begin(), down_pile.end());
		if (target_hum == current_player && target_hum == human_player)
		{
			PrintHand(current_player);
		}
	}
	else
	{
		cout << player_names[target_hum] << " discards their hand, then redraws." << endl;
		for (unsigned int i = 0; i < active_player_hands[target_hum].size(); i++)
		{
			up_pile.push_back(active_player_hands[target_hum][i]);
		}
		active_player_hands[target_hum].erase(active_player_hands[target_hum].begin(), active_player_hands[target_hum].end());
		active_player_hands[target_hum].push_back(playing_deck[0]);
		playing_deck.erase(playing_deck.begin());
		if (target_hum == current_player && target_hum == human_player)
		{
			PrintHand(current_player);
		}
	}
}
void Chancellor()
{
	//Current Suitor draws two cards from the top of the deck and returns two cards to the bottom of the deck.
	if (playing_deck.empty())
	{
		cout << "The deck is empty. The " << card_names[6] << " plays with no effect." << endl;
		return;
	}
	if (playing_deck.size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			active_player_hands[current_player].push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
		}
		PrintHand(current_player);
	LOOP:
		cout << "First card to put back: " << endl;
		cin >> card_num;
		auto itA = find(active_player_hands[current_player].begin(), active_player_hands[current_player].end(), card_num);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOP;
		}
		if (!CardInHand(current_player, card_num))
		{
			ClearInput();
			goto LOOP;
		}
		else
		{
			playing_deck.push_back(card_num);
			if (itA != active_player_hands[current_player].end())
			{
				active_player_hands[current_player].erase(itA);
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
				PrintHand(current_player);
			}
		}
	LOOPA:
		cout << "Second card to put back: " << endl;
		cin >> card_num;
		auto itB = find(active_player_hands[current_player].begin(), active_player_hands[current_player].end(), card_num);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPA;
		}
		if (!CardInHand(current_player, card_num))
		{
			ClearInput();
			goto LOOPA;
		}
		else
		{
			playing_deck.push_back(card_num);
			if (itB != active_player_hands[current_player].end())
			{
				active_player_hands[current_player].erase(itB);
			}
			else
			{
				PrintHand(current_player);
			}
		}
	}
	if (playing_deck.size() == 1)
	{
		cout << "There is only one card in the deck." << endl;
		for (int i = 0; i < 1; i++)
		{
			active_player_hands[current_player].push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
		}
		PrintHand(current_player);
	LOOPB:
		cout << "Card to put back: " << endl;
		cin >> card_num;
		auto itC = find(active_player_hands[current_player].begin(), active_player_hands[current_player].end(), card_num);
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPB;
		}
		if (!CardInHand(current_player, card_num))
		{
			ClearInput();
			goto LOOPB;
		}
		else
		{
			playing_deck.push_back(card_num);
			if (itC != active_player_hands[current_player].end())
			{
				active_player_hands[current_player].erase(itC);
			}
			if (card_num == 9)
			{
				cout << "You discarded the " << card_names[card_num] << " you are out!" << endl;
				RemovePlayer(current_player);
				return;
			}
			else
			{
				PrintHand(current_player);
			}
		}
	}
}
void King(int agressor, int victim)
{
	//Swaps current Suitor's hand with Target Suitor's hand.
	active_player_hands[agressor].swap(active_player_hands[victim]);
	ReturnPlayer(agressor);
	cout << " 's hand is now..." << endl;
	PrintHand(agressor);
	ReturnPlayer(victim);
	cout << " 's hand is now..." << endl;
	PrintHand(victim);
}
void Princess()
{
	//When a Suitor discards the Princess they are out.
	cout << player_names[current_player] << " is out!" << endl;
	RemovePlayer(1);
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
		King(current_player, target_hum);
		break;
	case 9:
		Princess();
		break;
	}
}

//game states

void InitialSetup()
{
	//Tasks that are performed at the start of every GAME.
	active_player_count = GivePlayerCount();

	original_player_count = active_player_count;
	SetWinningTokenCount();
	//Add hand vectors to a vector container.
	for (i = 1; i < active_player_count + 1; ++i)
	{
		players.push_back(i);
	}
	for (i = 1; i < active_player_count + 1; ++i)
	{
		vector<int> hand;
		active_player_hands.push_back(hand);
	}
	current_player = 0;
	human_player = 0;

	PrintSeperator();
	
	//Set up the target number Suitors will need to guess correctly to go first.
	srand((int)time(NULL));
	int target = rand() % active_player_hands.size() + 1;
	//Prompt and record all Suitor guesses, check if they are correct and if they are duplicates of previous guesses.
	cout << "I have a suitor number (1 - " << active_player_hands.size() << ") in my head. Guess it!" << endl;
LOOPA:
	for (unsigned int i = 0; i < active_player_hands.size() + 1; ++i)
	{
	LOOPB:
		cout << player_names.at(i) << " guess: " << endl;
		cin >> guess;
		if (guess <= active_player_hands.size() && guess >= 1)
		{
			//Duplicate guess.
			for (unsigned int i = 0; i < temp_vector.size(); ++i)
			{
				if (guess == temp_vector.at(i))
				{
					cout << guess << " has already been guessed. Try again." << endl;
					ClearInput();
					goto LOOPB;
				}
			}
			//Correct guess.
			if (guess == target)
			{
				ClearScreen();
				cout << player_names.at(i) << " got it!" << endl;
				current_player = i;
				break;
			}
			//Add previous guesses to be checked as duplicates.
			temp_vector.push_back(guess);
		}
		else
		{
			cout << "Invalid input, please input a guess between 1 and " << active_player_count << '.' << endl;
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
	cout << "-- ROUND " << round_count << " --" << endl;
	//Check for starting round.
	if (round_count != starting_round)
	{
		//Round is second round or above.
		active_player_count = original_player_count;
		for (i = 1; i < active_player_count + 1; ++i)
		{
			players.push_back(i);
		}
		for (i = 1; i < active_player_count + 1; ++i)
		{
			vector<int> hand;
			active_player_hands.push_back(hand);
		}
		cout << player_names.at(winner) << " won the last round. " << player_names.at(winner) << " goes first." << endl;
		current_player = winner;
		winner = 0;
	}
	//Check for two Suitor game.
	if (active_player_count == min_players)
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
	for (unsigned int i = 0; i < active_player_hands.size(); i++)
	{
		active_player_hands.at(i).push_back(playing_deck[0]);
		playing_deck.erase(playing_deck.begin());
	}
}
void PlayerTurn()
{
LOOP:
	//More than one Suitor must be playing and the deck must not be empty.
	while (active_player_count > 1 && !playing_deck.empty())
	{
		//Remove Handmaid protection from previous turn.
		if (suitor_objects[current_player].HandmaidStatus())
		{
			suitor_objects[current_player].RemoveHandmaid();
			auto itD = find(players_with_handmaid.begin(), players_with_handmaid.end(), current_player);
			players_with_handmaid.erase(itD);
		}
		//Check for empty deck so these functions don't duplicate.
		if (!playing_deck.empty())
		{
			PrintDeckSize();
			PrintActivePlayers();
			PrintUpPile();
			PrintPlayersWithSpy();
			PrintHand(current_player);
		}
		else
		{
			return;
		}
		//Current Suitor draws a card to their hand.
		cout << player_names.at(current_player) << " draw a card (d): " << endl;
		cin >> input;
		PrintSeperator();
		if (input == 'd')
		{
			active_player_hands.at(current_player).push_back(playing_deck[0]);
			playing_deck.erase(playing_deck.begin());
		}
		else
		{
			cout << "Invalid input, please input 'd' to draw a card." << endl;
			ClearInput();
			goto LOOP;
		}
	LOOPA:
		PrintHand(current_player);
		//Current Suitor plays a card from their hand.
		ReturnPlayer(current_player);
		cout << " play a card: " << endl;
		cin >> card_num;
		PrintSeperator();
		if (!ProperCardInput())
		{
			ClearInput();
			goto LOOPA;
		}
		if (!CardInHand(current_player, card_num))
		{
			cout << "You do not have " << card_names[card_num] << " in your hand." << endl;
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
			ChooseTargetPlayer(target_hum);
			if (TargetHandmaidProtected() && active_player_count == 2)
			{
				ReturnPlayer(target_hum);
				cout << " has Handmaid protection." << endl;
				PrintSeperator();
				SwitchPlayer();
				goto LOOP;
			}
			if (players_with_handmaid.size() == active_player_count - 1)
			{
				ReturnPlayer(target_hum);
				cout << " has Handmaid protection." << endl;
				cout << "All target Suitors have Handmaid protection." << endl;
				PrintSeperator();
				SwitchPlayer();
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
		if (active_player_count > 1)
		{
			SwitchPlayer();
		}
		temp_input.clear();
	}
}
void EndRound()
{
	//When the deck runs out.
	if (playing_deck.empty())
	{
		cout << "The deck is empty, suitors compare hands" << endl;
		for (unsigned int i = 0; i < active_player_hands.size(); i++)
		{
			//Print remaining Suitors.
			if (!active_player_hands[i].empty())
			{
				cout << player_names[i] << " hand: " << active_player_hands[i][0] << endl;
			}
		}
		//Assign Suitor with highest hand to winner.
		for (unsigned int i = 0; i < active_player_hands.size(); i++)
		{
			if (!active_player_hands[i].empty())
			{
				if (winner < active_player_hands[i][0])
				{
					winner = active_player_hands[i][0];
				}
			}
		}
		//Assign winner as a Suitor integer.
		for (unsigned int i = 0; i < active_player_hands.size(); i++)
		{
			if (!active_player_hands[i].empty() && active_player_hands[i][0] == winner)
			{
				winner = i;
				break;
			}
		}
		//Check for Spy bonus, give Spy bonus token, no Spies, or duplicate Spies.
		if (active_player_count > 1)
		{
			for (unsigned int i = 0; i < active_player_hands.size(); i++)
			{
				if (suitor_objects[i].SpyStatus())
				{
					temp_vector.push_back(i);
				}
			}
			if (temp_vector.size() > 1)
			{
				cout << "Multiple suitors had the Spy. No one gets a bonus." << endl;
			}
			if (temp_vector.size() == 1)
			{
				cout << player_names.at(temp_vector[0]) << " Has the Spy, they gain an extra favor token <3" << endl;
				suitor_objects.at(temp_vector[0]).GainToken();
				cout << player_names.at(temp_vector[0]) << " token count: " << suitor_objects.at(temp_vector[0]).GetTokenCount() << endl;
			}
			if (temp_vector.empty())
			{
				cout << "No one had the Spy this round." << endl;
			}
		}
	}
	//When there is one Suitor remaining.
	else
	{
		//Assign winner as a Suitor integer.
		for (unsigned int i = 0; i < active_player_hands.size(); i++)
		{
			if (!active_player_hands[i].empty())
			{
				winner = i;
			}
		}
		cout << "Round over. " << player_names[winner] << " is the last suitor standing." << endl;
		//Check for Spy bonus and give bonus token.
		if (suitor_objects[winner].SpyStatus())
		{
			cout << player_names[winner] << " has the Spy, they gain an extra favor token <3" << endl;
			suitor_objects[winner].GainToken();
			suitor_objects[winner].RemoveSpy();
			cout << player_names[winner] << " token count: " << suitor_objects[winner].GetTokenCount() << endl;
		}
	}
	//Give winner a favor token.
	suitor_objects[winner].GainToken();
	cout << player_names[winner] << " gains one[1] favor token <3" << endl;
	cout << player_names[winner] << " total tokens: " << suitor_objects[winner].GetTokenCount() << endl;
	//Prepare for next round.
	for (unsigned int i = 0; i < active_player_hands.size(); i++)
	{
		suitor_objects[i].RemoveHandmaid();
	}
	if (suitor_objects[winner].GetTokenCount() < token_count_to_win)
	{
		++round_count;
		active_player_hands.clear();
		players.clear();
		down_pile.clear();
		up_pile.clear();
		active_player_count = 0;
		cout << "Moving on to the next round..." << endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		ClearScreen();
	}
	if (suitor_objects[winner].GetTokenCount() == token_count_to_win)
	{
		cout << player_names[winner] << " has won the heart of the princess." << endl;
		cout << "-- GAME OVER --" << endl;
		active_player_hands.clear();
		players.clear();
		down_pile.clear();
		up_pile.clear();
		active_player_count = 0;
		game_over = true;
	}
}
void PlayGame()
{
	InitialSetup();
	while (!game_over)
	{
		BeginRound();
		PlayerTurn();
		EndRound();
	}
}


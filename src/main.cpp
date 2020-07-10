#include "deck.h"
#include "player.h"
#include "reference.h"
#include "game_state.h"
#include "input_check.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::any_of;
using std::cin;
using std::cout;
using std::none_of;
using std::sort;
using std::to_string;
using std::vector;

int main()
{
	// game state
	GameState gameState;

	// checks
	InputCheck inputCheck;

	// Tasks that are performed at the start of every GAME.
	cout << "-- WELCOME TO LOVE LETTER --\n";

	// starting player count
	bool pass_input_check = false;
	int player_count = 0;
	while (!pass_input_check)
	{
		cout << "How many suitors will be playing: ";
		cin >> player_count;

		// set players
		if (inputCheck.CheckStartingPlayerCount(player_count))
		{
			pass_input_check = true;
		}
		else
		{
			cout << "Please input a number of Suitors between 2 and 6.\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	gameState.SetPlayers(player_count);

	// game loop
	bool game_over = false;
	while (!game_over)
	{
		Deck deck;

		deck.Set();
		deck.Shuffle();

		cout << "-- ROUND " << gameState.round_count_ << " --\n";

		// second round and above: reset player stats
		if (gameState.round_count_ > 1)
		{
			for (Player &i : gameState.players_)
			{
				i.Reset();
			}
		}

		Deck aside;

		// discard to down pile
		aside.Insert(deck.GetCard(0));

		Deck discard;

		// two player game: discard two cards
		if (gameState.players_.size() == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				discard.Insert(deck.GetCard(0));
			}
		}

		// deal starting hand
		for (Player &i : gameState.players_)
		{
			i.Draw(deck.GetCard(0));
		}

		// player turn
		bool session_end = false;
		while (!session_end)
		{
			for (Player &iPlayer : gameState.players_)
			{
				// player must be playing
				if (iPlayer.Status())
				{
					// remove handmaid protection
					iPlayer.SetProtection(0);

					// draw input check
					bool check_passed = false;
					while (!check_passed)
					{
						cout << iPlayer.GetName() << " draw a card (d): ";
						char draw = ' ';
						cin >> draw;
						if (draw == 'd')
						{
							break;
						}
						else
						{
							cout << "Invalid input.\n";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}

					// current player draw card
					iPlayer.Draw(deck.GetCard(0));

					cout << "\nDeck size: \n";
					cout << deck.Size() << '\n';

					cout << "\nDiscard pile:\n";
					discard.Print();

					cout << "\nOpponents:\n";
					for (size_t i = 0; i < gameState.players_.size(); i++)
					{
						if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != iPlayer.GetValue())
						{
							cout << gameState.players_.at(i).GetName() << '\n';
						}
						else
						{
							if (gameState.players_.at(i).GetValue() != iPlayer.GetValue())
							{
								if (i == gameState.players_.size() - 1)
								{
									cout << gameState.players_.at(i).GetName() << '\n';
								}
								else
								{
									cout << gameState.players_.at(i).GetName() << ", ";
								}
							}
						}
					}

					// print opponents with Handmaid protection
					cout << "\nHandmaid protection:\n";
					for (size_t i = 0; i < gameState.players_.size(); i++)
					{
						if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != iPlayer.GetValue() && gameState.players_.at(i).ProtectionStatus())
						{
							cout << gameState.players_.at(i).GetName() << '\n';
						}
						else
						{
							if (gameState.players_.at(i).GetValue() != iPlayer.GetValue() && gameState.players_.at(i).ProtectionStatus())
							{
								if (i == gameState.players_.size() - 1)
								{
									cout << gameState.players_.at(i).GetName() << '\n';
								}
								else if (gameState.players_.at(i).ProtectionStatus())
								{
									cout << gameState.players_.at(i).GetName() << ", ";
								}
							}
						}
					}
					if (none_of(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.ProtectionStatus(); }))
					{
						cout << "NONE\n";
					}

					iPlayer.PrintHand();
					cout << "--\n";

					int card = 0;
					bool card_input = false;
					while (!card_input)
					{
						// log cards already in hand
						vector<int> in_hand;
						vector<Card> hand = iPlayer.GetHand();
						for (const Card iCard : hand)
						{
							in_hand.push_back(iCard.GetValue());
						}

						// countess restriction check
						bool countess = any_of(in_hand.begin(), in_hand.end(),
											   [](int i) { return i == 8; });
						bool king = any_of(in_hand.begin(), in_hand.end(),
										   [](int i) { return i == 7; });
						bool prince = any_of(in_hand.begin(), in_hand.end(),
											 [](int i) { return i == 5; });

						if (countess && king || countess && prince)
						{
							bool countess_input = false;
							while (!countess_input)
							{
								cout << "You MUST play the Countess.\n";

								cin >> card;

								if (card == 8)
								{
									countess_input = true;
									card_input = true;
									break;
								}
								else
								{
									cin.clear();
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									break;
								}
							}
						}

						// play card in hand: without restriction
						else
						{
							bool in_hand = false;
							while (!in_hand)
							{
								cout << iPlayer.GetName() << " play a card: ";
								cin >> card;

								if (!inputCheck.CheckCard(card))
								{
									cout << "Invalid input.\n";
								}
								else
								{
									for (Card &iCard : hand)
									{
										if (iCard.GetValue() == card)
										{
											in_hand = true;
											card_input = true;
											break;
										}
									}
									if (!in_hand)
									{
										cout << "Not in hand.\n";
										cin.clear();
										cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
								}
							}
						}
					}

					// discard card
					discard.Insert(*iPlayer.Discard(card));
					iPlayer.RemoveCard(card);

					// play card action
					switch (card)
					{
					case 0:
						iPlayer.Spy();
						break;
					case 1:
						iPlayer.Guard(&gameState.players_);
						break;
					case 2:
						iPlayer.Priest(&gameState.players_);
						break;
					case 3:
						iPlayer.Baron(gameState);
						break;
					case 4:
						iPlayer.Handmaid();
						break;
					case 5:
						iPlayer.Prince(&gameState.players_); // does not respect handmaid protection
						break;
					case 6:
						iPlayer.Chancellor(&deck);
						break;
					case 7:
						iPlayer.King(gameState, inputCheck);
						break;
					case 8:
						iPlayer.Countess();
						break;
					case 9:
						iPlayer.Princess();
						break;
					}

					// track remaining players
					vector<Player *> remaining_players;
					for (Player &iPlayer : gameState.players_)
					{
						if (iPlayer.Status())
						{
							remaining_players.push_back(&iPlayer);
						}
					}

					// round ends when one player is standing or deck is empty
					if (remaining_players.size() == 1 || deck.Size() == 0)
					{
						session_end = true;
						break;
					}

					cout << '\n';
					cout << iPlayer.GetName() << " end turn.\n";
					cout << "Moving on to " << iPlayer.GetName() << "'s turn.\n";

					// increase round count
					gameState.round_count_++;
				}
				else
				{
					break;
				}
			}
		}

		// round end
		if (deck.Size() == 0)
		{
			cout << "Deck is empty, players compare hands!\n";
			Player *winner = nullptr;
			for (Player &iPlayer : gameState.players_)
			{
				if (iPlayer.GetValue() > winner->GetValue())
				{
					winner == &iPlayer;
				}
			}
			cout << winner->GetName() << " has the highest hand! " << winner->GetHand().at(0).GetName() << '\n';
			winner->Addtoken();
			winner->Winner(1);
		}

		// spy bonus
		int spy_count = 0;
		Player *spy_bonus = nullptr;
		for (Player &iPlayer : gameState.players_)
		{
			if (iPlayer.Status() && iPlayer.SpyStatus() && spy_count < 2)
			{
				spy_bonus = &iPlayer;
				spy_count++;
			}
		}

		if (spy_count >= 2)
		{
			cout << "Multiple players had the Spy, no one gets a bonus\n";
		}
		else
		{
			cout << spy_bonus->GetName() << " had the Spy!\n";
			spy_bonus->Addtoken();
			cout << spy_bonus->GetName() << " token count: " << spy_bonus->GetTokenCount() << '\n';
		}

		for (Player &iPlayer : gameState.players_)
		{
			if (iPlayer.GetTokenCount() == gameState.winning_token_count_)
			{
				cout << iPlayer.GetName() << " has " << iPlayer.GetTokenCount() << " tokens!\n";
				cout << iPlayer.GetName() << " wins the game!\n";
				game_over = true;
			}
		}
	}

	return 0;
}
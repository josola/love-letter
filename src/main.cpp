#include "aside.h"
#include "deck.h"
#include "discard.h"
#include "functions.h"
#include "player.h"
#include "reference.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::any_of;
using std::cin;
using std::cout;
using std::endl;
using std::to_string;
using std::vector;

int main()
{
  // game state
  short unsigned int suitor_count = 0;
  short unsigned int winning_token_count = 0;
  vector<Player> players;
  Reference reference;
  short unsigned int current_suitor = 0;
  short unsigned int round_count = 1;

  // Tasks that are performed at the start of every GAME.
  cout << "-- WELCOME TO LOVE LETTER --" << endl;

  // starting player count
  bool correct_player_count = false;
  while (!correct_player_count)
  {
    cout << "How many suitors will be playing: " << endl;

    cin >> suitor_count;

    cout << "--" << endl;

    // set players
    if (suitor_count >= 2 && suitor_count <= 6 && cin)
    {
      correct_player_count = true;
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
      cout << "Invalid input, please input a number of Suitors between 2 and 6."
           << endl;
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  // game loop
  bool game_over = false;
  while (!game_over)
  {
    Deck deck;
    deck.Set();
    deck.Shuffle();

    Discard discard;
    Aside aside;

    cout << "-- ROUND " << round_count << " --" << endl;

    // second round and above: reset player stats
    if (round_count > 1)
    {
      for (Player &i : players)
      {
        i.Reset();
      }
    }

    // discard to down pile
    aside.Insert(deck.GetCard(0));

    // two player game: discard two cards
    if (players.size() == 2)
    {
      for (int i = 0; i < 2; i++)
      {
        discard.Insert(deck.GetCard(0));
      }
    }

    // deal starting hand
    for (Player &i : players)
    {
      i.Draw(deck.GetCard(0));
    }

    // game ends with empty deck
    if (deck.Size() == 0)
    {
      game_over = true;
      break;
    }

    // player turn
    for (Player &iPlayer : players)
    {
      // player must be playing
      if (iPlayer.Status())
      {
        // remove handmaid protection
        iPlayer.ResetProtection();

        // draw card from deck
        bool draw_input = false;
        while (!draw_input)
        {
          cout << iPlayer.GetName() << " draw a card (d): " << endl;
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
        iPlayer.Draw(deck.GetCard(0));
        iPlayer.PrintHand();

        cout << "--" << endl;
        int card = 0;
        bool card_input = false;
        while (!card_input)
        {
          vector<int> in_hand;
          vector<Card> hand = iPlayer.GetHand();
          for (const Card iCard : hand)
          {
            in_hand.push_back(iCard.GetValue());
          }

          // countess restriction
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
              cout << "You MUST play the Countess." << endl;

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
            cout << iPlayer.GetName() << " play a card: " << endl;

            cin >> card;
            for (Card &iCard : hand)
            {
              if (iCard.GetValue() == card)
              {
                card_input = true;
                break;
              }
              else
              {
                cout << "Not in hand." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
              }
            }
          }
        }
        /// play card
        iPlayer.Discard(card);
      }
      else
      {
        break;
      }
    }

    game_over = true;
  }

  // PlayGame();

  return 0;
}

/*
	//new structure
		//end round
		if (playingDeck.empty())
		{
			cout << "The deck is empty, suitors compare hands" <<
endl; 			for (unsigned int i = 0; i < activeSuitorHands.size(); i++)
			{
				if (!activeSuitorHands[i].empty())
				{
					cout << suitorNames[i] << " hand: " <<
activeSuitorHands[i][0] << endl;
				}
			}
			for (unsigned int i = 0; i < activeSuitorHands.size();
i++)
			{
				if (!activeSuitorHands[i].empty())
				{
					if (winner < activeSuitorHands[i][0])
					{
						winner =
activeSuitorHands[i][0];
					}
				}
			}
			for (unsigned int i = 0; i < activeSuitorHands.size();
i++)
			{
				if (!activeSuitorHands[i].empty() &&
activeSuitorHands[i][0] == winner)
				{
					winner = i;
					break;
				}
			}
			if (activeSuitorCount > 1)
			{
				for (unsigned int i = 0; i < activeSuitorHands.size();
i++)
				{
					if (suitorObjects[i].SpyStatus())
					{
						tempVector.push_back(i);
					}
				}
				if (tempVector.size() > 1)
				{
					cout << "Multiple suitors had the Spy. No one gets a
bonus." << endl;
				}
				if (tempVector.size() == 1)
				{
					cout << suitorNames.at(tempVector[0]) << " Has the
Spy, they gain an extra favor token <3" << endl;
					suitorObjects.at(tempVector[0]).GainToken();
					cout << suitorNames.at(tempVector[0]) << " token
count: " << suitorObjects.at(tempVector[0]).GetTokenCount() << endl;
				}
				if (tempVector.empty())
				{
					cout << "No one had the Spy this round." <<
endl;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < activeSuitorHands.size();
i++)
			{
				if (!activeSuitorHands[i].empty())
				{
					winner = i;
				}
			}
			cout << "Round over. " << suitorNames[winner] << " is the last
suitor standing." << endl; 			if (suitorObjects[winner].SpyStatus())
			{
				cout << suitorNames[winner] << " has the Spy, they gain
an extra favor token <3" << endl; 				suitorObjects[winner].GainToken();
				suitorObjects[winner].RemoveSpy();
				cout << suitorNames[winner] << " token count: " <<
suitorObjects[winner].GetTokenCount() << endl;
			}
		}
		suitorObjects[winner].GainToken();
		cout << suitorNames[winner] << " gains one[1] favor token <3" <<
endl; 		cout << suitorNames[winner] << " total tokens: " <<
suitorObjects[winner].GetTokenCount() << endl; 		for (unsigned int i = 0; i <
activeSuitorHands.size(); i++)
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
			std::this_thread::sleep_for(std::chrono::seconds(3));
			ClearScreen();
		}
		if (suitorObjects[winner].GetTokenCount() == tokenCountToWin)
		{
			cout << suitorNames[winner] << " has won the heart of the
princess." << endl; 			cout << "-- GAME OVER --" << endl;
			activeSuitorHands.clear();
			suitors.clear();
			downPile.clear();
			upPile.clear();
			activeSuitorCount = 0;
			game_over = true;
		}
	}
}
*/
#include "deck.h"
#include "player.h"
#include "input.h"
#include "reference.h"
#include "game_state.h"
#include "card_actions.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <limits>

using std::any_of;
using std::cin;
using std::count_if;
using std::cout;
using std::none_of;
using std::numeric_limits;
using std::sort;
using std::streamsize;
using std::to_string;
using std::vector;

int main()
{
    GameState gameState;

    cout << "\n-- WELCOME TO LOVE LETTER --\n\n";

    // get starting player count
    int player_count = -1;
    while (player_count < 2 || player_count > 6)
    {
        cout << "How many players will be playing: ";
        cin >> player_count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (player_count < 2 || player_count > 9)
        {
            cout << "Number must be between 2 and 6 players:\n";
        }
    }
    cout << '\n';

    gameState.SetPlayers(player_count);

    // game loop
    bool game_over = false;
    while (!game_over)
    {
        // main deck
        vector<Card> deck;
        Build(deck);
        Shuffle(deck);

        // face up deck
        vector<Card> aside;
        aside.push_back(deck.at(0));
        deck.erase(deck.begin() + 0);

        // discard deck
        vector<Card> discard;
        if (gameState.players_.size() == 2)
        {
            for (int i = 0; i < 2; i++)
            {
                discard.push_back(deck.at(0));
                deck.erase(deck.begin() + 0);
            }
        }

        // deal starting hand
        for (Player &i : gameState.players_)
        {
            i.Draw(deck.at(0));
            deck.erase(deck.begin() + 0);
        }

        // round count prompt
        cout << "-- ROUND " << gameState.round_count_ << " --\n\n";

        // player turn

        vector<Player *> remaining_players;
        Player *winner = nullptr;

        bool end_round = false;
        while (!end_round)
        {
            for (size_t i = 0; i < gameState.players_.size(); i++)
            {
                // set winner of previous round as starting player
                if (gameState.round_count_ > 1)
                {
                    for (size_t j = 0; j < gameState.players_.size(); j++)
                    {
                        if (gameState.players_.at(j).Starting())
                        {
                            i = j;
                            gameState.players_.at(i).SetStarting(0);
                        }
                    }
                }

                // access to player object during play
                Player *current_player = &gameState.players_.at(i);

                if (current_player->Status())
                {
                    current_player->SetProtection(0);

                    // draw input
                    char draw = ' ';
                    while (draw != 'd')
                    {
                        cout << current_player->GetName() << " draw a card (d): ";
                        cin >> draw;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (draw != 'd')
                        {
                            cout << "Input MUST be 'd':\n";
                        }
                    }

                    // current player draw card
                    // current_player->Draw(deck.at(0));
                    deck.erase(deck.begin() + 0);

                    current_player->Draw(Card("HANDMAID", 4, "REF"));

                    // print game state
                    cout << "\nDeck size: \n";
                    cout << deck.size() << '\n';

                    cout << "\nDiscard pile:\n";
                    if (discard.empty())
                    {
                        cout << "EMPTY" << '\n';
                    }
                    else
                    {
                        if (discard.size() == 1)
                        {
                            cout << discard.at(0).GetName() << '\n';
                        }
                        else
                        {
                            for (size_t i = 0; i < discard.size(); i++)
                            {
                                if (i < discard.size() - 1)
                                {
                                    cout << discard.at(i).GetName() << ", ";
                                }
                                else
                                {
                                    cout << discard.at(i).GetName() << '\n';
                                }
                            }
                        }
                    }

                    cout << "\nOpponents:\n";
                    for (size_t i = 0; i < gameState.players_.size(); i++)
                    {
                        if (gameState.players_.at(i).Status())
                        {
                            if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != current_player->GetValue())
                            {
                                cout << gameState.players_.at(i).GetName() << '\n';
                            }
                            else
                            {
                                if (gameState.players_.at(i).GetValue() != current_player->GetValue())
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
                    }

                    cout << "\nHandmaid protection:\n";
                    bool players_have_handmaid = any_of(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.ProtectionStatus(); });
                    if (players_have_handmaid)
                    {
                        int handmaid_count = count_if(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.ProtectionStatus(); });
                        if (handmaid_count == 1)
                        {
                            for (size_t i = 0; i < gameState.players_.size(); i++)
                            {
                                Player *handmaidPlayer = &gameState.players_.at(i);
                                if (handmaidPlayer->ProtectionStatus() && (handmaidPlayer->GetValue() != current_player->GetValue()))
                                {
                                    cout << handmaidPlayer->GetName() << '\n';
                                    break;
                                }
                            }
                        }
                        else
                        {
                            int handmaid_tally = 1;
                            for (size_t i = 0; i < gameState.players_.size(); i++)
                            {
                                Player *iPlayer = &gameState.players_.at(i);
                                if (iPlayer->ProtectionStatus() && (iPlayer->GetValue() != current_player->GetValue()))
                                {
                                    if (handmaid_tally != handmaid_count)
                                    {
                                        cout << iPlayer->GetName() << ", ";
                                    }
                                    else
                                    {
                                        cout << iPlayer->GetName() << '\n';
                                    }
                                    handmaid_tally++;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "NONE\n";
                    }

                    cout << "\nSpy Bonus:\n";
                    bool players_have_spy = any_of(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.SpyStatus(); });
                    if (players_have_spy)
                    {
                        int spy_count = count_if(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.SpyStatus(); });
                        if (spy_count == 1)
                        {
                            for (size_t i = 0; i < gameState.players_.size(); i++)
                            {
                                Player *spyPlayer = &gameState.players_.at(i);
                                if (gameState.players_.at(i).SpyStatus())
                                {
                                    cout << spyPlayer->GetName() << '\n';
                                    break;
                                }
                            }
                        }
                        else
                        {
                            int spy_tally = 1;
                            for (size_t i = 0; i < gameState.players_.size(); i++)
                            {
                                Player *iPlayer = &gameState.players_.at(i);
                                if (iPlayer->GetValue() != current_player->GetValue() && iPlayer->SpyStatus())
                                {
                                    if (spy_tally == 1)
                                    {
                                        cout << iPlayer->GetName() << ", ";
                                        spy_tally++;
                                    }
                                    else
                                    {
                                        cout << iPlayer->GetName() << '\n';
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "NONE\n";
                    }

                    current_player->PrintHand();

                    // log cards already in hand
                    vector<int> in_hand;
                    for (Card iCard : *current_player->GetHand())
                    {
                        in_hand.push_back(iCard.GetValue());
                    }

                    // countess restriction check
                    bool countess = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 8; });
                    bool king = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 7; });
                    bool prince = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 5; });

                    bool correct_input = false;
                    int card = 0;
                    while (!correct_input)
                    {
                        cout << current_player->GetName() << " play a card: ";
                        cin >> card;
                        SanitizeCard(card, -1);

                        if ((countess && king) || (countess && prince))
                        {
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "You MUST play the Countess.\n";
                        }
                        else
                        {
                            for (Card &iCard : *current_player->GetHand())
                            {
                                if (iCard.GetValue() == card)
                                {
                                    correct_input = true;
                                    break;
                                }
                            }
                            if (!correct_input)
                            {
                                cout << "Not in hand.\n";
                            }
                        }
                    }

                    // discard card
                    current_player->Discard(card, discard);

                    // play card action
                    switch (card)
                    {
                    case 0:
                        Spy(current_player);
                        break;
                    case 1:
                        Guard(gameState, current_player, discard);
                        break;
                    case 2:
                        Priest(gameState, current_player);
                        break;
                    case 3:
                        Baron(gameState, current_player, discard);
                        break;
                    case 4:
                        Handmaid(current_player);
                        break;
                    case 5:
                        Prince(gameState, current_player, discard);
                        break;
                    case 6:
                        Chancellor(discard, current_player);
                        break;
                    case 7:
                        King(gameState, current_player);
                        break;
                    case 8:
                        Countess(current_player);
                        break;
                    case 9:
                        Princess(current_player, discard);
                        break;
                    }
                    cout << '\n';
                }

                // reset remaining players, so as not to stack remainders
                remaining_players.erase(remaining_players.begin(), remaining_players.end());

                // check how many standing players
                for (Player &iPlayer : gameState.players_)
                {
                    if (iPlayer.Status())
                    {
                        remaining_players.push_back(&iPlayer);
                    }
                }

                // round end check
                if (deck.empty() || remaining_players.size() == 1)
                {
                    end_round = true;
                    break;
                }
            }
        }

        // increase round count
        gameState.round_count_ += 1;

        // round end

        // deck is empty, players compare hands, highest hand wins the round
        if (deck.size() == 0)
        {
            cout << "Deck is empty, players compare hands!\n";
            for (size_t i = 0; i < gameState.players_.size(); i++)
            {
                Player *iPlayer = &gameState.players_.at(i);
                if (i < gameState.players_.size() - 1)
                {
                    if (iPlayer->GetHand()->at(0).GetValue() > gameState.players_.at(i + 1).GetHand()->at(0).GetValue())
                    {
                        winner = &gameState.players_.at(i);
                    }
                }
            }
            cout << winner->GetName() << " has the highest hand! " << winner->GetHand()->at(0).GetName() << '\n';
            winner->Addtoken();
            winner->Winner(1);
        }

        // spy bonus
        int spy_count = 0;
        if (any_of(gameState.players_.begin(), gameState.players_.end(), [](Player &iPlayer) { return iPlayer.SpyStatus(); }))
        {
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
            else if (spy_count == 1)
            {
                cout << spy_bonus->GetName() << " had the Spy!\n";
                spy_bonus->Addtoken();
                cout << spy_bonus->GetName() << " token count: " << spy_bonus->GetTokenCount() << '\n';
            }
        }

        // celebrate the last player standing
        for (Player &iPlayer : gameState.players_)
        {
            if (iPlayer.Status())
            {
                winner = &iPlayer;
            }
        }

        cout << winner->GetName() << " was the last player standing!\n";
        winner->Addtoken();
        cout << winner->GetName() << " token count: " << winner->GetTokenCount() << "\n\n";
        winner->SetStarting(1);

        // set players to base
        if (gameState.round_count_ > 1)
        {
            for (Player &i : gameState.players_)
            {
                i.Reset();
            }
        }

        // check that player has winning token count
        for (Player &iPlayer : gameState.players_)
        {
            if (iPlayer.GetTokenCount() == gameState.winning_token_count_)
            {
                cout << iPlayer.GetName() << " has " << iPlayer.GetTokenCount() << " tokens!\n";
                cout << iPlayer.GetName() << " wins the game!\n";
                game_over = true;
                break;
            }
        }
    }

    return 0;
}

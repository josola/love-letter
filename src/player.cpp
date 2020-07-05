#include "player.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;

Player::Player(const string name, const int value, const Reference &reference)
    : name_(name), value_(value), reference_(reference){};

// getters
const bool Player::ProtectionStatus() const { return handmaid_; }
const string Player::GetName() const { return name_; }
const vector<Card> Player::GetHand() const { return hand_; }
const bool Player::Status() const { return playing_; }
const int Player::GetValue() const { return value_; }

// setters
void Player::Draw(const Card obj) { hand_.push_back(obj); }
void Player::SetProtection(const bool state) { handmaid_ = state; }
void Player::GainSpy() { spy_ = true; }
void Player::Reset()
{
  hand_.clear();
  handmaid_ = false;
  spy_ = false;
}
void Player::Discard(const int choice)
{
  for (size_t i = 0; i < hand_.size(); i++)
  {
    if (hand_.at(i).GetValue() == choice)
    {
      hand_.erase(hand_.begin() + i);
      break;
    }
  }
}
void Player::DiscardHand()
{
  for (Card &iCard : hand_)
  {
    Discard(iCard.GetValue());
  }
}
void Player::Playing(const bool state) { playing_ = state; }

// printer
void Player::PrintHand() const
{
  if (!hand_.empty())
  {
    for (size_t i = 0; i < hand_.size(); i++)
    {
      if (i < hand_.size() - 1)
      {
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << ", ";
      }
      else
      {
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << '\n';
      }
    }
  }
}

void Player::Spy() { spy_ = true; }
void Player::Guard(vector<Player> *players)
{
  Player *target_player = NULL;
  bool target_input = false;
  while (!target_input)
  {
    cout << this->GetName() << " choose a target: ";
    int target = 0;
    cin >> target;
    if (target != this->GetValue() && target >= 1 && target <= 6 && cin)
    {
      for (Player &iPlayer : *players)
      {
        if (iPlayer.GetValue() == target)
        {
          if (iPlayer.ProtectionStatus())
          {
            cout << iPlayer.GetName() << " has Handmaid protection...\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
          }
        }
      }
      for (Player &iPlayer : *players)
      {
        if (iPlayer.GetValue() == target)
        {
          target_player = &iPlayer;
        }
      }
      break;
    }
    else
    {
      cout << target << " is not a player...\n";
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  bool card_input = false;
  int card_choice = 0;
  while (!card_input)
  {
    cout << this->GetName() << " guess a card: ";
    cin >> card_choice;
    if (card_choice >= 0 && card_choice <= 9 && cin)
    {
      if (card_choice == 1)
      {
        cout << "You cannot choose another Guard...\n";
      }
      else
      {
        card_input = true;
      }
    }
    else
    {
      cout << card_choice << " is not a card...\n";
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  vector<Card> target_hand = target_player->GetHand();
  for (Card &iCard : target_hand)
  {
    if (iCard.GetValue() == card_choice)
    {
      cout << "Match!\n";
      target_player->Playing(0);
      return;
    }
  }
  cout << "No match!\n";
}
void Player::Priest(vector<Player> *players)
{
  cout << this->GetName() << " choose a target player: ";
  short unsigned int target = 0;
  cin >> target;
  bool target_input = false;
  while (!target_input)
  {
    if (target != this->GetValue() && target <= 1 && target >= 6 && cin)
    {
      target_input = true;
    }
    else
    {
      cout << "Invalid input.\n";
    }
  }
  Player *target_player = NULL;
  for (Player &iPlayer : *players)
  {
    if (iPlayer.GetValue() == target)
    {
      target_player = &iPlayer;
      break;
    }
  }
  cout << target_player->GetName() << "'s hand is:\n";
  target_player->PrintHand();
}
void Player::Baron(vector<Player> *players)
{
  cout << this->GetName() << " choose a target player: ";
  short unsigned int target = 0;
  cin >> target;
  bool target_input = false;
  while (!target_input)
  {
    if (target != this->GetValue() && target >= 1 && target <= 6 && cin)
    {
      target_input = true;
    }
    else
    {
      cout << "Invalid input.\n";
    }
  }
  Player *target_player = NULL;
  for (Player &iPlayer : *players)
  {
    if (iPlayer.GetValue() == target)
    {
      target_player = &iPlayer;
    }
  }
  vector<Card> *hand;
  for (Card iCard : this->GetHand())
  {
    hand->push_back(iCard);
  }
  for (Card iCard : target_player->GetHand())
  {
    hand->push_back(iCard);
  }
  if (hand->at(0).GetValue() > hand->at(1).GetValue())
  {
    cout << target_player->GetName() << " had the lower card!\n";
    cout << target_player->GetName() << " is out!\n";
    target_player->Discard(0);
    target_player->Reset();
    target_player->Playing(0);
  }
  else if (hand->at(0).GetValue() == hand->at(1).GetValue())
  {
    cout << "Hands are equal! Play moves on!\n";
  }
  else
  {
    cout << this->GetName() << " had the lower card!\n";
    cout << this->GetName() << " is out!\n";
    this->Discard(0);
    this->Reset();
    this->Playing(0);
  }
}
void Player::Handmaid() { this->SetProtection(1); }
void Player::Prince(vector<Player> *players)
{
  bool target_input = false;
  while (!target_input)
  {
    cout << this->GetName() << " choose a target player: ";
    short unsigned int target = 0;
    cin >> target;
    if (target == this->GetValue())
    {
      cout << "You chose yourself!\n";
      bool self_discard = false;
      while (!self_discard)
      {
        cout << "Please discard your hand (d): ";
        char discard = ' ';
        cin >> discard;
        if (discard == 'd')
        {
          this->DiscardHand();
          self_discard = true;
        }
        else
        {
          cout << discard << " is invald.\n";
        }
      }
    }
    else if (target >= 1 && target <= 6 && cin)
    {
      Player *player_target = NULL;
      for (Player &iPlayer : *players)
      {
        if (iPlayer.GetValue() == target)
        {
          player_target = &iPlayer;
        }
      }
      cout << player_target->GetName() << " discards their hand!\n";
    }
    else
    {
      cout << "Invalid input.\n";
    }
  }
}
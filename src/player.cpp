#include "player.h"
#include "suits.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::distance;
using std::endl;
using std::find;
using std::invalid_argument;

Player::Player(const string name, const int value, const Reference &reference)
    : name_(name), value_(value), reference_(reference){};

void Player::Draw(const Card obj) { hand_.push_back(obj); }

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

void Player::Reset()
{
  hand_.clear();
  handmaid_ = false;
  spy_ = false;
}

const bool Player::Status() const { return playing_; }

const bool Player::Protection() const { return handmaid_; }

void Player::ResetProtection() { handmaid_ = false; }

const string Player::GetName() const { return name_; }

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
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << endl;
      }
    }
  }
}

const vector<Card> Player::GetHand() const { return hand_; }

void Player::Play(const int choice)
{
  Player *player = this;
  switch (choice)
  {
  case 0:
  {
    Spy spy;
    spy.Action(player);
    break;
  }
  case 1:
  {
    Guard guard;
    guard.Action();
    break;
  }
  case 2:
  {
    Priest priest;
    priest.Action();
    break;
  }
  case 3:
  {
    Baron baron;
    baron.Action();
    break;
  }
  case 4:
  {
    Handmaid handmaid;
    handmaid.Action();
    break;
  }
  case 5:
  {
    Prince prince;
    prince.Action();
    break;
  }
  case 6:
  {
    Chancellor chancellor;
    chancellor.Action();
    break;
  }
  case 7:
  {
    King king;
    king.Action();
    break;
  }
  case 8:
  {
    Countess countess;
    countess.Action();
    break;
  }
  case 9:
  {
    Princess princess;
    princess.Action();
    break;
  }
  }
}

void Player::GainSpy()
{
  spy_ = true;
}
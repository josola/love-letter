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
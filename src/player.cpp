#include "player.h"
#include "deck.h"
#include "card.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

Player::Player(const string name, const int value, const Reference &reference) : name_(name), value_(value), reference_(reference){};

// getters
const bool Player::ProtectionStatus() const
{
  return handmaid_;
}

const string Player::GetName() const
{
  return name_;
}

vector<Card>* Player::GetHand()
{
  return &hand_;
}

const bool Player::Status() const
{
  return playing_;
}

const int Player::GetValue() const
{
  return value_;
}

const int Player::GetTokenCount() const
{
  return token_count_;
}

const bool Player::SpyStatus() const
{
  return spy_;
}

Converter *Player::GetConversion()
{
  return &convert_;
}

// setters
void Player::Draw(const Card obj)
{
  hand_.push_back(obj);
}

void Player::SetProtection(const bool state)
{
  handmaid_ = state;
}

void Player::GainSpy()
{
  spy_ = true;
}

void Player::Reset()
{
  hand_.clear();
  handmaid_ = false;
  spy_ = false;
  winner_ = false;
  playing_ = true;
}

void Player::Discard(const int choice, Deck &deck)
{
  for (Card &iCard : hand_)
  {
    if (iCard.GetValue() == choice)
    {
      deck.Insert(iCard);
      RemoveCard(iCard.GetValue());
      break;
    }
  }
}

void Player::DiscardHand(Deck &deck)
{
  for (Card &iCard : hand_)
  {
    Discard(iCard.GetValue(), deck);
  }
}

void Player::Addtoken()
{
  token_count_++;
}

void Player::Winner(const bool state)
{
  winner_ = state;
}

void Player::RemoveCard(const int card)
{
  for (size_t i = 0; i < hand_.size(); i++)
  {
    if (hand_.at(i).GetValue() == card)
    {
      hand_.erase(hand_.begin() + i);
      break;
    }
  }
}

void Player::Out(Deck &deck)
{
  this->DiscardHand(deck);
  this->Reset();
  this->playing_ = false;
}

// printers
void Player::PrintHand() const
{
  cout << '\n' << this->GetName() << " hand:\n";

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
  else
  {
    cout << "EMPTY\n";
  }
}

// overload
bool operator<(const Player &l, const Player &r)
{
  return l.hand_.at(0).GetValue() < r.hand_.at(0).GetValue();
}
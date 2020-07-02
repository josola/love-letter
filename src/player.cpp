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

void Player::Discard(const int choice) {
  for (size_t i = 0; i < hand_.size(); i++) {
    if (hand_.at(i).GetValue() == choice) {
      hand_.erase(hand_.begin() + i);
      break;
    }
  }
}

void Player::Reset() {
  hand_.clear();
  handmaid_ = false;
  spy_ = false;
}

const bool Player::Status() const { return playing_; }

const bool Player::Protection() const { return handmaid_; }

void Player::ResetProtection() { handmaid_ = false; }

const string Player::GetName() const { return name_; }

void Player::PrintHand() const {
  if (!hand_.empty()) {
    for (size_t i = 0; i < hand_.size(); i++) {
      if (i < hand_.size() - 1) {
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << ", ";
      } else {
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << endl;
      }
    }
  }
}

const vector<Card> Player::GetHand() const { return hand_; }

void Player::Play(Card &card) {
  switch (card.GetValue()) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  default:
    break;
  }
}
/*
 * player.cpp
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "player.h"

using std::cout;
using std::distance;
using std::endl;
using std::find;
using std::invalid_argument;

Player::Player(const string name, const int value, const Reference &reference)
	: name_(name), value_(value), reference_(reference){};

void Player::Draw(const Card obj)
{
	hand_.push_back(obj);
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

void Player::Reset()
{
	hand_.clear();
	handmaid_ = false;
	spy_ = false;
}

const bool Player::Status() const
{
	return playing_;
}

const bool Player::Protection() const
{
	return handmaid_;
}

void Player::ResetProtection()
{
	handmaid_ = false;
}

const string Player::GetName() const
{
	return name_;
}

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

const vector<Card> Player::GetHand() const
{
	return hand_;
}

void Player::Play(const int choice)
{
	for (Card &i : hand_)
	{
		if (i.GetValue() == choice)
		{
			i.Action();
		}
	}
}
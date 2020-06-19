/*
 * player.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "player.h"

using std::exception;

Player::Player(string name, int value, Reference &reference)
	: name_(name), value_(value), reference_(reference){};

template <typename T>
void Player::Draw(Pile<T> &obj)
{
	if (typeid(obj) == typeid(Card))
	{
		hand_.push_back(obj);
	}
	else if (typeid(obj) == typeid(Token))
	{
		tokens_.push_back(obj);
	}
	else
	{
		throw exception("Player does not know what to do with that type");
	}
}
template <typename T>
void Player::Discard(T &obj)
{
	if (typeid(obj) == typeid(Card) && typeid(obj) != typeid(int))
	{
		typename vector<T>::iterator it =
			find(hand_.begin(), hand_.end(), [obj](Card &i) { return i == obj; });
		if (it != hand_.end())
		{
			int index = distance(hand_.begin(), it);
			hand_.erase(hand_.begin() + index);
		}
	}
	else if (typeid(obj) == typeid(int) && typeid(obj) != typeid(Card))
	{
		if (obj >= 0 && obj <= 9)
		{
			typename vector<T>::iterator it =
				find(hand_.begin(), hand_.end(),
					 [obj](const Card &i) { return obj == i.GetValue(); });
			if (it != hand_.end())
			{
				int index = distance(hand_.begin(), it);
				hand_.erase(hand_.begin() + index);
			}
			else
			{
				throw exception("Object not in hand");
				return;
			}
		}
		else
		{
			throw exception("Object not in hand");
			return;
		}
	}
	else
	{
		throw exception("Player does not know what to do with that type");
		return;
	}
}
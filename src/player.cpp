/*
 * player.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "player.h"

using std::exception;

Player::Player(string name, int value, Reference& reference) : name_(name), value_(value), reference_(reference) {};

template <typename T>
void Player::Draw(Pile<T>& obj)
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
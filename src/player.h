/*
 * player.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "token.h"
#include "reference.h"
#include "pile.h"

class Player
{
public:
	Player(const string name, const int value, const Reference &reference);

	template <typename T>
	void Draw(const Pile<T> &obj);
	template <typename T>
	void Discard(T &obj);
	void Print(short unsigned int choice);
	void ClearHand();

protected:
	string name_ = "";
	int value_ = 0;
	Reference reference_;
	vector<Card> hand_;
	vector<Token> tokens_;
	bool handmaid_ = false;
	bool spy_ = false;
};

#endif

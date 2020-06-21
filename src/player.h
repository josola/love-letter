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
	Player(string name, int value, Reference& reference);

	template <typename T>
	void Draw(Pile<T>& obj);

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
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

	void Draw(const Card obj);
	template <typename T>
	void Discard(T &obj);
	void Reset();
	const bool Status() const;
	const bool Protection() const;
	void ResetProtection();
	const string GetName() const;

protected:
	string name_ = "";
	int value_ = 0;
	Reference reference_;
	vector<Card> hand_;
	vector<Token> tokens_;
	bool handmaid_ = false;
	bool spy_ = false;
	bool playing_ = true;
};

#endif

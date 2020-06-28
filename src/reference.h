/*
 * reference.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef REFERENCE_H
#define REFERENCE_H

#include <string>
#include "card.h"

using std::string;

class Reference : public Card
{
public:
	Reference();
	void Print();

protected:
	string reference[10] = {
		"9-Princess (x1): Out of the round if you play/discard.",
		"8-Countess (x1): Must play if you have King or Prince.",
		"7-King (x1): Trade hands.",
		"6-Chancellor (x2): Draw & return 2 cards.",
		"5-Prince (x2): Discard a hand & redraw.",
		"4-Handmaid (x2): Immune to other cards until your next turn.",
		"3-Baron (x2): Compare hands.",
		"2-Priest (x2): Look at a hand.",
		"1-Guard (x6): Guess a hand.",
		"0-Spy (x2): Gain favor if no one else plays/discards a Spy.",
	};
};

#endif

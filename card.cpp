/*
 * Determines card information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include <string>
#include "card.h"

using std::string;

Card::Card(string name, int value) : name(name), value(value){};
CardController::CardController(Card card) : card(card){};

string Card::GetName() { return name; }
int Card::GetValue() { return value; }
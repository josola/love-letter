/*
 * Determines deck information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2020
 */

#include <vector>
#include "deck.h"
#include "card.h"

using std::vector;

DeckController::DeckController(Deck &deck) : deck(deck){};

vector<Card> Deck::GetDeck() { return deck; }
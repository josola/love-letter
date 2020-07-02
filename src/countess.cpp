#include "countess.h"

Countess::Countess()
    : Card{
          "COUNTESS", 8,
          "If the King or Prince is in your hand, you must play this card."} {};

void Countess::Action() {}
#include "prince.h"

Prince::Prince()
    : Card{"PRINCE", 5,
           "Choose any player (including yourself). That player discards their "
           "hand and redraws."} {};

void Prince::Action() {}
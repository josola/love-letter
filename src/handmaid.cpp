#include "handmaid.h"

Handmaid::Handmaid()
    : Card{"HANDMAID", 4,
           "Until yout next turn, other players cannot choose you for their "
           "card effects."} {};

void Handmaid::Action() {}
#include "guard.h"
#include <iostream>

using std::cout;
using std::endl;

Guard::Guard()
    : Card{"GUARD", 1,
           "Choose another player and name a non-Guard card. If that player "
           "has that card, they are out of the round."} {};

void Guard::Action() {}
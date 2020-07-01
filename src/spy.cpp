/*
 * spy.cpp
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "spy.h"
#include <iostream>

using std::cout;
using std::endl;

Spy::Spy() : Card{"SPY", 0, "At the end of the round, if you are the only player in the round who played or discarded a Spy, gain 1 favor token."}{};

void Spy::Action()
{

}
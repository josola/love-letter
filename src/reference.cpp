/*
 * reference.cpp
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include <iostream>
#include "reference.h"

using std::cout;
using std::endl;

Reference::Reference() : Card{ "REFERENCE", -1 }{};

void Reference::Print()
{
    for (const string i : reference)
    {
        cout << i << endl;
    }
}
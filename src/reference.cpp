#include "reference.h"
#include <iostream>

using std::cout;
using std::endl;

Reference::Reference() : Card{"REFERENCE", -1} {};

void Reference::Print()
{
  for (const string i : reference)
  {
    cout << i << endl;
  }
}
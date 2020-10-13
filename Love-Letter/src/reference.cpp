#include "reference.h"
#include <iostream>

using std::cout;
using std::endl;

Reference::Reference() : Card{"REFERENCE", -1} {};

void Reference::Print()
{
  for (string i : reference)
  {
    cout << i << endl;
  }
}

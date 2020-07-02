//===-- baron.h - Baron class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

#include "card.h"
#include <string>

using std::string;

class Baron : virtual public Card {
public:
  Baron();
  virtual void Action();

protected:
};
//===-- guard.h - Guard class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------===//

#include "card.h"
#include <string>

using std::string;

class Guard : virtual public Card {
public:
  Guard();
  virtual void Action();

protected:
};
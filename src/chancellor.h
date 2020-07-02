//===-- countess.h - Countess class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

#include "card.h"
#include <string>

using std::string;

class Chancellor : virtual public Card {
public:
  Chancellor();
  virtual void Action();

protected:
};
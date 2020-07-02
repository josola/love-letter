//===-- king.h - King class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===---------------------------------------------------===//

#include "card.h"

class King : virtual public Card {
public:
  King();
  virtual void Action();

protected:
};
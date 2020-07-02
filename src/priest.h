//===-- priest.h - Priest class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-------------------------------------------------------===//

#include "card.h"

class Priest : virtual public Card {
public:
  Priest();
  virtual void Action();

protected:
};
//===-- prince.h - Prince class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-------------------------------------------------------===//

#include "card.h"

class Prince : virtual public Card {
public:
  Prince();
  virtual void Action();

protected:
};
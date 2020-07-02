//===-- handmaid.h - Handmaid class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

#include "card.h"

class Handmaid : virtual public Card {
public:
  Handmaid();
  virtual void Action();

protected:
};
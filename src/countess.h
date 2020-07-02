//===-- countess.h - Countess class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of the Countess card.
///
//===----------------------------------------------------------------------===//

#include "card.h"

class Countess : virtual public Card {
public:
  Countess();
  virtual void Action();

protected:
};
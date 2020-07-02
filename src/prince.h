//===-- prince.h - Prince class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of the Prince card.
///
//===----------------------------------------------------------------------===//

#include "card.h"

class Prince : virtual public Card {
public:
  Prince();
  virtual void Action();

protected:
};
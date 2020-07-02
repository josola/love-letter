//===-- princess.h - Princess class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of the Princess card.
///
//===----------------------------------------------------------------------===//

#include "card.h"

class Princess : virtual public Card {
public:
  Princess();
  virtual void Action();

protected:
};
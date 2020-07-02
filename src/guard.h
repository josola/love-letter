//===-- guard.h - Guard class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of the Guard card.
///
//===----------------------------------------------------------------------===//

#include "card.h"
#include <string>

using std::string;

class Guard : virtual public Card {
public:
  Guard();
  virtual void Action();

protected:
};
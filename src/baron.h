//===-- baron.h - Baron class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of the Baron card.
///
//===----------------------------------------------------------------------===//

#include "card.h"
#include <string>

using std::string;

class Baron : virtual public Card {
public:
  Baron();
  virtual void Action();

protected:
};
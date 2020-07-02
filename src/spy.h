//===-- spy.h - Spy class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

#include "card.h"
#include "player.h"

class Spy : virtual public Card {
public:
  Spy();
  virtual void Action(Player *player);

protected:
};
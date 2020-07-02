//===-- card.h - Card class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// The file is the Card base class. Individual suits ie. "Baron" are derived
/// from this class.
///
//===----------------------------------------------------------------------===//

#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Card {
public:
  Card(const string name = "", const int value = 0,
       const string description = "");
  const string GetName() const;
  const string GetDescription() const;
  const int GetValue() const;
  void PrintName() const;
  void PrintValue() const;
  void PrintDescription() const;
  template <class T> void Action(T *obj);

protected:
  string name_ = "";
  string description_ = "";
  int value_ = 0;
};

#endif

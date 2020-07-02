//===-- pile.h - Pile class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===---------------------------------------------------===//

#ifndef PILE_H
#define PILE_H

#include <vector>

using std::vector;

template <class T> class Pile {
public:
  T Remove(T obj);
  void Clear();
  void InsertBottom(T &obj);
  int Size() const;

protected:
  vector<T> pile_;
};

#endif // !PILE_H

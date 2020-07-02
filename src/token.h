//===-- token.h - Token class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines that capabilities of a token during gameplay.
///
//===----------------------------------------------------------------------===//

#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
  const int GetValue() const;

protected:
  const int value_ = 1;
};

#endif

//===-- input_check.h - Input check mechanisms -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file contains functions that check input against set limitations.
///
//===----------------------------------------------------------------------===//

#ifndef INPUT_CHECK_h
#define INPUT_CHECK_h

struct InputCheck
{
	const bool CheckTargetPlayer(const int input);
	const bool CheckStartingPlayerCount(const int input);
	const bool CheckCard(const int input);
};

#endif // !INPUT_CHECK_h

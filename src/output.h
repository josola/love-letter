//===-- output.h - Output functions definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

// deprecated

#ifndef OUTPUT_h
#define OUTPUT_h

#include "suitor.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// functions that are updated
void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void PrintActiveSuitors();
void ClearScreen();
void PrintSeperator();
void returnSuitor();
void printHand();

#endif //! OUTPUT_h
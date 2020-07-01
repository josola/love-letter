/*
 * output.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

//deprecated

#ifndef OUTPUT_h
#define OUTPUT_h

#include <vector>
#include <string>
#include "suitor.h"

using std::vector;
using std::string;

//functions that are updated
void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void PrintActiveSuitors();
void ClearScreen();
void PrintSeperator();
void returnSuitor();
void printHand();

#endif //!OUTPUT_h
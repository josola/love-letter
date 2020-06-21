/*
 * Output
 * Uses the standard output stream to output to screen.
 * Written by Jordan Sola 2019 - 2020
 * This software uses the MIT license
 */

#ifndef OUTPUT_h
#define OUTPUT_h

#include <vector>
#include <string>
#include "suitor.h"

using std::vector;
using std::string;

//functions that are updated
void PrintUpPile(vector<int> up_pile, vector<string> names);
void PrintDeckSize(vector<int> deck);
void PrintSuitorsWithSpy(vector<vector<int>> hand, vector<Suitor> suitors);
void PrintActiveSuitors(int current_suitor, vector<vector<int>>& hand, vector<int> suitors);
void ClearScreen();
void PrintSeperator();
void returnSuitor(const int suitor);
void printHand(int suitor, vector<string> card_names, vector<vector<int>> suitor_hands);

#endif //!OUTPUT_h
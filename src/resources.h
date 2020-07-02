//===-- resources.h - Resources class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===-----------------------------------------------------------===//

// deprecated

#ifndef RESOURCES_h
#define RESOURCES_h

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

int activeSuitorCount;
int originalSuitorCount;
int currentSuitor;
int tokenCountToWin;
int cardNum;
int roundCount = 1;
int tempVictor;
int i;
int iLength;
int cardPosition;
int humanSuitor;

static const int spy = 0, guard = 1, priest = 2, baron = 3, handmaid = 4,
                 prince = 5, chancellor = 6, king = 7, countess = 8,
                 princess = 9, startingRound = 1, minSuitorsPlaying = 2,
                 maxSuitorsPlaying = 6;

std::vector<int> tempVector, suitors, upPile, downPile, tempInput,
    suitorsWithHandmaid;

std::vector<std::vector<int>> activeSuitorHands;

auto winner = 0;
unsigned int targetNum = 0, guess = 0;
bool gameOver = false;
char input;

std::vector<std::string> suitorNames{"SUITOR 1", "SUITOR 2", "SUITOR 3",
                                     "SUITOR 4", "SUITOR 5", "SUITOR 6"};

std::vector<std::string> cardNames{
    "SPY[0]",    "GUARD[1]",      "PRIEST[2]", "BARON[3]",    "HANDMAID[4]",
    "PRINCE[5]", "CHANCELLOR[6]", "KING[7]",   "COUNTESS[8]", "PRINCESS[9]"};

std::vector<int> baseDeck{
    spy,    spy,    guard,      guard,      guard, guard,    guard,
    guard,  priest, priest,     baron,      baron, handmaid, handmaid,
    prince, prince, chancellor, chancellor, king,  countess, princess};

std::vector<int> playingDeck{
    spy,    spy,    guard,      guard,      guard, guard,    guard,
    guard,  priest, priest,     baron,      baron, handmaid, handmaid,
    prince, prince, chancellor, chancellor, king,  countess, princess};

#endif
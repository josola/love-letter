/*
MIT License

Copyright (c) 2020 Jordan Sola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

using std::vector;
using std::string;

int active_suitor_count;
int original_suitor_count;
int current_suitor;
int token_count_to_win;
int card_num;
int round_count = 1;
int temp_victor;
int i;
int iLength;
int car_position;
int human_suitor;

const int spy = 0;
const int guard = 1;
const int priest = 2;
const int baron = 3;
const int handmaid = 4;
const int prince = 5;
const int chancellor = 6;
const int king = 7;
const int countess = 8;
const int princess = 9;
const int starting_round = 1;
const int minSuitorsPlaying = 2;
const int maxSuitorsPlaying = 6;

vector<int> temp_vector;
vector<int> suitors;
vector<int> up_pile;
vector<int> down_pile;
vector<int> temp_input;
vector<int> suitors_with_handmaid;

vector<vector<int> > active_suitor_hands;

auto winner = 0;
unsigned int target_hum = 0, guess = 0;
bool game_over = false;
char input;

vector<string> suitor_names
	{ "SUITOR 1", "SUITOR 2", "SUITOR 3", "SUITOR 4", "SUITOR 5", "SUITOR 6" };

vector<string> card_names
	{ "SPY[0]","GUARD[1]","PRIEST[2]","BARON[3]","HANDMAID[4]","PRINCE[5]"
	"CHANCELLOR[6]","KING[7]","COUNTESS[8]","PRINCESS[9]" };

vector<int> base_deck
	{ spy, spy, guard, guard, guard, guard, guard, guard, priest, priest,
	baron, baron, handmaid, handmaid, prince, prince, chancellor,
	chancellor, king, countess, princess };

vector<int> playing_deck
	{ spy, spy, guard, guard, guard, guard, guard, guard, priest, priest,
	baron, baron, handmaid, handmaid, prince, prince, chancellor,
	chancellor, king, countess, princess };

/*TODO: update included libraries to reflect what is only needed per file and
not included in one file then that file is included in another file wile the
other file uses the libraries in the included file, seems sloppy.*/

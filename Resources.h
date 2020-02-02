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

int
active_suitor_count,
original_suitor_count,
current_suitor,
token_count_to_win,
card_num,
round_count = 1,
temp_victor,
i,
iLength,
car_position,
human_suitor;

static const int
spy = 0,
guard = 1,
priest = 2,
baron = 3,
handmaid = 4,
prince = 5,
chancellor = 6,
king = 7,
countess = 8,
princess = 9,
starting_round = 1,
minSuitorsPlaying = 2,
maxSuitorsPlaying = 6;

std::vector<int>
temp_vector,
suitors,
up_pile,
down_pile,
temp_input,
suitors_with_handmaid;

std::vector<std::vector<int> > activeSuitorHands;

auto winner = 0;
unsigned int target_hum = 0, guess = 0;
bool game_over = false;
char input;

std::vector<std::string> suitor_names
{
	"SUITOR 1",
	"SUITOR 2",
	"SUITOR 3",
	"SUITOR 4",
	"SUITOR 5",
	"SUITOR 6"
};

std::vector<std::string> card_names
{
	"SPY[0]",
	"GUARD[1]",
	"PRIEST[2]",
	"BARON[3]",
	"HANDMAID[4]",
	"PRINCE[5]",
	"CHANCELLOR[6]",
	"KING[7]",
	"COUNTESS[8]",
	"PRINCESS[9]"
};

std::vector<int> base_deck
{
	spy,
	spy,
	guard,
	guard,
	guard,
	guard,
	guard,
	guard,
	priest,
	priest,
	baron,
	baron,
	handmaid,
	handmaid,
	prince,
	prince,
	chancellor,
	chancellor,
	king,
	countess,
	princess
};

std::vector<int> playing_deck
{
	spy,
	spy,
	guard,
	guard,
	guard,
	guard,
	guard,
	guard,
	priest,
	priest,
	baron,
	baron,
	handmaid,
	handmaid,
	prince,
	prince,
	chancellor,
	chancellor,
	king,
	countess,
	princess
};

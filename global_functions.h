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

//input

void ClearInput();
bool ProperCardInput();
bool ProperSuitorInput();
bool ProperSuitorCount();

//output

void ReturnSuitor(int suitor);
void ClearScreen();
void PrintSeperator();
void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void PrintActiveSuitors();
void printHand(int suitor);

//card position

bool CardInHand(int suitor, int card);
int HandPosition(int suitor, int pos);

//suitor status

bool CountessRestriction();
bool IsSuitorPlaying();
bool TargetHandmaidProtected();
void ChooseTargetSuitor(int target);

//suitor modifiers

void SwitchSuitor();
void DiscardPlayedCard();
void RemoveSuitor(int suitor);
void SetWinningTokenCount();

//deck modifiers

void ShuffleDeck();
void ResetDeck();

//card actions

void Spy();
void Guard();
void Priest();
void Baron();
void Handmaid();
void Prince();
void Chancellor();
void King(int aggresor, int victim);
void Princess();
void PlayCard();

//game states

void InitialSetup();
void BeginRound();
void SuitorTurn();
void EndRound();
void PlayGame();
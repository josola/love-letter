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

//Game functions.
void
PrintUpPile(),
PrintDeckSize(),
PrintSuitorsWithSpy(),
SwitchSuitor(),
DiscardPlayedCard(),
PrintActiveSuitors(),
ChooseTargetSuitor(int target),
PlayCard(),
InitialSetup(),
SuitorTurn(),
EndRound(),
PlayCard(),
ClearScreen(),
PlayGame(),
PrintSeperator(),
ClearInput(),
RemoveSuitor(int suitor),
SetWinningTokenCount(),
ShuffleDeck(),
ResetDeck(),
BeginRound();

void returnSuitor(int suitor);
void ClearScreen();
void PrintSeperator();
void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void PrintActiveSuitors();
void printHand(int suitor);

bool
TargetHandmaidProtected(),
ProperCardInput(),
CountessRestriction(),
IsSuitorPlaying(),
ProperSuitorInput(),
CardInHand(int suitor, int card),
ProperCardInput(),
ProperSuitorInput(),
ProperSuitorCount();

//Card functions.
void
Spy(),
Guard(),
Priest(),
Baron(),
Handmaid(),
Prince(),
Chancellor(),
King(),
Princess();

int HandPosition(int suitor, int pos);
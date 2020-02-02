/*
Jordan Sola 2019
Function delcarations that are used in Functions.cpp
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
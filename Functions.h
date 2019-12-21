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
PrintCurrentSuitorHand(),
ChooseTargetSuitor(),
PlayCard(),
InitialSetup(),
SuitorTurn(),
EndRound(),
PlayCard(),
ClearScreen(),
PlayGame(),
PrintSeperator(),
PrintTargetSuitorHand(),
ClearInput(),
RemoveSuitor(int suitor),
SetWinningTokenCount(),
ShuffleDeck(),
ResetDeck(),
BeginRound();

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

auto
CurrentSuitor(),
TargetSuitor();

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
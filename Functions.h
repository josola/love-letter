/*
Jordan Sola 2019
Function delcarations that are used in Functions.cpp
*/

#pragma once

//Game functions.
void
PrintFaceUpPile(),
PrintDeckSize(),
PrintSuitorsWithSpy(),
SwitchSuitor(),
DiscardPlayedCard(),
PrintActiveSuitors(),
PrintCurrentSuitorHand(),
ChooseTargetSuitor(),
RemoveSuitor(bool effectedSuitor),
PlayCard(),
InitialSetup(),
SuitorTurn(),
EndRound(),
PlayCard(),
ClearScreen(),
PlayGame();

bool
TargetHandmaidProtected(),
ProperCardInput(),
CardInHand(),
CountessRestriction(),
IsSuitorPlaying(),
ProperSuitorInput();

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

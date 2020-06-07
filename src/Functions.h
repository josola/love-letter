/*
 * Functions
 * Functions that determine gameplay capabilities.
 * Written by Jordan Sola 2019 2020
 * This software uses the MIT license.
 */

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void SwitchSuitor();
void DiscardPlayedCard();
void PrintActiveSuitors();
void ChooseTargetSuitor(int target);
void PlayCard();
void InitialSetup();
void SuitorTurn();
void EndRound();
void PlayCard();
void ClearScreen();
void PlayGame();
void PrintSeperator();
void ClearInput();
void RemoveSuitor(int suitor);
void SetWinningTokenCount();
void ShuffleDeck();
void ResetDeck();
void BeginRound();
void returnSuitor(int suitor);
void ClearScreen();
void PrintSeperator();
void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void PrintActiveSuitors();
void printHand(int suitor);
bool TargetHandmaidProtected();
bool ProperCardInput();
bool CountessRestriction();
bool IsSuitorPlaying();
bool ProperSuitorInput();
bool CardInHand(int suitor, int card);
bool ProperCardInput();
bool ProperSuitorInput();
bool ProperSuitorCount();
void Spy();
void Guard();
void Priest();
void Baron();
void Handmaid();
void Prince();
void Chancellor();
void King();
void Princess();
int HandPosition(int suitor, int pos);

#endif
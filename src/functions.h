/*
 * Functions
 * Functions that determine gameplay capabilities.
 * Written by Jordan Sola 2019 2020
 * This software uses the MIT license.
 */

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

//to go into an output header
void PrintUpPile();
void PrintDeckSize();
void PrintSuitorsWithSpy();
void PrintActiveSuitors();
void ClearScreen();
void PrintSeperator();
void returnSuitor(int suitor);
void printHand(int suitor);

//to go into an input header
void ClearInput();
bool ProperCardInput();
bool ProperSuitorInput();
bool ProperSuitorCount();

//to go into a suitor header
void SwitchSuitor();
void DiscardPlayedCard();
void ChooseTargetSuitor(int target);
void PlayCard();
void RemoveSuitor(int suitor);
bool TargetHandmaidProtected();
bool CountessRestriction();
bool IsSuitorPlaying();
bool CardInHand(int suitor, int card);
int HandPosition(int suitor, int pos);

//to go into a game state header
void InitialSetup();
void SuitorTurn();
void EndRound();
void PlayGame();
void SetWinningTokenCount();
void BeginRound();

//to go into a deck header
void ShuffleDeck();
void ResetDeck();

//to go into a card header
void Spy();
void Guard();
void Priest();
void Baron();
void Handmaid();
void Prince();
void Chancellor();
void King(int agressor, int victim);
void Princess();

#endif
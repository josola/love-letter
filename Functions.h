#pragma once

//Game functions.
bool TargetHasHandmaidProtection();
auto CurrentSuitor();
auto TargetSuitor();
bool CheckProperCardInput();
bool CheckCardIsInHand();
bool CheckCountessRestriction();
bool IsSuitorPlaying();
bool CheckProperSuitorInput();
void SwitchSuitor();
void DiscardPlayedCard();
void PrintActiveSuitors();
void PrintCurrentSuitorHand();
void PrintCurrentSuitorHand();
void ChooseTargetSuitor();
void RemoveSuitor(bool effectedSuitor);
void PlayCard();
void InitialSetup();
void SuitorTurn();
void EndRound();
void PlayCard();
void PlayGame();

//Card functions.
void Spy();
void Guard();
void Priest();
void Baron();
void Handmaid();
void Prince();
void Chancellor();
void King();
void Countess();
void Princess();
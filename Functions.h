#pragma once

//Game functions.
bool TargetHandmaidProtected();
auto CurrentSuitor();
auto TargetSuitor();
bool ProperCardInput();
bool CardInHand();
bool CountessRestriction();
bool IsSuitorPlaying();
bool ProperSuitorInput();
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
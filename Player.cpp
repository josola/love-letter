#include "Player.h"

//Constructor/Destructor
Player::Player(std::string name) : name(name) {};
Player::~Player() {};

//Member Functions
std::string Player::GetName() const { return name; }
bool Player::GetActiveStatus() const { return isActive; }
void Player::SetActiveStatus(bool status) { isActive = status; }
bool Player::GetOutStatus() const { return isOut; }
void Player::SetOutStatus(bool status) { isOut = status; }
bool Player::GetHandmaidStatus() const { return hasHandmaid; }
void Player::SetHandmaidStatus(bool status) { hasHandmaid = status; }
bool Player::GetSpyStatus() const { return hasSpy; }
void Player::SetSpyStatus(bool status) { hasSpy = status; }
int Player::GetTokenCount() const { return tokenCount; }
void Player::UpTokenCount() { tokenCount++; }
std::vector<int> Player::GetHand() const { return hand; }
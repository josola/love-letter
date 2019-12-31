#include "Player.h"
#include <iostream>

Player::Player(std::string name) : name(name)
{
    std::cout << "Constructing: " + name << std::endl;
    
};
Player::~Player()
{
    std::cout << "Destructing: " + name << std::endl;
};

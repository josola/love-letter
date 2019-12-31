#include "Input.h"
#include <iostream>

Input::Input() {};
Input::~Input() {};

void Input::ReceiveIntInput() { std::cin >> intInput; }
void Input::ReceiveStrInput() { std::cin >> strInput; }
void Input::ReceiveCharInput() { std::cin >> charInput; }

//Needs error Checking
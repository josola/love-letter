#include "Input.h"
#include <iostream>

Input::Input() {};
Input::~Input() {};

int Input::ReceiveIntInput()
{
	std::cin >> intInput;
	return intInput;
}
std::string Input::ReceiveStrInput()
{
	std::cin >> strInput;
	return strInput;
}
char Input::ReceiveCharInput()
{
	std::cin >> charInput;
	return charInput;
}
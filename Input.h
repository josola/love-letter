#pragma once
#include <string>

struct Input
{
public:
	Input();
	~Input();

	int intInput = 0;
	std::string strInput = " ";
	char charInput = ' ';
	
	void ReceiveIntInput();
	void ReceiveStrInput();
	void ReceiveCharInput();

	//Needs error Checking
};
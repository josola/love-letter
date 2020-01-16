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
	
	int ReceiveIntInput();
	std::string ReceiveStrInput();
	char ReceiveCharInput();
};
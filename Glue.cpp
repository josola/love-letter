#include "Glue.h"

Glue::Glue() {};
Glue::~Glue() {};

Log out;
Input in;

int Glue::GetPlayerCount()
{
	out.PrintStartupDialogue();
	in.ReceiveIntInput();
	return in.intInput;
}
#include "Glue.h"

Glue::Glue() {};
Glue::~Glue() {};

Log out;
Input in;
Check check;

int Glue::GetPlayerCount()
{
	out.PrintStartupDialogue();
	LOOP: if (check.PlayerCount(in.ReceiveIntInput()))
	{
		return in.intInput;
	}
	else
	{
		out.PrintInvalidInput();
		goto LOOP;
	}
}
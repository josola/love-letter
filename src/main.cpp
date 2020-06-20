/*
 * main.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "card.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "Enter number of players: ";
    int player_count = 0;
    while (player_count < 2 || player_count > 6)
    {
        cin >> player_count;
        if (player_count < 2 || player_count > 6)
        {
            cout << "Invalid input!" << endl;
            cin.clear();
        }
        else
        {
            break;
        }
    }
    return 0;
}

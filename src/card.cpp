/*
 * card.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "card.h"
#include <iostream>

using std::cout;
using std::endl;

Card::Card(const string name, const int value, const string description) : name_(name), description_(description), value_(value)
{
}

const string Card::GetName() const
{
    return name_;
}

const string Card::GetDescription() const
{
    return description_;
}

const int Card::GetValue() const
{
    return value_;
}

void Card::Print(int choice)
{
    switch (choice)
    {
    case 0:
        cout << name_;
        break;
    
    case 1:
        cout << value_;
        break;

    case 2:
        cout << description_;
        break;
        
    default:
        break;
    }
}

void Card::Action()
{
    cout << "CARD ACTION!" << endl;
}
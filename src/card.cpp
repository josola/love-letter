/*
 * card.cpp
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"
#include <iostream>

using std::cout;
using std::endl;

Card::Card(const string name, const int value, const string description) : name_(name), value_(value), description_(description)
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

void Card::PrintName() const
{
    cout << name_;
}

void Card::PrintValue() const
{
    cout << value_;
}

void Card::PrintDescription() const
{
    cout << description_;
}

void Card::Action(Player* player)
{
    cout << "CARD ACTION!" << endl;
}
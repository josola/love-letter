/*
 * card.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "card.h"



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
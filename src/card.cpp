/*
 * card.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "card.h"



Card::Card(const string name, const string description) : name_(name), description_(description)
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
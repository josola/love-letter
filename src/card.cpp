/*
 * card.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include "card.h"

Card::Card(const string name, const int value) : name_(name), value_(value){};
const string Card::GetName()
{
    return name_;
}
const int Card::GetValue()
{
    return value_;
}
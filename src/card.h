/*
 * card.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Card
{
public:
    Card(const string name = "", const int value = 0, const string description = "");
    const string GetName() const;
    const string GetDescription() const;
    const int GetValue() const;
    void Print(int choice);

protected:
    string name_ = "";
    string description_ = "";
    int value_ = 0;
};

#endif

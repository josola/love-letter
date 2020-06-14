/*
 * card.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <fstream>
#include <streambuf>

using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

class Card
{
public:
    Card(const string name, const int value);
    const string GetName();
    const int GetValue();

protected:
    string name_ = "";
    int value_ = 0;

};

#endif

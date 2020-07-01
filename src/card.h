/*
 * card.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#ifndef CARD_H
#define CARD_H

#include "player.h"
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
    void PrintName() const;
    void PrintValue() const;
    void PrintDescription() const;
    virtual void Action(Player* player);

protected:
    string name_ = "";
    string description_ = "";
    int value_ = 0;
};

#endif

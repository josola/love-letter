/*
 * prince.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"

class Prince : virtual public Card
{
public:
    Prince();
    virtual void Action();

protected:
};
/*
 * king.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"

class King : virtual public Card
{
public:
    King();
    virtual void Action();
    
protected:
};
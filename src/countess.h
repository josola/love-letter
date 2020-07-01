/*
 * countess.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"

class Countess : virtual public Card
{
public:
    Countess();
    virtual void Action();
    
protected:
};
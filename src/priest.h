/*
 * priest.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"

class Priest : virtual public Card
{
public:
    Priest();
    virtual void Action();
    
protected:
};
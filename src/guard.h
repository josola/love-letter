/*
 * guard.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"
#include <string>

using std::string;

class Guard : virtual public Card
{
public:
    Guard();
    virtual void Action();

protected:

};
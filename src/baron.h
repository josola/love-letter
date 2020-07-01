/*
 * baron.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"
#include <string>

using std::string;

class Baron : virtual public Card
{
public:
    Baron();
    virtual void Action();

protected:

};
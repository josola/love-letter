/*
 * chancellor.h
 * (C) Jordan Sola 2019/2020 - MIT License
 */

#include "card.h"
#include <string>

using std::string;

class Chancellor : virtual public Card
{
public:
    Chancellor();
    virtual void Action();

protected:

};
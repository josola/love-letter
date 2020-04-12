/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_h
#define CARD_h

#include <string>

using std::string;

class CardMdl
{
protected:
    string name = "";
    int value = 0;
};

class CardInterface : virtual public CardMdl
{
public:
    CardInterface(string name, int value) : CardMdl{} { SetName(name), SetValue(value); };

    //getters
    string Name();
    int Value();

    //setters
    void SetName(string input);
    void SetValue(int input);
};

class CardUtl : virtual public CardInterface
{
public:
    CardUtl(string name, int value) : CardInterface{ name, value } {};

    CardUtl Builder(int input);
};

#endif
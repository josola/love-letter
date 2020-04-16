/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_h
#define CARD_h

#include <string>

using std::string;

class CardModel
{
protected:
    string name = "";
    int value = 0;
};

class CardInterface : public CardModel
{
public:
    CardInterface(string name, int value) : CardModel{} { SetName(name), SetValue(value); };

    //getters
    string Name();
    int Value();

    //setters
    void SetName(string input);
    void SetValue(int input);
};

class CardController : public CardInterface
{
public:
    CardController(string name, int value) : CardInterface{ name, value } {};

    CardController Builder(int input);
};

#endif
#pragma once
#include <vector>
#include <string>

struct Log
{
public:
    Log();
    ~Log();
    
    void PrintVector(std::vector<int> vect) const;
    void PrintName(std::string name) const;
    void PrintCard(int cardNum) const;
    void PrintVectSize(std::vector<int> vect) const;
    void PrintStartupDialogue() const;
    void PrintIntInput(int input) const;
    void PrintStrInput(std::string input) const;
    void PrintCharInput(char input) const;
    void PrintInvalidInput() const;
};

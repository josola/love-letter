#pragma once
#include <iostream>
#include <vector>

struct Log
{
public:
    Log();
    ~Log();
    
    void PrintVector(std::vector<int> vect) const;
    void PrintName(std::string name) const;
    void PrintCard(int cardNum) const;
    void PrintVectSize(std::vector<int> vect) const;
};

#pragma once
#include <vector>

class Deck
{
private:
    int const
    spy = 0, guard = 1, priest = 2, baron = 3, handmaid = 4,
    prince = 5, chancellor = 6, king = 7, countess = 8, princess = 9;
    
    std::vector<int> numDeck
    {
        spy, spy, guard, guard, guard, guard, guard, guard, priest, priest,
        baron, baron, prince, prince, chancellor, chancellor, king, countess, princess
    };
    
public:
    Deck();
    ~Deck();
    
    std::vector<int> GetDeck() const;
    int AcquireCard(int pos);
    bool RemoveCard(int cardPosition);
};

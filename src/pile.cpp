#include "pile.h"
#include "card.h"
#include <algorithm>
#include <iterator>

using std::distance;
using std::exception;
using std::find;
using std::iterator;

template <class T>
T Pile<T>::Remove(T obj)
{
  if (typeid(obj) == typeid(Card))
  {
    typename vector<T>::iterator it =
        find(pile_.begin(), pile_.end(), [obj](T &i) { return i == obj; });
    if (it != pile_.end())
    {
      int index = distance(pile_.begin(), it);
      pile_.erase(pile_.begin() + index);
      return *it;
    }
    else
    {
      throw exception("Object not in pile!");
      return;
    }
  }
  else
  {
    if (typeid(obj) == typeid(int) && obj < 0 || obj > pile_.size())
    {
      throw exception("Object location out of range");
    }
    else
    {
      return pile_.at(obj);
      pile_.erase(pile_.begin() + obj);
    }
  }
  return;
}

template <class T>
void Pile<T>::Clear()
{
  if (pile_.empty())
  {
    throw exception("Pile is already empty!");
  }
  else
  {
    pile_.clear(pile_.begin(), pile_.end());
    if (!pile_.empty())
    {
      throw exception("Erase did not work!");
    }
  }
}

template <class T>
void Pile<T>::InsertBottom(T &obj) { pile_.push_back(obj); }

template <class T>
int Pile<T>::Size() const { return pile_.size(); }

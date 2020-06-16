/*
 * pile.h
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#ifndef PILE_H
#define PILE_H

#include <vector>

using std::vector;

template <class T>
class Pile
{
public:
	T Remove(T obj);
	void Clear();
	void InsertBottom(T &obj);
	int Size() const;

protected:
	vector<T> pile_;

};

#endif // !PILE_H

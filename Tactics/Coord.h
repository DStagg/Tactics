#ifndef COORD_H
#define COORD_H

#include <math.h>

struct Coord
{
public:

	Coord(int x = 0, int y = 0)
	{
		_X = x;
		_Y = y;
	};

	int _X, _Y;

	friend bool operator==(const Coord& ca, const Coord& cb)
	{
		return ((ca._X == cb._X) && (ca._Y == cb._Y));
	};

	friend bool operator<(const Coord& ca, const Coord& cb)
	{
		return ca.Size() < cb.Size();
	};

	friend bool operator>(const Coord& ca, const Coord& cb)
	{
		return ca.Size() > cb.Size();
	};

	friend bool operator<=(const Coord& ca, const Coord& cb)
	{
		return ca.Size() <= cb.Size();
	};

	friend bool operator>=(const Coord& ca, const Coord& cb)
	{
		return ca.Size() >= cb.Size();
	};

	friend bool operator!=(const Coord& ca, const Coord& cb)
	{
		return !((ca._X == cb._X) && (ca._Y == cb._Y));
	};

	float Size() const
	{
		return sqrtf(((float)_X * (float)_X) + ((float)_Y * (float)_Y));
	};
};



#endif
#ifndef UNIT_MAP_H
#define UNIT_MAP_H

#include "Coord.h"
#include "GraphicUnit.h"

struct UnitPos
{
	Coord _Position;
	GraphicUnit _Unit;
	bool _Occupied;

	UnitPos()
	{
		_Occupied = false;
	}

	UnitPos(Coord c, GraphicUnit g)
	{
		_Occupied = true;
		_Position = c;
		_Unit = g;
	}
};

class UnitMap
{
public:

	UnitMap();

	bool Occupied(int x, int y);
	GraphicUnit& UnitAt(int x, int y);
	int CountUnits();

	Coord& GetCoord(int i);
	GraphicUnit& GetUnit(int i);

	void AddUnit(int x, int y, GraphicUnit unit);
	void DelUnit(int x, int y);

private:

	GraphicUnit _DefaultUnit;
	Coord _DefaultCoord;
	std::vector<UnitPos> _Units;
};

#endif
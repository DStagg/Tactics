#include "UnitMap.h"

UnitMap::UnitMap()
{

};

bool UnitMap::Occupied(int x, int y)
{
	for (int i = 0; i < CountUnits(); i++)
	{
		if (_Units[i]._Position == Coord(x, y))
			return true;
	}
	return false;
};
GraphicUnit& UnitMap::UnitAt(int x, int y)
{
	for (int i = 0; i < CountUnits(); i++)
	{
		if (_Units[i]._Position == Coord(x, y))
			return _Units[i]._Unit;
	}
	return _DefaultUnit;
};
int UnitMap::CountUnits()
{
	return (int)_Units.size();
};

Coord& UnitMap::GetCoord(int i)
{
	if ((i < 0) || (i >= CountUnits()))
		return _DefaultCoord;
	return _Units[i]._Position;
};
GraphicUnit& UnitMap::GetUnit(int i)
{
	if ((i < 0) || (i >= CountUnits()))
		return _DefaultUnit;
	return _Units[i]._Unit;
};

void UnitMap::AddUnit(int x, int y, GraphicUnit unit)
{
	for (int i = 0; i < CountUnits(); i++)
	{
		if (_Units[i]._Position == Coord(x, y))
		{
			_Units[i]._Unit = unit;
			return;
		}
	}
	_Units.push_back(UnitPos(Coord(x, y), unit));
};
void UnitMap::DelUnit(int x, int y)
{
	for (int i = 0; i < CountUnits(); i++)
	{
		if (_Units[i]._Position == Coord(x, y))
		{
			_Units.erase(_Units.begin() + i);
			return;
		}
	}
};

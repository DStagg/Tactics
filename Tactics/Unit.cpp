#include "Unit.h"

Unit::Unit(int hp, int atk, int def, int team)
{
	_Health = Stat(hp);
	_Attack = Stat(atk);
	_Defense = Stat(def);
	_Alive = true;
	_Team = team;
};

Stat& Unit::GetHP()
{
	return _Health;
};
Stat& Unit::GetAtk()
{
	return _Attack;
};
Stat& Unit::GetDef()
{
	return _Defense;
};
bool& Unit::GetAlive()
{
	return _Alive;
};
int& Unit::GetTeam()
{
	return _Team;
};
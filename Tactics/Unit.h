#ifndef UNIT_H
#define UNIT_H

struct Stat
{
	int _Base;
	int _Current;

	Stat(int base, int current)
	{
		_Base = base;
		_Current = current;
	};
	Stat(int both = 0)
	{
		_Base = both;
		_Current = both;
	};

	void Reset()
	{
		_Current = _Base;
	};

};

class Unit
{
public:

	Unit(int hp = 0, int atk = 0, int def = 0, int team = 0);

	Stat& GetHP();
	Stat& GetAtk();
	Stat& GetDef();
	bool& GetAlive();
	int& GetTeam();
	
private:

	Stat _Health;
	Stat _Attack;
	Stat _Defense;
	bool _Alive;
	int _Team;
};

#endif
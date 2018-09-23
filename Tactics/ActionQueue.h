#ifndef ACTION_QUEUE_H
#define ACTION_QUEUE_H

#include <queue>

struct Action
{
	std::string _Type;
	int _SourceX, _SourceY;
	int _TargetX, _TargetY;

	Action(std::string type, int sx, int sy, int tx, int ty)
	{
		_Type = type;
		_SourceX = sx;
		_SourceY = sy;
		_TargetX = tx;
		_TargetY = ty;
	};
};

class ActionQueue
{
public:

	void QueueAction(std::string type, int sx, int sy, int tx, int ty);
	void QueueAction(Action a);
	Action PeekAction();
	Action PopAction();

	int CountActions();

private:

	std::queue<Action> _Actions;

};

#endif
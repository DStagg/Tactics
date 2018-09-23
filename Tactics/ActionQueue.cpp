#include "ActionQueue.h"

void ActionQueue::QueueAction(std::string type, int sx, int sy, int tx, int ty)
{
	QueueAction(Action(type, sx, sy, tx, ty));
}

void ActionQueue::QueueAction(Action a)
{
	_Actions.push(a);
};

Action ActionQueue::PeekAction()
{
	return _Actions.front();
};

Action ActionQueue::PopAction()
{
	Action temp = _Actions.front();
	_Actions.pop();
	return temp;
}

int ActionQueue::CountActions()
{
	return (int)_Actions.size();
};
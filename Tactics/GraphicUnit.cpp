#include "GraphicUnit.h"

GraphicUnit::GraphicUnit() : Unit()
{
	
};

void GraphicUnit::SetSprite(sf::Sprite spr)
{
	_Sprite = spr;
};
sf::Sprite& GraphicUnit::GetSprite()
{
	return _Sprite;
};

void GraphicUnit::Draw(sf::RenderWindow* rw, int x, int y)
{
	_Sprite.setPosition((float)x, (float)y);

	rw->draw(_Sprite);
};
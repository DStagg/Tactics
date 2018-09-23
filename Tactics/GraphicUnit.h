#ifndef GRAPHIC_UNIT_H
#define GRAPHIC_UNIT_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class GraphicUnit : public Unit
{
public:

	GraphicUnit();

	void SetSprite(sf::Sprite spr);
	sf::Sprite& GetSprite();

	void Draw(sf::RenderWindow* rw, int x, int y);



private:

	sf::Sprite _Sprite;
};

#endif
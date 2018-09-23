#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};
MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	

};
void MainScene::End()
{

};
void MainScene::Pause()
{

};
void MainScene::Resume()
{

};
void MainScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code) 
			{
			case sf::Keyboard::Escape:
				GetManager()->Quit();

			default:
				break;
			}
	}

};
void MainScene::DrawScreen()
{

};

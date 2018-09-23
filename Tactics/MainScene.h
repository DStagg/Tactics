#ifndef MainScene_H
#define MainScene_H

#include "Framework/Utility/Utility.h"
#include "Framework/SFMLScene.h"

#include "Framework\Data\Grid.h"
#include "Framework\Data\CompositeTex.h"

#include "Framework\IO\ImageManager.h"
#include "Framework\IO\MouseInput.h"

class MainScene : public SFMLScene
{
public:

	MainScene(sf::RenderWindow* rw);
	~MainScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:


};

#endif
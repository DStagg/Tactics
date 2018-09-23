#ifndef MainScene_H
#define MainScene_H

#include "Framework/Utility/Utility.h"
#include "Framework/SFMLScene.h"

#include "Framework\Data\Grid.h"
#include "Framework\Data\CompositeTex.h"

#include "Framework\IO\ImageManager.h"
#include "Framework\IO\MouseInput.h"

#include "GraphicUnit.h"
#include "Coord.h"
#include "UnitMap.h"

#include "ActionQueue.h"

#define Tile_Width 32
#define Tile_Height 32

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
	
	ActionQueue _ActionQueue;

	ImageManager _ImgMan;
	SFMLMouseInput _MouseInput;
	
	UnitMap _UnitMap;
	Coord _SelectedTile;
	
	sf::View _CameraView;
	int _CameraPanX, _CameraPanY;
	
	void ProcessAction(Action a);
};

#endif
#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};

MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	//	Initialise the selected tile to [-1, -1] i.e. no tile selected
	_SelectedTile = Coord(-1, -1);

	//	Initialise the camera view to the default
	_CameraView = _Window->getDefaultView();

	//	Initialise the mouse input helper
	_MouseInput.Init(_Window);
	
	//	Load test data into the unit list
	GraphicUnit temp;
	temp.GetHP() = Stat(1);
	temp.GetAtk() = Stat(1);
	temp.SetSprite(sf::Sprite(*_ImgMan.GetTexturePntr("DEFAULT")));
	_UnitMap.AddUnit(1, 1, temp);
	_UnitMap.AddUnit(3, 2, temp);
	_UnitMap.AddUnit(2, 0, temp);

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
				break;
			case sf::Keyboard::BackSpace:
				_CameraView = _Window->getDefaultView();
				break;
			default:
				break;
			}
		else if (Event.type == sf::Event::MouseMoved)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
				_CameraView.move((float)_CameraPanX - Event.mouseMove.x, (float)_CameraPanY - Event.mouseMove.y);

			_CameraPanX = Event.mouseMove.x;
			_CameraPanY = Event.mouseMove.y;
		}
		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			//	Calculate world coordinates, inc. map coordinates
			PairInt pos = _MouseInput.GetWorldPos();
			int col = (int)floor((float)pos._A / (float)Tile_Width);
			int row = (int)floor((float)pos._B / (float)Tile_Height);

			if (Event.mouseButton.button == sf::Mouse::Button::Left)		//	Left Click - select, de-select
			{
				if ((col < 0) || (row < 0))	//	TODO: check for if greater than the map size once that's implemented
					_ActionQueue.QueueAction("SELECT_TILE", _SelectedTile._X, _SelectedTile._Y, -1, -1);	
				else
					_ActionQueue.QueueAction("SELECT_TILE", _SelectedTile._X, _SelectedTile._Y, col, row);	
			}
			else if (Event.mouseButton.button == sf::Mouse::Button::Right)	//	Right Click - move, attack
			{
				if ((col < 0) || (row < 0))	//	TODO: check for if greater than the map size once that's implemented
				{
				}
				else
				{
					if (_UnitMap.Occupied(_SelectedTile._X, _SelectedTile._Y))						//	Move the selected unit (does not currently check if the destination square is occupied)
					{
						_ActionQueue.QueueAction("TRY_MOVE", _SelectedTile._X, _SelectedTile._Y, col, row);
						_ActionQueue.QueueAction("SELECT_TILE", _SelectedTile._X, _SelectedTile._Y, -1, -1);
					}
				}
			}
		}
	}
	while (_ActionQueue.CountActions() > 0)
		ProcessAction(_ActionQueue.PopAction());
	for (int i = 0; i < _UnitMap.CountUnits(); i++)
	{
		if (!_UnitMap.GetUnit(i).GetAlive())
			_UnitMap.DelUnit(_UnitMap.GetCoord(i)._X, _UnitMap.GetCoord(i)._Y);
	}
};

void MainScene::DrawScreen()
{
	//	Set the camera view for unit & map rendering
	_Window->setView(_CameraView);

	//	Draw a temporary background
	//	TODO: set the background to the proper size, once map size is implemented
	//	TODO: make the background fancier than a block shape
	sf::RectangleShape background(sf::Vector2f(352.f, 352.f));
	background.setFillColor(sf::Color(255, 255, 255, 155));
	_Window->draw(background);

	//	Draw the units in the unit list
	for (int i = 0; i < _UnitMap.CountUnits(); i++)
	{
		_UnitMap.GetUnit(i).Draw(_Window, _UnitMap.GetCoord(i)._X * Tile_Width, _UnitMap.GetCoord(i)._Y * Tile_Height);
	}

	//	Draw the tile selection highlight
	if (_SelectedTile != Coord(-1, -1))
	{
		sf::RectangleShape rect(sf::Vector2f((float)Tile_Width, (float)Tile_Height));
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(2.f);
		rect.setPosition(_SelectedTile._X * Tile_Width, _SelectedTile._Y * Tile_Height);
		_Window->draw(rect);
	}

	//	Reset the camera view for UI rendering
	_Window->setView(_Window->getDefaultView());


	//	Set the camera view (for input assistance in the next frame)
	_Window->setView(_CameraView);
};

void MainScene::ProcessAction(Action a)
{
	if (a._Type == "SELECT_TILE")
	{
		if ((a._TargetX < 0) || (a._TargetY < 0))	//	TODO: Check for outside of map bounds
			_SelectedTile = Coord(-1, -1);
		else if ((_SelectedTile != Coord(-1, -1)) && (_UnitMap.Occupied(a._SourceX, a._SourceY)) && (!_UnitMap.Occupied(a._TargetX, a._TargetY)))
			_SelectedTile = Coord(-1, -1);
		else
			_SelectedTile = Coord(a._TargetX, a._TargetY);
	}
	else if (a._Type == "MOVE_UNIT")
	{
		if ((a._SourceX == a._TargetX) && (a._SourceY == a._TargetY)) return;

		GraphicUnit temp = _UnitMap.UnitAt(a._SourceX, a._SourceY);
		_UnitMap.DelUnit(a._SourceX, a._SourceY);
		_UnitMap.AddUnit(a._TargetX, a._TargetY, temp);
		_ActionQueue.QueueAction("SELECT_TILE", _SelectedTile._X, _SelectedTile._Y, a._TargetX, a._TargetY);
	}
	else if (a._Type == "ATTACK_UNIT")
	{
		if (!_UnitMap.Occupied(a._SourceX, a._SourceY)) return;
		if (!_UnitMap.Occupied(a._TargetX, a._TargetY)) return;
		if ((a._SourceX == a._TargetX) && (a._SourceY == a._TargetY)) return;

		int dmg = _UnitMap.UnitAt(a._SourceX, a._SourceY).GetAtk()._Current - _UnitMap.UnitAt(a._TargetX, a._TargetY).GetDef()._Current;
		_UnitMap.UnitAt(a._TargetX, a._TargetY).GetHP().Mod(-dmg);
		if (_UnitMap.UnitAt(a._TargetX, a._TargetY).GetHP()._Current <= 0) _UnitMap.UnitAt(a._TargetX, a._TargetY).GetAlive() = false;
	}
	else if (a._Type == "TRY_MOVE")
	{
		if (!_UnitMap.Occupied(a._SourceX, a._SourceY)) return;
		if ((a._SourceX == a._TargetX) && (a._SourceY == a._TargetY)) return;
		
		if (_UnitMap.Occupied(a._TargetX, a._TargetY))
			_ActionQueue.QueueAction("ATTACK_UNIT", a._SourceX, a._SourceY, a._TargetX, a._TargetY);
		else
			_ActionQueue.QueueAction("MOVE_UNIT", a._SourceX, a._SourceY, a._TargetX, a._TargetY);
	}






	
};
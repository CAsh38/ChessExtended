#pragma once
#include "PlayerManager.h"
#include "Foundations.h"
#include "Defines.h"
#include "Board.h"
#include <iostream>
#include <list>

using SceneObject = std::variant<TextBox, Button, ClasicSquareBoard>;
using Scene = std::list<struct SceneWrap>;
using Object2D = std::variant<Rectangle>;

typedef struct SceneWrap
{
	std::list <SceneObject> Storage;
	Rectangle Border{};
} SceneWrap;

using SceneList = std::list<Scene>;

class SceneManager
{
protected: 
	
	/*Placeholder for all scene logic implemented as singleton*/
	SceneManager() = default;
	static SceneManager* instance;

	// Delete copy constructor and assignment
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

public:
	
	static SceneManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new SceneManager();
		return instance;
	}

	SceneList sceneStack = {};

	Color BackGroundColor = {};

	Scene GetMainMenu()
	{
		SceneWrap Container; Scene scene;
		TextBox PlayText = TextBox((std::string)"Play", MAIN_MENU_BUTTON_FONT, 0,
			PLAY_BUTTON_POSY, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_FONT_SIZE);
		Button PlayButton = Button(PlayText, PlayTheFuckingGame, MOUSE_LEFT_BUTTON);
		Container.Storage.push_back(PlayButton);
		TextBox SettingsButton = TextBox((std::string)"Settings", MAIN_MENU_BUTTON_FONT, 0,
			PLAY_BUTTON_POSY + MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_FONT_SIZE);
		Container.Storage.push_back(SettingsButton);
		TextBox ExitText = TextBox((std::string)"Exit", MAIN_MENU_BUTTON_FONT, 0,
			PLAY_BUTTON_POSY + 2 * MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_FONT_SIZE);
		Button ExitButton = Button(ExitText, ExitApp, MOUSE_LEFT_BUTTON);
		Container.Storage.push_back(ExitButton);
		Container.Border = Rectangle(0, PLAY_BUTTON_POSY, MAIN_MENU_BUTTON_WIDTH, 3 * MAIN_MENU_BUTTON_HEIGHT);
		scene.push_back(Container);
		BackGroundColor = BLACK;
		return scene;
	};
	Scene GetStandardBoardScene(Player *user, Player *opp)
	{
		StrVector mods = {};
		std::string wrap = "standard";
		SceneWrap Container; Scene scene;
		Rectangle rect = Rectangle(60, 60, 120, 120);
		ClasicSquareBoard board(8, 8, wrap, mods, user, opp, rect);
		Rectangle chungus = Rectangle(60, 60, 960, 960);
		StrColor colors = {}; colors.push_back(CURRANT); colors.push_back(WHITE);
		board.TransformBoard(colors);
		Container.Storage.push_back(board);
		Container.Border = chungus;
		scene.push_back(Container);
		BackGroundColor = BUTTER_YELLOW;
		return scene;
	}
};	

void DrawSceneOnScreen(Scene& scene);
void RespondToPlayerInput(Scene scene);

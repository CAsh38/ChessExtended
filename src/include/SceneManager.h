#pragma once
#include "Foundations.h"
#include "Defines.h"
#include <iostream>

using SceneObject = std::variant<TextBox, Button>;

typedef struct SceneWrap
{
	std::list <SceneObject> Storage;
	Rectangle Border{};
} SceneWrap;

using Scene = std::list<struct SceneWrap>;

using Object2D = std::variant<Rectangle>;

class SceneManager
{
public:
	Scene GetMainMenu()
	{
		SceneWrap Container; Scene scene;
		TextBox PlayButton = TextBox((std::string)"Play", MAIN_MENU_BUTTON_FONT, 0,
			PLAY_BUTTON_POSY, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_FONT_SIZE);
		Container.Storage.push_back(PlayButton);
		TextBox SettingsButton = TextBox((std::string)"Settings", MAIN_MENU_BUTTON_FONT, 0,
			PLAY_BUTTON_POSY + MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_FONT_SIZE);
		Container.Storage.push_back(SettingsButton);
		TextBox ExitText = TextBox((std::string)"Exit", MAIN_MENU_BUTTON_FONT, 0,
			PLAY_BUTTON_POSY + 2 * MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_FONT_SIZE);
		Button ExitButton = Button(ExitText, ExitApp, MOUSE_LEFT_BUTTON);
		Container.Storage.push_back(ExitButton);
		Container.Border.x = 0;
		Container.Border.y = PLAY_BUTTON_POSY;
		Container.Border.width = MAIN_MENU_BUTTON_WIDTH;
		Container.Border.height = MAIN_MENU_BUTTON_HEIGHT * 3;
		scene.push_back(Container);
		return scene;
	};
};

void DrawSceneOnScreen(Scene scene);
void RespondToPlayerInput(Scene scene);

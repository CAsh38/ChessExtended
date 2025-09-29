#include "include/SceneManager.h"

void DrawSceneOnScreen(Scene scene)
{
	for (const auto& scene_item : scene)
	{
		for (const auto& item : scene_item.Storage)
		{
			if (std::holds_alternative<TextBox>(item))
			{
				TextBox text = std::get<TextBox>(item);
				DrawText(text.Text.c_str(), text.Box.x, text.Box.y, text.Font_Size, WHITE);
			}
			else if (std::holds_alternative<Button>(item))
			{
				TextBox text = std::get<Button>(item).Text;
				DrawText(text.Text.c_str(), text.Box.x, text.Box.y, text.Font_Size, WHITE);
			}
		}
	}
}

void RespondToPlayerInput(Scene scene)
{
	int x = GetMouseX(), y = GetMouseY();
	for (const auto& scene_item : scene)
	{

	}
}

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

static bool IsCursorHoveringInsideObject(Object2D obj, int x, int y)
{
	if (std::holds_alternative<Rectangle>(obj))
	{
		Rectangle rect = std::get<Rectangle>(obj);
		if (rect.x + rect.width < x || rect.y - rect.height > y) return 0;
		if (rect.x > x || rect.y < y) return 0;
		return 1;
	}
}

void RespondToPlayerInput(Scene scene)
{
	int x = GetMouseX(), y = GetMouseY();
	for (const auto& scene_item : scene)
	{
		if (IsCursorHoveringInsideObject(scene_item.Border, x , y))
		{
			for (const auto& item : scene_item.Storage)
			{
				if (std::holds_alternative<Button>(item))
				{
					Button button = std::get<Button>(item);
					if (IsCursorHoveringInsideObject(button.Text.Box, x, y))
					{
						int key = button.Binding;
						if (IsKeyPressed(key)) button.Function();
					}
				}
			}
		}
	}
}

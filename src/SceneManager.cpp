#include "include/SceneManager.h"


extern Scene ActualScene;
SceneManager* SceneManager::instance = nullptr;

void DrawSceneOnScreen(Scene scene)
{
	for (const auto& scene_item : scene)
	{
		for (const auto& item : scene_item.Storage)
		{
			if (std::holds_alternative<TextBox>(item))
			{
				TextBox text = std::get<TextBox>(item);
				DrawText(text.Text.c_str(), text.Box.x, text.Box.y + text.Box.height, text.Font_Size, WHITE);
			}
			else if (std::holds_alternative<Button>(item))
			{
				TextBox text = std::get<Button>(item).Text;
				DrawText(text.Text.c_str(), text.Box.x, text.Box.y + text.Box.height, text.Font_Size, WHITE);
			}
			else if (std::holds_alternative<ClasicSquareBoard>(item))
			{
				ClasicSquareBoard board = std::get<ClasicSquareBoard>(item);
				board.DrawingMethod();
			}
		}
	}
}

static bool IsCursorHoveringInsideObject(Object2D obj, int x, int y)
{
	if (std::holds_alternative<Rectangle>(obj))
	{
		Rectangle rect = std::get<Rectangle>(obj);
		if ((rect.x + rect.width) < x || (rect.y + rect.height) < y) return 0;
		if (rect.x > x || rect.y > y) return 0;
		return 1;
	}
	else return 0;
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
						if (IsMouseButtonDown(key)) button.Function();
						if (IsKeyDown(key)) button.Function();
					}
				}
			}
		}
	}
}

int ExitApp()
{
	EXIT = 1;
	std::exit(0);
	return 0;
}

int PlayTheFuckingGame()
{
	SceneManager* thatSceneMan = SceneManager::GetInstance();
	ActualScene = thatSceneMan->GetStandardBoardScene();
	return 0;
}
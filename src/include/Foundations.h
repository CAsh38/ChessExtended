#pragma once
#include <variant>
#include <vector>
#include <string>
#include "raylib.h"

typedef std::vector<std::variant<int, float, double, char, std::string, char*>> Info;

extern bool EXIT;

class TextBox
{
public:
	std::string Text, Font;
	Rectangle Box;
	char rounded;
	int Font_Size;
	float opacity;
	TextBox(std::string text, std::string font, float X, float Y, float Width, float Height, int font_size)
	{
		Box.x = X; Box.y = Y;
		Box.width = Width; Box.height = Height;
		Text = text; Font = font;
		Font_Size = font_size;
		opacity = 100;
		rounded = 0;
	}
	void DrawBorders(float lineThickness, Color color)
	{
		Rectangle improptu = Box;
		Box.y += Box.height;
		if (!rounded) DrawRectangleLinesEx(Box, lineThickness, color);
	}
};

class Button
{
public:
	TextBox Text;
	int Binding;
	int (*Function)();
	Button(TextBox text, int (*function)(), int binding)
		: Text(std::move(text)), Function(function), Binding(binding) {}
};

int ExitApp();
int PlayTheFuckingGame();
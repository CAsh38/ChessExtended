#pragma once
#include <string>
#include "raylib.h"

class Board
{
public:
	__int32 Length, Height;
	std::string Topology, * modifications = nullptr;

	Board(int L, int H, std::string topology, std::string* mods)
	{
		Length = L, Height = H;
		Topology = topology;
		modifications = mods;
	}
};

class ClasicSquareBoard : public Board
{
public:
	using Board::Board;

};

class TextBox
{
public:
	std::string Text, Font;
	Rectangle Box;
	int Font_Size;
	float opacity;
	TextBox(std::string text, std::string font, float X, float Y, float Width, float Height, int font_size)
	{
		Box.x = X; Box.y = Y;
		Box.width = Width; Box.height = Height;
		Text = text; Font = font;
		Font_Size = font_size;
		opacity = 100;
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
	/*Button(TextBox text, int (*function)())
	{
		Text = std::move(text);
		Function = function;
	}*/
};
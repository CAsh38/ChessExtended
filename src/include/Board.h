#pragma once
#include <string>
#include <vector>
#include <functional>
#include "Pieces.h"
#include "LinkedLists.h"
#include "raylib.h"

namespace LLSC = LinkedLists::SimpleCircular;

typedef std::vector<std::string> StrVector;
typedef std::vector<Color> StrColor;

class Board
{
public:
	int Length, Height;
	std::string Topology;
	StrVector modifications;

	Board(int L, int H, std::string topology, StrVector mods)
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
	Rectangle LeftMostRectangle;
	LLSC::CircularLinkedList<Color> ColorTypes;
	std::function<void()> DrawingMethod = NULL;

	ClasicSquareBoard() = default;

	void TransformBoard(StrColor colors, Rectangle Base)
	{
		ColorTypes.Init(colors[0]);
		for (int i = 1; i < colors.size(); i++) ColorTypes.InsertAt(ColorTypes.size, colors[i]);
		LeftMostRectangle = Base;
		if (Topology == "standard") DrawingMethod = [this]() {DrawStandardBoard(); };
	}

	ClasicSquareBoard(const ClasicSquareBoard& other)
		: Board(other.Length, other.Height, other.Topology, other.modifications),
		LeftMostRectangle(other.LeftMostRectangle),
		ColorTypes(other.ColorTypes)
	{
		if (other.Topology == "standard")
			DrawingMethod = [this]() { DrawStandardBoard(); };
	}

	ClasicSquareBoard& operator=(const ClasicSquareBoard& other)
	{
		if (this == &other) return *this;

		// cleanup current data
		ColorTypes.~CircularLinkedList();

		new (&ColorTypes) LLSC::CircularLinkedList<Color>();
		*this = ClasicSquareBoard(other);
		return *this;
	}

protected: void DrawStandardBoard()
	{
		LinkedLists::Node<Color> *now = ColorTypes.GetAt(0);
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Length; j++)
			{
				DrawRectangle(j * LeftMostRectangle.width + LeftMostRectangle.x, 
					i * LeftMostRectangle.height + LeftMostRectangle.y, LeftMostRectangle.width,
					LeftMostRectangle.height, now->data);
				now = now->next;
			}
			now = now->next;
		}
	}
};
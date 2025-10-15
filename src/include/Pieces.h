#pragma once
#include <string>
#include <functional>
#include "raylib.h"
#include "Defines.h"

typedef std::vector<std::string> StrVector;

class Piece
{
public:
	unsigned ID, Value;
	int posX, posY;
	Texture2D* texture;
	std::string Name;
	std::vector<Vector2> Moves, Takes;
	std::vector<std::function<void()>> Properties;
	Piece(int id, unsigned value, std::string name, int x, int y, Texture2D* text) : 
		ID(id), Value(value), Name(name), posX(x), posY(y), texture(text) {}
};

class StandardPiece : public Piece
{
public:
	using Piece::Piece;
	void SetProperties(StrVector strs)
	{
		for (int i = 0; i < strs.size(); i++)
		{
			std::function<void()> method = NULL;
			if (strs[i] == "PawnPush") method = [this]() {PawnPush(); };
			Properties.push_back(method);
		}
	}
	void SetStructure()
	{
		if (Name == "Pawn") getPawnStructure();
	}

	void getPawnStructure()
	{
		Vector2 vec = {};
		vec.x = 0, vec.y = -1;
		Moves.push_back(vec);
		vec.x = 1; 
		Takes.push_back(vec);
		vec.x = -1;
		Takes.push_back(vec);
		return;
	}
	void PawnPush()
	{
		if (posY == 6)
		{
			Vector2 vec = {};
			vec.x = 0, vec.y = -2;
			Moves.push_back(vec);
		}
		return;
	}
};

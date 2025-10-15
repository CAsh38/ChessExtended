#pragma once
#include <variant>
#include <list>
#include <algorithm>
#include "Pieces.h"
#include "Defines.h"

typedef std::list<std::variant<StandardPiece>> PieceContainer;

class Player
{
public:
	std::string Class, PlayerColor;
	PieceContainer data;
	Image* image;
	Player(Image* ref) : image(ref) {}
	~Player()
	{
		std::list<std::string> removed;
		UnloadImage(*image);
		for (const auto& piece : data)
		{
			if (std::holds_alternative<StandardPiece>(piece))
			{
				StandardPiece STDpiece = std::get<StandardPiece>(piece);
				std::string name = STDpiece.Name;
				if (std::find(removed.begin(), removed.end(), name) != removed.end())
				{
					removed.push_back(name);
					UnloadTexture(*STDpiece.texture);
				}
			}
		}
	}
};

class PlayerManager
{
protected:

	PlayerManager() = default;
	static PlayerManager* instance;

	// Delete copy constructor and assignment
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;

public:
	static PlayerManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new PlayerManager();
		return instance;
	}

	Player *GetStandardPieceSet(std::string color)
	{
		PieceContainer container;
		int IDCounter = 0;
		std::string name = "Pawn", path;
		StrVector strs = {};
		strs.push_back("PawnPush");
		Rectangle rec = Rectangle(PIECE_SQUARE_LATERAL * 6,
			0, PIECE_SQUARE_LATERAL, PIECE_SQUARE_LATERAL);
		if (color == "WHITE") path = "C:/Users/Julian/source/repos/ChessExtended/x64/Debug/WHITEstandard.png";
		else path = "C:/Users/Julian/source/repos/ChessExtended/x64/Debug/BLACKstandard.png";
		Image* mainImage = new Image();
		*mainImage = LoadImage(path.data());
		Player *player = new Player(mainImage);
		Image Pawn = ImageFromImage(*(*player).image, rec);
		Texture2D *texture = new Texture2D();
		*texture = LoadTextureFromImage(Pawn);
		for (int i = 0; i < 8; i++)
		{
			StandardPiece piece = StandardPiece(IDCounter, 1, name, IDCounter, 6, texture);
			piece.SetStructure();
			piece.SetProperties(strs);
			container.push_back(piece);
			IDCounter++;
		}
		(*player).Class = "standard";
		(*player).data = container;
		(*player).PlayerColor = color;
		return player;
	}

	/*GetUserPieceSet*/
	/*GetOpponentXPieceSet*/
};

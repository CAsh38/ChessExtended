#pragma once
#include <string>
#include <vector>
#include <functional>
#include "LinkedLists.h"
#include "PlayerManager.h"
#include "raylib.h"

namespace LLSC = LinkedLists::SimpleCircular;

typedef std::vector<std::string> StrVector;
typedef std::vector<Color> StrColor;

class Board
{
public:
	int Length = 0, Height = 0;
	std::string Topology;
	StrVector modifications;
	Player *User, *Opponent;
	Rectangle LeftMostRectangle{};
	std::function<void()> DrawPiecesMethod = NULL;

	Board(int L, int H, std::string topology, StrVector mods, Player *user, Player *opp, Rectangle Base) :
		Length(L), Height(H), Topology(topology), modifications(mods), User(user), Opponent(opp), LeftMostRectangle(Base) 
	{}


	//Board copy constructor
	Board(const Board& other)
		: Length(other.Length), Height(other.Height),
		Topology(other.Topology), modifications(other.modifications),
		User(other.User), Opponent(other.Opponent),
		LeftMostRectangle(other.LeftMostRectangle),DrawPiecesMethod(other.DrawPiecesMethod) 
	{
		DrawPiecesMethod = [this]() { DrawStandardPieces(); };
	}

	//Board move constructor
	Board(Board&& other) noexcept
		: Length(other.Length), Height(other.Height),
		Topology(other.Topology), modifications(other.modifications),
		User(other.User), Opponent(other.Opponent),
		LeftMostRectangle(other.LeftMostRectangle), DrawPiecesMethod(other.DrawPiecesMethod) 
	{
		DrawPiecesMethod = [this]() { DrawStandardPieces(); };
	}

	//Board copy assignment
	Board& operator=(const Board& other){
		if (this != &other) {
			Length = other.Length;
			Height = other.Height;
			Topology = other.Topology;
			modifications = other.modifications;
			User = other.User;
			Opponent = other.Opponent;
			LeftMostRectangle = other.LeftMostRectangle;
			DrawPiecesMethod = other.DrawPiecesMethod;
		}
		return *this;
	}

	//Board move assignment
	Board& operator=(Board&& other) noexcept {
		if (this != &other) {
			Length = other.Length;
			Height = other.Height;
			Topology = std::move(other.Topology);
			modifications = std::move(other.modifications);
			User = std::move(other.User);
			Opponent = std::move(other.Opponent);
			LeftMostRectangle = other.LeftMostRectangle;
			DrawPiecesMethod = std::move(other.DrawPiecesMethod);
		}
		return *this;
	}

protected:
	void DrawStandardPieces()
	{
		for (const auto& user_piece : (*User).data)
		{
			StandardPiece piece = std::get<StandardPiece>(user_piece);
			if (piece.Name == "Pawn")
			{
				int X = LeftMostRectangle.x + (piece.posX) * LeftMostRectangle.height;
				int Y = LeftMostRectangle.y + (piece.posY) * LeftMostRectangle.height;
				DrawTexture(*piece.texture, X, Y, WHITE);
			}
		}
	}
};

class ClasicSquareBoard : public Board
{
public:
	using Board::Board;
	LLSC::CircularLinkedList<Color> ColorTypes;
	std::function<void()> DrawingMethod = NULL;

	ClasicSquareBoard() = default;

	//ClasicSquareBoard copy constructor
	ClasicSquareBoard(const ClasicSquareBoard& other)
		: Board(other)
	{
		ColorTypes = other.ColorTypes;
		if (other.Topology == "standard")
			DrawingMethod = [this]() { DrawStandardBoard(); };
	}

	//ClasicSquareBoard move constructor
	ClasicSquareBoard(ClasicSquareBoard&& other) noexcept
		: Board(std::move(other))
	{
		ColorTypes = other.ColorTypes;
		if (other.Topology == "standard")
			DrawingMethod = [this]() { DrawStandardBoard(); };
	}

	//ClasicSquareBoard copy assignment
	ClasicSquareBoard& operator=(const ClasicSquareBoard& other)
	{
		if (this != &other) Board::operator=(other);

		// cleanup current data
		/*ColorTypes.~CircularLinkedList();

		new (&ColorTypes) LLSC::CircularLinkedList<Color>();
		*this = ClasicSquareBoard(other);*/
		return *this;
	}

	//ClasicSquareBoard move assignment
	ClasicSquareBoard& operator=(const ClasicSquareBoard&& other) noexcept
	{
		if (this != &other) 
			Board::operator=(std::move(other));

		// cleanup current data
		/*ColorTypes.~CircularLinkedList();

		new (&ColorTypes) LLSC::CircularLinkedList<Color>();
		*this = ClasicSquareBoard(other);*/
		return *this;
	}

	void TransformBoard(StrColor colors)
	{
		ColorTypes.Init(colors[0]);
		for (int i = 1; i < colors.size(); i++) ColorTypes.InsertAt(ColorTypes.size, colors[i]);
		if (Topology == "standard")
			DrawingMethod = [this]() {DrawStandardBoard(); };
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
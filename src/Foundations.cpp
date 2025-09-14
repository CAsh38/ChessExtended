#include "Foundations.h"

class Board
{
	public:
	__int32 Length, Height;
	std::string Topology, *modifications = nullptr;

	Board(int L, int H, std::string topology, std::string *mods)
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
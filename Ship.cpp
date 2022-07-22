#include "Ship.h"

Ship::Ship() : Length(1), StartPos({0,0}), direction(CT::Direction::DOWN), status(CT::Status::Alive), ship(new wchar_t[Length+1]), ShipBlocksStatus(new uint32_t[Length])
{
	//ship[Length] = '\0';
	shipPart = new CT::ShipPart[1];
	shipPart[0] = CT::ShipPart::Edge;
	SetupShip();
}

Ship::Ship(uint32_t _Length, CT::Vector2<uint32_t> _StartPos, CT::Direction _Direction) : Length(_Length), StartPos(_StartPos), direction(_Direction), status(CT::Status::Alive), ship(new wchar_t[Length + 1]), ShipBlocksStatus(new uint32_t[Length])
{
	//ship[Length] = '\0';
	shipPart = new CT::ShipPart[Length];
	switch (Length)
	{
	case 1:
		shipPart[0] = CT::ShipPart::Edge;
		break;
	case 2:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Edge;
		break;
	case 3:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Body;
		shipPart[2] = CT::ShipPart::Edge;
		break;
	case 4:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Body;
		shipPart[2] = CT::ShipPart::Body;
		shipPart[3] = CT::ShipPart::Edge;
		break;
	default:
		break;
	}
	
	SetupShip();
}

Ship::Ship(uint32_t _Length, CT::Cell _Cell, CT::Direction _Direction) : Length(_Length), cell(_Cell), direction(_Direction), status(CT::Status::Alive), ship(new wchar_t[Length + 1]), ShipBlocksStatus(new uint32_t[Length])
{
	shipPart = new CT::ShipPart[Length];
	switch (Length)
	{
	case 1:
		shipPart[0] = CT::ShipPart::Edge;
		break;
	case 2:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Edge;
		break;
	case 3:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Body;
		shipPart[2] = CT::ShipPart::Edge;
		break;
	case 4:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Body;
		shipPart[2] = CT::ShipPart::Body;
		shipPart[3] = CT::ShipPart::Edge;
		break;
	default:
		break;
	}
	SetupShip();
}

Ship::Ship(uint32_t _Length, CT::Direction _Direction) : Length(_Length), direction(_Direction), status(CT::Status::Alive), ship(new wchar_t[Length + 1]), ShipBlocksStatus(new uint32_t[Length])
{
	shipPart = new CT::ShipPart[Length];
	switch (Length)
	{
	case 1:
		shipPart[0] = CT::ShipPart::Edge;
		break;
	case 2:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Edge;
		break;
	case 3:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Body;
		shipPart[2] = CT::ShipPart::Edge;
		break;
	case 4:
		shipPart[0] = CT::ShipPart::Edge;
		shipPart[1] = CT::ShipPart::Body;
		shipPart[2] = CT::ShipPart::Body;
		shipPart[3] = CT::ShipPart::Edge;
		break;
	default:
		break;
	}
	SetupShip();
}

Ship::~Ship(){}

void Ship::SetStartCell(CT::Cell _cell)
{
	cell = _cell;
}

bool Ship::IsShipThere(CT::Vector2<uint32_t> Coord) const
{
	if (StartPos == Coord) return true;
	switch (direction)
	{
	case CT::Direction::UP:
		if (StartPos.X == Coord.X && StartPos.Y >= Coord.Y && StartPos.Y - Length <= Coord.Y) return true;
		break;
	case CT::Direction::RIGHT:
		if (StartPos.Y == Coord.Y && StartPos.X <= Coord.X && StartPos.X + Length >= Coord.X) return true;
		break;
	case CT::Direction::DOWN:
		if (StartPos.X == Coord.X && StartPos.Y <= Coord.Y && StartPos.Y + Length >= Coord.Y) return true;
		break;
	case CT::Direction::LEFT:
		if (StartPos.Y == Coord.Y && StartPos.X >= Coord.X && StartPos.X - Length <= Coord.X) return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

bool Ship::Hit(CT::Vector2<uint32_t> Pos)
{
	if (ShipBlocksStatus[CoordToArrPos(Pos)] -1 < 0) return false;
	ShipBlocksStatus[CoordToArrPos(Pos)] -= 1;
	ship[CoordToArrPos(Pos)] = Symbols[ShipBlocksStatus[CoordToArrPos(Pos)]];
	return true;
	//
}

inline void Ship::SetupShip()
{
	//for (size_t i = 0; i < Length; i++)
	//    ShipBlocksStatus[i] = 2;
	for (uint32_t i = 0; i < Length; i++)
	{
		ShipBlocksStatus[i] = 2;
		//ship[i] = Symbols[ShipBlocksStatus[i]];
		ship[i] = Symbols[2];
	}
	ship[Length] = '\0';
}

uint32_t Ship::CoordToArrPos(CT::Vector2<uint32_t> Pos) const
{
	if (!IsShipThere(Pos)) return 0;
	switch (direction)
	{
	case CT::Direction::UP:
		for (size_t i = StartPos.Y; i >= StartPos.Y - Length; i--) if (StartPos.X == Pos.X && i == Pos.Y) return StartPos.Y - i;
		break;
	case  CT::Direction::RIGHT:
		for (size_t i = StartPos.X; i <= StartPos.X + Length; i++) if (StartPos.Y == Pos.Y && i == Pos.X) return i - StartPos.X;;
		break;
	case CT::Direction::DOWN:
		for (size_t i = StartPos.Y; i <= StartPos.Y + Length; i++) if (StartPos.X == Pos.X && i == Pos.Y) return i - StartPos.Y;
		break;
	case CT::Direction::LEFT:
		for (size_t i = StartPos.X; i >= StartPos.X - Length; i--) if (StartPos.Y == Pos.Y && i == Pos.X) return StartPos.X - i;
	break;
	}
}
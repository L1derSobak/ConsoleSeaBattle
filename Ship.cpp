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

CT::ShipPart Ship::GetShipPartByCell(std::wstring cellName)
{
	for (auto i = 0U;i< Length;i++)
	{
		
		wchar_t Sym = cell.GetCellName()[0];
		wchar_t tSym = Sym;
		int32_t Pos = cell.GetCellName().size() == 3 ? 10 : cell.GetCellName()[1] - 48;
		int32_t tPos = Pos;
		switch (direction)
		{
		case CT::Direction::DOWN:
			for (; Pos < tPos + Length; Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return shipPart[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::UP:
			for (; Pos > tPos - Length; Pos--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return shipPart[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::LEFT:
			for (; Sym > tSym - Length; Sym--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return shipPart[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::RIGHT:
			for (; Sym < tSym + Length; Sym++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return shipPart[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		default:
			break;
		}
		//it.GetStartCell()
	}
	return CT::ShipPart::None;
	//return CT::ShipPart();
}

uint32_t Ship::GetBlockPosByCell(std::wstring cellName)
{
	for (auto i = 0U; i < Length; i++)
	{

		wchar_t Sym = cell.GetCellName()[0];
		wchar_t tSym = Sym;
		int32_t Pos = cell.GetCellName().size() == 3 ? 10 : cell.GetCellName()[1] - 48;
		int32_t tPos = Pos;
		switch (direction)
		{
		case CT::Direction::DOWN:
			for (; Pos < tPos + Length; Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return i;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::UP:
			for (; Pos > tPos - Length; Pos--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return i;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::LEFT:
			for (; Sym > tSym - Length; Sym--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return i;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::RIGHT:
			for (; Sym < tSym + Length; Sym++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return i;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		default:
			break;
		}
		//it.GetStartCell()
	}
	return 404;
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

bool Ship::Hit(std::wstring cellName)
{
	uint32_t i = GetShipPartsStatus()[GetBlockPosByCell(cellName)];
	if (i - 1 < 0) return false;
	ship[GetBlockPosByCell(cellName)] = Symbols[i - 1];
	//GetShipPartsStatus()[GetBlockPosByCell(cellName)]
	//this->ShipBlocksStatus[GetBlockPosByCell(cellName)]
	return true;
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
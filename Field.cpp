#include "Field.h"
//#include <Windows.h>

Field::Field(CT::Owner _owner, CT::Vector2<uint32_t> _RelativePosition) : owner(_owner), RelativePosition(_RelativePosition), AvaliableShips(10)
{
	FieldLength = CellSize * 11 + 11;
	FieldSize = FieldLength * FieldLength + 1;//(blockSize * 11 + 11) * (blockSize * 11 + 11) + 1;
	field = new wchar_t[FieldSize];
	int Length = 1, Count = 4;
	for (auto& it : ShipsLength)
	{
		it.first = Length;
		it.second = Count;
		Length++;
		Count--;
	}
	InitCells();
	InitShips();
	ClearField();
	DrawField();
	//field[FieldSize] = '\0';
	//ZeroMemory(field, FieldSize);
	/*
	uint32_t count = 1;
	for (uint32_t i = 0; i < FieldSize; i++)
	{
		if (i == blockSize * count)
		{
			field[i] = ' ';
			count++;
		}
		else
			field[i] = '*';
	}*/

	//0 1 2 3 (4) 5 6 7 8 (9) 10 11 12 13 (14)   => 5-1
	
	/*
	uint32_t posX = 1, posY = 1;
	for (uint32_t i = 0; i < blockSize * 10 + 9; i++)
	{
		if (i == blockSize * posX) posX++;
		for (uint32_t j = 0; j < blockSize * 10 + 9; j++)
		{
			if (j == blockSize * posY || i == blockSize * posX)
			{
				field[i + j * (blockSize * 10 + 9)] = ' ';
				posY++;
			}
			else field[i + j * (blockSize * 10 + 9)] = '*';
		}
	}
	*/
}

Field::~Field()
{

}

bool Field::AttachShip(Ship ship)
{
	for (auto& it : ShipsLength)
	{
		if (ship.GetLength() == it.first)
		{ if (it.second == 0) return false;
			else
			{
			it.second--;
			}
		}
	}
	OwnersShips[ShipsPosition] = ship;
	ShipsPosition++;
	return true;
}

void Field::ResetShips()
{
	ShipsPosition = 0;
}

bool Field::Hit(CT::Vector2<uint32_t> Pos)
{
	if (IsAnyoneShipHited(Pos))
		return GetHitedShip(Pos).Hit(Pos);
	if(IsCellFree(Pos)) 
	{
		field[GetArrayFromPos(Pos)] = '*';
		return true;
	}
	return false;
}

bool Field::Hit(std::wstring cellName) 
{
	if ((GetCellStatus(cellName) == CT::CellStatus::None || GetCellStatus(cellName) == CT::CellStatus::Hited) || !EditCellStatus(cellName)) return false;
	//if ()) return false;

	//TODO:
	//1)??????????? ????? Hit ??? ??????? ?.? ?? ??????? ??????? ????? ??????? ??? ??????????,
	//? ????? ??????????? ??? ?????? ???????? ???? ??????
	/*
			Field
			  |
			  v
		WhatShipHited(cellName); ??? ?? ??????? ??? ? ??????? ??????????. ????? ??????? ??? ??????? ? ??????? OwnersShips
			  |
			  v
		Ship.Hit(cellName)
	*/
	bool isShort = OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetLength() == 1 ? true : false;//GetShipByCell(cellName).GetLength() == 1 ? true : false;
	if (WhatShipHited(cellName) != CT::Status::None)
	{
		/*
		Ship* tempShip = &OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)];
		DrawShip(cellName,
			OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetShipPartByCell(cellName),
			OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetDirection(),
			OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetShipArray()[OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetBlockPosByCell(cellName)],
			isShort,
			OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetBlockPosByCell(cellName) == OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)].GetLength() - 1 ? true : false
		);
		*/
		Ship* tempShip = &OwnersShips[ArrShipPosByCell(cellName) == 404 ? 0 : ArrShipPosByCell(cellName)];
		DrawShip(cellName,
			tempShip->GetShipPartByCell(cellName),
			tempShip->GetDirection(),
			tempShip->GetShipArray()[tempShip->GetBlockPosByCell(cellName)],
			isShort,
			tempShip->GetBlockPosByCell(cellName) == tempShip->GetLength() - 1 ? true : false
		);
	}
	else
	{
		CT::Cell* findCell = GetCellByName(cellName);
		CT::Vector2<uint32_t> Pos = findCell->GetWindowPosition();// GetPosFromCell(cellName);//findCell.GetWindowPosition();
		for (uint32_t i = Pos.X; i < Pos.X + CellSize; i++)
		{
			for (uint32_t j = Pos.Y; j < Pos.Y + CellSize; j++)
				field[i + j * FieldLength] = L'*';
		}
	}
	return true;




	//temps.Hit(cellName);
	//bool isShort = temps.GetLength() == 1 ? true : false;//GetShipByCell(cellName).GetLength() == 1 ? true : false;
	if (IsAnyShipThere(cellName))
	{
		//DrawShip(cellName, temps.GetShipPartByCell(cellName), temps.GetDirection(),temps.GetSymByStatus(temps.GetShipPartsStatus()[temps.GetBlockPosByCell(cellName)])/* temps.GetShipPartsStatus()[temps.GetBlockPosByCell(cellName)]*/, isShort, temps.GetBlockPosByCell(cellName) == temps.GetLength() - 1 ? true : false);
		//DrawShip(cellName, GetShipByCell(cellName).GetShipPartByCell(cellName), GetShipByCell(cellName).GetDirection(), GetShipByCell(cellName).GetShipPartsStatus()[GetShipByCell().GetBlockPosByCell(cellName)], isShort, i == ship.GetLength() - 1 ? true : false)
	}
	else
	{
		CT::Cell* findCell = GetCellByName(cellName);
		CT::Vector2<uint32_t> Pos = findCell->GetWindowPosition();// GetPosFromCell(cellName);//findCell.GetWindowPosition();
		for (uint32_t i = Pos.X; i < Pos.X + CellSize; i++)
		{
			for (uint32_t j = Pos.Y; j < Pos.Y + CellSize; j++)
				field[i + j * FieldLength] = L'*';
		}
	}
	return true;
	/*
	
	CT::Cell findCell = GetCellByName(cellName);
	CT::Vector2<uint32_t> Pos = findCell.GetWindowPosition();// GetPosFromCell(cellName);//findCell.GetWindowPosition();
	for (uint32_t i = Pos.X; i < Pos.X + CellSize; i++)
	{
		for (uint32_t j = Pos.Y; j < Pos.Y + CellSize; j++)
			field[i + j * FieldLength] = '*';
	}
	//field[Pos.X + Pos.Y * CellSize] = '*';
	return true;
	//CT::Vector2<uint32_t> Pos = GetCellByName(cellName).GetWindowPosition();//GetPosFromCell(cellName);
	//uint32_t PosX = GetArrayFromPos
	//return Hit(GetPosFromCell(cellName));
	*/
}

wchar_t* Field::GetFieldArray() const
{
	return field;
}

CT::Vector2<uint32_t> Field::GetFieldSize() const
{
	return { FieldLength, FieldLength };
}

bool Field::SetShip(Ship &ship, std::wstring cellName)
{
	AvaliableShips--;
	OwnersShips[aShipPosition].SetStartCell(*GetCellByName(cellName));
	aShipPosition++;
	bool isShort = ship.GetLength() == 1 ? true : false;
	std::wstring nextCell = cellName;
	wchar_t Sym = cellName[0];
	uint32_t Num = cellName.size() == 3 ? 10 : cellName[1]-48;
	for (uint32_t i = 0; i < ship.GetLength(); i++)
	{
		switch (ship.GetDirection())
		{
		case CT::Direction::UP:
			DrawShip(nextCell, ship.GetShipParts()[i], ship.GetDirection(), ship.GetShipArray()[i]/*ship.GetShipPartsStatus()[i]*/, isShort, i==ship.GetLength()-1?true : false);
			Num--;
			//DrawShip()
			break;
		case CT::Direction::DOWN:
			DrawShip(nextCell, ship.GetShipParts()[i], ship.GetDirection(), ship.GetShipArray()[i]/*ship.GetShipPartsStatus()[i]*/, isShort, i == ship.GetLength() - 1 ? true : false);
			Num++;
			break;
		case CT::Direction::LEFT:
			DrawShip(nextCell, ship.GetShipParts()[i], ship.GetDirection(), ship.GetShipArray()[i] /*ship.GetShipPartsStatus()[i]*/, isShort, i == ship.GetLength() - 1 ? true : false);
			Sym--;
			break;
		case CT::Direction::RIGHT:
			DrawShip(nextCell, ship.GetShipParts()[i], ship.GetDirection(), ship.GetShipArray()[i] /*ship.GetShipPartsStatus()[i]*/, isShort, i == ship.GetLength() - 1 ? true : false);
			Sym++;
			break;
		default:
			break;
		}
		nextCell = Sym + std::to_wstring(Num);
	}
	
	return true;
}

bool Field::EditShip(Ship ship)
{
	return false;
}

const bool Field::IsAnyShipThere(std::wstring cellName)
{
	/*
	wchar_t Sym = cellName[0];
	wchar_t tSym = Sym;
	int32_t Pos = cellName.size() == 3 ? 10 : cellName[1] - 48;
	int32_t tPos = Pos;
	*/
	for (auto it : OwnersShips)
	{
		wchar_t Sym = it.GetStartCell().GetCellName()[0];
		wchar_t tSym = Sym;
		int32_t Pos = it.GetStartCell().GetCellName().size() == 3 ? 10 : it.GetStartCell().GetCellName()[1] - 48;
		int32_t tPos = Pos;
		switch (it.GetDirection())
		{
		case CT::Direction::DOWN:
			for (; Pos < tPos + it.GetLength(); Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return true;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::UP:
			for (; Pos > tPos - it.GetLength(); Pos--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return true;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::LEFT:
			for (; Sym > tSym - it.GetLength(); Sym--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return true;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::RIGHT:
			for (; Sym < tSym + it.GetLength(); Sym++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return true;
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		default:
			break;
		}
		//it.GetStartCell()
	}
	return false;
}

Ship* Field::GetShipByCell(std::wstring cellName)
{
	for(auto i = 0U; i < OwnersShips.size(); i++)
	//for (auto& it : OwnersShips)
	{
		wchar_t Sym = OwnersShips[i].GetStartCell().GetCellName()[0]; //<++++++++++++++++++++++++++++++++++++++++++++++++++>
		wchar_t tSym = Sym;
		int32_t Pos = OwnersShips[i].GetStartCell().GetCellName().size() == 3 ? 10 : OwnersShips[i].GetStartCell().GetCellName()[1] - 48;
		int32_t tPos = Pos;
		switch (OwnersShips[i].GetDirection())
		{
		case CT::Direction::DOWN:
			for (; Pos < tPos + OwnersShips[i].GetLength(); Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return &OwnersShips[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::UP:
			for (; Pos > tPos - OwnersShips[i].GetLength(); Pos--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return &OwnersShips[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::LEFT:
			for (; Sym > tSym - OwnersShips[i].GetLength(); Sym--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return &OwnersShips[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::RIGHT:
			for (; Sym < tSym + OwnersShips[i].GetLength(); Sym++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName) return &OwnersShips[i];
				//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		default:
			break;
		}
		//it.GetStartCell()
	}
	//return nullptr;
}

bool Field::IsAnyoneShipHited(CT::Vector2<uint32_t> Pos) const
{
	for(uint32_t i = 0; i < OwnersShips.size(); i++)
		if (OwnersShips[i].IsShipThere(Pos)) return true;
	return false;
}

bool Field::IsCellFree(CT::Vector2<uint32_t> Pos) const
{
	if (field[GetArrayFromPos(Pos)] == L' ') return true;
	return false;
}

Ship Field::GetHitedShip(CT::Vector2<uint32_t> Pos) const
{
	for (uint32_t i = 0; i < OwnersShips.size(); i++)
		if (OwnersShips[i].IsShipThere(Pos)) return OwnersShips[i];
}

bool Field::HitShip(Ship& ship, std::wstring cellName)
{
	return false;
}

const CT::Status Field::WhatShipHited(std::wstring cellName)
{

	for (auto& it : OwnersShips)
	{
		//<++++++++++++++++++++++++++++++++++++++++++++++++++>
		wchar_t Sym = it.GetStartCell().GetCellName()[0]; 
		wchar_t tSym = Sym;
		int32_t Pos =it.GetStartCell().GetCellName().size() == 3 ? 10 : it.GetStartCell().GetCellName()[1] - 48;
		int32_t tPos = Pos;
		for (auto i = 0; i < it.GetLength(); i++)
		{
			switch (it.GetDirection())
			{
			case CT::Direction::UP:
				for (; Pos > tPos - it.GetLength(); Pos--)
				{
					std::wstring name = Sym + std::to_wstring(Pos);
					if (name == cellName) 
					{
						it.Hit(cellName);
						return it.GetStatus();
					}
					//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
				}
				break;
			case CT::Direction::DOWN:
				for (; Pos < tPos + it.GetLength(); Pos++)
				{
					std::wstring name = Sym + std::to_wstring(Pos);
					if (name == cellName) 
					{
						it.Hit(cellName);
						return it.GetStatus();
					}
				}
				break;
			case CT::Direction::LEFT:
				for (; Sym > tSym -it.GetLength(); Sym--)
				{
					std::wstring name = Sym + std::to_wstring(Pos);
					if (name == cellName) 
					{
						it.Hit(cellName);
						return it.GetStatus();
					}
					//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
				}
				break;
			case CT::Direction::RIGHT:
				for (; Sym < tSym + it.GetLength(); Sym++)
				{
					std::wstring name = Sym + std::to_wstring(Pos);
					if (name == cellName)
					{
						it.Hit(cellName);
						return it.GetStatus();
					}//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
				}
				break;
			default:
				break;
			}
		}
	}

	return CT::Status::None;
}

void Field::ClearField()
{
	for (uint32_t i = 0; i < FieldSize; i++)
		field[i] = L' ';
	field[FieldSize] = '\0';
}

void Field::DrawField()
{
	for (uint32_t i = 0; i < FieldLength; i++)
	{
		for (uint32_t j = 0; j < FieldLength; j++)
		{
			if ((i + 1) % (CellSize + 1) == 0 || (j + 1) % (CellSize + 1) == 0) field[i + j * FieldLength] = L'.';
			else field[i + j * FieldLength] = ' ';
		}
	}

	//??????? ???? ??????, ????? ?????????? ???????
	for (uint32_t i = 0; i < CellSize; i++)
		for (uint32_t j = 0; j < FieldLength; j++)
			field[i + j * FieldLength] = ' ';

	for (uint32_t i = 0; i < FieldLength; i++)
		for (uint32_t j = 0; j < CellSize; j++)
			field[i + j * FieldLength] = L' ';

	//????????? ???????

	//?????
	wchar_t num = 49;
	for (uint32_t i = CellSize + ceilf(CellSize / 2) + 1; i < FieldLength; i+= CellSize + 1)
	{
		if (num == 58)
		{
			field[0 + i * FieldLength] = L'1';
			field[1 + i * FieldLength] = L'0';
		}
		else field[1 + i * FieldLength] = num;
		num++;
	}
	//?????
	wchar_t sym = 1040; // A (end)
	for (uint32_t i = CellSize + ceilf(CellSize / 2) + 1; i < FieldLength; i += CellSize + 1)
	{
		field[i + 1 * FieldLength] = sym;
		sym++;
		//num++;
	}
}

void Field::DrawShip(std::wstring _cell, CT::ShipPart shipPart, CT::Direction _direction, wchar_t ShipSymbol, bool isShort, bool invert)
{
	CT::Cell* tempCell = GetCellByName(_cell);
	if (isShort)
	{
		field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
		return;
	}
	if (shipPart == CT::ShipPart::Edge)
	{
		switch (_direction)
		{
		case CT::Direction::UP:
			if (invert)
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'^';
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y+2) * FieldLength] = ShipSymbol;
			}
			else
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'v';
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y) * FieldLength] = ShipSymbol;
			}
			break;
		case CT::Direction::DOWN:
			if (invert)
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'v';
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y) * FieldLength] = ShipSymbol;
			}
			else
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'^';
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 2) * FieldLength] = ShipSymbol;
			}
			break;
		case CT::Direction::LEFT:
			if (invert)
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'<';
				field[tempCell->GetWindowPosition().X + 2 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			}
			else
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'>';
				field[tempCell->GetWindowPosition().X + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			}
			break;
		case CT::Direction::RIGHT:
			if (invert)
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'>';
				field[tempCell->GetWindowPosition().X + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			}
			else
			{
				field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = L'<';
				field[tempCell->GetWindowPosition().X + 2 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (_direction == CT::Direction::DOWN || _direction == CT::Direction::UP)
		{
			field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y) * FieldLength] = ShipSymbol;
			field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 2) * FieldLength] = ShipSymbol;
		}
		else
		{
			field[tempCell->GetWindowPosition().X  + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			field[tempCell->GetWindowPosition().X + 1 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
			field[tempCell->GetWindowPosition().X + 2 + (tempCell->GetWindowPosition().Y + 1) * FieldLength] = ShipSymbol;
		}
	}
	/*switch (_direction)
	{
	case CT::Direction::UP:
		if (shipPart == CT::ShipPart::Edge)
		{
			field[_cell.GetWindowPosition().X + 1 + (_cell.GetWindowPosition().Y + 1) * FieldLength] = L'v';
			field[_cell.GetWindowPosition().X + 1 + (_cell.GetWindowPosition().Y) * FieldLength] = ShipSymbol;
		}
		else
		{

		}
		break;
	case CT::Direction::DOWN:
		break;
	case CT::Direction::LEFT:
		break;
	case CT::Direction::RIGHT:
		break;
	default:
		break;
	}*/
}

void Field::FillField(wchar_t sym)
{
	for (uint32_t i = 0; i < FieldSize; i++)
		field[i] = sym;
	field[FieldSize] = '\0';
}

void Field::InitCells()
{
	wchar_t sym = 1040; 
	uint32_t pos = 1, arrPos = 0;
	std::wstring CellName;
	for (auto& it : Cells)
	{
		if (pos > 10)
		{
			pos = 1;
			sym++;
		}
		CellName = sym + std::to_wstring(pos);//std::to_wstring(static_cast<wchar_t>(sym))
		it.ResetData(CellSize, arrPos,GetPosFromCell(CellName) /*{1 + CellSize * pos, 1 + CellSize * sym - 64}*/, CellName);
		//it.first = CellName;
		//it.second = CT::CellStatus::Clear;
		pos++;
		arrPos++;
	}
}

void Field::InitShips()
{
	uint32_t Length = 1;
	for (uint32_t i = 0; i < OwnersShips.size(); i++)
	{
		if (i == 4 || i == 7 || i == 9)
			Length++;
		OwnersShips[i] = Ship(Length, CT::Direction::NONE);
	}
}

const CT::CellStatus Field::GetCellStatus(std::wstring CellName)
{
	for (auto it : Cells)
		if (it.GetCellName() == CellName) return it.GetCellStatus();
	return CT::CellStatus::None;
	/*for (auto it : CellStatus)
		if (CellName == it.first) return it.second;
	return CT::CellStatus::None;*/
}

CT::Cell* Field::GetCellByName(std::wstring CellName)
{
	for(auto i = 0U; i < Cells.size(); i++)
		if (Cells[i].GetCellName() == CellName) return &Cells[i];
	/*
	for (auto& it : Cells)
		if (it.GetCellName() == CellName) return &it;
	*/
	//return CT::Cell();
}

const bool Field::EditCellStatus(std::wstring cellName)
{
	for (auto& it : Cells)
		if (it.GetCellName() == cellName) return(it.SetCellStatus(CT::CellStatus::Hited));
	return false;
	/*for (auto it : CellStatus)
		if (cellName == it.first) it.second = CT::CellStatus::Hited;*/
}

uint32_t Field::GetArrayFromPos(CT::Vector2<uint32_t> Pos) const
{
	return (Pos.X + Pos.Y* CellSize *10);
}

const uint32_t Field::ArrShipPosByCell(std::wstring cellName)
{
	for (size_t i = 0U; i < 10U;i++)//for (auto& it : OwnersShips)
	{
		//<++++++++++++++++++++++++++++++++++++++++++++++++++>
		wchar_t Sym = OwnersShips[i].GetStartCell().GetCellName()[0];
		wchar_t tSym = Sym;
		int32_t Pos = OwnersShips[i].GetStartCell().GetCellName().size() == 3 ? 10 : OwnersShips[i].GetStartCell().GetCellName()[1] - 48;
		int32_t tPos = Pos;
		//for (auto j = 0U; j < OwnersShips[i].GetLength(); j++)
		//{
		switch (OwnersShips[i].GetDirection())
		{
		case CT::Direction::UP:
			for (; Pos > tPos - OwnersShips[i].GetLength(); Pos--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName)
					return i;
					//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::DOWN:
			for (; Pos < tPos + OwnersShips[i].GetLength(); Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName)
					return i;
			}
			break;
		case CT::Direction::LEFT:
			for (; Sym > tSym - OwnersShips[i].GetLength(); Sym--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName)
					return i;
					//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		case CT::Direction::RIGHT:
			for (; Sym < tSym + OwnersShips[i].GetLength(); Sym++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (name == cellName)
					return i;//if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
			}
			break;
		default:
			break;
		}
		//}
	}
	return 404;
}

CT::Vector2<uint32_t> Field::GetPosFromCell(std::wstring cellName) const
{
	//??????? ?????????? ??????? ?? ?????
	uint32_t pos = CellSize + ceilf(CellSize / 2), add = CellSize + 1;//second = cellName.c_str()[1] - 49;
	CT::Vector2<uint32_t> Position;
	Position.X = pos + add * (cellName.c_str()[0]-1040);
	if (cellName.size() == 3)
		Position.Y = pos + add * 9;//(cellName.c_str()[1] - 49);
	else
		Position.Y = pos + add * (cellName.c_str()[1] - 49);
	//Position.Y = pos + add * (cellName.c_str()[1] - 49);
	return Position;
}

const bool Field::EditCellStatus(std::wstring cellName, CT::CellStatus cellStatus)
{
	for (auto& it : Cells)
		if (it.GetCellName() == cellName) return(it.SetCellStatus(cellStatus));
	return false;
}

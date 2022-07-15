#include "Field.h"
//#include <Windows.h>

Field::Field(CT::Owner _owner, CT::Vector2<uint32_t> _RelativePosition) : owner(_owner), RelativePosition(_RelativePosition)
{
	for (uint32_t i = 0; i < OwnersShips.size(); i++)
		OwnersShips[i] = Ship(1, { 0,0 }, CT::Direction::RIGHT);
	FieldLength = blockSize * 11 + 11;
	FieldSize = FieldLength * FieldLength + 1;//(blockSize * 11 + 11) * (blockSize * 11 + 11) + 1;
	field = new wchar_t[FieldSize];
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

void Field::AttachShip(Ship ship)
{
	OwnersShips[ShipsPosition] = ship;
	ShipsPosition++;
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

wchar_t* Field::GetFieldArray() const
{
	return field;
}

CT::Vector2<uint32_t> Field::GetFieldSize() const
{
	return { FieldLength, FieldLength };
}

bool Field::IsAnyoneShipHited(CT::Vector2<uint32_t> Pos) const
{
	for(uint32_t i = 0; i < OwnersShips.size(); i++)
		if (OwnersShips[i].IsShipThere(Pos)) return true;
	return false;
}

bool Field::IsCellFree(CT::Vector2<uint32_t> Pos) const
{
	if (field[GetArrayFromPos(Pos)] == ' ') return true;
	return false;
}

Ship Field::GetHitedShip(CT::Vector2<uint32_t> Pos) const
{
	for (uint32_t i = 0; i < OwnersShips.size(); i++)
		if (OwnersShips[i].IsShipThere(Pos)) return OwnersShips[i];
}

void Field::ClearField()
{
	for (uint32_t i = 0; i < FieldSize; i++)
		field[i] = ' ';
	field[FieldSize] = '\0';
}

void Field::DrawField()
{
	for (uint32_t i = 0; i < FieldLength; i++)
	{
		for (uint32_t j = 0; j < FieldLength; j++)
		{
			if ((i + 1) % (blockSize + 1) == 0 || (j + 1) % (blockSize + 1) == 0) field[i + j * FieldLength] = '.';
			else field[i + j * FieldLength] = ' ';
		}
	}

	//Очищаем угол первый, чтобы разместить символы
	for (uint32_t i = 0; i < blockSize; i++)
		for (uint32_t j = 0; j < FieldLength; j++)
			field[i + j * FieldLength] = ' ';

	for (uint32_t i = 0; i < FieldLength; i++)
		for (uint32_t j = 0; j < blockSize; j++)
			field[i + j * FieldLength] = ' ';

	//Размещаем символы

	//Цифры
	wchar_t num = 49;
	for (uint32_t i = blockSize + ceilf(blockSize / 2) + 1; i < FieldLength; i+= blockSize + 1)
	{
		if (num == 58)
		{
			field[0 + i * FieldLength] = '1';
			field[1 + i * FieldLength] = '0';
		}
		else field[1 + i * FieldLength] = num;
		num++;
	}
	//Буквы
	wchar_t sym = 65; // A (end)
	for (uint32_t i = blockSize + ceilf(blockSize / 2) + 1; i < FieldLength; i += blockSize + 1)
	{
		field[i + 1 * FieldLength] = sym;
		sym++;
		//num++;
	}
}

void Field::FillField(wchar_t sym)
{
	for (uint32_t i = 0; i < FieldSize; i++)
		field[i] = sym;
	field[FieldSize] = '\0';
}

uint32_t Field::GetArrayFromPos(CT::Vector2<uint32_t> Pos) const
{
	return (Pos.X + Pos.Y*blockSize*10);
}

CT::Vector2<uint32_t> Field::GetPosFromCell(std::wstring cellName) const
{
	//Сначала определяем столбец по букве
	uint32_t pos = blockSize + ceilf(blockSize / 2), add = blockSize + 1;//second = cellName.c_str()[1] - 49;
	CT::Vector2<uint32_t> Position;
	Position.X = pos + add * (cellName.c_str()[0]-65);
	Position.Y = pos + add * (cellName.c_str()[1] - 49);
	return Position;
}

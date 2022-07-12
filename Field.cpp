#include "Field.h"

Field::Field(CT::Owner _owner, CT::Vector2<uint32_t> _RelativePosition) : owner(_owner), RelativePosition(_RelativePosition)
{
	for (uint32_t i = 0; i < OwnersShips.size(); i++)
		OwnersShips[i] = Ship(1, { 0,0 }, CT::Direction::RIGHT);
	FieldSize = (blockSize * 10 + 9) * (blockSize * 10 + 9) + 1;
	field = new wchar_t[FieldSize];
	field[FieldSize] = '\0';
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

	for (uint32_t i = 0; i < blockSize * 10 + 9; i++)
	{
		for (uint32_t j = 0; j < blockSize * 10 + 9; j++)
		{
			if ((i + 1) % (blockSize+1) == 0 || (j + 1) % (blockSize + 1) == 0) field[i + j * (blockSize * 10 + 9)] = '.';
			else field[i + j * (blockSize * 10 + 9)] = ' ';
		}
	}

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
	return { blockSize * 10 + 9, blockSize * 10 + 9};
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

uint32_t Field::GetArrayFromPos(CT::Vector2<uint32_t> Pos) const
{
	return (Pos.X + Pos.Y*blockSize*10);
}

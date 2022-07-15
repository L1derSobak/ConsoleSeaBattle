#pragma once
#include <iostream>
#include "CoreTypes.h"
#include "Ship.h"
#include <array>

class Field
{
public:
	Field(CT::Owner _owner, CT::Vector2<uint32_t> _RelativePosition);
	~Field();

	void AttachShip(Ship ship);
	void ResetShips();
	void ClearField();

	bool Hit(CT::Vector2<uint32_t> Pos);
	wchar_t* GetFieldArray() const;
	CT::Vector2<uint32_t> GetFieldSize() const;

	//DEBUG ZONE
	CT::Vector2<uint32_t> GetPosFromCell(std::wstring cellName) const;
private:
	bool IsAnyoneShipHited(CT::Vector2<uint32_t> Pos) const;
	bool IsCellFree(CT::Vector2<uint32_t> Pos) const;
	Ship GetHitedShip(CT::Vector2<uint32_t> Pos) const;

	void DrawField();
	void FillField(wchar_t sym);

	uint32_t GetArrayFromPos(CT::Vector2<uint32_t> Pos) const;
	//CT::Vector2<uint32_t> GetPosFromCell(std::wstring cellName) const;

	uint32_t FieldSize = 1, blockSize = 3, ShipsPosition = 0, FieldLength = 0;
	wchar_t* field = nullptr;
	std::array<Ship, 10> OwnersShips;
	CT::Owner owner;

	CT::Vector2<uint32_t> RelativePosition;
};
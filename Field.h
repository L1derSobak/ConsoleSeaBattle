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
	bool Hit(std::wstring cellName);
	wchar_t* GetFieldArray() const;
	CT::Vector2<uint32_t> GetFieldSize() const;

	bool SetShip(Ship ship, std::wstring cellName);
	bool EditShip(Ship ship);

	//DEBUG ZONE
	CT::Vector2<uint32_t> GetPosFromCell(std::wstring cellName) const;




private:
	bool IsAnyoneShipHited(CT::Vector2<uint32_t> Pos) const;
	bool IsCellFree(CT::Vector2<uint32_t> Pos) const;
	Ship GetHitedShip(CT::Vector2<uint32_t> Pos) const;

	void DrawField();
	void DrawShip(std::wstring _cell, CT::ShipPart shipPart, CT::Direction _direction, wchar_t ShipSymbol = L'=', bool isShort = false, bool invert = false);
	void FillField(wchar_t sym);

	void InitCells();
	void InitShips();
	const CT::CellStatus GetCellStatus(std::wstring CellName);
	CT::Cell GetCellByName(std::wstring CellName);
	const bool EditCellStatus(std::wstring cellName);

	uint32_t GetArrayFromPos(CT::Vector2<uint32_t> Pos) const;
	//CT::Vector2<uint32_t> GetPosFromCell(std::wstring cellName) const;

	uint32_t FieldSize = 1, CellSize = 3, ShipsPosition = 0, FieldLength = 0;
	wchar_t* field = nullptr;
	std::array<Ship, 10> OwnersShips;
	std::array<CT::Cell, 100U> Cells;
	//std::array<std::pair<std::wstring,CT::CellStatus>, 100> CellStatus;
	CT::Owner owner = CT::Owner::None;

	CT::Vector2<uint32_t> RelativePosition;
};
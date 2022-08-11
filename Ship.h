#pragma once
#include <iostream>
#include "CoreTypes.h"
#include <array>
#include <map>

class Ship
{
public:
	Ship();
	Ship(uint32_t _Length, CT::Vector2<uint32_t> _StartPos, CT::Direction _Direction);
	Ship(uint32_t _Length, CT::Cell _Cell, CT::Direction _Direction);
	Ship(uint32_t _Length, CT::Direction _Direction);
	~Ship();

	void SetStartCell(CT::Cell _cell);

	CT::ShipPart GetShipPartByCell(std::wstring cellName);
	uint32_t GetBlockPosByCell(std::wstring cellName);

	bool IsShipThere(CT::Vector2<uint32_t> Coord) const;
	CT::Vector2<uint32_t> GetStartPos() const { return StartPos; }
	int32_t GetLength() const { return Length; }
	CT::Direction GetDirection() const { return direction; }
	CT::Status GetStatus() { return status; }
	CT::Cell& GetStartCell() {return cell; }
	CT::ShipPart* GetShipParts() { return shipPart; }
	uint32_t* GetShipPartsStatus() { return ShipBlocksStatus; }
	wchar_t* GetShipArray() const { return ship; }
	const wchar_t GetSymByStatus(uint32_t Status) { return Symbols[Status]; }
	bool Hit(CT::Vector2<uint32_t> Pos);
	bool Hit(std::wstring cellName);
protected:

private:
	inline void SetupShip();
	uint32_t CoordToArrPos(CT::Vector2<uint32_t> Pos) const;

	int32_t Length;
	CT::Cell cell;
	CT::Vector2<uint32_t> StartPos;
	CT::Direction direction;
	CT::Status status;
	
	wchar_t Symbols[3] = { L'X',L'-',L'=' }; //1 - Alive, 2 - Wraped, 3 - Destroyed
	wchar_t* ship = nullptr;
	uint32_t* ShipBlocksStatus = nullptr;
	CT::ShipPart* shipPart = nullptr;
	//std::array<std::map<uint32_t,wchar_t>, Length> ship   //Бля буду, варик хороший, но надо доработать...
};


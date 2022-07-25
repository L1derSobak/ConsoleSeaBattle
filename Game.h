#pragma once
#include "Screen.h"
#include "Field.h"

class Game
{
public:
	Game();
	~Game();

	void InitGameFields();
	void DrawFields();

	bool HitCell(std::wstring CellName);
	bool SetShip(Ship ship, std::wstring cellName);
	//DEBUG ZONE
	CT::Vector2<uint32_t> GetPosFromCell(std::wstring Cell);
protected:
	Screen scrn;
private:
	void WriteavaliableShips(uint32_t _AvaliableShips);

	//bool isValidCellName();
	uint32_t AvalibleShips;
	const bool isCellExist(std::wstring cellName);
	const bool EditCellStatus(std::wstring cellName, CT::CellStatus cellStatus);
	Field PlayerField = Field(CT::Owner::Player, { 10U,40U });
	Field AIField = Field(CT::Owner::AI, { 100U,40U });


};


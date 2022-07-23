#include "Game.h"

Game::Game()
{
	InitGameFields();
	DrawFields();
}

Game::~Game()
{

}

void Game::InitGameFields()
{

}

void Game::DrawFields()
{
	scrn.Add2dArray(PlayerField.GetFieldArray(), PlayerField.GetFieldSize(), { 5,1 });
	scrn.Add2dArray(AIField.GetFieldArray(), AIField.GetFieldSize(), { 70,1 });
	scrn.Draw();
}

bool Game::HitCell(std::wstring CellName)
{
	//return PlayerField.Hit(GetPosFromCell(CellName));
	//std::wstring _TCellName = std::nouppercase(CellName);
	CellName[0] = toupper(CellName[0]);
	if (CellName.size() > 3 || CellName.size()<2) return false;
	return PlayerField.Hit(CellName);
}

bool Game::SetShip(Ship ship, std::wstring cellName)
{
	//Öèôðû
	//wchar_t num = 49;//1
	//Áóêâû
	//wchar_t sym = 65; // A (end)
	wchar_t Sym = cellName[0], Num = cellName.size() == 3 ? 59 : cellName[1];
	switch (ship.GetDirection())
	{
	case CT::Direction::UP:
		if (Num - ship.GetLength() < L'1'-1)return false;
		break;
	case CT::Direction::DOWN:
		if (Num + ship.GetLength() >59)return false;
		break;
	case CT::Direction::LEFT:
		if (Sym - ship.GetLength() < L'A'-1)return false;
		break;
	case CT::Direction::RIGHT:
		if (Sym + ship.GetLength() > L'J'+1)return false;
		break;
	default:
		break;
	}
	PlayerField.SetShip(ship, cellName);
	return false;
}

CT::Vector2<uint32_t> Game::GetPosFromCell(std::wstring Cell)
{
	return PlayerField.GetPosFromCell(Cell);
}

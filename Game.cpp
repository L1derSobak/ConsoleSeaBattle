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

CT::Vector2<uint32_t> Game::GetPosFromCell(std::wstring Cell)
{
	return PlayerField.GetPosFromCell(Cell);
}

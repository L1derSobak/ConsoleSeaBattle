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
	scrn.Add2dArray(PlayerField.GetFieldArray(), PlayerField.GetFieldSize(), { 10,1 });
	scrn.Add2dArray(AIField.GetFieldArray(), AIField.GetFieldSize(), { 70,1 });
	scrn.Draw();
}

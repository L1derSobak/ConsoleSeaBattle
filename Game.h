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

	//DEBUG ZONE
	CT::Vector2<uint32_t> GetPosFromCell(std::wstring Cell);
protected:
	Screen scrn;
private:
	Field PlayerField = Field(CT::Owner::Player, { 10,40 });
	Field AIField = Field(CT::Owner::AI, { 100,40 });
};


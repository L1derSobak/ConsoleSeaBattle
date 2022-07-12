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
protected:
	Screen scrn;
private:
	Field PlayerField = Field(CT::Owner::Player, { 10,40 });
	Field AIField = Field(CT::Owner::AI, { 100,40 });
};


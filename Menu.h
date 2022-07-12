#pragma once
#include <list>
#include <string>
#include "CoreTypes.h"
#include "System.h"

class Menu
{
public:
	Menu();
	Menu(std::list<std::string> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, CT::Vector2<int16_t> WindowSize, CT::Vector2<unsigned int>WindowPos);
	Menu(std::list<CT::MenuPoint> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, CT::Vector2<int16_t> WindowSize, CT::Vector2<unsigned int>WindowPos);
	Menu(CT::MenuParams Params);
	~Menu();

	std::list<CT::MenuPoint> StringToMenuPoint(std::list<std::string> Params);
	std::list<CT::MenuPoint> GetChoises();
	void SetValue(std::list<CT::MenuPoint> Params);
	void SetMenuParams(CT::MenuParams MenuParameters);
	void Draw(unsigned const short pos);
	unsigned const short GetChoice();

private:
	CT::MenuParams CMenuParams;
	System sys;
	/*Monitor and Console Screen Parameters*/
	CT::Vector2<unsigned int>SymbolNums;

	unsigned short ActualPosition = 0;

	void ClearScreen();
	void DebugInfo();
};


#pragma once
#include <list>
#include <string>
#include "BaseTypes.h"
#include "CoreFunctions.h"
#include "Graphics.h"
#include "System.h"

class Menu
{
public:
	Menu();
	Menu(std::list<std::string> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<int16_t> WindowSize, BT::Vector2<unsigned int>WindowPos);
	Menu(std::list<BT::MenuPoint> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<int16_t> WindowSize, BT::Vector2<unsigned int>WindowPos);
	Menu(BT::MenuParams Params);
	~Menu();

	std::list<BT::MenuPoint> StringToMenuPoint(std::list<std::string> Params);
	std::list<BT::MenuPoint> GetChoises();
	void SetValue(std::list<BT::MenuPoint> Params);
	void SetMenuParams(BT::MenuParams MenuParameters);
	void Draw(unsigned const short pos);
	unsigned const short GetChoice();

private:
	BT::MenuParams CMenuParams;
	System sys;
	/*Monitor and Console Screen Parameters*/
	BT::Vector2<unsigned int>SymbolNums;

	unsigned short ActualPosition = 0;

	void ClearScreen();
	void DebugInfo();
};


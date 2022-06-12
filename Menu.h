#pragma once
#include <list>
#include <string>
#include "BaseTypes.h"
#include "CoreFunctions.h"
#include "Graphics.h"

class Menu
{
public:
	Menu();
	Menu(std::list<std::string> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int>WindowPos);
	Menu(std::list<BT::MenuPoint> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int>WindowPos);
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
	HWND hWindowConsole = GetConsoleWindow();

	/*Monitor and Console Screen Parameters*/
	unsigned int SWidth = GetSystemMetrics(SM_CXSCREEN);  // разрешение экрана по горизонтали
	unsigned int SHeight = GetSystemMetrics(SM_CYSCREEN); // разрешение экрана по вертикали
	unsigned const int MinWinSizeX = 680; 
	unsigned const int MinWinSizeY = 480;
	BT::Vector2<unsigned int> DefaultWindowSize{ MinWinSizeX,MinWinSizeY };
	BT::Vector2<unsigned int> DefaultPos{ (SWidth - MinWinSizeX) / 2 - 1 ,(SHeight - MinWinSizeY) / 2 - 1 };
	BT::Vector2<unsigned int>SymbolNums;

	unsigned short ActualPosition = 0;

	void SetWindowPosition(unsigned int X, unsigned int Y);
	void SetWindowSize(unsigned int Width, unsigned int Height);
	void ClearScreen();
	void DebugInfo();
};


#pragma once
#include <list>
#include <string>
#include "BaseTypes.h"
#include "CoreFunctions.h"

struct MenuPoint
{
	std::string Name;
	unsigned short Position;
};

class MenuParams
{
public:
	std::string MenuName;
	std::list<MenuPoint> Params;
	unsigned short TextSize;
	unsigned short Padding;
	BT::Vector2<unsigned int> WindowSize;
	BT::Vector2<unsigned int> WindowPos;
	bool IsNumerated;
};

class Menu
{
public:
	Menu();
	Menu(std::list<std::string> Params);
	Menu(std::list<std::string> Params, unsigned short const TextSize);
	Menu(std::list<std::string> Params, unsigned short const TextSize, unsigned short const Padding);
	Menu(std::list<std::string> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize);
	Menu(std::list<std::string> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int>WindowPos);
	Menu(std::list<MenuPoint> Params);
	Menu(std::list<MenuPoint> Params, unsigned short const TextSize);
	Menu(std::list<MenuPoint> Params, unsigned short const TextSize, unsigned short const Padding);
	Menu(std::list<MenuPoint> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize);
	Menu(std::list<MenuPoint> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int>WindowPos);
	Menu(MenuParams Params);
	~Menu();

	std::list<MenuPoint> StringToMenuPoint(std::list<std::string> Params);
	std::list<std::string> GetChoisesC(); //C - Classic
	std::list<MenuPoint> GetChoisesM(); //M - Modern
	void SetValue(std::list<std::string> Params);
	void SetValue(std::list<MenuPoint> Params);
	void SetMenuParams(MenuParams MenuParameters);
	void Draw();

private:
	HWND hWindowConsole = GetConsoleWindow();
	std::list<MenuPoint> MenuPoints;
	std::string MenuName;
	unsigned short TextSize;
	unsigned short Padding;

	/*Monitor and Console Screen Parameters*/
	unsigned int SWidth = GetSystemMetrics(SM_CXSCREEN);  // разрешение экрана по горизонтали
	unsigned int SHeight = GetSystemMetrics(SM_CYSCREEN); // разрешение экрана по вертикали
	BT::Vector2<unsigned int> WindowSize;
	//unsigned int WindowSizeX = 900; //Размер окна консоли по горизонтали
	//unsigned int WindowSizeY = 800; //Размер окна консоли по вертикали
	unsigned const int MinWinSizeX = 680; //81 символ => размер символа:8,4
	unsigned const int MinWinSizeY = 480;
	BT::Vector2<unsigned int> DefaultWindowSize{ MinWinSizeX,MinWinSizeY };
	BT::Vector2<unsigned const int> DefaultPos{ (SWidth - MinWinSizeX) / 2 - 1 ,(SHeight - MinWinSizeY) / 2 - 1 };
	BT::Vector2<unsigned int> DefaultPosE{ (SWidth - MinWinSizeX) / 2 - 1 ,(SHeight - MinWinSizeY) / 2 - 1 };
	//unsigned const int DefaultPosX = (SWidth - MinWinSizeX) / 2 - 1;
	//unsigned const int DefaultPosY = (SHeight - MinWinSizeY) / 2 - 1;
	BT::Vector2<unsigned int> WindowPos;

	void SetWindowPosition(unsigned int X, unsigned int Y);
	void SetWindowSize(unsigned int Width, unsigned int Height);
	void DebuggInfo();
};


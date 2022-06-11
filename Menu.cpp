#include "Menu.h"
#include <iostream>
Menu::Menu() : MenuName("Menu"), 
				TextSize(12),
				Padding(2),
				WindowPos(DefaultPosE)
{
	MenuPoints.push_back({ "Start", 0 });
	MenuPoints.push_back({ "Options", 1 });
	MenuPoints.push_back({ "Exit", 2 });
	WindowSize = DefaultWindowSize;
}
Menu::Menu(std::list<std::string> Params) : MenuName("Menu"),
											TextSize(12),
											Padding(2),
											WindowPos(DefaultPosE)
{
	WindowSize = DefaultWindowSize;
	unsigned short Pos = 0;
	for (auto item : Params)
	{
		MenuPoints.push_back({ item, Pos });
		Pos++;
	}
}
Menu::Menu(std::list<std::string> Params, unsigned short const TextSize) : MenuName("Menu"),
																			TextSize(TextSize),
																			Padding(2),
																			WindowPos(DefaultPosE)
{
	WindowSize = DefaultWindowSize;
	unsigned short Pos = 0;
	for (auto item : Params)
	{
		MenuPoints.push_back({ item, Pos });
		Pos++;
	}
}
Menu::Menu(std::list<std::string> Params, unsigned short const TextSize, unsigned short const Padding) : MenuName("Menu"),
																											TextSize(TextSize),
																											Padding(Padding),
																											WindowPos(DefaultPosE)
{
	WindowSize = DefaultWindowSize;
	unsigned short Pos = 0;
	for (auto item : Params)
	{
		MenuPoints.push_back({ item, Pos });
		Pos++;
	}
}
Menu::Menu(std::list<std::string> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize) : MenuName("Menu"),
																																				TextSize(TextSize),
																																				Padding(Padding),
																																				WindowPos(DefaultPosE)
{
	this->WindowSize=WindowSize;
	unsigned short Pos = 0;
	for (auto item : Params)
	{
		MenuPoints.push_back({ item, Pos });
		Pos++;
	}
}
Menu::Menu(std::list<std::string> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int> WindowPos) : MenuName("Menu"),
																																													TextSize(TextSize),
																																													Padding(Padding),
																																													WindowPos(WindowPos)
{
	this->WindowSize = WindowSize;
}
Menu::Menu(std::list<MenuPoint> Params) : MenuName("Menu"), 
											TextSize(12),
											Padding(2),
											MenuPoints(Params),
											WindowPos(DefaultPosE)
{
	WindowSize = DefaultWindowSize;
}
Menu::Menu(std::list<MenuPoint> Params, unsigned short const TextSize) : MenuName("Menu"),
																			TextSize(TextSize),
																			Padding(2), MenuPoints(Params), 
																			WindowPos(DefaultPosE)
{
	WindowSize = DefaultWindowSize;
}
Menu::Menu(std::list<MenuPoint> Params, unsigned short const TextSize, unsigned short const Padding) : MenuName("Menu"),
																										TextSize(TextSize),
																										Padding(Padding),
																										MenuPoints(Params), 
																										WindowPos(DefaultPosE)
{
	WindowSize = DefaultWindowSize;
}
Menu::Menu(std::list<MenuPoint> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize) : MenuName("Menu"),
																																				TextSize(TextSize),
																																				Padding(Padding),
																																				MenuPoints(Params),
																																				WindowPos(DefaultPosE)
{
	this->WindowSize = WindowSize;
}
Menu::Menu(std::list<MenuPoint> Params, unsigned short const TextSize, unsigned short const Padding, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int>WindowPos) : MenuName("Menu"),
																																													TextSize(TextSize),
																																													Padding(Padding),
																																													MenuPoints(Params),
																																													WindowPos(WindowPos)
{
	this->WindowSize = WindowSize;
}
Menu::Menu(MenuParams Params) : MenuName(Params.MenuName), 
								TextSize(Params.TextSize),
								Padding(Params.Padding),
								MenuPoints(Params.Params),
								WindowPos(Params.WindowPos)
{
	WindowSize = Params.WindowSize;
}
Menu::~Menu() { std::cout << "\t\t\t\tDestroyed"; }

std::list<MenuPoint> Menu::StringToMenuPoint(std::list<std::string> Params)
{
	std::list<MenuPoint> Return;
	unsigned short Pos = 0;
	for (auto item : Params)
		Return.push_back({ item, Pos++ });
	return Return;
}

std::list<std::string> Menu::GetChoisesC()
{
	std::list<std::string> Params;
	for (auto item : MenuPoints)
		Params.push_back(item.Name);
	return Params;
}

std::list<MenuPoint> Menu::GetChoisesM()
{
	return MenuPoints;
}

void Menu::SetValue(std::list<std::string> Params)
{
	MenuPoints = StringToMenuPoint(Params);
	//for(size_t i = Params.size()<MenuPoints.size() ? MenuPoints.size() : Params.size(); i)
}

void Menu::SetValue(std::list<MenuPoint> Params)
{
	MenuPoints = Params;
}

void Menu::SetMenuParams(MenuParams MenuParameters)
{
	MenuName = MenuParameters.MenuName;
	TextSize = MenuParameters.TextSize;
	Padding = MenuParameters.Padding;
	MenuPoints = MenuParameters.Params;
	WindowSize = MenuParameters.WindowSize;
	WindowPos = MenuParameters.WindowPos;
}

void Menu::Draw()
{
	DebuggInfo();
}

void Menu::SetWindowPosition(unsigned int X, unsigned int Y)
{
	MoveWindow(hWindowConsole,X, Y,WindowSize.Element1, WindowSize.Element2, TRUE);
}

void Menu::SetWindowSize(unsigned int Width, unsigned int Height)
{
	MoveWindow(hWindowConsole, WindowPos.Element1, WindowPos.Element2, Width, Height, TRUE);
}

void Menu::DebuggInfo()
{/*
	std::cout << "     \n\n       n\tn\ba";
	HWND Console = GetConsoleWindow();
	HDC Hdc = GetDC(Console);
	COLORREF Color = RGB(122, 220, 69);
	for (size_t i = 0; i < WindowSize.Element1; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			SetPixel(Hdc, i, j, Color);
			SetPixel(Hdc, i, j+427, Color);
		}
	}
	for (size_t i = 0; i < WindowSize.Element2; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			SetPixel(Hdc, j, i, Color);
			SetPixel(Hdc, j + 635, i, Color);
		}
	}
	
	ReleaseDC(Console, Hdc);
	std::cin.ignore();
	*/
	unsigned int LastSymPos = static_cast<unsigned int>(((WindowSize.Element1 - 1) / 8) - 5);
	std::cout << "+";
	for (size_t i = 1; i < ((WindowSize.Element1 - 1)/8)-5; i++)
		std::cout << "-";
	std::cout << "+";
	//8(ширина)x16(высота)
	//680x480
	//680/8=85
	//480/16=30
	std::cout << "|\t";
	CF::gotoxy(((WindowSize.Element1/8-11)/2)-1, 1);
	std::cout << "DEBUG MODE"; CF::gotoxy(LastSymPos, 1); std::cout << "|\n";// << std::endl;
	std::cout << "|\tMenu name: " << MenuName; CF::gotoxy(LastSymPos, 2); std::cout << "|\n";// << std::endl;
	std::cout << "|\tText Size: " << TextSize;  CF::gotoxy(LastSymPos, 3); std::cout << "|\n";// << std::endl;
	std::cout << "|\tPadding: " << Padding; CF::gotoxy(LastSymPos, 4); std::cout << "|\n";// << std::endl;
	std::cout << "|\tChoises:"; CF::gotoxy(LastSymPos, 5); std::cout << "|\n";// << std::endl;
	short p = 6;
	for (auto it : MenuPoints)
	{
		std::cout << "|\t\t" << it.Name << " is " << it.Position; CF::gotoxy(LastSymPos, p++); std::cout << "|\n";// << std::endl;
	}
	std::cout << "|"; CF::gotoxy(LastSymPos, 9); std::cout << "|";
	std::cout << "|";
	CF::gotoxy(((WindowSize.Element1 / 8 - 23) / 2) - 1, 9);
	std::cout << "Window and Screen Info"; CF::gotoxy(LastSymPos, 10); std::cout << "|";
	std::cout << "|"; CF::gotoxy(LastSymPos, 11); std::cout << "|";
	std::cout << "|\tWidth: " << SWidth << " | " << "Height: " << SHeight; CF::gotoxy(LastSymPos, 12); std::cout << "|\n";// << std::endl;
	std::cout << "|\tWindow size: \n\tX: " << WindowSize.Element1 << "\tY: " << WindowSize.Element2; CF::gotoxy(LastSymPos, 13); std::cout << "|\n";// << std::endl;
	std::cout << "|\tWindow Position: \n\tX: " << WindowPos.Element1 << "\tY: " << WindowPos.Element2; CF::gotoxy(LastSymPos, 14); std::cout << "|\n";// << std::endl;

	std::cout << "+";
	for (size_t i = 1; i < ((WindowSize.Element1 - 1) / 8) - 5; i++)
		std::cout << "-";
	std::cout << "+";
	SetWindowSize(WindowSize.Element1, WindowSize.Element2);
	SetWindowPosition(WindowPos.Element1, WindowPos.Element2);
	
}


#include "Menu.h"
#include <iostream>
#include <exception>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
Menu::Menu()
{
	CMenuParams.MenuName = "Menu";
	CMenuParams.Padding = 2;
	CMenuParams.TextSize = 16;
	CMenuParams.IsNumerated = false;
	CMenuParams.Positions = 3;
	CMenuParams.Params = { {"Start",0},{"settings",1},{"Exit",2} };
	CMenuParams.WindowPos = sys.GetWindowPos();
	CMenuParams.WindowSize = sys.GetWindowSize();
	SymbolNums.X = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.X - 1) / 8) - 5));
	SymbolNums.Y = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Y - 1) / 16) - 3));
}
Menu::Menu(std::list<std::string> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<int16_t> WindowSize, BT::Vector2<unsigned int> WindowPos)
{
	CMenuParams.MenuName = MenuName;
	CMenuParams.Padding = Padding;
	CMenuParams.TextSize = TextSize;
	CMenuParams.IsNumerated = isNumirated;
	CMenuParams.Params = StringToMenuPoint(Params);
	CMenuParams.WindowPos = WindowPos;
	CMenuParams.WindowSize = WindowSize;
	SymbolNums.X = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.X - 1) / 8) - 5));
	SymbolNums.Y = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Y - 1) / 16) - 3));
}
Menu::Menu(std::list<BT::MenuPoint> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<int16_t> WindowSize, BT::Vector2<unsigned int>WindowPos)
{
	CMenuParams.MenuName = MenuName;
	CMenuParams.Padding = Padding;
	CMenuParams.TextSize = TextSize;
	CMenuParams.IsNumerated = isNumirated;
	CMenuParams.Params = Params;
	CMenuParams.WindowPos = WindowPos;
	CMenuParams.WindowSize = WindowSize;
	SymbolNums.X = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Y - 1) / 8) - 5));
	SymbolNums.X = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Y - 1) / 16) - 3));
}
Menu::Menu(BT::MenuParams Params)
{
	CMenuParams = Params;
	SymbolNums.X = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Y - 1) / 8) - 5));
	SymbolNums.X = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Y - 1) / 16) - 3));
}
Menu::~Menu() { std::cout << "\t\t\t\tDestroyed"; }

std::list<BT::MenuPoint> Menu::StringToMenuPoint(std::list<std::string> Params)
{
	std::list<BT::MenuPoint> Return;
	unsigned short Pos = 0;
	for (auto item : Params)
		Return.push_back({ item, Pos++ });
	return Return;
}

std::list<BT::MenuPoint> Menu::GetChoises()
{
	return CMenuParams.Params;
}

void Menu::SetValue(std::list<BT::MenuPoint> Params)
{
	CMenuParams.Params = Params;
}

void Menu::SetMenuParams(BT::MenuParams MenuParameters)
{
	CMenuParams = MenuParameters;
}

void Menu::Draw(unsigned const short pos)
{
	
}

unsigned const short Menu::GetChoice()
{
	return 0;
}

void Menu::ClearScreen()
{
	
}

void Menu::DebugInfo()
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
	//CF::DrawTable(CMenuParams.WindowSize.X, CMenuParams.WindowSize.Y);

	//8(ширина)x16(высота)
	//680x480
	//680/8=85
	//480/16=30
	
	CF::gotoxy(((CMenuParams.WindowSize.X/8-11)/2)-1, 1);
	std::cout << "DEBUG MODE" << std::endl;// CF::gotoxy(LastSymPosX, 1); std::cout << "|\n";// << std::endl;
	std::cout << "\tMenu name: " << CMenuParams.MenuName << std::endl;// CF::gotoxy(LastSymPosX, 2); std::cout << "|\n";// << std::endl;
	std::cout << "\tText Size: " << CMenuParams.TextSize << std::endl;//  CF::gotoxy(LastSymPosX, 3); std::cout << "|\n";// << std::endl;
	std::cout << "\tPadding: " << CMenuParams.Padding << std::endl;// CF::gotoxy(LastSymPosX, 4); std::cout << "|\n";// << std::endl;
	std::cout << "\tIs numirated: " << CMenuParams.IsNumerated << std::endl;
	std::cout << "\tThere is "<<CMenuParams.Positions<<" Choises:" << std::endl; //CF::gotoxy(LastSymPosX, 5); std::cout << " | \n";// << std::endl;
	for (auto it : CMenuParams.Params)
	{
		std::cout << "\t\t" << it.Name << " is " << it.Position << std::endl;// CF::gotoxy(LastSymPosX, p++); std::cout << "|\n";// << std::endl;
	}
	CF::gotoxy(((CMenuParams.WindowSize.X / 8 - 23) / 2) - 1, 11);
	std::cout << "Window and Screen Info\n" << std::endl;// CF::gotoxy(LastSymPosX, 10); std::cout << "|";
	std::cout << "\tWidth: " << sys.GetScreenSize().X << " | " << "Height: " << sys.GetScreenSize().Y << std::endl;// CF::gotoxy(LastSymPosX, 12); std::cout << "|\n";// << std::endl;
	std::cout << "\tWindow size: \n\tX: " << CMenuParams.WindowSize.X << "\tY: " << CMenuParams.WindowSize.Y << std::endl;// CF::gotoxy(LastSymPosX, 13); std::cout << "|\n";// << std::endl;
	std::cout << "\tWindow Position: \n\tX: " << CMenuParams.WindowPos.X << "\tY: " << CMenuParams.WindowPos.Y << std::endl;// CF::gotoxy(LastSymPosX, 14); std::cout << "|\n";// << std::endl;
	try {
		sys.SetWindowSize(CMenuParams.WindowSize.X, CMenuParams.WindowSize.Y);
		sys.SetWindowPosition(CMenuParams.WindowPos.X, CMenuParams.WindowPos.Y);
		//SetWindowSize(CMenuParams.WindowSize.Element1, CMenuParams.WindowSize.Element2);
		//SetWindowPosition(CMenuParams.WindowPos.Element1, CMenuParams.WindowPos.Element2);
	}
	catch (std::exception e) { throw e.what(); }
	
	
}

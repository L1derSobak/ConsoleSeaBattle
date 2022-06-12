#include "Menu.h"
#include <iostream>
#include <exception>
#include <Windows.h>
#include <conio.h>

Menu::Menu()
{
	CMenuParams.MenuName = "Menu";
	CMenuParams.Padding = 2;
	CMenuParams.TextSize = 16;
	CMenuParams.IsNumerated = false;
	CMenuParams.Positions = 3;
	CMenuParams.Params = { {"Start",0},{"settings",1},{"Exit",2} };
	CMenuParams.WindowPos = DefaultPos;
	CMenuParams.WindowSize = { MinWinSizeX,MinWinSizeY };
	SymbolNums.Element1 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element1 - 1) / 8) - 5));
	SymbolNums.Element2 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element2 - 1) / 16) - 3));
}
Menu::Menu(std::list<std::string> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int> WindowPos)
{
	CMenuParams.MenuName = MenuName;
	CMenuParams.Padding = Padding;
	CMenuParams.TextSize = TextSize;
	CMenuParams.IsNumerated = isNumirated;
	CMenuParams.Params = StringToMenuPoint(Params);
	CMenuParams.WindowPos = WindowPos;
	CMenuParams.WindowSize = WindowSize;
	SymbolNums.Element1 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element1 - 1) / 8) - 5));
	SymbolNums.Element2 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element2 - 1) / 16) - 3));
}
Menu::Menu(std::list<BT::MenuPoint> Params, std::string MenuName, bool isNumirated, unsigned short const TextSize, unsigned short const Padding, unsigned short const Positions, BT::Vector2<unsigned int> WindowSize, BT::Vector2<unsigned int>WindowPos)
{
	CMenuParams.MenuName = MenuName;
	CMenuParams.Padding = Padding;
	CMenuParams.TextSize = TextSize;
	CMenuParams.IsNumerated = isNumirated;
	CMenuParams.Params = Params;
	CMenuParams.WindowPos = WindowPos;
	CMenuParams.WindowSize = WindowSize;
	SymbolNums.Element1 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element1 - 1) / 8) - 5));
	SymbolNums.Element2 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element2 - 1) / 16) - 3));
}
Menu::Menu(BT::MenuParams Params)
{
	CMenuParams = Params;
	SymbolNums.Element1 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element1 - 1) / 8) - 5));
	SymbolNums.Element2 = static_cast<unsigned int>(floor(((CMenuParams.WindowSize.Element2 - 1) / 16) - 3));
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
	//Надо попробовать соотношение 3:2х+1
	//Инициилизация необходимых данных
	ActualPosition = pos;
	unsigned int MenuNameSymbols = floor(3 * (SymbolNums.Element2 / (4 + 2 * CMenuParams.Positions)));
	unsigned int ParamSymbols = floor((1 + 2 * CMenuParams.Positions) * (SymbolNums.Element2 / (4 + 2 * CMenuParams.Positions)));
	unsigned int ParamSot = floor(2 * CMenuParams.Positions + 1);
	
	ClearScreen();

	CF::DrawTable(CMenuParams.WindowSize.Element1, CMenuParams.WindowSize.Element2);
	//Отрисовываем позиции
	CF::gotoxy(((SymbolNums.Element1 - 2) - CMenuParams.MenuName.size()) / 2, 2 * (MenuNameSymbols / 3));
	std::cout << CMenuParams.MenuName;

	/*
		+------+
		|      |
		+------+
		|      |
		|      |
		|      |
		+------+

		((ParamsSymbol/CMenuParams.Positions)/3)*(2*(it.posiion+1)) //Технически, это должно правильно дать позиции пунктов т.к
		((Высота общего кол-во символов дляпунктов/Кол-во пунктов)/3)*(2*(позиция пункта+1))

	*/

	

	for (auto it : CMenuParams.Params)
	{
		if (!CMenuParams.IsNumerated == true)
		{
			//CF::gotoxy(((SymbolNums.Element1 - 2) - it.Name.size()) / 2, MenuNameSymbols + (ParamSymbols / ParamSot) * ((it.Position + 1) * 2));
			if (it.Position == pos)
			{
				CF::gotoxy(((SymbolNums.Element1 - 2) - (it.Name.size()+8)) / 2, MenuNameSymbols + (floor((ParamSymbols / CMenuParams.Positions) / 3) * 2 * (2 * (it.Position + 1))));
				std::cout << ">>  " << it.Name << "  <<";
			}
			CF::gotoxy(((SymbolNums.Element1 - 2) - it.Name.size()) / 2, MenuNameSymbols+(floor((ParamSymbols/CMenuParams.Positions)/3)*2*(2*(it.Position+1))));
			std::cout << it.Name;
		}
		else
		{
			if (it.Position == pos)
			{
				CF::gotoxy(((SymbolNums.Element1 - 2) - (it.Name.size() + 11)) / 2, MenuNameSymbols + (floor((ParamSymbols / CMenuParams.Positions) / 3) * 2 * (2 * (it.Position + 1))));
				std::cout << ">>  " << it.Position + 1 << ". " << it.Name << "  <<";
			}
			//CF::gotoxy(((SymbolNums.Element1 - 2) - (it.Name.size()+3)) / 2, MenuNameSymbols + (ParamSymbols / ParamSot) * ((it.Position + 1) * 2));
			CF::gotoxy(((SymbolNums.Element1 - 2) - (it.Name.size()+3)) / 2, MenuNameSymbols + (floor((ParamSymbols / CMenuParams.Positions) / 3) * 2 * (2 * (it.Position + 1))));
			std::cout << it.Position + 1 << ". " << it.Name;
		}
	}
	//DebugInfo();
}

unsigned const short Menu::GetChoice()
{
	unsigned short Choice;
	Choice = _getch();
	Choice = Choice == 224 ? _getch() : Choice;
	return Choice;
}

void Menu::SetWindowPosition(unsigned int X, unsigned int Y)
{
	MoveWindow(hWindowConsole,X, Y,CMenuParams.WindowSize.Element1, CMenuParams.WindowSize.Element2, TRUE);
}

void Menu::SetWindowSize(unsigned int Width, unsigned int Height)
{
	MoveWindow(hWindowConsole, CMenuParams.WindowPos.Element1, CMenuParams.WindowPos.Element2, Width, Height, TRUE);
}

void Menu::ClearScreen()
{
	CF::gotoxy(0, 0);
	for (size_t i = 0; i < SymbolNums.Element2; i++)
	{
		for (size_t i = 0; i < SymbolNums.Element1; i++)
			std::cout << " ";
		std::cout << std::endl;
	}
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
	CF::DrawTable(CMenuParams.WindowSize.Element1, CMenuParams.WindowSize.Element2);

	//8(ширина)x16(высота)
	//680x480
	//680/8=85
	//480/16=30
	
	CF::gotoxy(((CMenuParams.WindowSize.Element1/8-11)/2)-1, 1);
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
	CF::gotoxy(((CMenuParams.WindowSize.Element1 / 8 - 23) / 2) - 1, 11);
	std::cout << "Window and Screen Info\n" << std::endl;// CF::gotoxy(LastSymPosX, 10); std::cout << "|";
	std::cout << "\tWidth: " << SWidth << " | " << "Height: " << SHeight << std::endl;// CF::gotoxy(LastSymPosX, 12); std::cout << "|\n";// << std::endl;
	std::cout << "\tWindow size: \n\tX: " << CMenuParams.WindowSize.Element1 << "\tY: " << CMenuParams.WindowSize.Element2 << std::endl;// CF::gotoxy(LastSymPosX, 13); std::cout << "|\n";// << std::endl;
	std::cout << "\tWindow Position: \n\tX: " << CMenuParams.WindowPos.Element1 << "\tY: " << CMenuParams.WindowPos.Element2 << std::endl;// CF::gotoxy(LastSymPosX, 14); std::cout << "|\n";// << std::endl;
	try {
		SetWindowSize(CMenuParams.WindowSize.Element1, CMenuParams.WindowSize.Element2);
		SetWindowPosition(CMenuParams.WindowPos.Element1, CMenuParams.WindowPos.Element2);
	}
	catch (std::exception e) { throw e.what(); }
	
	
}

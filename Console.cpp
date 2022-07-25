#include <iostream>
#include <Windows.h>
#include "Screen.h"
#include "Game.h"
#include "Ship.h"

/*wchar_t* DrawEdge(wchar_t* buffer)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
				buffer[i + j * width] = '+';
			else
				buffer[i + j * width] = ' ';
			//screen[i + j * width] = pixel;
		}
	}
	buffer[width * height] = '\0';
	return buffer;
}*/
/*
	CT::Vector2<SHORT> GetCursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO CursorInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
	return { CursorInfo.dwCursorPosition.X, CursorInfo.dwCursorPosition.Y };
}
 */
COORD GetCursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;

	if (GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		coord.X = csbi.dwCursorPosition.X;
		coord.Y = csbi.dwCursorPosition.Y;
		return coord;
	}
	else
	{
		coord.X = 0;
		coord.Y = 0;
		return coord;
	}
}
/*
int x;
int* y = &x; // От любой переменной можно взять адрес при помощи операции взятия адреса "&". Эта операция возвращает указатель
int z = *y; // Указатель можно разыменовать при помощи операции разыменовывания "*". Это операция возвращает тот объект, на который указывает указатель

int x;
int &y = x;
int z = y;
*/
int wmain(int argc, wchar_t* argv[])
{
	//setlocale(LC_ALL, "Rus");
	//screen = FullBuffer(screen);
	//Sleep(500);
	//screen = DrawEdge(screen);
	//WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
	//Screen scrn;
	//Game game;
	//Ship ship(5, { 20,20 }, CT::Direction::DOWN);
		//Screen scrn;
	//for (uint32_t i = 0; i < ship.GetLength(); i++)
	//	scrn.AddCharacter(ship.GetShipArray()[i], { 20,i + 20 });
	//wchar_t* testArray = new wchar_t[21];
	//testArray[20] = '\0';
	//ZeroMemory(testArray, 20);
	//for (size_t i = 0; i < 20; i++)
	//	testArray[i] = '*';
	//scrn.Add2dArray(testArray, { 4,5 }, { 20,20 });
	//scrn.AddString(L"I LOVE YOU!", { 30,20 });
	//std::cout << scrn.GetSystem().GetOptimalWindowSize().X << " | " << scrn.GetSystem().GetOptimalWindowSize().Y;

	Game game;
	//if (game.HitCell(L"A3"))//exit(0);// std::cout << "Sucess!";
	//game.HitCell(L"A1");
	//game.HitCell(L"C9");
	//game.HitCell(L"j1");
	//game.HitCell(L"A1");
	//game.HitCell(L"B1");
	//if(!game.HitCell(L"BB")) game.HitCell(L"f10");
	//game.SetShip({ 2U, CT::Direction::UP }, L"J8"); //Ship(uint32_t _Length, CT::Cell _Cell, CT::Direction _Direction);
	
	game.SetShip({ 4U,CT::Direction::DOWN }, L"Б2");
	game.SetShip({ 3U,CT::Direction::UP }, L"Й8");
	if(!game.SetShip({ 2U,CT::Direction::RIGHT }, L"Б2"))game.SetShip({ 2U,CT::Direction::DOWN }, L"Д5");

	game.SetShip({ 3U,CT::Direction::RIGHT }, L"Ж1");
	game.SetShip({ 2U,CT::Direction::UP }, L"Б9");
	game.SetShip({ 2U,CT::Direction::RIGHT }, L"Г10");
	game.SetShip({ 1U,CT::Direction::UP }, L"Г3");
	game.SetShip({ 1U,CT::Direction::UP }, L"Д1");
	game.SetShip({ 1U,CT::Direction::UP }, L"Е8");
	game.SetShip({ 1U,CT::Direction::UP }, L"Й2");

	//52428
	
	
	//if(!game.SetShip({2U, CT::Direction::RIGHT},L"A2"))game.SetShip({ 2U,CT::Direction::RIGHT }, L"A3");
	//if(!game.SetShip({ 4U, CT::Direction::DOWN }, L"GG1"))game.SetShip({ 2U, CT::Direction::UP }, L"G4");
	for (size_t i = 0; i < 100000; i++)
	{
		game.DrawFields();
		//std::cout << "Hello!";
		//std::wcout << game.GetPosFromCell(L"A1").X << " | " << game.GetPosFromCell(L"A1").Y << std::endl;
		/*if (GetAsyncKeyState(VK_RETURN))
		{
			std::cout << "Enter is Pressed!" << std::endl;
			std::cout << "\t\t";
			COORD crd = GetCursorPos();
			std::cout << crd.X << " | " << crd.Y << std::endl;
		}Sleep(100);
		COORD crd = GetCursorPos();
		std::cout << crd.X << " | " << crd.Y << std::endl;
		*/
		//if (ScreenToClient(hwnd, &p)) std::cout << p.x << " | " << p.y << std::endl;
		//if (GetAsyncKeyState(VK_LBUTTON))
		//{
			//CT::Vector2<SHORT> MPos = GetCursorPos();
			//std::cout << MPos.X << " | " << MPos.Y << std::endl;
		//	std::cout << "L button Pressd!" << std::endl;
		//}
		//Sleep(100);
		//for (uint32_t i = 0; i < ship.GetLength(); i++)
		//	scrn.AddCharacter(ship.GetShipArray()[i], { 20,i + 20 });
		//scrn.Draw();
		//if (i == 5000)
		//	ship.Hit({ 20,22 });
		//if(i == 9000)
		//	ship.Hit({ 20,22 });
		
		//uint32_t posx = i<120? i: i%120;
		//scrn.ClearScreen();
		//scrn.AddCharacter('X', {posx, 0});
		//scrn.Draw();
			//screen.SetScreenBuffer(CF::ClearBuffer(screen.GetScreenBuffer()));
			//screen.SetScreenBuffer(CF::DrawCircle(screen.GetScreenBuffer(), { 10,10 }, 6, screen.GetSystem()));
		
			//CF::DrawBuffer(screen.GetScreenBuffer(), screen.GetSystem().GetConsoleBufferHandle());
		//Sleep(100);
		//Sleep(100);
	}

}






/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void fill_line(const char* str) {
	const int line_width = 30; // took out of my head
	std::cout << str;
	for (int i(0); i < line_width - strlen(str); ++i)
		std::cout << ' ';
}

int main()
{
	//_setmode(_fileno(stdout), _O_U16TEXT);
	//setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	
	int iWidth = GetSystemMetrics(SM_CXSCREEN);  // разрешение экрана по горизонтали
	int iHeight = GetSystemMetrics(SM_CYSCREEN); // разрешение экрана по вертикали
	//std::cout << "Vertical: " << iHeight << " | " << "Horizontal: " << iWidth;
	const int WindowsSizeX = 680;
	const int WindowsSizeY = 480;
	HWND hWindowConsole = GetConsoleWindow();
	//std::cout << ((iWidth - WindowsSizeX) / 2) - 1 << " | " << ((iHeight - WindowsSizeY) / 2) - 1;
	MoveWindow(hWindowConsole, ((iWidth - WindowsSizeX) / 2)-1, ((iHeight - WindowsSizeY) / 2) - 1,   WindowsSizeX, WindowsSizeY, TRUE);

	//Меняем стиль и размер шрифта
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	wcscpy(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = 16;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	//std::cout << "\nHello! Привет!";

	//Считывание нажатий кнопок мыши 
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
	INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
	DWORD Events; // unsigned long
	COORD coord; // для координат X, Y

	//Запретить выделение консоли
	DWORD prev_mode;
	GetConsoleMode(hin, &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	std::cin.get();
	return 0;
}*/
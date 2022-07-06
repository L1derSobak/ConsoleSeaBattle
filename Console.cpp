#include <iostream>
#include <Windows.h>
#include "Screen.h"
#include "CoreFunctions.h"

int width = 120;
int height = 60;

void SetWindow(int Width, int Height)
{
	_COORD coord = { Width, Height };
	//coord.X = Width;
	//coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

wchar_t* DrawEdge(wchar_t* buffer)
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
}

int main()
{
	//screen = FullBuffer(screen);
	//Sleep(500);
	//screen = DrawEdge(screen);
	//WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
	Screen scrn;
	scrn.AddString(L"I LOVE YOU!", { 30,20 });
	//std::cout << scrn.GetSystem().GetOptimalWindowSize().X << " | " << scrn.GetSystem().GetOptimalWindowSize().Y;
	for (size_t i = 0; i < 10000; i++)
	{
		uint32_t posx = i<120? i: i%120;
		scrn.ClearScreen();
		scrn.AddCharacter('X', {posx, 0});
		scrn.Draw();
			//screen.SetScreenBuffer(CF::ClearBuffer(screen.GetScreenBuffer()));
			//screen.SetScreenBuffer(CF::DrawCircle(screen.GetScreenBuffer(), { 10,10 }, 6, screen.GetSystem()));
		
			//CF::DrawBuffer(screen.GetScreenBuffer(), screen.GetSystem().GetConsoleBufferHandle());
		Sleep(100);
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
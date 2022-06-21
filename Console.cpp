#include <iostream>
#include <Windows.h>
#include "System.h"
#include "CoreFunctions.h"
#include "Graphics.h"

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

wchar_t* AddString(wchar_t* buffer,const wchar_t* string, uint16_t x, uint16_t y)
{
	if (x > width || y > height || buffer == nullptr) return nullptr;
	
	uint16_t  sympos = 0;
	for (size_t i = x; i < x + wcslen(string); i++)
	{
		buffer[i + y * width] = string[sympos];
		sympos++;
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
	System sys;
	//wchar_t* scrn = new wchar_t[wcslen(sys.GetScreenBuffer())];
	sys.SetScreenBuffer(CF::DrawTable(sys.GetScreenBuffer(), 10, 10, 32, 32, sys));
	sys.SetScreenBuffer(CF::DrawTable(sys.GetScreenBuffer(), 0, 0, 60, 60, sys));
	for (size_t i = 0; i < 10000; i++)
	{
		CF::DrawBuffer(sys.GetScreenBuffer(), sys.GetConsoleBufferHandle());
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
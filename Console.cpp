#include "Menu.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "CoreFunctions.h"
#include "BaseTypes.h"

int main()
{
	//CF::gotoxy(2, 5);
	//std::cout << "Bonjour!";
	
	/*int i_input;
	for (size_t i = 0; i < 20; i++)
	{
		i_input = _getch();
		std::cout << i_input << std::endl;
		if (i_input == BT::Input::ArrowUp) std::cout << "pressed arrow Up\n";
	}
	*/
	
	Menu menu;
	unsigned int pos = 0;
	int temp = pos;
	menu.Draw(pos);
	unsigned short choice = menu.GetChoice();
	while (choice != BT::Input::Esc)
	{
		switch (choice)
		{
		case BT::Input::ArrowUp:
			temp--;
			pos = temp < 0 ? 0 : temp;
			menu.Draw(pos);
			break;
		case BT::Input::ArrowDown:
			temp++;
			pos = temp > menu.GetChoises().size() ? menu.GetChoises().size() : temp;
			menu.Draw(pos);
			break;
		case BT::Input::Enter:
			if (pos == 2)
				exit(0);
			break;
		}
		choice = menu.GetChoice();
	}
	std::cout << "End!";
	exit(0);
	
	std::cin.get();
	
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
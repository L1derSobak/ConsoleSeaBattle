#include "CoreFunctions.h"

void CF::gotoxy(const int& x, const int& y)
{
	COORD coord{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

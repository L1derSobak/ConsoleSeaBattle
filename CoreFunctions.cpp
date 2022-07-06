#include "CoreFunctions.h"
#include <algorithm>

void CF::gotoxy(const int& x, const int& y)
{
	COORD coord{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

wchar_t* CF::FullBuffer(wchar_t* buffer, wchar_t symbol)
{
	uint32_t size = wcslen(buffer);
	for (uint32_t i = 0; i < size; i++)
		buffer[i] = symbol;
	buffer[size] = '\0';
	return buffer;
}

wchar_t* CF::ClearBuffer(wchar_t* buffer)
{
	uint32_t size = wcslen(buffer);
	for (uint32_t i = 0; i < size; i++)
		buffer[i] = ' ';
	buffer[size] = '\0';
	return buffer;
}

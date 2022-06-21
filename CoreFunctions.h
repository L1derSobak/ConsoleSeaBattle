#pragma once
#include <Windows.h>
namespace CF
{
	void gotoxy(const int& x, const int& y);//X - Widht, Y - Height
	wchar_t* FullBuffer(wchar_t* buffer, wchar_t symbol);
	wchar_t* ClearBuffer(wchar_t* buffer);
}
class CoreFunctions
{
};


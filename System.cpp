#include "System.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <map>

System::System()
{
	CT::Vector2<uint32_t> WSize = GetOptimalWindowSize();
	SetWindowSize(WSize.X, WSize.Y);
	ConsoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(ConsoleHandle);
	//CF::FullBuffer(Screen, '+');
	//CF::DrawBuffer(Screen, ConsoleHandle);
	
	//DWORD dwBytesWritten = 0;

	/*
    SetWindowSize(WindowSize.X, WindowSize.Y);

    WindowBufferSize = WindowSize.X * WindowSize.Y + 1;
    Screen = new wchar_t[WindowBufferSize];
    ScreenBufferSize = {WindowSize.X, WindowSize.Y };
    
    SetConsoleActiveScreenBuffer(hConsole);
	*/
}

System::System(CT::Vector2<uint32_t> WinSize)
{
	SetWindowSize(WinSize.X, WinSize.Y);
	ConsoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(ConsoleHandle);
}

System::~System()
{
   
}

HANDLE System::GetHandle()
{
    return Handle;
}

HANDLE System::GetConsoleBufferHandle()
{
	return ConsoleHandle;
}

CT::Vector2<uint32_t> System::GetScreenSize()
{
	return ScreenSize;
}

CT::Vector2<int16_t> System::GetWindowSize() 
{
	return WindowSize;
}

CT::Vector2<uint32_t> System::GetWindowPos() 
{
	return WindowPosition;
}

bool System::SetWindowPosition(uint32_t X, uint32_t Y)
{
	return MoveWindow(hWindowConsole, X, Y, WindowSize.X, WindowSize.Y, TRUE);
}

/*bool System::SetWindowSize(uint32_t Width, uint32_t Height)
{
	return MoveWindow(hWindowConsole, WindowPosition.X, WindowPosition.Y, Width, Height, TRUE);
}*/

void System::SetWindowSize(int16_t Width, int16_t Height)
{
	_COORD coord = { Width, Height };
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

CT::Vector2<uint32_t> System::GetOptimalWindowSize()
{
	/*
	 Screen & Window size
		1920 x 1080 -> 120 x 60
		1680 x 1050 -> 120 x 60
		1600 x 1024 -> 120 x 58
		1600 x 900 -> 120 x 50
		1440 x 900 -> 120 x 50
		1400 x 1050 -> 120 x 60
		1366 x 768 -> 120 x 42

	*/
	return CT::Vector2<uint32_t> {120, 60};
}

CT::Vector2<uint32_t> System::GetConsolScreenSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    uint32_t columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return CT::Vector2<uint32_t>{ columns, rows };
}
#include "System.h"
#include "Graphics.h"
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include <iostream>
#include <sstream>

System::System()
{
	SetWindowSize(DefaultWindowSize.X, DefaultWindowSize.Y);
	Screen = new wchar_t[DefaultWindowSize.X * DefaultWindowSize.Y + 1];
	Screen = CF::ClearBuffer(Screen);
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

System::~System()
{
    delete[] Screen;
}

HANDLE System::GetHandle()
{
    return Handle;
}

HANDLE System::GetConsoleBufferHandle()
{
	return ConsoleHandle;
}

BT::Vector2<uint32_t> System::GetScreenSize()
{
	return ScreenSize;
}

BT::Vector2<int16_t> System::GetWindowSize() 
{
	return WindowSize;
}

BT::Vector2<uint32_t> System::GetWindowPos() 
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

wchar_t* System::GetScreenBuffer()
{
	return Screen;
}

void System::SetScreenBuffer(wchar_t* buffer)
{
	Screen = buffer;
}

BT::Vector2<uint32_t> System::GetConsolScreenSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    uint32_t columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return BT::Vector2<uint32_t>{ columns, rows };
}
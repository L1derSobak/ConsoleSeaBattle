#pragma once
#include "CoreTypes.h"
#include <Windows.h>
#include <conio.h>

class System
{
public:
	System();
	System(CT::Vector2<uint32_t> WinSize);
	~System();

	HANDLE GetHandle();
	HANDLE GetConsoleBufferHandle();
	CT::Vector2<uint32_t> GetScreenSize();
	CT::Vector2<int16_t> GetWindowSize();
	CT::Vector2<uint32_t> GetWindowPos();
	bool SetWindowPosition(uint32_t X, uint32_t Y);
	void SetWindowSize(int16_t Width, int16_t Height);

	CT::Vector2<uint32_t> GetOptimalWindowSize();
private:
	CT::Vector2<uint32_t> GetConsolScreenSize();

	//Стандартные типы Винды
	HWND hWindowConsole = GetConsoleWindow();
	HANDLE  Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  ScreenBufferSize; //{ 100, 100 };

	HANDLE ConsoleHandle = NULL;

	CT::Vector2<uint32_t>ScreenSize{ static_cast<uint32_t>(GetSystemMetrics(SM_CXSCREEN)),static_cast<uint32_t>(GetSystemMetrics(SM_CYSCREEN)) };

	uint32_t const MinWinSizeX = 680;
	uint32_t const MinWinSizeY = 480;

	CT::Vector2<int16_t> DefaultWindowSize = { 120,42 };//GetConsolScreenSize();
	CT::Vector2<uint32_t> DefaultPos{ (ScreenSize.X - MinWinSizeX) / 2 - 1 ,(ScreenSize.Y - MinWinSizeY) / 2 - 1 };
	CT::Vector2<uint32_t> WindowPosition = DefaultPos;
	CT::Vector2<int16_t> WindowSize = DefaultWindowSize;

	
};


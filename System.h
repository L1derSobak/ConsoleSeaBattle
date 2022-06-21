#pragma once
#include "BaseTypes.h"
#include "CoreFunctions.h"
#include <Windows.h>
#include <conio.h>

class System
{
public:
	System();
	~System();

	HANDLE GetHandle();
	HANDLE GetConsoleBufferHandle();
	BT::Vector2<uint32_t> GetScreenSize();
	BT::Vector2<int16_t> GetWindowSize();
	BT::Vector2<uint32_t> GetWindowPos();
	bool SetWindowPosition(uint32_t X, uint32_t Y);
	void SetWindowSize(int16_t Width, int16_t Height);
	
	wchar_t* GetScreenBuffer();
	void SetScreenBuffer(wchar_t* buffer);
private:
	BT::Vector2<uint32_t> GetConsolScreenSize();

	//Стандартные типы Винды
	HWND hWindowConsole = GetConsoleWindow();
	HANDLE  Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  ScreenBufferSize; //{ 100, 100 };

	HANDLE ConsoleHandle = NULL;

	BT::Vector2<uint32_t>ScreenSize{ static_cast<uint32_t>(GetSystemMetrics(SM_CXSCREEN)),static_cast<uint32_t>(GetSystemMetrics(SM_CYSCREEN)) };

	uint32_t const MinWinSizeX = 680;
	uint32_t const MinWinSizeY = 480;

	BT::Vector2<int16_t> DefaultWindowSize = { 120,60 };//GetConsolScreenSize();
	BT::Vector2<uint32_t> DefaultPos{ (ScreenSize.X - MinWinSizeX) / 2 - 1 ,(ScreenSize.Y - MinWinSizeY) / 2 - 1 };
	BT::Vector2<uint32_t> WindowPosition = DefaultPos;
	BT::Vector2<int16_t> WindowSize = DefaultWindowSize;

	uint32_t WindowBufferSize = 0;
	wchar_t* Screen = nullptr;
};


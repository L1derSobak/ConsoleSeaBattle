#pragma once
#include <iostream>
#include "System.h"

class Screen
{
public:
	Screen();
	Screen(CT::Vector2<uint32_t> ScrSize);
	~Screen();

	wchar_t* GetScreenBuffer() {return ScreenBuffer;}
	uint32_t GetScreenBufferSize() {return ScreenBufferSize;}
	System GetSystem() {return sys;}

	wchar_t GetScreenBufferCharacter(CT::Vector2<uint32_t> Position);

	void SetScreenBuffer(wchar_t* _ScreenBuffer);
	void AddString(const wchar_t* string, CT::Vector2<uint32_t>Position);
	void AddCharacter(const wchar_t character, CT::Vector2<uint32_t> Position);
	void AddArray(const wchar_t* array, CT::Vector2<uint32_t>Position);
	void Add2dArray(const wchar_t* array, CT::Vector2<uint32_t> Size, CT::Vector2<uint32_t>Position);

	void Draw();
	void ClearScreen();
	void FillScreen(wchar_t symbol);
private:
	wchar_t* DrawTable(wchar_t* buffer, const CT::Vector2<uint16_t>Start, const CT::Vector2<uint16_t>End, System sys);
	//wchar_t* DrawCircle(wchar_t* buffer, const CT::Vector2<uint16_t>CenterCoord, uint16_t Radius, System sys);
	void DrawBuffer(wchar_t* buffer, HANDLE ScreenHandle);

	uint32_t ScreenBufferSize = 0;
	wchar_t* ScreenBuffer = nullptr;

	System sys;
	HANDLE ScreenHandle = 0;
};


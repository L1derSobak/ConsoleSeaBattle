#pragma once
#include "System.h"

namespace CF
{
	wchar_t* DrawTable(wchar_t* buffer, const uint16_t& XS, const uint16_t& YS, const uint16_t& XE, const uint16_t& YE, System& sys);
	void DrawBuffer(wchar_t* buffer, HANDLE ScreenBuffer);
}
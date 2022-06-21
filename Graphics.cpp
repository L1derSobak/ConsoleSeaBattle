#include "Graphics.h"
#include <math.h>
#include <iostream>
#include "CoreFunctions.h"

wchar_t* CF::DrawTable(wchar_t* buffer, const uint16_t& XS, const uint16_t& YS, const uint16_t& XE, const uint16_t& YE, System& sys)
{
	for (uint16_t i = 0; i < sys.GetWindowSize().X; i++)
	{
		for (uint16_t j = 0; j < sys.GetWindowSize().Y; j++)
		{
			if ((i == XS && j>=YS && j<=YE) || (i ==XE && j>=YS && j<=YE) || (i>=XS && i <= XE && (j == YS || j == YE)))//|| i == XE || j == YS || j == YE)
				buffer[i + j * sys.GetWindowSize().X] = '+';
			//else
				//buffer[i + j * sys.GetWindowSize().X] = ' ';
			//screen[i + j * width] = pixel;
		}
	}
	buffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
	return buffer;
}

void CF::DrawBuffer(wchar_t* buffer, HANDLE ScreenBuffer)
{
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(ScreenBuffer, buffer, wcslen(buffer), { 0, 0 }, &dwBytesWritten);
}

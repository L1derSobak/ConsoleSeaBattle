#include "Screen.h"

Screen::Screen() 
{
	ScreenBufferSize = sys.GetWindowSize().X * sys.GetWindowSize().Y + 1;
	ScreenBuffer = new wchar_t[ScreenBufferSize];
	ScreenBuffer = CF::ClearBuffer(ScreenBuffer);
	ScreenHandle = sys.GetConsoleBufferHandle();
}

Screen::Screen(CT::Vector2<uint32_t> ScrSize)
{
	ScreenBufferSize = ScrSize.X * ScrSize.Y + 1;
	ScreenBuffer = new wchar_t[ScreenBufferSize];
	ScreenBuffer = CF::ClearBuffer(ScreenBuffer);
	
}

Screen::~Screen()
{
	ScreenBuffer = nullptr;
	//delete[] ScreenBuffer;
}

wchar_t Screen::GetScreenBufferCharacter(CT::Vector2<uint32_t> Position)
{
	return ScreenBuffer[Position.X + Position.Y * sys.GetWindowSize().X];
}

void Screen::SetScreenBuffer(wchar_t* _ScreenBuffer)
{
	ScreenBuffer = _ScreenBuffer;
}

void Screen::AddString(const wchar_t* string, CT::Vector2<uint16_t>Position)
{
	if (Position.X > sys.GetWindowSize().X || Position.Y > sys.GetWindowSize().Y) throw;

	uint16_t  sympos = 0;
	for (size_t i = Position.X; i < Position.X + wcslen(string); i++)
	{
		ScreenBuffer[i + Position.Y * sys.GetWindowSize().X] = string[sympos];
		sympos++;
	}
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
}

void Screen::AddCharacter(const wchar_t character, CT::Vector2<uint32_t> Position)
{
	if (Position.X > sys.GetWindowSize().X || Position.Y > sys.GetWindowSize().Y) throw;
	ScreenBuffer[Position.X + Position.Y * sys.GetWindowSize().X] = character;
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
}

void Screen::Draw()
{
	DWORD dwBytesWritten = 0;
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
	WriteConsoleOutputCharacter(ScreenHandle, ScreenBuffer, ScreenBufferSize, { 0,0 }, &dwBytesWritten);
	//WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
}

void Screen::ClearScreen()
{
	ScreenBuffer = CF::ClearBuffer(ScreenBuffer);
}

wchar_t* Screen::DrawTable(wchar_t* buffer, const CT::Vector2<uint16_t>Start, const CT::Vector2<uint16_t>End, System sys)
{
	for (uint16_t i = 0; i < sys.GetWindowSize().X; i++)
	{
		for (uint16_t j = 0; j < sys.GetWindowSize().Y; j++)
		{
			if ((i == Start.X && j >= Start.Y && j <= End.Y) || (i == End.X && j >= Start.X && j <= End.Y) || (i >= Start.X && i <= End.X && (j == Start.Y || j == End.Y)))//|| i == XE || j == YS || j == YE)
				buffer[i + j * sys.GetWindowSize().X] = '+';
			//else
				//buffer[i + j * sys.GetWindowSize().X] = ' ';
			//screen[i + j * width] = pixel;
		}
	}
	buffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
	return buffer;
}

wchar_t* Screen::DrawCircle(wchar_t* buffer, const CT::Vector2<uint16_t> CenterCoord, uint16_t Radius, System sys)
{
	const float aspect = sys.GetWindowSize().X / sys.GetWindowSize().Y;
	const float pixelAspect = 11.0f / 24.0f;
	for (uint16_t i = 0; i < sys.GetWindowSize().X; i++)
	{
		for (uint16_t j = 0; j < sys.GetWindowSize().Y; j++)
		{
			//float x = static_cast<float>((float)i / sys.GetWindowSize().X * 2.0f - 1.0f);// * aspect * pixelAspect;
			//float y = static_cast<float>((float)j / sys.GetWindowSize().Y * 2.0f - 1.0f);
			float x = (float)i / sys.GetWindowSize().X * 2.0f - 1.0f;
			float y = (float)j / sys.GetWindowSize().Y * 2.0f - 1.0f;
			x *= aspect * pixelAspect;
			//float r = (float)Radius / sys.GetWindowSize().X * 2.0f - 1.0f;
			//float x = i - CenterCoord.X;
			//float y = j - CenterCoord.Y;
			if (x * x + y * y < 0.5) buffer[i + j * sys.GetWindowSize().X] = '+';
			//buffer[i + j * sys.GetWindowSize().X] = '*';
			//else
				//buffer[i + j * sys.GetWindowSize().X] = ' ';
			//screen[i + j * width] = pixel;
		}
	}
	buffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
	return buffer;
}

void Screen::DrawBuffer(wchar_t* buffer, HANDLE ScreenHandle)
{
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(ScreenHandle, buffer, wcslen(buffer), { 0, 0 }, &dwBytesWritten);
}


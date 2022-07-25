#include "Screen.h"

Screen::Screen() 
{
	ScreenBufferSize = sys.GetWindowSize().X * sys.GetWindowSize().Y + 1;
	ScreenBuffer = new wchar_t[ScreenBufferSize];
	ClearScreen();
	//ScreenBuffer = CF::ClearBuffer(ScreenBuffer);
	ScreenHandle = sys.GetConsoleBufferHandle();
}

Screen::Screen(CT::Vector2<uint32_t> ScrSize)
{
	ScreenBufferSize = ScrSize.X * ScrSize.Y + 1;
	ScreenBuffer = new wchar_t[ScreenBufferSize];
	ClearScreen();
	//ScreenBuffer = CF::ClearBuffer(ScreenBuffer);
	
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

void Screen::AddString(const wchar_t* string, CT::Vector2<uint32_t>Position)
{
	if (Position.X > sys.GetWindowSize().X || Position.Y > sys.GetWindowSize().Y) return;

	uint16_t  sympos = 0;
	for (uint32_t i = Position.X; i < Position.X + wcslen(string); i++)
	{
		ScreenBuffer[i + Position.Y * sys.GetWindowSize().X] = string[sympos];
		sympos++;
	}
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
}

void Screen::AddString(const std::wstring string, CT::Vector2<uint32_t> Position)
{
	if (Position.X > sys.GetWindowSize().X || Position.Y > sys.GetWindowSize().Y) return;
	uint32_t i = Position.X;
	for (auto it : string)
	{
		ScreenBuffer[i + Position.Y * sys.GetWindowSize().X] = it;
		i++;
	}
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
}

void Screen::AddCharacter(const wchar_t character, CT::Vector2<uint32_t> Position)
{
	if (Position.X > sys.GetWindowSize().X || Position.Y > sys.GetWindowSize().Y) return;
	ScreenBuffer[Position.X + Position.Y * sys.GetWindowSize().X] = character;
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
}

void Screen::AddArray(const wchar_t* array, CT::Vector2<uint32_t> Position)
{
	uint16_t  sympos = 0;
	for (uint32_t i = Position.X; i < Position.X + wcslen(array); i++)
	{
		ScreenBuffer[i + Position.Y * sys.GetWindowSize().X] = array[sympos];
		sympos++;
	}
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
}

void Screen::Add2dArray(const wchar_t* array, CT::Vector2<uint32_t> Size, CT::Vector2<uint32_t> Position)
{
	uint32_t x = 0, y = 0;
	for (uint32_t i = Position.X; i < (Position.X + Size.X); i++)
	{
		for (uint32_t j = Position.Y; j < (Position.Y + Size.Y); j++)
		{
			ScreenBuffer[i + j * sys.GetWindowSize().X] = array[x + y * Size.X];
			y++;
		}
		x++;
		y = 0;
	}
}

void Screen::Draw()
{
	DWORD dwBytesWritten = 0;
	ScreenBuffer[sys.GetWindowSize().X * sys.GetWindowSize().Y] = '\0';
	WriteConsoleOutputCharacterW(ScreenHandle, ScreenBuffer, ScreenBufferSize, { 0,0 }, &dwBytesWritten);
	//WriteConsoleOutputCharacterW
	//WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
}

void Screen::ClearScreen()
{
	uint32_t size = ScreenBufferSize;
	for (uint32_t i = 0; i < size; i++)
		ScreenBuffer[i] = ' ';
	ScreenBuffer[size] = '\0';
}

void Screen::FillScreen(wchar_t symbol)
{
	uint32_t size = ScreenBufferSize;
	for (uint32_t i = 0; i < size; i++)
		ScreenBuffer[i] = symbol;
	ScreenBuffer[size] = '\0';
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

/*wchar_t* Screen::DrawCircle(wchar_t* buffer, const CT::Vector2<uint16_t> CenterCoord, uint16_t Radius, System sys)
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
}*/

void Screen::DrawBuffer(wchar_t* buffer, HANDLE ScreenHandle)
{
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(ScreenHandle, buffer, wcslen(buffer), { 0, 0 }, &dwBytesWritten);
}


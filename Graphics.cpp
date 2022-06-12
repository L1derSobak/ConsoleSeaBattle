#include "Graphics.h"
#include <math.h>
#include <iostream>
#include "CoreFunctions.h"

void CF::DrawTable(unsigned const int& X, unsigned const int& Y)
{
	unsigned int LastSymPosX = static_cast<unsigned int>(floor(((X - 1) / 8) - 5));
	unsigned int LastSymPosY = static_cast<unsigned int>(floor(((Y - 1) / 16) - 3));
	//Draw border
	CF::gotoxy(0, 0);
	std::cout << "+";
	for (size_t i = 1; i < LastSymPosX; i++)
		std::cout << "-";
	std::cout << "+";
	for (size_t i = 1; i < LastSymPosY; i++)
	{
		CF::gotoxy(0, i);
		std::cout << "|";
		CF::gotoxy(LastSymPosX, i);
		std::cout << "|";
	}
	CF::gotoxy(0, LastSymPosY);
	std::cout << "+";
	for (size_t i = 1; i < LastSymPosX; i++)
		std::cout << "-";
	std::cout << "+";
}

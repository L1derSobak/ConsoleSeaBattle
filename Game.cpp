#include "Game.h"

Game::Game()
{
	InitGameFields();
	AvalibleShips = PlayerField.GetAvaliableShips();
	DrawFields();
	Input = new wchar_t[4];
	//memset(Input, L' ', sizeof(Input));
	for (auto i = 0U; i < 4U; i++)
		Input[i] = L' ';
	Input[3] = L'\0';
	//wchar_t Sym = 1040;//187;//328;
	//wchar_t str[] = L"Всем привет!";
	//scrn.AddString(str, { 0,0 });
	//scrn.AddCharacter(Sym, { 0,0 });
	//1040 - русские символы
}

Game::~Game()
{

}

void Game::InitGameFields()
{

}

void Game::DrawFields()
{
	scrn.Add2dArray(PlayerField.GetFieldArray(), PlayerField.GetFieldSize(), { 5,1 });
	scrn.Add2dArray(AIField.GetFieldArray(), AIField.GetFieldSize(), { 70,1 });
	scrn.Draw();
	wchar_t arr[] = { L"    " };
	WriteInput(arr);
}

bool Game::HitCell(std::wstring CellName)
{
	//return PlayerField.Hit(GetPosFromCell(CellName));
	//std::wstring _TCellName = std::nouppercase(CellName);
	//CellName[0] = static_cast<wchar_t>(toupper(CellName[0]));
	if (!isCellExist(CellName)) return false;
	//if (CellName.size() > 3 || CellName.size()<2) return false;
	return PlayerField.Hit(CellName);
}

bool Game::SetShip(Ship ship, std::wstring cellName)
{
	if (!isCellExist(cellName) || AvalibleShips==0) return false;
	bool IsCanSetShip = true;
	wchar_t Sym = cellName[0];
	wchar_t tSym = Sym;
	int32_t Pos = cellName.size() == 3 ? 10 : cellName[1] - 48;
	int32_t tPos = Pos;
	//Можно ли разместить этот корабль на поле
	switch (ship.GetDirection())
	{
	case CT::Direction::DOWN:
		for (; Pos < tPos + ship.GetLength(); Pos++)
		{
			std::wstring name = Sym + std::to_wstring(Pos);
			if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
		}
		break;
	case CT::Direction::UP:
		for (; Pos > tPos - ship.GetLength(); Pos--)
		{
			std::wstring name = Sym + std::to_wstring(Pos);
			if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
		}
		break;
	case CT::Direction::LEFT:
		for (;Sym > tSym - ship.GetLength() ; Sym--)
		{
			std::wstring name = Sym + std::to_wstring(Pos);
			if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
		}
		break;
	case CT::Direction::RIGHT:
		for (; Sym < tSym + ship.GetLength(); Sym++)
		{
			std::wstring name = Sym + std::to_wstring(Pos);
			if (!(isCellExist(name) && PlayerField.GetCellStatus(name) == CT::CellStatus::Clear)) IsCanSetShip = false;
		}
		break;
	default:
		break;
	}
	if (!IsCanSetShip || !PlayerField.AttachShip(ship)) return false;
	//Размечаем для корабля клетки-запреты 
	Sym = cellName[0];// -1;
	tSym = Sym;
	Pos = cellName.size() == 3 ? 10 : cellName[1] - 48;//49;
	tPos = Pos;
	switch (ship.GetDirection())
	{
		/*
		for (; Sym < cellName[0] + 2; Sym++)
		{
			for (; Pos < tPos + ship.GetLength() + 1; Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (isCellExist(name)) PlayerField.EditCellStatus(name, CT::CellStatus::NearShip);
			}
		}
		*/
	case CT::Direction::UP:
		Sym--;
		Pos++;
		tPos = Pos;
		for (; Sym < cellName[0] + 2; Sym++)
		{
			Pos = tPos;
			for (; Pos > tPos - ship.GetLength() - 1; Pos--)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (isCellExist(name)) PlayerField.EditCellStatus(name, CT::CellStatus::NearShip);
			}
		}
		break;
	case CT::Direction::DOWN:
		Sym--;
		Pos--;
		tPos = Pos;
		for (; Sym < cellName[0] + 2; Sym++)
		{
			Pos = tPos;
			for (; Pos < tPos + ship.GetLength() + 1; Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (isCellExist(name)) PlayerField.EditCellStatus(name, CT::CellStatus::NearShip);
			}
		}
		break;
	case CT::Direction::LEFT:
		Sym++;
		Pos--;//Sym = cellName[0] + 1;
		tPos = Pos;
		for (; Sym > cellName[0]-ship.GetLength() - 1; Sym--)
		{
			Pos = tPos;
			for (; Pos < tPos + 2; Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (isCellExist(name)) PlayerField.EditCellStatus(name, CT::CellStatus::NearShip);
			}
		}
		break;
	case CT::Direction::RIGHT:
		Sym--;
		Pos--;
		tPos = Pos;
		for (; Sym < cellName[0] + ship.GetLength() + 1; Sym++)
		{
			Pos = tPos;
			for (; Pos < tPos + 2; Pos++)
			{
				std::wstring name = Sym + std::to_wstring(Pos);
				if (isCellExist(name)) PlayerField.EditCellStatus(name, CT::CellStatus::NearShip);
			}
		}
		break;
	default:
		break;
	}
	//Цифры
	//wchar_t num = 49;//1
	//Буквы
	//wchar_t sym = 65; // A (end)
	//wchar_t dfs = L'9';
	Sym = cellName[0];
	Pos = cellName.size() == 3 ? 10 : cellName[1] - 48;
	//wchar_t Num = cellName.size() == 3 ? 59 : cellName[1];
	switch (ship.GetDirection())
	{
	case CT::Direction::UP:
		if (Pos - ship.GetLength() < 0)return false;
		break;
	case CT::Direction::DOWN:
		if (Pos + ship.GetLength() >11)return false;
		break;
	case CT::Direction::LEFT:
		if (Sym - ship.GetLength() < 1039)return false;
		break;
	case CT::Direction::RIGHT:
		if (Sym + ship.GetLength() > 1050)return false;
		break;
	default:
		break;
	}
	bool doneCode = PlayerField.SetShip(ship, cellName);
	AvalibleShips = PlayerField.GetAvaliableShips();
	WriteavaliableShips(AvalibleShips);
	return doneCode;
	//return false;
}

const std::wstring Game::GetInput()
{
	std::wstring CellName = L" ";
	//memset(Input, L'0', 4);
	//Input[3] = L'\0';
	bool isEnd = false, enable = true;
	while (1)
	{
		CT::RusKeyCode get = inputManager.GetLastInputR();
		if (get == CT::RusKeyCode::Enter || get == CT::RusKeyCode::Esc) break;
		for (auto it : CT::AvaliableInput)
		{
			if (get == it)
			{
				if (inputManager.GetSymByInput(get) == L'\b')
				{
					/*
					if (pos == 2)
					{
						Input[pos] = ' ';
						pos--;
					}
					else
					{
						Input[pos] = ' ';
						pos = (pos - 1) < 0 ? 0 : pos - 1;
					}
					*/
					isEnd = (pos == 2) && enable ? true : false;
					if (isEnd)
					{
						Input[pos] = L' ';
						enable = false;
					}
					else 
					{
						pos = (pos - 1) < 0 ? 0 : pos - 1;
						Input[pos] = L' ';
						enable = true;
					}
					//if(pos==2)Input[pos] = ' ';
					//pos = (pos - 1) < 0 ? 0 : pos - 1;
					//Input[pos] = ' ';
				}
				else
				{
					Input[pos] = inputManager.GetSymByInput(get);
					pos = pos + 1 > 2 ? 2 : pos + 1;
				}
				Input[3] = L'\0';
				WriteInput(Input);
			}
		}
	}
	CellName = Input;
	std::size_t found = CellName.find(L' ');
	if(found != std::string::npos)
		CellName.erase(found);
	return CellName;
}

CT::Vector2<uint32_t> Game::GetPosFromCell(std::wstring Cell)
{
	return PlayerField.GetPosFromCell(Cell);
}

void Game::WriteavaliableShips(uint32_t _AvaliableShips)
{
	std::wstring shps = L"Можно установить кораблей: " + std::to_wstring(_AvaliableShips) + L"  ";
	scrn.AddString(shps, { 0,0 });
}

void Game::WriteInput(wchar_t* input)
{
	std::wstring Literal = L"Введите название клетки: ";// +std::to_wstring(input);
	std::wstring voidInput = L"    ";
	scrn.AddString(Literal, { 0,1 });
	scrn.AddString(voidInput, { 24,1 });
	scrn.AddArray(input, { 24,1 });
	scrn.Draw();
	Sleep(100);
}

const bool Game::isCellExist(std::wstring cellName)
{
	if (cellName.size() < 2 || cellName.size() > 3) return false;
	wchar_t Sym = cellName[0];
	uint32_t Num = cellName.size() == 3 ? 10 : cellName[1]-48;
	if ((Sym >= 1040 && Sym <= 1049) && (Num >= 1 && Num <= 10)) return true;
	return false;
}

const bool Game::EditCellStatus(std::wstring cellName, CT::CellStatus cellStatus)
{
	
	return false;
}

#pragma once
#include <iostream>
#include "CoreTypes.h"
#include <Windows.h>

class InputManager
{
public:
	InputManager() {Input = new wchar_t[4];}
	~InputManager() {}
	const CT::KeyCode GetLastInputE();
	const CT::RusKeyCode GetLastInputR();
	const uint8_t* GetInputStatus();
	const wchar_t GetSymByInput(const CT::RusKeyCode rkc);
	const wchar_t* GetInputArray() { return Input; }
private:
	void UpdateArray();

	wchar_t* Input = nullptr;
	int temp;
	uint8_t arr[256];
	uint32_t pos = 0;
};


#include "InputManager.h"

const CT::KeyCode InputManager::GetLastInputE()
{
    memset(arr, 0, sizeof(256));
    GetKeyState(0);
    if (GetKeyboardState(arr))
    {
        for (int i = 0; i < 256; i++)
        {
            temp = (int)arr[i];
            temp >>= 7;
            if (temp == 1)
                return static_cast<CT::KeyCode>(i);
        }
    }
    CT::KeyCode::None;
}

const CT::RusKeyCode InputManager::GetLastInputR()
{
    memset(arr, 0, sizeof(256));
    GetKeyState(0);
    if (GetKeyboardState(arr))
    {
        for (int i = 0; i < 256; i++)
        {
            temp = (int)arr[i];
            temp >>= 7;
            if (temp == 1)
                return static_cast<CT::RusKeyCode>(i);
        }
    }
    CT::RusKeyCode::None;
}

const uint8_t* InputManager::GetInputStatus()
{
    memset(arr, 0, sizeof(256));
    GetKeyState(0);
    if (GetKeyboardState(arr))
    {
        for (int i = 0; i < 256; i++)
        {
            temp = (int)arr[i];
            temp >>= 7;
        }
        return arr;
    }
    return nullptr;

}

const wchar_t InputManager::GetSymByInput(const CT::RusKeyCode rkc)
{
    switch (rkc)
    {
    case CT::RusKeyCode::�:
        return L'A';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::�:
        return L'�';
        break;
    case CT::RusKeyCode::_0:
        return L'0';
        break;
    case CT::RusKeyCode::_1:
        return L'1';
        break;
    case CT::RusKeyCode::_2:
        return L'2';
        break;
    case CT::RusKeyCode::_3:
        return L'3';
        break;
    case CT::RusKeyCode::_4:
        return L'4';
        break;
    case CT::RusKeyCode::_5:
        return L'5';
        break;
    case CT::RusKeyCode::_6:
        return L'6';
        break;
    case CT::RusKeyCode::_7:
        return L'7';
        break;
    case CT::RusKeyCode::_8:
        return L'8';
        break;
    case CT::RusKeyCode::_9:
        return L'9';
        break;
    case CT::RusKeyCode::UpArrow:
        return L'^';
        break;
    case CT::RusKeyCode::DownArrow:
        return L'v';
        break;
    case CT::RusKeyCode::LeftArrow:
        return L'<';
        break;
    case CT::RusKeyCode::RightArrow:
        return L'>';
        break;
    case CT::RusKeyCode::BackSpace:
        //std::cout << "\b ";
        return L'\b';
        break;
    default:
        return L' ';
        break;
    }
}
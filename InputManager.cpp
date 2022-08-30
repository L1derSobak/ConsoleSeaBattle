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
    case CT::RusKeyCode::À:
        return L'A';
        break;
    case CT::RusKeyCode::Á:
        return L'Á';
        break;
    case CT::RusKeyCode::Â:
        return L'Â';
        break;
    case CT::RusKeyCode::Ã:
        return L'Ã';
        break;
    case CT::RusKeyCode::Ä:
        return L'Ä';
        break;
    case CT::RusKeyCode::Å:
        return L'Å';
        break;
    case CT::RusKeyCode::¨:
        return L'¨';
        break;
    case CT::RusKeyCode::Æ:
        return L'Æ';
        break;
    case CT::RusKeyCode::Ç:
        return L'Ç';
        break;
    case CT::RusKeyCode::È:
        return L'È';
        break;
    case CT::RusKeyCode::É:
        return L'É';
        break;
    case CT::RusKeyCode::Ê:
        return L'Ê';
        break;
    case CT::RusKeyCode::Ë:
        return L'Ë';
        break;
    case CT::RusKeyCode::Ì:
        return L'Ì';
        break;
    case CT::RusKeyCode::Í:
        return L'Í';
        break;
    case CT::RusKeyCode::Î:
        return L'Î';
        break;
    case CT::RusKeyCode::Ï:
        return L'Ï';
        break;
    case CT::RusKeyCode::Ð:
        return L'Ð';
        break;
    case CT::RusKeyCode::Ñ:
        return L'Ñ';
        break;
    case CT::RusKeyCode::Ò:
        return L'Ò';
        break;
    case CT::RusKeyCode::Ó:
        return L'Ó';
        break;
    case CT::RusKeyCode::Ô:
        return L'Ô';
        break;
    case CT::RusKeyCode::Õ:
        return L'Õ';
        break;
    case CT::RusKeyCode::Ö:
        return L'Ö';
        break;
    case CT::RusKeyCode::×:
        return L'×';
        break;
    case CT::RusKeyCode::Ø:
        return L'Ø';
        break;
    case CT::RusKeyCode::Ù:
        return L'Ù';
        break;
    case CT::RusKeyCode::Ú:
        return L'Ú';
        break;
    case CT::RusKeyCode::Û:
        return L'Û';
        break;
    case CT::RusKeyCode::Ü:
        return L'Ü';
        break;
    case CT::RusKeyCode::Ý:
        return L'Ý';
        break;
    case CT::RusKeyCode::Þ:
        return L'Þ';
        break;
    case CT::RusKeyCode::ß:
        return L'ß';
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
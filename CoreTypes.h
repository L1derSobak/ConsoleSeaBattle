#pragma once
#include <string>
#include <list>

namespace CT {

	template<typename Type>
	class Vector2
	{
	public:
		Type X;
		Type Y;

		Vector2() : X(0), Y(0) {}
		Vector2(Type a) : X(a), Y(a) {}
		Vector2(Type a, Type b) : X(a), Y(b) {}

		friend bool operator==(Vector2<Type> const& Vec1, Vector2<Type> const& Vec2) noexcept
		{
			return (Vec1.X == Vec2.X && Vec1.Y == Vec2.Y);
		}

		friend bool operator!=(Vector2<Type> const& Vec1, Vector2<Type> const& Vec2) noexcept
		{
			return (Vec1.X != Vec2.X || Vec1.Y != Vec2.Y);
		}
	};

	enum class KeyCode : uint8_t {
		None = 0,
		MouseLeft = 1,
		MouseRight = 2,
		MouseMiddle = 4,
		BackSpace = 8,
		Tab = 9,
		Enter = 13,
		LShift = 16,
		Ctrl = 17,
		Alt = 18,
		Esc = 27,
		Space = 32,
		LeftArrow = 37,
		UpArrow = 38,
		RightArrow = 39,
		DownArrow = 40,
		Del = 46,

		_0 = 48,
		_1 = 49,
		_2 = 50,
		_3 = 51,
		_4 = 52,
		_5 = 53,
		_6 = 54,
		_7 = 55,
		_8 = 56,
		_9 = 57,

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		S = 83,
		R = 82,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		F1 = 112,
		F2 = 113,
		F3 = 114,
		F4 = 115,
		F5 = 116,
		F6 = 117,
		F7 = 118,
		F8 = 119,
		F9 = 120,
		F10 = 121,
		F11 = 122,
		F12 = 123,
		Plus = 187, Minus = 189,
		Lover = 188,
		Dot = 190,
		Tilde = 192,
	};
	enum class RusKeyCode : uint8_t
	{
		None = 0,
		MouseLeft = 1,
		MouseRight = 2,
		MouseMiddle = 4,
		BackSpace = 8,
		Tab = 9,
		Enter = 13,
		LShift = 16,
		Ctrl = 17,
		Alt = 18,
		Esc = 27,
		Space = 32,
		LeftArrow = 37,
		UpArrow = 38,
		RightArrow = 39,
		DownArrow = 40,
		Del = 46,

		_0 = 48,
		_1 = 49,
		_2 = 50,
		_3 = 51,
		_4 = 52,
		_5 = 53,
		_6 = 54,
		_7 = 55,
		_8 = 56,
		_9 = 57,

		À = 70,
		Á = 188,
		Â = 68,
		Ã = 85,
		Ä = 76,
		Å = 84,
		¨ = 192,
		Æ = 186,
		Ç = 80,
		È = 66,
		É = 81,
		Ê = 82,
		Ë = 75,
		Ì = 86,
		Í = 89,
		Î = 74,
		Ï = 71,
		Ð = 72,
		Ñ = 67,
		Ò = 78,
		Ó = 69,
		Ô = 65,
		Õ = 219,
		Ö = 87,
		× = 88,
		Ø = 73,
		Ù = 79,
		Ú = 221,
		Û = 83,
		Ü = 77,
		Ý = 222,
		Þ = 190,
		ß = 90,

		F1 = 112,
		F2 = 113,
		F3 = 114,
		F4 = 115,
		F5 = 116,
		F6 = 117,
		F7 = 118,
		F8 = 119,
		F9 = 120,
		F10 = 121,
		F11 = 122,
		F12 = 123,
		Plus = 187, Minus = 189,
		Dot = 190,
		Tilde = 192,
	};
	const RusKeyCode AvaliableInput[] =
	{
		RusKeyCode::À,
		RusKeyCode::Á,
		RusKeyCode::Â,
		RusKeyCode::Ã,
		RusKeyCode::Ä,
		RusKeyCode::Å,
		RusKeyCode::Æ,
		RusKeyCode::Ç,
		RusKeyCode::È,
		RusKeyCode::É,
		RusKeyCode::_0,
		RusKeyCode::_1,
		RusKeyCode::_2,
		RusKeyCode::_3,
		RusKeyCode::_4,
		RusKeyCode::_5,
		RusKeyCode::_6,
		RusKeyCode::_7,
		RusKeyCode::_8,
		RusKeyCode::_9,
		RusKeyCode::Esc,
		RusKeyCode::Enter,
		RusKeyCode::BackSpace
	};

	enum class Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE
	};

	enum class Status
	{
		Alive,
		Wrecked,
		Destroyed,
		None
	};

	enum class Owner
	{
		Player,
		AI,
		None
	};

	enum class CellStatus
	{
		Clear,
		NearShip,
		Hited,
		None
	};

	enum class ShipPart
	{
		Edge,
		Body,
		None
	};
	/*
	Class Cell
	*/
	class Cell
	{
	public:
		Cell() : size(3), arrayPosition(0), windowPosition({ 0,0 }), cellStatus(CellStatus::Clear) {}
		Cell(uint32_t Size, uint32_t ArrayPosition, CT::Vector2<uint32_t> WindowPosition, std::wstring CellName) : size(Size), arrayPosition(ArrayPosition), windowPosition(WindowPosition), cellStatus(CellStatus::Clear), cellName(CellName){}

		void ResetData(uint32_t Size, uint32_t ArrayPosition, CT::Vector2<uint32_t> WindowPosition, std::wstring CellName)
		{
			size = Size;
			arrayPosition = ArrayPosition;
			windowPosition = WindowPosition;
			cellStatus = CellStatus::Clear;
			cellName = CellName;
		}

		const uint32_t GetCellSize() { return size; }
		const uint32_t GetArrayPosition() { return arrayPosition; }
		const CT::Vector2<uint32_t> GetWindowPosition() { return windowPosition; }
		const CT::CellStatus GetCellStatus() { return cellStatus; }
		const std::wstring GetCellName() { return cellName; }

		const bool SetCellStatus(CellStatus _cellStatus);
	private:
		std::wstring cellName;
		uint32_t size, arrayPosition;
		CT::Vector2<uint32_t> windowPosition;
		CT::CellStatus cellStatus;
	};


	struct MenuPoint
	{
		std::string Name;
		unsigned short Position;
	};

	class MenuParams
	{
	public:
		std::string MenuName;
		std::list<MenuPoint> Params;
		unsigned short TextSize;
		unsigned short Padding;
		unsigned short Positions;
		CT::Vector2<int16_t> WindowSize;
		CT::Vector2<uint32_t> WindowPos;
		bool IsNumerated;
	};


	namespace Input {
		enum Mouseclick
		{
			RightClick,
			LeftClick,
			MiddleClick
		};

		enum KeyboardClick
		{
			Esc = 27,
			F1 = 59,
			F2 = 60,
			F3 = 61,
			F4 = 62,
			F5 = 63,
			F6 = 64,
			F7 = 65,
			F8 = 66,
			F9 = 67,
			F10 = 68,
			F11 = 84,
			F12 = 85,
			Tilda = 96,
			d1 = 49,
			d2 = 50,
			d3 = 51,
			d4 = 52,
			d5 = 53,
			d6 = 54,
			d7 = 55,
			d8 = 56,
			d9 = 57,
			d0 = 48,
			MMinus = 45,
			MPlus = 61,
			BackSpace = 8,
			Tab = 9,
			Q = 113,
			W = 119,
			E = 101,
			R = 114,
			T = 116,
			Y = 121,
			U = 117,
			I = 105,
			O = 111,
			P = 112,
			COBracket = 91,
			CCBracket = 93,
			BSlash = 92,
			CapsLock,
			A = 97,
			S = 115,
			D = 100,
			F = 102,
			G = 103,
			H = 104,
			J = 106,
			K = 107,
			L = 108,
			TwoDots = 59,
			TwoParagraphs = 39,
			Enter = 13,
			LShift,
			Z = 122,
			X = 120,
			C = 99,
			V = 118,
			B = 98,
			N = 110,
			M = 109,
			Low = 44,
			Bigger = 46,
			Dot = 47,
			RShift,
			LCtrl,
			LWin,
			LAlt,
			Space = 32,
			RAlt,
			RWin,
			RCtrl,
			ArrowUp = 72,
			ArrowDown = 80,
			ArrowLeft = 75,
			ArrowRight = 77,
			Insert = 82,
			Delete = 83,
			PageUp = 73,
			PageDown = 81,
			Home = 71,
			End = 79,
			m0 = 48,
			m1 = 49,
			m2 = 50,
			m3 = 51,
			m4 = 52,
			m5 = 53,
			m6 = 54,
			m7 = 55,
			m8 = 56,
			m9 = 57,
			mSlash = 47,
			mStar = 42,
			mMinus = 45,
			mPlus = 43,
			mEnter = 13,
			mDot = 46
		};
	}
}


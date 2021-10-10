// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

namespace Heirloom
{
	using KeyCode = enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

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
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define HL_KEY_SPACE           ::Heirloom::Key::Space
#define HL_KEY_APOSTROPHE      ::Heirloom::Key::Apostrophe    /* ' */
#define HL_KEY_COMMA           ::Heirloom::Key::Comma         /* , */
#define HL_KEY_MINUS           ::Heirloom::Key::Minus         /* - */
#define HL_KEY_PERIOD          ::Heirloom::Key::Period        /* . */
#define HL_KEY_SLASH           ::Heirloom::Key::Slash         /* / */
#define HL_KEY_0               ::Heirloom::Key::D0
#define HL_KEY_1               ::Heirloom::Key::D1
#define HL_KEY_2               ::Heirloom::Key::D2
#define HL_KEY_3               ::Heirloom::Key::D3
#define HL_KEY_4               ::Heirloom::Key::D4
#define HL_KEY_5               ::Heirloom::Key::D5
#define HL_KEY_6               ::Heirloom::Key::D6
#define HL_KEY_7               ::Heirloom::Key::D7
#define HL_KEY_8               ::Heirloom::Key::D8
#define HL_KEY_9               ::Heirloom::Key::D9
#define HL_KEY_SEMICOLON       ::Heirloom::Key::Semicolon     /* ; */
#define HL_KEY_EQUAL           ::Heirloom::Key::Equal         /* = */
#define HL_KEY_A               ::Heirloom::Key::A
#define HL_KEY_B               ::Heirloom::Key::B
#define HL_KEY_C               ::Heirloom::Key::C
#define HL_KEY_D               ::Heirloom::Key::D
#define HL_KEY_E               ::Heirloom::Key::E
#define HL_KEY_F               ::Heirloom::Key::F
#define HL_KEY_G               ::Heirloom::Key::G
#define HL_KEY_H               ::Heirloom::Key::H
#define HL_KEY_I               ::Heirloom::Key::I
#define HL_KEY_J               ::Heirloom::Key::J
#define HL_KEY_K               ::Heirloom::Key::K
#define HL_KEY_L               ::Heirloom::Key::L
#define HL_KEY_M               ::Heirloom::Key::M
#define HL_KEY_N               ::Heirloom::Key::N
#define HL_KEY_O               ::Heirloom::Key::O
#define HL_KEY_P               ::Heirloom::Key::P
#define HL_KEY_Q               ::Heirloom::Key::Q
#define HL_KEY_R               ::Heirloom::Key::R
#define HL_KEY_S               ::Heirloom::Key::S
#define HL_KEY_T               ::Heirloom::Key::T
#define HL_KEY_U               ::Heirloom::Key::U
#define HL_KEY_V               ::Heirloom::Key::V
#define HL_KEY_W               ::Heirloom::Key::W
#define HL_KEY_X               ::Heirloom::Key::X
#define HL_KEY_Y               ::Heirloom::Key::Y
#define HL_KEY_Z               ::Heirloom::Key::Z
#define HL_KEY_LEFT_BRACKET    ::Heirloom::Key::LeftBracket   /* [ */
#define HL_KEY_BACKSLASH       ::Heirloom::Key::Backslash     /* \ */
#define HL_KEY_RIGHT_BRACKET   ::Heirloom::Key::RightBracket  /* ] */
#define HL_KEY_GRAVE_ACCENT    ::Heirloom::Key::GraveAccent   /* ` */
#define HL_KEY_WORLD_1         ::Heirloom::Key::World1        /* non-US #1 */
#define HL_KEY_WORLD_2         ::Heirloom::Key::World2        /* non-US #2 */

/* Function keys */
#define HL_KEY_ESCAPE          ::Heirloom::Key::Escape
#define HL_KEY_ENTER           ::Heirloom::Key::Enter
#define HL_KEY_TAB             ::Heirloom::Key::Tab
#define HL_KEY_BACKSPACE       ::Heirloom::Key::Backspace
#define HL_KEY_INSERT          ::Heirloom::Key::Insert
#define HL_KEY_DELETE          ::Heirloom::Key::Delete
#define HL_KEY_RIGHT           ::Heirloom::Key::Right
#define HL_KEY_LEFT            ::Heirloom::Key::Left
#define HL_KEY_DOWN            ::Heirloom::Key::Down
#define HL_KEY_UP              ::Heirloom::Key::Up
#define HL_KEY_PAGE_UP         ::Heirloom::Key::PageUp
#define HL_KEY_PAGE_DOWN       ::Heirloom::Key::PageDown
#define HL_KEY_HOME            ::Heirloom::Key::Home
#define HL_KEY_END             ::Heirloom::Key::End
#define HL_KEY_CAPS_LOCK       ::Heirloom::Key::CapsLock
#define HL_KEY_SCROLL_LOCK     ::Heirloom::Key::ScrollLock
#define HL_KEY_NUM_LOCK        ::Heirloom::Key::NumLock
#define HL_KEY_PRINT_SCREEN    ::Heirloom::Key::PrintScreen
#define HL_KEY_PAUSE           ::Heirloom::Key::Pause
#define HL_KEY_F1              ::Heirloom::Key::F1
#define HL_KEY_F2              ::Heirloom::Key::F2
#define HL_KEY_F3              ::Heirloom::Key::F3
#define HL_KEY_F4              ::Heirloom::Key::F4
#define HL_KEY_F5              ::Heirloom::Key::F5
#define HL_KEY_F6              ::Heirloom::Key::F6
#define HL_KEY_F7              ::Heirloom::Key::F7
#define HL_KEY_F8              ::Heirloom::Key::F8
#define HL_KEY_F9              ::Heirloom::Key::F9
#define HL_KEY_F10             ::Heirloom::Key::F10
#define HL_KEY_F11             ::Heirloom::Key::F11
#define HL_KEY_F12             ::Heirloom::Key::F12
#define HL_KEY_F13             ::Heirloom::Key::F13
#define HL_KEY_F14             ::Heirloom::Key::F14
#define HL_KEY_F15             ::Heirloom::Key::F15
#define HL_KEY_F16             ::Heirloom::Key::F16
#define HL_KEY_F17             ::Heirloom::Key::F17
#define HL_KEY_F18             ::Heirloom::Key::F18
#define HL_KEY_F19             ::Heirloom::Key::F19
#define HL_KEY_F20             ::Heirloom::Key::F20
#define HL_KEY_F21             ::Heirloom::Key::F21
#define HL_KEY_F22             ::Heirloom::Key::F22
#define HL_KEY_F23             ::Heirloom::Key::F23
#define HL_KEY_F24             ::Heirloom::Key::F24
#define HL_KEY_F25             ::Heirloom::Key::F25

/* Keypad */
#define HL_KEY_KP_0            ::Heirloom::Key::KP0
#define HL_KEY_KP_1            ::Heirloom::Key::KP1
#define HL_KEY_KP_2            ::Heirloom::Key::KP2
#define HL_KEY_KP_3            ::Heirloom::Key::KP3
#define HL_KEY_KP_4            ::Heirloom::Key::KP4
#define HL_KEY_KP_5            ::Heirloom::Key::KP5
#define HL_KEY_KP_6            ::Heirloom::Key::KP6
#define HL_KEY_KP_7            ::Heirloom::Key::KP7
#define HL_KEY_KP_8            ::Heirloom::Key::KP8
#define HL_KEY_KP_9            ::Heirloom::Key::KP9
#define HL_KEY_KP_DECIMAL      ::Heirloom::Key::KPDecimal
#define HL_KEY_KP_DIVIDE       ::Heirloom::Key::KPDivide
#define HL_KEY_KP_MULTIPLY     ::Heirloom::Key::KPMultiply
#define HL_KEY_KP_SUBTRACT     ::Heirloom::Key::KPSubtract
#define HL_KEY_KP_ADD          ::Heirloom::Key::KPAdd
#define HL_KEY_KP_ENTER        ::Heirloom::Key::KPEnter
#define HL_KEY_KP_EQUAL        ::Heirloom::Key::KPEqual

#define HL_KEY_LEFT_SHIFT      ::Heirloom::Key::LeftShift
#define HL_KEY_LEFT_CONTROL    ::Heirloom::Key::LeftControl
#define HL_KEY_LEFT_ALT        ::Heirloom::Key::LeftAlt
#define HL_KEY_LEFT_SUPER      ::Heirloom::Key::LeftSuper
#define HL_KEY_RIGHT_SHIFT     ::Heirloom::Key::RightShift
#define HL_KEY_RIGHT_CONTROL   ::Heirloom::Key::RightControl
#define HL_KEY_RIGHT_ALT       ::Heirloom::Key::RightAlt
#define HL_KEY_RIGHT_SUPER     ::Heirloom::Key::RightSuper
#define HL_KEY_MENU            ::Heirloom::Key::Menu
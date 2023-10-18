#ifndef DXNA_KEYS_HPP
#define DXNA_KEYS_HPP

#include "../includes.hpp"

namespace dxna::input {
	//Representa os estados das chaves do teclado.
	enum class KeyState {
		Up,
		Down
	};

	//Representa as chaves do teclado.
	enum class Keys {
		None = 0,
		Back = VK_BACK,
		Tab = VK_TAB,
		Enter = VK_RETURN, // 0x0000000D
		Pause = VK_PAUSE, // 0x00000013
		CapsLock = VK_CAPITAL, // 0x00000014
		Kana = VK_KANA, // 0x00000015
		Kanji = VK_KANJI, // 0x00000019
		Escape = VK_ESCAPE, // 0x0000001B
		ImeConvert = VK_CONVERT, // 0x0000001C
		ImeNoConvert = VK_NONCONVERT, // 0x0000001D
		Space = VK_SPACE, // 0x00000020
		PageUp = VK_PRIOR, // 0x00000021
		PageDown = VK_NEXT, // 0x00000022
		End = VK_END, // 0x00000023
		Home = VK_HOME, // 0x00000024
		Left = VK_LEFT, // 0x00000025
		Up = VK_UP, // 0x00000026
		Right = VK_RIGHT, // 0x00000027
		Down = VK_DOWN, // 0x00000028
		Select = VK_SELECT, // 0x00000029
		Print = VK_PRINT, // 0x0000002A
		Execute = VK_EXECUTE, // 0x0000002B
		PrintScreen = VK_SNAPSHOT, // 0x0000002C
		Insert = VK_INSERT, // 0x0000002D
		Delete = VK_DELETE, // 0x0000002E
		Help = VK_HELP, // 0x0000002F
		D0 = 48, // 0x00000030
		D1 = 49, // 0x00000031
		D2 = 50, // 0x00000032
		D3 = 51, // 0x00000033
		D4 = 52, // 0x00000034
		D5 = 53, // 0x00000035
		D6 = 54, // 0x00000036
		D7 = 55, // 0x00000037
		D8 = 56, // 0x00000038
		D9 = 57, // 0x00000039
		A = 65, // 0x00000041
		B = 66, // 0x00000042
		C = 67, // 0x00000043
		D = 68, // 0x00000044
		E = 69, // 0x00000045
		F = 70, // 0x00000046
		G = 71, // 0x00000047
		H = 72, // 0x00000048
		I = 73, // 0x00000049
		J = 74, // 0x0000004A
		K = 75, // 0x0000004B
		L = 76, // 0x0000004C
		M = 77, // 0x0000004D
		N = 78, // 0x0000004E
		O = 79, // 0x0000004F
		P = 80, // 0x00000050
		Q = 81, // 0x00000051
		R = 82, // 0x00000052
		S = 83, // 0x00000053
		T = 84, // 0x00000054
		U = 85, // 0x00000055
		V = 86, // 0x00000056
		W = 87, // 0x00000057
		X = 88, // 0x00000058
		Y = 89, // 0x00000059
		Z = 90, // 0x0000005A
		LeftWindows = VK_LWIN, // 0x0000005B
		RightWindows = VK_RWIN, // 0x0000005C
		Apps = VK_APPS, // 0x0000005D
		Sleep = VK_SLEEP, // 0x0000005F
		NumPad0 = VK_NUMPAD0, // 0x00000060
		NumPad1 = VK_NUMPAD1, // 0x00000061
		NumPad2 = VK_NUMPAD2, // 0x00000062
		NumPad3 = VK_NUMPAD3, // 0x00000063
		NumPad4 = VK_NUMPAD4, // 0x00000064
		NumPad5 = VK_NUMPAD5, // 0x00000065
		NumPad6 = VK_NUMPAD6, // 0x00000066
		NumPad7 = VK_NUMPAD7, // 0x00000067
		NumPad8 = VK_NUMPAD8, // 0x00000068
		NumPad9 = VK_NUMPAD9, // 0x00000069
		Multiply = VK_MULTIPLY, // 0x0000006A
		Add = VK_ADD, // 0x0000006B
		Separator = VK_SEPARATOR, // 0x0000006C
		Subtract = VK_SUBTRACT, // 0x0000006D
		Decimal = VK_DECIMAL, // 0x0000006E
		Divide = VK_DIVIDE, // 0x0000006F
		F1 = VK_F1, // 0x00000070
		F2 = VK_F2, // 0x00000071
		F3 = VK_F3, // 0x00000072
		F4 = VK_F4, // 0x00000073
		F5 = VK_F5, // 0x00000074
		F6 = VK_F6, // 0x00000075
		F7 = VK_F7, // 0x00000076
		F8 = VK_F8, // 0x00000077
		F9 = VK_F9, // 0x00000078
		F10 = VK_F10, // 0x00000079
		F11 = VK_F11, // 0x0000007A
		F12 = VK_F12, // 0x0000007B
		F13 = VK_F13, // 0x0000007C
		F14 = VK_F14, // 0x0000007D
		F15 = VK_F15, // 0x0000007E
		F16 = VK_F16, // 0x0000007F
		F17 = VK_F17, // 0x00000080
		F18 = VK_F18, // 0x00000081
		F19 = VK_F19, // 0x00000082
		F20 = VK_F20, // 0x00000083
		F21 = VK_F21, // 0x00000084
		F22 = VK_F22, // 0x00000085
		F23 = VK_F23, // 0x00000086
		F24 = VK_F24, // 0x00000087
		NumLock = VK_NUMLOCK, // 0x00000090
		Scroll = VK_SCROLL, // 0x00000091
		LeftShift = VK_LSHIFT, // 0x000000A0
		RightShift = VK_RSHIFT, // 0x000000A1
		LeftControl = VK_LCONTROL, // 0x000000A2
		RightControl = VK_RCONTROL, // 0x000000A3
		LeftAlt = VK_LMENU, // 0x000000A4
		RightAlt = VK_RMENU, // 0x000000A5
		BrowserBack = VK_BROWSER_BACK, // 0x000000A6
		BrowserForward = VK_BROWSER_FORWARD, // 0x000000A7
		BrowserRefresh = VK_BROWSER_REFRESH, // 0x000000A8
		BrowserStop = VK_BROWSER_STOP, // 0x000000A9
		BrowserSearch = VK_BROWSER_SEARCH, // 0x000000AA
		BrowserFavorites = VK_BROWSER_FAVORITES, // 0x000000AB
		BrowserHome = VK_BROWSER_HOME, // 0x000000AC
		VolumeMute = VK_VOLUME_MUTE, // 0x000000AD
		VolumeDown = VK_VOLUME_DOWN, // 0x000000AE
		VolumeUp = VK_VOLUME_UP, // 0x000000AF
		MediaNextTrack = VK_MEDIA_NEXT_TRACK, // 0x000000B0
		MediaPreviousTrack = VK_MEDIA_PREV_TRACK, // 0x000000B1
		MediaStop = VK_MEDIA_STOP, // 0x000000B2
		MediaPlayPause = VK_MEDIA_PLAY_PAUSE, // 0x000000B3
		LaunchMail = VK_LAUNCH_MAIL, // 0x000000B4
		SelectMedia = VK_LAUNCH_MEDIA_SELECT, // 0x000000B5
		LaunchApplication1 = VK_LAUNCH_APP1, // 0x000000B6
		LaunchApplication2 = VK_LAUNCH_APP2, // 0x000000B7
		OemSemicolon = VK_OEM_1, // 0x000000BA
		OemPlus = VK_OEM_PLUS, // 0x000000BB
		OemComma = VK_OEM_COMMA, // 0x000000BC
		OemMinus = VK_OEM_MINUS, // 0x000000BD
		OemPeriod = VK_OEM_PERIOD, // 0x000000BE
		OemQuestion = VK_OEM_2, // 0x000000BF
		OemTilde = VK_OEM_3, // 0x000000C0
		ChatPadGreen = VK_GAMEPAD_RIGHT_TRIGGER, // 0x000000CA
		ChatPadOrange = VK_GAMEPAD_DPAD_UP, // 0x000000CB
		OemOpenBrackets = VK_OEM_4, // 0x000000DB
		OemPipe = VK_OEM_5, // 0x000000DC
		OemCloseBrackets = VK_OEM_6, // 0x000000DD
		OemQuotes = VK_OEM_7, // 0x000000DE
		Oem8 = VK_OEM_8, // 0x000000DF
		OemBackslash = VK_OEM_102, // 0x000000E2
		ProcessKey = VK_PROCESSKEY, // 0x000000E5
		OemCopy = VK_OEM_COPY, // 0x000000F2
		OemAuto = VK_OEM_AUTO, // 0x000000F3
		OemEnlW = VK_OEM_ENLW, // 0x000000F4
		Attn = VK_ATTN, // 0x000000F6
		Crsel = VK_CRSEL, // 0x000000F7
		Exsel = VK_EXSEL, // 0x000000F8
		EraseEof = VK_EREOF, // 0x000000F9
		Play = VK_PLAY, // 0x000000FA
		Zoom = VK_ZOOM, // 0x000000FB
		Pa1 = VK_PA1, // 0x000000FD
		OemClear = VK_OEM_CLEAR, // 0x000000FE
	};
}

#endif
#ifndef DXNA_PLT_WIN_WINPUT_HPP
#define DXNA_PLT_WIN_WINPUT_HPP

#include "win32includes.hpp"
#include "../../input/input.hpp"

namespace dxna::input{
	static constexpr void KeyboardWinProc(UINT message, WPARAM wparam, LPARAM lparam) {
		switch (message)
		{
		case WM_KEYDOWN:
			Keyboard::SetFlag(wparam, true);
			return;
		case WM_KEYUP:
			Keyboard::SetFlag(wparam, false);
			return;
		default:
			return;
		}
	}

	static constexpr void MouseWinProc(UINT message, WPARAM wparam, LPARAM lparam) {
		switch (message)
		{
		case WM_MOUSEMOVE:
			Mouse::X = GET_X_LPARAM(lparam);
			Mouse::Y = GET_Y_LPARAM(lparam);
			return;
		case WM_MOUSEWHEEL:
			Mouse::Wheel += GET_WHEEL_DELTA_WPARAM(wparam);
			return;
		case WM_LBUTTONDOWN:
			Mouse::Left = ButtonState::Pressed;
			return;
		case WM_LBUTTONUP:
			Mouse::Left = ButtonState::Released;
			return;
		case WM_MBUTTONDOWN:
			Mouse::Middle = ButtonState::Pressed;
			return;
		case WM_MBUTTONUP:
			Mouse::Middle = ButtonState::Released;
			return;
		case WM_RBUTTONDOWN:
			Mouse::Right = ButtonState::Pressed;
			return;
		case WM_RBUTTONUP:
			Mouse::Right = ButtonState::Released;
			return;
		case WM_XBUTTONDOWN:
			if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON1) {
				Mouse::X1 = ButtonState::Pressed;
			}
			else if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON2) {
				Mouse::X2 = ButtonState::Pressed;
			}
			return;
		case WM_XBUTTONUP:
			if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON1) {
				Mouse::X1 = ButtonState::Released;
			}
			else if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON2) {
				Mouse::X2 = ButtonState::Released;
			}
			return;
		default:
			break;
		}
	}

	inline void Mouse::SetPosition(int x, int y) {
		X = x;
		Y = y;
		SetCursorPos(x, y);
	}
}


#endif
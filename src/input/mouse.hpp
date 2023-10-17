#ifndef DXNA_MOUSE_HPP
#define DXNA_MOUSE_HPP

#include "../includes.hpp"
#include "buttons.hpp"

namespace dxna::input {
	struct MouseState {
		int X{ 0 };
		int Y{ 0 };
		int Wheel{ 0 };
		ButtonState Left{ ButtonState::Released };
		ButtonState Right{ ButtonState::Released };
		ButtonState Middle{ ButtonState::Released };
		ButtonState X1{ ButtonState::Released };
		ButtonState X2{ ButtonState::Released };

		constexpr MouseState() = default;

		constexpr MouseState(int x, int y, int scrollWheel,
			ButtonState const& left, ButtonState const& right, ButtonState const& middle,
			ButtonState const& x1, ButtonState const& x2) :
			X(x), Y(y),	Wheel(scrollWheel),
			Left(left),	Right(right), Middle(middle),
			X1(x1),	X2(x2) {
		}

		constexpr bool IsDown(MouseButton const& button) const {
			switch (button)
			{
			case MouseButton::Left:
				return Left == ButtonState::Pressed;
			case MouseButton::Right:
				return Right == ButtonState::Pressed;
			case MouseButton::Middle:
				return Middle == ButtonState::Pressed;
			case MouseButton::X1:
				return X1 == ButtonState::Pressed;
			case MouseButton::X2:
				return X2 == ButtonState::Pressed;
			default:
				return false;
			}
		}

		constexpr bool IsUp(MouseButton const& button) const {
			switch (button)
			{
			case MouseButton::Left:
				return Left == ButtonState::Released;
			case MouseButton::Right:
				return Right == ButtonState::Released;
			case MouseButton::Middle:
				return Middle == ButtonState::Released;
			case MouseButton::X1:
				return X1 == ButtonState::Released;
			case MouseButton::X2:
				return X2 == ButtonState::Released;
			default:
				return false;
			}
		}		
	};

	struct Mouse {
		static int X;
		static int Y;
		static int Wheel;
		static ButtonState Left;
		static ButtonState Right;
		static ButtonState Middle;
		static ButtonState X1;
		static ButtonState X2;

		static constexpr MouseState GetState() {
			return MouseState(X, Y, Wheel, Left, Right, Middle, X1, X2);
		}

		static constexpr void WinProc(UINT message, WPARAM wparam, LPARAM lparam) {
			switch (message)
			{
			case WM_MOUSEMOVE:
				X = LOWORD(lparam);
				Y = HIWORD(lparam);
				return;
			case WM_MOUSEWHEEL:
				Wheel = GET_WHEEL_DELTA_WPARAM(wparam);
				return;
			case WM_LBUTTONDOWN:
				Left = ButtonState::Pressed;
				return;
			case WM_LBUTTONUP:
				Left = ButtonState::Released;
				return;
			case WM_MBUTTONDOWN:
				Middle = ButtonState::Pressed;
				return;
			case WM_MBUTTONUP:
				Middle = ButtonState::Released;
				return;
			case WM_RBUTTONDOWN:
				Right = ButtonState::Pressed;
				return;
			case WM_RBUTTONUP:
				Right = ButtonState::Released;
				return;
			default:
				break;
			}
		}

		static constexpr bool IsDown(MouseButton const& button) {
			switch (button)
			{
			case MouseButton::Left:
				return Left == ButtonState::Pressed;
			case MouseButton::Right:
				return Right == ButtonState::Pressed;
			case MouseButton::Middle:
				return Middle == ButtonState::Pressed;
			case MouseButton::X1:
				return X1 == ButtonState::Pressed;
			case MouseButton::X2:
				return X2 == ButtonState::Pressed;
			default:
				return false;
			}
		}

		static constexpr bool IsUp(MouseButton const& button) {					
			switch (button)
			{
			case MouseButton::Left:
				return Left == ButtonState::Released;
			case MouseButton::Right:
				return Right == ButtonState::Released;
			case MouseButton::Middle:
				return Middle == ButtonState::Released;
			case MouseButton::X1:
				return X1 == ButtonState::Released;
			case MouseButton::X2:
				return X2 == ButtonState::Released;
			default:
				return false;
			}
		}

		static void SetPosition(int x, int y);

	private:
		constexpr Mouse() = default;
		constexpr Mouse(Mouse&&) = default;
		constexpr Mouse(const Mouse&) = default;
	};
}

#endif
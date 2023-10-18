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

		//Obtém TRUE caso o botão informado estaja pressionado.
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

		//Obtém TRUE caso o botão informado estaja liberado.
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
		//Obtém o estado atual do teclado.
		static constexpr MouseState GetState() {
			return MouseState(X, Y, Wheel, Left, Right, Middle, X1, X2);
		}		

		//Obtém TRUE caso o botão informado estaja pressionado.
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

		//Obtém TRUE caso o botão informado estaja liberado.
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

		//Define a posição do cursor do mouse.
		static void SetPosition(int x, int y);

		static constexpr void WinProc(UINT message, WPARAM wparam, LPARAM lparam) {
			switch (message)
			{
			case WM_MOUSEMOVE:
				PreviousX = X;
				PreviousY = Y;
				X = GET_X_LPARAM(lparam);
				Y = GET_Y_LPARAM(lparam);
				return;
			case WM_MOUSEWHEEL:
				PreviousWheel = Wheel;
				Wheel += GET_WHEEL_DELTA_WPARAM(wparam);
				return;
			case WM_LBUTTONDOWN:
				PreviousLeft = Left;
				Left = ButtonState::Pressed;
				return;
			case WM_LBUTTONUP:
				PreviousLeft = Left;
				Left = ButtonState::Released;
				return;
			case WM_MBUTTONDOWN:
				PreviousMiddle = Middle;
				Middle = ButtonState::Pressed;
				return;
			case WM_MBUTTONUP:
				PreviousMiddle = Middle;
				Middle = ButtonState::Released;
				return;
			case WM_RBUTTONDOWN:
				PreviousRight = Right;
				Right = ButtonState::Pressed;
				return;
			case WM_RBUTTONUP:
				PreviousRight = Right;
				Right = ButtonState::Released;
				return;
			case WM_XBUTTONDOWN:
				if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON1) {
					PreviousX1 = X1;
					X1 = ButtonState::Pressed;
				}
				else if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON2) {
					PreviousX2 = X2;
					X2 = ButtonState::Pressed;
				}
				return;
			case WM_XBUTTONUP:
				if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON1) {
					PreviousX1 = X1;
					X1 = ButtonState::Released;
				}
				else if (GET_XBUTTON_WPARAM(wparam) == MK_XBUTTON2) {
					PreviousX2 = X2;
					X2 = ButtonState::Released;
				}
				return;		
			default:
				break;
			}
		}	

		static int X;
		static int Y;
		static int64_t Wheel;
		static ButtonState Left;
		static ButtonState Right;
		static ButtonState Middle;
		static ButtonState X1;
		static ButtonState X2;

		static int PreviousX;
		static int PreviousY;
		static int64_t PreviousWheel;
		static ButtonState PreviousLeft;
		static ButtonState PreviousRight;
		static ButtonState PreviousMiddle;
		static ButtonState PreviousX1;
		static ButtonState PreviousX2;

	private:		
		constexpr Mouse() = default;
		constexpr Mouse(Mouse&&) = default;
		constexpr Mouse(const Mouse&) = default;
	};
}

#endif
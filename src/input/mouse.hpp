#ifndef DXNA_NPUT_MOUSE_HPP
#define DXNA_NPUT_MOUSE_HPP

#include "buttons.hpp"
#include <cstdint>

namespace dxna::input {
	struct MouseState {
		int X{ 0 };
		int Y{ 0 };
		int64_t Wheel{ 0 };
		ButtonState Left{ ButtonState::Released };
		ButtonState Right{ ButtonState::Released };
		ButtonState Middle{ ButtonState::Released };
		ButtonState X1{ ButtonState::Released };
		ButtonState X2{ ButtonState::Released };

		constexpr MouseState() = default;

		constexpr MouseState(int x, int y, int64_t scrollWheel,
			ButtonState const& left, ButtonState const& right, ButtonState const& middle,
			ButtonState const& x1, ButtonState const& x2) :
			X(x), Y(y),	Wheel(scrollWheel),
			Left(left),	Right(right), Middle(middle),
			X1(x1),	X2(x2) {
		}

		//Obt�m TRUE caso o bot�o informado estaja pressionado.
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

		//Obt�m TRUE caso o bot�o informado estaja liberado.
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
		//Obt�m o estado atual do teclado.
		static constexpr MouseState GetState() {
			return MouseState(X, Y, Wheel, Left, Right, Middle, X1, X2);
		}		

		//Obt�m TRUE caso o bot�o informado estaja pressionado.
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

		//Obt�m TRUE caso o bot�o informado estaja liberado.
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

		//Define a posi��o do cursor do mouse.
		static void SetPosition(int x, int y);

		static int X;
		static int Y;
		static int64_t Wheel;
		static ButtonState Left;
		static ButtonState Right;
		static ButtonState Middle;
		static ButtonState X1;
		static ButtonState X2;

	private:		
		constexpr Mouse() = default;
		constexpr Mouse(Mouse&&) = default;
		constexpr Mouse(const Mouse&) = default;
	};
}

#endif
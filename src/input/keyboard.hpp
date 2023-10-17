#ifndef DXNA_KEYBOARD_HPP
#define DXNA_KEYBOARD_HPP

#include "keys.hpp"

namespace dxna::input {
	struct KeyboardState {	

		constexpr KeyboardState() = default;		

		constexpr KeyboardState(std::vector<bool> const& states) : flags(states) {
		}

		constexpr bool IsKeyDown(Keys const& key) const {
			return flags[(int)key];
		}

		constexpr bool IsKeyUp(Keys const& key) const {
			return !flags[(int)key];
		}

		constexpr std::vector<Keys> GetPressedKeys() {			
			auto const size = flags.size();
			std::vector<Keys> pressedKeys;

			for (size_t i = 0; i < size; ++i) {
				if (IsKeyDown(static_cast<int>(i)))
					pressedKeys.push_back((Keys)i);
			}

			return pressedKeys;
		}

		constexpr KeyState operator[](Keys const& key) const {
			return IsKeyDown(key) ? KeyState::Down : KeyState::Up;
		}

	private:
		std::vector<bool> flags;
		
		bool constexpr IsKeyDown(int const& key) const {
			return flags[key];
		}

		bool constexpr IsKeyUp(int const& key) const {
			return !flags[key];
		}
	};

	struct Keyboard {
		static KeyboardState GetState() {			
			return KeyboardState(flags);
		}

		static constexpr bool IsKeyDown(Keys const& key) {
			return flags[(int)key];
		}

		static constexpr bool IsKeyUp(Keys const& key) {
			return !flags[(int)key];
		}

		static constexpr void WinProc(UINT const& message, WPARAM const& wparam) {
			switch (message)
			{
			case WM_KEYDOWN:
				flags[wparam] = true;
				return;
			case WM_KEYUP:
				flags[wparam] = false;
				return;
			default:
				return;
			}
		}

	private:
		static std::vector<bool> flags;
		static constexpr int KEYDOWN_FLAG = 0x8000;

		constexpr Keyboard() = default;
		constexpr Keyboard(Keyboard&&) = default;
		constexpr Keyboard(const Keyboard&) = default;
	};
}

#endif
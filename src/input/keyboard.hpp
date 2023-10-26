#ifndef DXNA_NPUT_KEYBOARD_HPP
#define DXNA_NPUT_KEYBOARD_HPP

#include "keys.hpp"
#include <vector>

namespace dxna::input {
	struct KeyboardState {	

		constexpr KeyboardState() = default;		

		constexpr KeyboardState(std::vector<bool> const& states) : flags(states) {
		}

		//Obt�m TRUE caso a tecla informada esteja pressionada.
		constexpr bool IsKeyDown(Keys const& key) const {
			return flags[(int)key];
		}

		//Obt�m TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t key) const {
			if (key > 255)
				return false;

			return flags[key];
		}

		//Obt�m TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(Keys const& key) const {			
			return !flags[(int)key];
		}

		//Obt�m TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(size_t key) const {
			if (key > 255)
				return false;

			return !flags[(int)key];
		}

		constexpr KeyState operator[](Keys const& key) const {
			return IsKeyDown(key) ? KeyState::Down : KeyState::Up;
		}

	private:
		std::vector<bool> flags = std::vector<bool>(255);
	};

	struct Keyboard {
		//Obt�m o estado atual do teclado.
		static KeyboardState GetState() {			
			return KeyboardState(flags);
		}

		//Obt�m TRUE caso a tecla informada esteja pressionada.
		static constexpr bool IsKeyDown(Keys const& key) {
			return flags[(int)key];
		}

		//Obt�m TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t key) const {
			if (key > 255)
				return false;

			return flags[key];
		}

		//Obt�m TRUE caso a tecla informada esteja liberada.
		static constexpr bool IsKeyUp(Keys const& key) {
			return !flags[(int)key];
		}

		//Obt�m TRUE caso a tecla informada esteja liberada.
		bool constexpr IsKeyUp(size_t key) const {
			if (key > 255)
				return false;

			return !flags[(int)key];
		}

		static constexpr void SetFlag(size_t index, bool value) {
			if (index > 255)
				return;

			flags[index] = value;
		}

	private:
		static std::vector<bool> flags;

		constexpr Keyboard() = default;
		constexpr Keyboard(Keyboard&&) = default;
		constexpr Keyboard(const Keyboard&) = default;		
	};
}

#endif
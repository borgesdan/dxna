#ifndef DXNA_NPUT_KEYBOARD_HPP
#define DXNA_NPUT_KEYBOARD_HPP

#include "keys.hpp"
#include <vector>

namespace dxna::input {
	struct KeyboardState {	

		constexpr KeyboardState() = default;		

		constexpr KeyboardState(std::vector<bool> const& states) : flags(states) {
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		constexpr bool IsKeyDown(Keys const& key) const {
			return flags[(int)key];
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t key) const {
			if (key > 255)
				return false;

			return flags[key];
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(Keys const& key) const {			
			return !flags[(int)key];
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(size_t key) const {
			if (key > 255)
				return false;

			return !flags[(int)key];
		}

		//Obtém uma lista de todas as teclas pressionadas
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
	};

	struct Keyboard {
		//Obtém o estado atual do teclado.
		static KeyboardState GetState() {			
			return KeyboardState(flags);
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		static constexpr bool IsKeyDown(Keys const& key) {
			return flags[(int)key];
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t key) const {
			if (key > 255)
				return false;

			return flags[key];
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		static constexpr bool IsKeyUp(Keys const& key) {
			return !flags[(int)key];
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		bool constexpr IsKeyUp(size_t key) const {
			if (key > 255)
				return false;

			return !flags[(int)key];
		}

		//Obtém uma lista de todas as teclas pressionadas
		constexpr std::vector<Keys> GetPressedKeys() {
			auto const size = flags.size();
			std::vector<Keys> pressedKeys;

			for (size_t i = 0; i < size; ++i) {
				if (IsKeyDown(static_cast<int>(i)))
					pressedKeys.push_back((Keys)i);
			}

			return pressedKeys;
		}		

		static constexpr void SetFlag(size_t index, bool value) {
			if (index > 255)
				return;

			flags[index] = value;
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
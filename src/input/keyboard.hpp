#ifndef DXNA_NPUT_KEYBOARD_HPP
#define DXNA_NPUT_KEYBOARD_HPP

#include "keys.hpp"
#include <vector>

namespace dxna::input {
	struct KeyboardState {	

		constexpr KeyboardState() = default;

		//Obtém TRUE caso a tecla informada esteja pressionada.
		constexpr bool IsKeyDown(Keys const& key) const {
			if (index == 0)
				return false;

			for (size_t i = 0; i < MAX_KEYS; ++i) {
				if (downKeys[i] == (int)key)
					return true;				
				else if (i == -1)
					return false;
			}

			return false;
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t key) const {
			if (index == 0 || key > 255)
				return false;

			for (size_t i = 0; i < MAX_KEYS; ++i) {
				if (downKeys[i] == key)
					return true;
				else if (i == -1)
					return false;

			}

			return false;
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(Keys const& key) const {		
			if (index == 0)
				return true;

			for (size_t i = 0; i < MAX_KEYS; ++i) {
				if (downKeys[i] == (int)key)
					return false;
				else if (i == -1)
					return true;
			}

			return true;
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(size_t key) const {
			if (index == 0)
				return true;

			if (key > 255)
				return false;

			for (size_t i = 0; i < MAX_KEYS; ++i) {
				if (downKeys[i] == key)
					return false;
				else if (i == -1)
					return true;
			}

			return true;
		}

		constexpr KeyState operator[](Keys const& key) const {
			return IsKeyDown(key) ? KeyState::Down : KeyState::Up;
		}

		constexpr KeyState operator[](size_t key) const {
			return IsKeyDown(key) ? KeyState::Down : KeyState::Up;
		}

		//Adiciona teclas pressionadas ao estado atual, com o máximo de 20 registros.
		constexpr void AddPressedKey(Keys const& key) {
			downKeys[index++] = (int)key;
			
			if (index == MAX_KEYS)
				index = 0;
		}

		//Adiciona teclas pressionadas ao estado atual, com o máximo de 20 registros.
		constexpr void AddPressedKey(size_t key) {
			downKeys[index++] = static_cast<int>(key);

			if (index == MAX_KEYS)
				index = 0;
		}

	private:		
		static constexpr int MAX_KEYS = 10;
		size_t index{ 0 };

		//Vetor de teclas pressionadas com valores inicializados em -1, onde as teclas pressionadas são números inteiros positivos.
		//Na consulta, se o index do vetor tiver o valor -1 significa que não há mais teclas pressionadas a serem verificadas.
		std::vector<int> downKeys = std::vector<int>(MAX_KEYS, -1);		
	};

	struct Keyboard {
		//Obtém o estado atual do teclado.
		static KeyboardState GetState() {	
			KeyboardState state;

			for (size_t i = 0; i < 255; ++i) {
				if (flags[i]) {
					state.AddPressedKey(i);
				}
			}				
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
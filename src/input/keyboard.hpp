#ifndef DXNA_NPUT_KEYBOARD_HPP
#define DXNA_NPUT_KEYBOARD_HPP

#include "keys.hpp"
#include <vector>

namespace dxna::input {
	struct Keyboard;

	struct KeyboardState {	
		//Para acesso amigo a função interna AddPressedKey
		friend struct Keyboard;
		constexpr KeyboardState() = default;

		//Obtém TRUE caso a tecla informada esteja pressionada.
		constexpr bool IsKeyDown(Keys const& key) const {
			if (index < 0)
				return false;	

			return checkSlots((int)key);
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t vkkey) const {
			if (index < 0)
				return false;

			return checkSlots(static_cast<int>(vkkey));

			return false;
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(Keys const& key) const {		
			if (index < 0)
				return true;

			return !checkSlots((int)key);
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		constexpr bool IsKeyUp(size_t vkkey) const {
			if (index == 0)
				return true;			

			return !checkSlots((int)vkkey);
		}

		//Operador para acesso direto para verificar se uma tecla está pressionada
		constexpr KeyState operator[](Keys const& key) const {
			return IsKeyDown(key) ? KeyState::Down : KeyState::Up;
		}

		//Operador para acesso direto para verificar se uma tecla está pressionada
		constexpr KeyState operator[](size_t const& vkkey) const {
			return IsKeyDown(vkkey) ? KeyState::Down : KeyState::Up;
		}					

	private:		
		constexpr bool checkSlots(int const& value) const {
			return value == slot0 || value == slot1
				|| value == slot2 || value == slot3
				|| value == slot4 || value == slot5
				|| value == slot6 || value == slot7
				|| value == slot8 || value == slot9;
		}

		//Internal: Adiciona teclas pressionadas ao estado atual, com o máximo de 10 registros.
		//Retorna true caso a operação seja bem sucedida ou não exceda os 10 registros.
		constexpr bool AddPressedKey(size_t const& vkkey) {
			++index;

			if (index == MAX_KEYS)
				return false;

			switch (index)
			{
			case 0:
				slot0 = static_cast<int>(vkkey);
				break;
			case 1:
				slot1 = static_cast<int>(vkkey);
				break;
			case 2:
				slot2 = static_cast<int>(vkkey);
				break;
			case 3:
				slot3 = static_cast<int>(vkkey);
				break;
			case 4:
				slot4 = static_cast<int>(vkkey);
				break;
			case 5:
				slot5 = static_cast<int>(vkkey);
				break;
			case 6:
				slot6 = static_cast<int>(vkkey);
				break;
			case 7:
				slot7 = static_cast<int>(vkkey);
				break;
			case 8:
				slot8 = static_cast<int>(vkkey);
				break;
			case 9:
				slot9 = static_cast<int>(vkkey);
				break;
			default:
				return false;
			}

			return true;
		}

		static constexpr int MAX_KEYS = 10;
		
		int index{ -1 };		
		int slot0{ -1 };
		int slot1{ -1 };
		int slot2{ -1 };
		int slot3{ -1 };
		int slot4{ -1 };
		int slot5{ -1 };
		int slot6{ -1 };
		int slot7{ -1 };
		int slot8{ -1 };
		int slot9{ -1 };
	};

	struct Keyboard {
		//Obtém o estado atual do teclado.
		static KeyboardState GetState() {	
			KeyboardState state;				

			for (size_t i = 0; i < 255; ++i) {
				if (flags[i]) {					
					const auto result = state.AddPressedKey(i);					

					if (!result)
						break;
				}
			}				

			return state;
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		static constexpr bool IsKeyDown(Keys const& key) {
			return flags[(int)key];
		}

		//Obtém TRUE caso a tecla informada esteja pressionada.
		bool constexpr IsKeyDown(size_t vkkey) const {
			if (vkkey > 255)
				return false;

			return flags[vkkey];
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		static constexpr bool IsKeyUp(Keys const& key) {
			return !flags[static_cast<int>(key)];
		}

		//Obtém TRUE caso a tecla informada esteja liberada.
		static constexpr bool IsKeyUp(size_t vkkey) {
			if (vkkey > 255)
				return false;

			return !flags[vkkey];
		}

		//Define uma flag de teclado.
		static constexpr void SetFlag(size_t vkkey, bool value) {
			if (vkkey > 255)
				return;

			flags[vkkey] = value;
		}

	private:
		static std::vector<bool> flags;

		//Esconde construtores para transformar a classe em estática.
		constexpr Keyboard() = default;
		constexpr Keyboard(Keyboard&&) = default;
		constexpr Keyboard(const Keyboard&) = default;		
	};
}

#endif

#include "mouse.hpp"

namespace dxna::input {
	int Mouse::X{ 0 };
	int Mouse::Y{ 0 };
	int64_t Mouse::Wheel{ 0 };
	ButtonState Mouse::Left{ ButtonState::Released };
	ButtonState Mouse::Right{ ButtonState::Released };
	ButtonState Mouse::Middle{ ButtonState::Released };
	ButtonState Mouse::X1{ ButtonState::Released };
	ButtonState Mouse::X2{ ButtonState::Released };	
}
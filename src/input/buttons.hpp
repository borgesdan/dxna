#ifndef DXNA_BUTTONS_HPP
#define DXNA_BUTTONS_HPP

namespace dxna::input {
	enum class ButtonState {
		Released,
		Pressed
	};

	enum class MouseButton {
		Left,
		Right,
		Middle,
		X1,
		X2
	};
}

#endif

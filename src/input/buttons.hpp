#ifndef DXNA_INPUT_BUTTONS_HPP
#define DXNA_NPUT_BUTTONS_HPP

namespace dxna::input {
	//Representa os estados dos botões.
	enum class ButtonState {
		Released,
		Pressed
	};

	//Representa os botões do mouse.
	enum class MouseButton {
		Left,
		Right,
		Middle,
		X1,
		X2
	};

    enum class ButtonValues {
        A = 4096, // 0x1000
        B = 8192, // 0x2000
        Back = 32, // 0x0020
        Down = 2,
        Left = 4,
        LeftShoulder = 256, // 0x0100
        LeftThumb = 64, // 0x0040
        Right = 8,
        RightShoulder = 512, // 0x0200
        RightThumb = 128, // 0x0080
        Start = 16, // 0x0010
        Up = 1,
        X = 16384, // 0x4000
        Y = 32768, // 0x8000
        BigButton = 2048, // 0x0800
    };
}

#endif

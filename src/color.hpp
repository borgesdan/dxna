#ifndef DXNA_COLOR_HPP
#define DXNA_COLOR_HPP

#include "defincludes.hpp"

namespace dxna {
	struct Color {
		constexpr Color(uint32_t packedValue) : packedValue(packedValue) {}

		constexpr Color(int32_t r, int32_t g, int32_t b) {
			if ((((r | g | b) & -256) != 0) {

			}
		}

	private:

		uint32_t packedValue{ 0 };
	};
}

#endif
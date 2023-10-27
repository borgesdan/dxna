#ifndef DXNA_GRAPHICS_VIEWPORT_HPP
#define DXNA_GRAPHICS_VIEWPORT_HPP

namespace dxna::graphics {
	struct Viewport {
		int X{ 0 };
		int Y{ 0 };
		int Width{ 0 };
		int Height{ 0 };

		constexpr Viewport() = default;		

		Viewport(int x, int y, int width, int height)
			: X(x), Y(y), Width(width), Height(height) {}
	};
}

#endif
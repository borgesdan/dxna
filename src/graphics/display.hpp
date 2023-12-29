#ifndef DXNA_GRAPHICS_DISPLAY_HPP
#define DXNA_GRAPHICS_DISPLAY_HPP

#include "enumerations.hpp"
#include "../cs/cs.hpp"
#include "../structs.hpp"

namespace dxna::graphics {
	class DisplayMode {
	public:
		DisplayMode(intcs width, intcs height, SurfaceFormat format) :
			format(format), width(width), height(height) {
		}

		constexpr float AspectRatio() const noexcept {
			return static_cast<float>(width) / static_cast<float>(height);
		}

		constexpr SurfaceFormat Format() const noexcept {
			return format;
		}

		constexpr intcs Height() const noexcept {
			return height;
		}

		constexpr intcs Width() const noexcept {
			return width;
		}

		Rectangle TitleSafeArea() {
			//TODO: GraphicsDevice.GetTitleSafeArea(0, 0, width, height);
			return Rectangle::Empty();
		}

	private:
		SurfaceFormat format;
		intcs height;
		intcs width;
	};
}

#endif
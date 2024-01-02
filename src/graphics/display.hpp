#ifndef DXNA_GRAPHICS_DISPLAY_HPP
#define DXNA_GRAPHICS_DISPLAY_HPP

#include <algorithm>
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

		constexpr bool operator==(const DisplayMode& other) const noexcept {
			return format == other.format
				&& height == other.height
				&& width == other.width;
		}

		constexpr bool operator<(const DisplayMode& other) const noexcept {
			return format < other.format
				&& width < other.width
				&& height < other.height;
		}

	private:
		SurfaceFormat format;
		intcs height;
		intcs width;
	};

	class DisplayModeCollection {
	public:
		DisplayModeCollection(vectorptr<DisplayModePtr> const& modes) : _modes(modes) {
			std::sort(_modes->begin(), _modes->end());
		}

		vectorptr<DisplayModePtr> operator[](SurfaceFormat const& format) {
			const auto size = _modes->size();
			vectorptr<DisplayModePtr> list = NewVector<DisplayModePtr>(size);
			auto count = 0;

			for (size_t i = 0; i < _modes->size(); ++i) {
				auto& mode = _modes->at(i);

				if (mode->Format() == format) {
					list->at(i) = mode;
					++count;
				}				
			}
			
			list->resize(count);

			return list;
		}

		vectorptr<DisplayModePtr> At(SurfaceFormat const& format) {
			const auto size = _modes->size();
			vectorptr<DisplayModePtr> list = NewVector<DisplayModePtr>(size);
			auto count = 0;

			for (size_t i = 0; i < _modes->size(); ++i) {
				auto& mode = _modes->at(i);

				if (mode->Format() == format) {
					list->at(i) = mode;
					++count;
				}
			}

			list->resize(count);

			return list;
		}

	public:
		vectorptr<DisplayModePtr> _modes;
	};
}

#endif
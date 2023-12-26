#ifndef DXNA_GRAPHICS_DEFPROCESSORS_HPP
#define DXNA_GRAPHICS_DEFPROCESSORS_HPP

#include "../cs/cs.hpp"

namespace dxna::graphics {
	class DefaultColorProcessors {
		static void ZeroTransparentPixels(bytecs* data, size_t dataLength) {
            for (size_t i = 0; i < dataLength; i += 4, data += 4) {
                if (data[3] == 0) {
                    data[0] = data[1] = data[2] = 0;
                }
            }
		}

        static void PremultiplyAlpha(bytecs* data, size_t dataLength) {
            for (size_t i = 0; i < dataLength; i += 4, data += 4) {
                const auto falpha = data[3] / 255.0f;
                data[0] = static_cast<bytecs>(data[0] * falpha);
                data[1] = static_cast<bytecs>(data[1] * falpha);
                data[2] = static_cast<bytecs>(data[2] * falpha);
            }
        }
	};
}

#endif
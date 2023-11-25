#ifndef DXNA_MATHHELPER_HPP
#define DXNA_MATHHELPER_HPP

#include <cmath>
#include <limits>

namespace dxna {
	struct MathHelper {
		static constexpr float Clamp(float value, float min, float max) noexcept {
			value = value > max ? max : value;
			value = value < min ? min : value;
			return value;
		}
		
		static constexpr float Lerp(float value1, float value2, float amount) noexcept {
			return value1 + (value2 - value1) * amount;
		}

		static constexpr float Min(float value1, float value2) noexcept {
			return std::min(value1, value2);
		}

		static constexpr float Max(float value1, float value2) noexcept {
			return std::max(value1, value2);
		}		
	};
}

#endif
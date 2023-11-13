#ifndef DXNA_MATHHELPER_HPP
#define DXNA_MATHHELPER_HPP

#include <cmath>
#include <limits>

namespace dxna {
	struct MathHelper {
		template <typename T>
		static constexpr T Clamp(T value, T min, T max) {
			value = value > max ? max : value;
			value = value < min ? min : value;
			return value;
		}

		template <typename T>
		static constexpr float Lerp(T value1, T value2, float amount) {
			return value1 + (value2 - value1) * amount;
		}

		static constexpr float Min(float value1, float value2) {
			return std::min(value1, value2);
		}

		static constexpr float Max(float value1, float value2) {
			return std::max(value1, value2);
		}
	};
}

#endif
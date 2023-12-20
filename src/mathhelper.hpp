#ifndef DXNA_MATHHELPER_HPP
#define DXNA_MATHHELPER_HPP

#include <cmath>
#include <limits>

namespace dxna {
	struct MathHelper {
		static constexpr float E = 2.71828175F;		
		static constexpr float Log10E = 0.4342945F;
		static constexpr float Log2E = 1.442695F;
		static constexpr double PI = 3.1415926535897931;
		static constexpr float PiOver2 = static_cast<float>(PI / 2.0);
		static constexpr float PiOver4 = static_cast<float>(PI / 4.0);
		static constexpr float TwoPI = static_cast<float>(PI * 2.0);
		static constexpr float Tau = TwoPI;
		static constexpr double Epsilon = std::numeric_limits<double>::epsilon();

		static float Barycentric(float value1, float value2, float value3, float amount1, float amount2) noexcept {
			return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
		}

		static float CatmullRom(float value1, float value2, float value3, float value4, float amount) noexcept {
			double amountSquared = amount * amount;
			double amountCubed = amountSquared * amount;
			
			return static_cast<float>(0.5 * (2.0 * value2 +
				(value3 - value1) * amount +
				(2.0 * value1 - 5.0 * value2 + 4.0 * value3 - value4) * amountSquared +
				(3.0 * value2 - value1 - 3.0 * value3 + value4) * amountCubed));
		}		

		static constexpr float Clamp(float value, float min, float max) noexcept {
			return Clamp(value, min, max);
		}

		static constexpr int Clamp(int value, int min, int max) noexcept {
			value = value > max ? max : value;
			value = value < min ? min : value;
			return value;
		}

		static float Distance(float value1, float value2) noexcept {
			return std::abs(value1 - value2);
		}

		static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount) noexcept {
			double v1 = value1, v2 = value2, t1 = tangent1, t2 = tangent2, s = amount, result;
			double sCubed = s * s * s;
			double sSquared = s * s;

			if (amount == 0.0f)
				result = value1;

			else if (amount == 1.0f)
				result = value2;
			else
				result = (2 * v1 - 2 * v2 + t2 + t1) * sCubed +
				(3 * v2 - 3 * v1 - 2 * t1 - t2) * sSquared +
				t1 * s +
				v1;

			return static_cast<float>(result);
		}
				
		static constexpr float Lerp(float value1, float value2, float amount) noexcept {
			return value1 + (value2 - value1) * amount;
		}

		static float LerpPrecise(float value1, float value2, float amount) noexcept {
			return ((1.0F - amount) * value1) + (value2 * amount);
		}

		static constexpr float Min(float value1, float value2) noexcept {
			return std::min(value1, value2);
		}

		static constexpr int Min(int value1, int value2) noexcept {
			return std::min(value1, value2);
		}

		static constexpr float Max(float value1, float value2) noexcept {
			return std::max(value1, value2);
		}

		static constexpr int Max(int value1, int value2) noexcept {
			return std::max(value1, value2);
		}

		static float SmoothStep(float value1, float value2, float amount) noexcept {
			const auto result = Clamp(amount, 0.0f, 1.0f);
			return Hermite(value1, 0.0f, value2, 0.0f, result);
		}

		static float ToDegrees(float radians) noexcept {
			return static_cast<float>(radians * 57.295779513082320876798154814105);
		}

		static float ToRadians(float degrees) noexcept {
			return static_cast<float>(degrees * 0.017453292519943295769236907684886);
		}

		static float WrapAngle(float angle) noexcept {
			if ((angle > -PI) && (angle <= PI))
				return angle;

			angle = fmod(angle, TwoPI);

			if (angle <= -PI)
				return angle + TwoPI;

			if (angle > PI)
				return angle - TwoPI;

			return angle;
		}

		static bool IsPowerOfTwo(int value) noexcept
		{
			return (value > 0) && ((value & (value - 1)) == 0);
		}
	};

	using Math = MathHelper;
}

#endif
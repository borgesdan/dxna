#include "structs.hpp"
#include <cmath>

namespace dxna {
	float Vector2::Length() const { return std::sqrt(LengthSquared()); }

	void Vector2::Normalize() {
		const auto num = 1.0F / Length();
		X *= num;
		Y *= num;
	}

	float Vector2::Distance(Vector2 const& value1, Vector2 const& value2) {
		const auto num1 = value1.X - value2.X;
		const auto num2 = value1.Y - value2.Y;
		return std::sqrt(num1 * num1 + num2 * num2);
	}

	float Vector3::Length() const {	return std::sqrt(LengthSquared()); }

	void Vector3::Normalize() {
		const auto num = 1.0F / Length();
		X *= num;
		Y *= num;
		Z *= num;
	}

	float Vector3::Distance(Vector3 const& value1, Vector3 const& value2) {
		const auto num1 = value1.X - value2.X;
		const auto num2 = value1.Y - value2.Y;
		const auto num3 = value1.Z - value2.Z;
		return std::sqrt(num1 * num1 + num2 * num2 + num3 * num3);
	}
}
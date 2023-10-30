#include "structs.hpp"
#include <cmath>

namespace dxna {
	float Vector2::Length() const { return std::sqrt((X * X) + (Y * Y)); }

	void Vector2::Normalize() {
		const auto num = 1.0F / std::sqrt(Length());
		X *= num;
		Y *= num;
	}

	float Vector2::Distance(Vector2 const& value1, Vector2 const& value2) {
		const auto num1 = value1.X - value2.X;
		const auto num2 = value1.Y - value2.Y;
		const auto d = num1 * num1 + num2 * num2;
		return std::sqrt(d);
	}
}
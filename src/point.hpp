#ifndef DXNA_POINT_HPP
#define DXNA_POINT_HPP

#include <cstdint>

namespace dxna {
	struct Point {
		int32_t X{ 0 };
		int32_t Y{ 0 };

		constexpr Point() = default;
		constexpr Point(int32_t x, int32_t y) :
			X(x), Y(y) {}

		static constexpr Point Zero() { return Point(); }

		bool constexpr Equals(Point const& other) const {
			return X == other.X && Y == other.Y;
		}

		constexpr Point operator-() {
			return Point(-X, -Y);
		}

		friend constexpr bool operator==(Point const& a, Point const& b) {
			return a.Equals(b);
		}

		friend constexpr bool operator!=(Point const& a, Point const& b) {
			return !a.Equals(b);
		}
	};
}

#endif
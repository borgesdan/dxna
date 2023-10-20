#ifndef DXNA_RECTANGLE_HPP
#define DXNA_RECTANGLE_HPP

#include <cstdint>
#include "point.hpp"

namespace dxna {
	struct Rectangle {
		int32_t X{ 0 };
		int32_t Y{ 0 };
		int32_t Width{ 0 };
		int32_t Height{ 0 };

		constexpr Rectangle() = default;

		constexpr Rectangle(int32_t x, int32_t y, int32_t width, int32_t height) :
			X(x), Y(y), Width(width), Height(height) {}

		static constexpr Rectangle Empty() {
			return Rectangle(0, 0, 0, 0);
		}

		constexpr int32_t Left() const {
			return X;
		}

		constexpr int32_t Right() const {
			return X + Width;
		}

		constexpr int32_t Top() const {
			return Y;
		}

		constexpr int32_t Bottom() const {
			return Y + Height;
		}

		constexpr void Offset(Point const& amount) {
			X += amount.X;
			Y += amount.Y;
		}

		constexpr void Offset(int32_t offsetX, int32_t offsetY) {
			X += offsetX;
			Y += offsetY;
		}

		constexpr void Inflate(int32_t horizontalAmount, int32_t verticalAmount) {
			X -= horizontalAmount;
			Y -= verticalAmount;
			Width += horizontalAmount * 2;
			Height += verticalAmount * 2;
		}

		constexpr bool Contains(int32_t x, int32_t y) const {
			return X <= x && x < X + Width && Y <= y && y < Y + Height;
		}

		constexpr bool Contains(Point const& value) const {
			return X <= value.X && value.X < X + Width && Y <= value.Y && value.Y < Y + Height;
		}

		constexpr bool Contains(Rectangle const& value) const {
			return X <= value.X && value.X + value.Width <= X + Width && Y <= value.Y && value.Y + value.Height <= Y + Height;
		}

		constexpr bool Intersects(Rectangle const& value) const {
			return value.X < X + Width && X < value.X + value.Width && value.Y < Y + Height && Y < value.Y + value.Height;
		}

		constexpr bool Equals(Rectangle const& other) const {
			return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height;
		}

		static constexpr Rectangle Intersect(Rectangle const& value1, Rectangle const& value2) {
			int32_t num1 = value1.X + value1.Width;
			int32_t num2 = value2.X + value2.Width;
			int32_t num3 = value1.Y + value1.Height;
			int32_t num4 = value2.Y + value2.Height;
			int32_t num5 = value1.X > value2.X ? value1.X : value2.X;
			int32_t num6 = value1.Y > value2.Y ? value1.Y : value2.Y;
			int32_t num7 = num1 < num2 ? num1 : num2;
			int32_t num8 = num3 < num4 ? num3 : num4;
			Rectangle rectangle;

			if (num7 > num5 && num8 > num6) {
				rectangle.X = num5;
				rectangle.Y = num6;
				rectangle.Width = num7 - num5;
				rectangle.Height = num8 - num6;
			}
			else {
				rectangle.X = 0;
				rectangle.Y = 0;
				rectangle.Width = 0;
				rectangle.Height = 0;
			}

			return rectangle;
		}

		static constexpr Rectangle Union(Rectangle const& value1, Rectangle const& value2) {
			int32_t num1 = value1.X + value1.Width;
			int32_t num2 = value2.X + value2.Width;
			int32_t num3 = value1.Y + value1.Height;
			int32_t num4 = value2.Y + value2.Height;
			int32_t num5 = value1.X < value2.X ? value1.X : value2.X;
			int32_t num6 = value1.Y < value2.Y ? value1.Y : value2.Y;
			int32_t num7 = num1 > num2 ? num1 : num2;
			int32_t num8 = num3 > num4 ? num3 : num4;

			Rectangle rectangle;
			rectangle.X = num5;
			rectangle.Y = num6;
			rectangle.Width = num7 - num5;
			rectangle.Height = num8 - num6;

			return rectangle;
		}

		friend constexpr bool operator==(Rectangle const& value1, Rectangle const& value2) {
			return value1.Equals(value2);
		}

		friend constexpr bool operator!=(Rectangle const& value1, Rectangle const& value2) {
			return !value1.Equals(value2);
		}
		
	};
}

#endif
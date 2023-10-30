#ifndef DXNA_STRUCTS_HPP
#define DXNA_STRUCTS_HPP

#include <cmath>
#include "mathhelper.hpp"
#include "cs/cstypes.hpp"

namespace dxna {
	//Point
	struct Point {
		intcs X{ 0 };
		intcs Y{ 0 };

		constexpr Point() = default;
		constexpr Point(intcs x, intcs y) :
			X(x), Y(y) {}

		static constexpr Point Zero() { return Point(); }

		bool constexpr Equals(Point const& other) const { return X == other.X && Y == other.Y; }

		constexpr Point operator-() { return Point(-X, -Y); }

		constexpr bool operator==(Point const& other) { return Equals(other); }
	};

	//Rectangle
	struct Rectangle {
		intcs X{ 0 };
		intcs Y{ 0 };
		intcs Width{ 0 };
		intcs Height{ 0 };

		constexpr Rectangle() = default;

		constexpr Rectangle(intcs x, intcs y, intcs width, intcs height) :
			X(x), Y(y), Width(width), Height(height) {}

		static constexpr Rectangle Empty() { return Rectangle(0, 0, 0, 0); }

		constexpr intcs Left() const { return X; }

		constexpr intcs Right() const { return X + Width; }

		constexpr intcs Top() const { return Y; }

		constexpr intcs Bottom() const { return Y + Height; }

		constexpr void Offset(Point const& amount) {
			X += amount.X;
			Y += amount.Y;
		}

		constexpr void Offset(intcs offsetX, intcs offsetY) {
			X += offsetX;
			Y += offsetY;
		}

		constexpr void Inflate(intcs horizontalAmount, intcs verticalAmount) {
			X -= horizontalAmount;
			Y -= verticalAmount;
			Width += horizontalAmount * 2;
			Height += verticalAmount * 2;
		}

		constexpr bool Contains(intcs x, intcs y) const {
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
			intcs num1 = value1.X + value1.Width;
			intcs num2 = value2.X + value2.Width;
			intcs num3 = value1.Y + value1.Height;
			intcs num4 = value2.Y + value2.Height;
			intcs num5 = value1.X > value2.X ? value1.X : value2.X;
			intcs num6 = value1.Y > value2.Y ? value1.Y : value2.Y;
			intcs num7 = num1 < num2 ? num1 : num2;
			intcs num8 = num3 < num4 ? num3 : num4;			

			if (num7 > num5 && num8 > num6) 
				return Rectangle(num5, num6, num7 - num5, num8 - num6);							
			else 
				return Rectangle::Empty();
		}

		static constexpr Rectangle Union(Rectangle const& value1, Rectangle const& value2) {
			intcs num1 = value1.X + value1.Width;
			intcs num2 = value2.X + value2.Width;
			intcs num3 = value1.Y + value1.Height;
			intcs num4 = value2.Y + value2.Height;
			intcs num5 = value1.X < value2.X ? value1.X : value2.X;
			intcs num6 = value1.Y < value2.Y ? value1.Y : value2.Y;
			intcs num7 = num1 > num2 ? num1 : num2;
			intcs num8 = num3 > num4 ? num3 : num4;

			return Rectangle(num5, num6, num7 - num5, num8 - num6);
		}

		constexpr bool operator==(Rectangle const& value2) {
			return Equals(value2);
		}
	};
}

#endif
#ifndef DXNA_STRUCTS_HPP
#define DXNA_STRUCTS_HPP

#include "cs/cstypes.hpp"

namespace dxna {
	struct Point {
		intcs X{ 0 };
		intcs Y{ 0 };

		constexpr Point() = default;
		constexpr Point(intcs x, intcs y) :
			X(x), Y(y) {}

		static constexpr Point Zero() { return Point(); }

		bool constexpr Equals(Point const& other) const { return X == other.X && Y == other.Y; }

		constexpr Point operator-() const { return Point(-X, -Y); }

		constexpr bool operator==(Point const& other) const { return Equals(other); }
	};

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

		constexpr bool operator==(Rectangle const& value2) const {
			return Equals(value2);
		}
	};

	struct Matrix;
	struct Quaternion;

	struct Vector2 {
		float X{ 0 };
		float Y{ 0 };

		constexpr Vector2() = default;
		constexpr Vector2(float x, float y) : X(x), Y(y) {}
		constexpr Vector2(float value) : X(value), Y(value) {}

		constexpr Vector2 operator-() const { return Negate(*this); }
		constexpr bool operator==(Vector2 const& other) const { return Equals(other); }
		friend constexpr Vector2 operator+(Vector2 const& value1, Vector2 const& value2) { return Add(value1, value2); }
		friend constexpr Vector2 operator-(Vector2 const& value1, Vector2 const& value2) { return Subtract(value1, value2); }
		friend constexpr Vector2 operator*(Vector2 const& value1, Vector2 const& value2) { return Multiply(value1, value2); }
		friend constexpr Vector2 operator*(Vector2 const& value, float scale) { return Multiply(value, scale); }
		friend constexpr Vector2 operator*(float scale, Vector2 const& value) { return Multiply(value, scale); }
		friend constexpr Vector2 operator/(Vector2 const& value1, Vector2 const& value2) { return Divide(value1, value2); }
		friend constexpr Vector2 operator/(Vector2 const& value, float divider) { return Divide(value, divider); }
		
		constexpr bool Equals(Vector2 const& other) const { return X == other.X && Y == other.Y; }
		constexpr float LengthSquared() const { return X * X + Y * Y; }
		
		float Length() const;		
		void Normalize();

		static constexpr Vector2 Zero() { return Vector2(); }
		static constexpr Vector2 One() { return Vector2(1.0); }
		static constexpr Vector2 UnitX() { return Vector2(1.0, 0.0); }
		static constexpr Vector2 UnitY() { return Vector2(0.0, 1.0); }	
		
		static float Distance(Vector2 const& value1, Vector2 const& value2);

		static constexpr float DistanceSquared(Vector2 const& value1, Vector2 const& value2) {
			const auto num1 = value1.X - value2.X;
			const auto num2 = value1.Y - value2.Y;
			return num1 * num1 + num2 * num2;
		}

		static constexpr float Dot(Vector2 const& value1, Vector2 const& value2) {
			return value1.X * value2.X + value1.Y * value2.Y;
		}

		static constexpr Vector2 Reflect(Vector2 const& vector, Vector2 const& normal) {
			const auto num = vector.X * normal.X + vector.Y * normal.Y;
			return Vector2(
				vector.X - 2.0F * num * normal.X,
				vector.Y - 2.0F * num * normal.Y);
		}

		static constexpr Vector2 Min(Vector2 const& value1, Vector2 const& value2) {
			Vector2 vector2;
			vector2.X = value1.X < value2.X ? value1.X : value2.X;
			vector2.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
			return vector2;
		}

		static constexpr Vector2 Max(Vector2 const& value1, Vector2 const& value2) {
			Vector2 vector2;
			vector2.X = value1.X > value2.X ? value1.X : value2.X;
			vector2.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
			return vector2;
		}

		static constexpr Vector2 Clamp(Vector2 const& value1, Vector2 const& min, Vector2 const& max) {
			const auto x = value1.X;
			const auto num1 = x > max.X ? max.X : x;
			const auto num2 = num1 < min.X ? min.X : num1;
			const auto y = value1.Y;
			const auto num3 = y > max.Y ? max.Y : y;
			const auto num4 = num3 < min.Y ? min.Y : num3;
			Vector2 vector2;
			vector2.X = num2;
			vector2.Y = num4;
			return vector2;
		}

		static constexpr Vector2 Lerp(Vector2 const& value1, Vector2 const& value2, float amount) {
			Vector2 vector2;
			vector2.X = value1.X + (value2.X - value1.X) * amount;
			vector2.Y = value1.Y + (value2.Y - value1.Y) * amount;
			return vector2;
		}		

		static constexpr Vector2 Barycentric(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3,
			float amount1, float amount2) {
			Vector2 vector2;
			vector2.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
			vector2.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
			return vector2;
		}
		
		static constexpr Vector2 SmoothStep(Vector2 const& value1, Vector2 const& value2, float amount) {
			amount = amount > 1.0 ? 1.0F : (amount < 0.0 ? 0.0F : amount);
			amount = amount * amount * (3.0F - 2.0F * amount);
			Vector2 vector2;
			vector2.X = value1.X + (value2.X - value1.X) * amount;
			vector2.Y = value1.Y + (value2.Y - value1.Y) * amount;
			return vector2;
		}

		static constexpr Vector2 CatmullRom(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3,
			Vector2 const& value4, float amount) {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			Vector2 vector2;
			vector2.X = 0.5F * (2.0F * value2.X + (-value1.X + value3.X) * amount + (2.0F * value1.X - 5.0F * value2.X + 4.0F * value3.X - value4.X) * num1 + (-value1.X + 3.0F * value2.X - 3.0F * value3.X + value4.X) * num2);
			vector2.Y = 0.5F * (2.0F * value2.Y + (-value1.Y + value3.Y) * amount + (2.0F * value1.Y - 5.0F * value2.Y + 4.0F * value3.Y - value4.Y) * num1 + (-value1.Y + 3.0F * value2.Y - 3.0F * value3.Y + value4.Y) * num2);
			return vector2;
		}

		static constexpr Vector2 Hermite(Vector2 const& value1, Vector2 const& tangent1, Vector2 const& value2,
			Vector2 const& tangent2, float amount) {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			const auto num3 = (2.0F * num2 - 3.0F * num1 + 1.0F);
			const auto num4 = (-2.0F * num2 + 3.0F * num1);
			const auto num5 = num2 - 2.0F * num1 + amount;
			const auto num6 = num2 - num1;
			Vector2 vector2;
			vector2.X = (value1.X * num3 + value2.X * num4 + tangent1.X * num5 + tangent2.X * num6);
			vector2.Y = (value1.Y * num3 + value2.Y * num4 + tangent1.Y * num5 + tangent2.Y * num6);
			return vector2;
		}

		static constexpr Vector2 Negate(Vector2 const& value) {
			Vector2 vector2;
			vector2.X = -value.X;
			vector2.Y = -value.Y;
			return vector2;
		}

		static constexpr Vector2 Add(Vector2 const& value1, Vector2 const& value2) {
			Vector2 vector2;
			vector2.X = value1.X + value2.X;
			vector2.Y = value1.Y + value2.Y;
			return vector2;
		}

		static constexpr Vector2 Subtract(Vector2 const& value1, Vector2 const& value2) {
			Vector2 vector2;
			vector2.X = value1.X - value2.X;
			vector2.Y = value1.Y - value2.Y;
			return vector2;
		}

		static constexpr Vector2 Multiply(Vector2 const& value1, Vector2 const& value2) {
			Vector2 vector2;
			vector2.X = value1.X * value2.X;
			vector2.Y = value1.Y * value2.Y;
			return vector2;
		}

		static constexpr Vector2 Multiply(Vector2 const& value1, float scaleFactor) {
			Vector2 vector2;
			vector2.X = value1.X * scaleFactor;
			vector2.Y = value1.Y * scaleFactor;
			return vector2;
		}

		static constexpr Vector2 Divide(Vector2 const& value1, Vector2 const& value2) {
			Vector2 vector2;
			vector2.X = value1.X / value2.X;
			vector2.Y = value1.Y / value2.Y;
			return vector2;
		}

		static constexpr Vector2 Divide(Vector2 const& value1, float divider) {
			const auto num = 1.0F / divider;
			Vector2 vector2;
			vector2.X = value1.X * num;
			vector2.Y = value1.Y * num;
			return vector2;
		}

		static Vector2 Transform(Vector2 const& position, Matrix const& matrix);
		static Vector2 TransformNormal(Vector2 const& normal, Matrix const& matrix);
		static Vector2 Transform(Vector2 const& value, Quaternion const& rotation);

		static void Transform(Vector2 *sourceArray, Matrix matrix,
			Vector2 *destinationArray, size_t length, size_t sourceIndex = 0,
			size_t destinationIndex = 0);

		static void Transform(Vector2* sourceArray, Quaternion rotation,
			Vector2* destinationArray, size_t length, size_t sourceIndex = 0,
			size_t destinationIndex = 0);

		static void TransformNormal(Vector2* sourceArray, Matrix const& matrix,
			Vector2* destinationArray, size_t length, size_t sourceIndex = 0,
			size_t destinationIndex = 0);	
	};
}

#endif
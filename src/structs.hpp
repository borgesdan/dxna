#ifndef DXNA_STRUCTS_HPP
#define DXNA_STRUCTS_HPP

#include "cs/cs.hpp"
#include <vector>
#include "enumerations.hpp"
#include "mathhelper.hpp"

namespace dxna {
	struct Matrix;
	struct Quaternion;
	struct Plane;
	struct BoundingSphere;
	struct BoundingFrustum;
	struct Ray;

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

	struct Vector2 {
		float X{ 0 };
		float Y{ 0 };

		constexpr Vector2() = default;
		constexpr Vector2(float x, float y) : X(x), Y(y) {}
		constexpr Vector2(float value) : X(value), Y(value) {}

		constexpr Vector2 operator-() const { return Vector2::Negate(*this); }
		constexpr bool operator==(Vector2 const& other) const { return Equals(other); }
		friend constexpr Vector2 operator+(Vector2 const& value1, Vector2 const& value2) { return Vector2::Add(value1, value2); }
		friend constexpr Vector2 operator-(Vector2 const& value1, Vector2 const& value2) { return Vector2::Subtract(value1, value2); }
		friend constexpr Vector2 operator*(Vector2 const& value1, Vector2 const& value2) { return Vector2::Multiply(value1, value2); }
		friend constexpr Vector2 operator*(Vector2 const& value, float scale) { return Vector2::Multiply(value, scale); }
		friend constexpr Vector2 operator*(float scale, Vector2 const& value) { return Vector2::Multiply(value, scale); }
		friend constexpr Vector2 operator/(Vector2 const& value1, Vector2 const& value2) { return Vector2::Divide(value1, value2); }
		friend constexpr Vector2 operator/(Vector2 const& value, float divider) { return Vector2::Divide(value, divider); }

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

		static constexpr Vector2 lect(Vector2 const& vector, Vector2 const& normal) {
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

		static Vector2 Normalize(Vector2 const& value);

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

		static constexpr Vector2 Transform(Vector2 const& position, Matrix const& matrix);
		static constexpr Vector2 TransformNormal(Vector2 const& normal, Matrix const& matrix);
		static constexpr Vector2 Transform(Vector2 const& value, Quaternion const& rotation);

		static constexpr void Transform(Vector2* sourceArray, Matrix matrix,
			Vector2* destinationArray, size_t length, size_t sourceIndex = 0,
			size_t destinationIndex = 0);

		static constexpr void Transform(Vector2* sourceArray, Quaternion rotation,
			Vector2* destinationArray, size_t length, size_t sourceIndex = 0,
			size_t destinationIndex = 0);

		static constexpr void TransformNormal(Vector2* sourceArray, Matrix const& matrix,
			Vector2* destinationArray, size_t length, size_t sourceIndex = 0,
			size_t destinationIndex = 0);
	};

	struct Vector3 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };

		constexpr Vector3() {}
		constexpr Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
		constexpr Vector3(float value) : X(value), Y(value), Z(value) {}
		constexpr Vector3(Vector2 const& value, float z) : X(value.X), Y(value.Y), Z(z) {}

		constexpr Vector3 operator-() const { return Vector3::Negate(*this); }
		constexpr bool operator==(Vector3 const& other) const { return Equals(other); }
		friend constexpr Vector3 operator+(Vector3 const& value1, Vector3 const& value2) { return Vector3::Add(value1, value2); }
		friend constexpr Vector3 operator-(Vector3 const& value1, Vector3 const& value2) { return Vector3::Subtract(value1, value2); }
		friend constexpr Vector3 operator*(Vector3 const& value1, Vector3 const& value2) { return Vector3::Multiply(value1, value2); }
		friend constexpr Vector3 operator*(Vector3 const& value, float scale) { return Vector3::Multiply(value, scale); }
		friend constexpr Vector3 operator*(float scale, Vector3 const& value) { return Vector3::Multiply(value, scale); }
		friend constexpr Vector3 operator/(Vector3 const& value1, Vector3 const& value2) { return Vector3::Divide(value1, value2); }
		friend constexpr Vector3 operator/(Vector3 const& value, float divider) { return Vector3::Divide(value, divider); }

		constexpr Vector3 operator+=(Vector3 const& other) const { return Vector3::Add(*this, other); }
		constexpr Vector3 operator-=(Vector3 const& other) const { return Vector3::Subtract(*this, other); }
		constexpr Vector3 operator*=(Vector3 const& other) const { return Vector3::Multiply(*this, other); }
		constexpr Vector3 operator/=(Vector3 const& other) const { return Vector3::Divide(*this, other); }


		float Length() const;
		void Normalize();

		constexpr bool Equals(const Vector3& other) const { return X == other.X && Y == other.Y && Z == other.Z; }
		constexpr float LengthSquared() const { return (X * X) + (Y * Y) + (Z * Z); }

		static constexpr Vector3 Zero() { return Vector3(); };
		static constexpr Vector3 One() { return Vector3(1.F, 1.F, 1.F); }
		static constexpr Vector3 UnitX() { return Vector3(1.0F, 0.0, 0.0); }
		static constexpr Vector3 UnitY() { return Vector3(0.0, 1.0F, 0.0); }
		static constexpr Vector3 UnitZ() { return Vector3(0.0, 0.0, 1.0F); }
		static constexpr Vector3 Up() { return UnitY(); }
		static constexpr Vector3 Down() { return -UnitY(); }
		static constexpr Vector3 Right() { return UnitX(); }
		static constexpr Vector3 Left() { { return -UnitX(); } }
		static constexpr Vector3 Forward() { return -UnitZ(); }
		static constexpr Vector3 Backward() { return UnitZ(); }

		static float Distance(Vector3 const& value1, Vector3 const& value2);

		static constexpr float DistanceSquared(Vector3 const& value1, Vector3 const& value2) {
			const auto num1 = value1.X - value2.X;
			const auto num2 = value1.Y - value2.Y;
			const auto num3 = value1.Z - value2.Z;
			return num1 * num1 + num2 * num2 + num3 * num3;
		}

		static constexpr float Dot(Vector3 const& vector1, Vector3 const& vector2) {
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z;
		}

		static constexpr Vector3 Cross(Vector3 const& vector1, Vector3 const& vector2) {
			Vector3 vector3;
			vector3.X = vector1.Y * vector2.Z - vector1.Z * vector2.Y;
			vector3.Y = vector1.Z * vector2.X - vector1.X * vector2.Z;
			vector3.Z = vector1.X * vector2.Y - vector1.Y * vector2.X;
			return vector3;
		}

		static constexpr Vector3 lect(Vector3 const& vector, Vector3 const& normal) {
			const auto num = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;
			Vector3 vector3;
			vector3.X = vector.X - 2.0F * num * normal.X;
			vector3.Y = vector.Y - 2.0F * num * normal.Y;
			vector3.Z = vector.Z - 2.0F * num * normal.Z;
			return vector3;
		}

		static constexpr Vector3 Min(Vector3 const& value1, Vector3 const& value2) {
			Vector3 vector3;
			vector3.X = value1.X < value2.X ? value1.X : value2.X;
			vector3.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
			vector3.Z = value1.Z < value2.Z ? value1.Z : value2.Z;
			return vector3;
		}

		static constexpr Vector3 Max(Vector3 const& value1, Vector3 const& value2) {
			Vector3 vector3;
			vector3.X = value1.X > value2.X ? value1.X : value2.X;
			vector3.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
			vector3.Z = value1.Z > value2.Z ? value1.Z : value2.Z;
			return vector3;
		}

		static constexpr Vector3 Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max) {
			const auto x = value1.X;
			const auto num1 = x > max.X ? max.X : x;
			const auto num2 = num1 < min.X ? min.X : num1;
			const auto y = value1.Y;
			const auto num3 = y > max.Y ? max.Y : y;
			const auto num4 = num3 < min.Y ? min.Y : num3;
			const auto z = value1.Z;
			const auto num5 = z > max.Z ? max.Z : z;
			const auto num6 = num5 < min.Z ? min.Z : num5;
			Vector3 vector3;
			vector3.X = num2;
			vector3.Y = num4;
			vector3.Z = num6;
			return vector3;
		}

		static constexpr Vector3 Lerp(Vector3 const& value1, Vector3 const& value2, float amount) {
			Vector3 vector3;
			vector3.X = value1.X + (value2.X - value1.X) * amount;
			vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;
			return vector3;
		}

		static constexpr Vector3 Barycentric(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3,
			float amount1, float amount2) {
			Vector3 vector3;
			vector3.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
			vector3.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
			vector3.Z = value1.Z + amount1 * (value2.Z - value1.Z) + amount2 * (value3.Z - value1.Z);
			return vector3;
		}

		static constexpr Vector3 SmoothStep(Vector3 const& value1, Vector3 const& value2, float amount) {
			amount = amount > 1.0F ? 1.0F : (amount < 0.0 ? 0.0F : amount);
			amount = amount * amount * (3.0F - 2.0F * amount);
			Vector3 vector3;
			vector3.X = value1.X + (value2.X - value1.X) * amount;
			vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;
			return vector3;
		}
		static constexpr Vector3 CatmullRom(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3,
			Vector3 const& value4, float amount) {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			Vector3 vector3;
			vector3.X = (0.5F * (2.0F * value2.X + (-value1.X + value3.X) * amount + (2.0F * value1.X - 5.0F * value2.X + 4.0F * value3.X - value4.X) * num1 + (-value1.X + 3.0F * value2.X - 3.0F * value3.X + value4.X) * num2));
			vector3.Y = (0.5F * (2.0F * value2.Y + (-value1.Y + value3.Y) * amount + (2.0F * value1.Y - 5.0F * value2.Y + 4.0F * value3.Y - value4.Y) * num1 + (-value1.Y + 3.0F * value2.Y - 3.0F * value3.Y + value4.Y) * num2));
			vector3.Z = (0.5F * (2.0F * value2.Z + (-value1.Z + value3.Z) * amount + (2.0F * value1.Z - 5.0F * value2.Z + 4.0F * value3.Z - value4.Z) * num1 + (-value1.Z + 3.0F * value2.Z - 3.0F * value3.Z + value4.Z) * num2));
			return vector3;
		}

		static constexpr Vector3 Hermite(Vector3 const& value1, Vector3 const& tangent1, Vector3 const& value2,
			Vector3 const& tangent2, float amount) {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			const auto num3 = 2.0F * num2 - 3.0F * num1 + 1.0F;
			const auto num4 = -2.0F * num2 + 3.0F * num1;
			const auto num5 = num2 - 2.0F * num1 + amount;
			const auto num6 = num2 - num1;
			Vector3 vector3;
			vector3.X = value1.X * num3 + value2.X * num4 + tangent1.X * num5 + tangent2.X * num6;
			vector3.Y = value1.Y * num3 + value2.Y * num4 + tangent1.Y * num5 + tangent2.Y * num6;
			vector3.Z = value1.Z * num3 + value2.Z * num4 + tangent1.Z * num5 + tangent2.Z * num6;
			return vector3;
		}

		static Vector3 Normalize(Vector3 const& value);

		static constexpr Vector3 Negate(Vector3 const& value) {
			Vector3 vector;
			vector.X = -value.X;
			vector.Y = -value.Y;
			vector.Z = -value.Z;
			return vector;
		}

		static constexpr Vector3 Add(Vector3 const& value1, Vector3 const& value2) {
			Vector3 vector3;
			vector3.X = value1.X + value2.X;
			vector3.Y = value1.Y + value2.Y;
			vector3.Z = value1.Z + value2.Z;
			return vector3;
		}

		static constexpr Vector3 Subtract(Vector3 const& value1, Vector3 const& value2) {
			Vector3 vector3;
			vector3.X = value1.X - value2.X;
			vector3.Y = value1.Y - value2.Y;
			vector3.Z = value1.Z - value2.Z;
			return vector3;
		}

		static constexpr Vector3 Multiply(Vector3 const& value1, Vector3 const& value2) {
			Vector3 vector3;
			vector3.X = value1.X * value2.X;
			vector3.Y = value1.Y * value2.Y;
			vector3.Z = value1.Z * value2.Z;
			return vector3;
		}

		static constexpr Vector3 Multiply(Vector3 const& value1, float scaleFactor) {
			Vector3 vector3;
			vector3.X = value1.X * scaleFactor;
			vector3.Y = value1.Y * scaleFactor;
			vector3.Z = value1.Z * scaleFactor;
			return vector3;
		}

		static constexpr Vector3 Divide(Vector3 const& value1, Vector3 const& value2) {
			Vector3 vector3;
			vector3.X = value1.X / value2.X;
			vector3.Y = value1.Y / value2.Y;
			vector3.Z = value1.Z / value2.Z;
			return vector3;
		}

		static constexpr Vector3 Divide(Vector3 const& value1, float value2) {
			float num = 1.0F / value2;
			Vector3 vector3;
			vector3.X = value1.X * num;
			vector3.Y = value1.Y * num;
			vector3.Z = value1.Z * num;
			return vector3;
		}

		static constexpr Vector3 Transform(Vector3 const& position, Matrix const& matrix);
		static constexpr Vector3 TransformNormal(Vector3 const& normal, Matrix const& matrix);
		static constexpr Vector3 Transform(Vector3 const& value, Quaternion const& rotation);
		static constexpr void Transform(Vector3* sourceArray, Matrix const& matrix,
			Vector3* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
		static constexpr void TransformNormal(Vector3* sourceArray, Matrix const& matrix,
			Vector3* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
		static constexpr void Transform(Vector3* sourceArray, Quaternion const& rotation,
			Vector3* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
	};

	struct Vector4 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		constexpr Vector4() = default;
		constexpr Vector4(float value) :
			X(value), Y(value), Z(value), W(value) {}
		constexpr Vector4(float x, float y, float z, float w) :
			X(x), Y(y), Z(z), W(w) {}
		constexpr Vector4(Vector2 value, float z, float w) :
			X(value.X), Y(value.Y), Z(z), W(w) {}
		constexpr Vector4(Vector3 value, float w) :
			X(value.X), Y(value.Y), Z(value.Z), W(w) {}

		constexpr Vector4 operator-() const { return Vector4::Negate(*this); }
		constexpr bool operator==(Vector4 const& other) const { return Equals(other); }
		friend constexpr Vector4 operator+(Vector4 const& value1, Vector4 const& value2) { return Vector4::Add(value1, value2); }
		friend constexpr Vector4 operator-(Vector4 const& value1, Vector4 const& value2) { return Vector4::Subtract(value1, value2); }
		friend constexpr Vector4 operator*(Vector4 const& value1, Vector4 const& value2) { return Vector4::Multiply(value1, value2); }
		friend constexpr Vector4 operator*(Vector4 const& value, float scale) { return Vector4::Multiply(value, scale); }
		friend constexpr Vector4 operator*(float scale, Vector4 const& value) { return Vector4::Multiply(value, scale); }
		friend constexpr Vector4 operator/(Vector4 const& value1, Vector4 const& value2) { return Vector4::Divide(value1, value2); }
		friend constexpr Vector4 operator/(Vector4 const& value, float divider) { return Vector4::Divide(value, divider); }

		float Length() const;
		void Normalize();

		constexpr float LengthSquared() const {
			return (X * X) + (Y * Y) + (Z * Z) + (W * W);
		}

		constexpr bool Equals(Vector4 const& other) const {
			return X == other.X
				&& Y == other.Y
				&& Z == other.Z
				&& W == other.W;
		}

		static constexpr Vector4 Zero() { return Vector4(); }
		static constexpr Vector4 One() { return Vector4(1); }
		static constexpr Vector4 UnitX() { return Vector4(1.0F, 0.0F, 0.0F, 0.0F); }
		static constexpr Vector4 UnitY() { return Vector4(0.0F, 1.0F, 0.0F, 0.0F); }
		static constexpr Vector4 UnitZ() { return Vector4(0.0F, 0.0F, 1.0F, 0.0F); }
		static constexpr Vector4 UnitW() { return Vector4(0.0F, 0.0F, 0.0F, 1.0F); }

		static float Distance(Vector4 const& value1, Vector4 const& value2);

		static constexpr float DistanceSquared(Vector4 value1, Vector4 value2)
		{
			const auto num1 = value1.X - value2.X;
			const auto num2 = value1.Y - value2.Y;
			const auto num3 = value1.Z - value2.Z;
			const auto num4 = value1.W - value2.W;
			return num1 * num1 + num2 * num2 + num3 * num3 + num4 * num4;
		}

		static constexpr float Dot(Vector4 vector1, Vector4 vector2) {
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z + vector1.W * vector2.W;
		}

		static constexpr Vector4 Min(Vector4 const& value1, Vector4 const& value2) {
			Vector4 vector4;
			vector4.X = value1.X < value2.X ? value1.X : value2.X;
			vector4.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
			vector4.Z = value1.Z < value2.Z ? value1.Z : value2.Z;
			vector4.W = value1.W < value2.W ? value1.W : value2.W;
			return vector4;
		}

		static constexpr Vector4 Max(Vector4 const& value1, Vector4 const& value2) {
			Vector4 vector4;
			vector4.X = value1.X > value2.X ? value1.X : value2.X;
			vector4.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
			vector4.Z = value1.Z > value2.Z ? value1.Z : value2.Z;
			vector4.W = value1.W > value2.W ? value1.W : value2.W;
			return vector4;
		}

		static constexpr Vector4 Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max) {
			const auto x = value1.X;
			const auto num1 = x > max.X ? max.X : x;
			const auto num2 = num1 < min.X ? min.X : num1;
			const auto y = value1.Y;
			const auto num3 = y > max.Y ? max.Y : y;
			const auto num4 = num3 < min.Y ? min.Y : num3;
			const auto z = value1.Z;
			const auto num5 = z > max.Z ? max.Z : z;
			const auto num6 = num5 < min.Z ? min.Z : num5;
			const auto w = value1.W;
			const auto num7 = w > max.W ? max.W : w;
			const auto num8 = num7 < min.W ? min.W : num7;
			Vector4 vector4;
			vector4.X = num2;
			vector4.Y = num4;
			vector4.Z = num6;
			vector4.W = num8;
			return vector4;
		}

		static constexpr Vector4 Lerp(Vector4 const& value1, Vector4 const& value2, float amount) {
			Vector4 vector4;
			vector4.X = value1.X + (value2.X - value1.X) * amount;
			vector4.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector4.Z = value1.Z + (value2.Z - value1.Z) * amount;
			vector4.W = value1.W + (value2.W - value1.W) * amount;
			return vector4;
		}

		static constexpr Vector4 Barycentric(Vector4 const& value1, Vector4 const& value2,
			Vector4 const& value3, float amount1, float amount2) {
			Vector4 vector4;
			vector4.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
			vector4.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
			vector4.Z = value1.Z + amount1 * (value2.Z - value1.Z) + amount2 * (value3.Z - value1.Z);
			vector4.W = value1.W + amount1 * (value2.W - value1.W) + amount2 * (value3.W - value1.W);
			return vector4;
		}

		static constexpr Vector4 SmoothStep(Vector4 const& value1, Vector4 const& value2, float amount) {
			amount = amount > 1.0F ? 1.0F : (amount < 0.0F ? 0.0F : amount);
			amount = amount * amount * (3.0F - 2.0F * amount);
			Vector4 vector4;
			vector4.X = value1.X + (value2.X - value1.X) * amount;
			vector4.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector4.Z = value1.Z + (value2.Z - value1.Z) * amount;
			vector4.W = value1.W + (value2.W - value1.W) * amount;
			return vector4;
		}

		static constexpr Vector4 CatmullRom(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3,
			Vector4 const& value4, float amount) {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			Vector4 vector4;
			vector4.X = 0.5F * (2.0F * value2.X + (-value1.X + value3.X) * amount + (2.0F * value1.X - 5.0F * value2.X + 4.0F * value3.X - value4.X) * num1 + (-value1.X + 3.0F * value2.X - 3.0F * value3.X + value4.X) * num2);
			vector4.Y = 0.5F * (2.0F * value2.Y + (-value1.Y + value3.Y) * amount + (2.0F * value1.Y - 5.0F * value2.Y + 4.0F * value3.Y - value4.Y) * num1 + (-value1.Y + 3.0F * value2.Y - 3.0F * value3.Y + value4.Y) * num2);
			vector4.Z = 0.5F * (2.0F * value2.Z + (-value1.Z + value3.Z) * amount + (2.0F * value1.Z - 5.0F * value2.Z + 4.0F * value3.Z - value4.Z) * num1 + (-value1.Z + 3.0F * value2.Z - 3.0F * value3.Z + value4.Z) * num2);
			vector4.W = 0.5F * (2.0F * value2.W + (-value1.W + value3.W) * amount + (2.0F * value1.W - 5.0F * value2.W + 4.0F * value3.W - value4.W) * num1 + (-value1.W + 3.0F * value2.W - 3.0F * value3.W + value4.W) * num2);
			return vector4;
		}

		static constexpr Vector4 Hermite(Vector4 const& value1, Vector4 const& tangent1, Vector4 const& value2,
			Vector4 const& tangent2, float amount) {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			const auto num3 = 2.0F * num2 - 3.0F * num1 + 1.0F;
			const auto num4 = -2.0F * num2 + 3.0F * num1;
			const auto num5 = num2 - 2.0F * num1 + amount;
			const auto num6 = num2 - num1;
			Vector4 vector4;
			vector4.X = (value1.X * num3 + value2.X * num4 + tangent1.X * num5 + tangent2.X * num6);
			vector4.Y = (value1.Y * num3 + value2.Y * num4 + tangent1.Y * num5 + tangent2.Y * num6);
			vector4.Z = (value1.Z * num3 + value2.Z * num4 + tangent1.Z * num5 + tangent2.Z * num6);
			vector4.W = (value1.W * num3 + value2.W * num4 + tangent1.W * num5 + tangent2.W * num6);
			return vector4;
		}

		static Vector4 Normalize(Vector4 const& value);

		static constexpr Vector4 Negate(Vector4 const& value) {
			Vector4 vector4;
			vector4.X = -value.X;
			vector4.Y = -value.Y;
			vector4.Z = -value.Z;
			vector4.W = -value.W;
			return vector4;
		}

		static constexpr Vector4 Add(Vector4 const& value1, Vector4 const& value2) {
			Vector4 vector4;
			vector4.X = value1.X + value2.X;
			vector4.Y = value1.Y + value2.Y;
			vector4.Z = value1.Z + value2.Z;
			vector4.W = value1.W + value2.W;
			return vector4;
		}

		static constexpr Vector4 Subtract(Vector4 const& value1, Vector4 const& value2) {
			Vector4 vector4;
			vector4.X = value1.X - value2.X;
			vector4.Y = value1.Y - value2.Y;
			vector4.Z = value1.Z - value2.Z;
			vector4.W = value1.W - value2.W;
			return vector4;
		}

		static constexpr Vector4 Multiply(Vector4 const& value1, Vector4 const& value2) {
			Vector4 vector4;
			vector4.X = value1.X * value2.X;
			vector4.Y = value1.Y * value2.Y;
			vector4.Z = value1.Z * value2.Z;
			vector4.W = value1.W * value2.W;
			return vector4;
		}

		static constexpr Vector4 Multiply(Vector4 const& value1, float scaleFactor) {
			Vector4 vector4;
			vector4.X = value1.X * scaleFactor;
			vector4.Y = value1.Y * scaleFactor;
			vector4.Z = value1.Z * scaleFactor;
			vector4.W = value1.W * scaleFactor;
			return vector4;
		}

		static constexpr Vector4 Divide(Vector4 const& value1, Vector4 const& value2) {
			Vector4 vector4;
			vector4.X = value1.X / value2.X;
			vector4.Y = value1.Y / value2.Y;
			vector4.Z = value1.Z / value2.Z;
			vector4.W = value1.W / value2.W;
			return vector4;
		}

		static constexpr Vector4 Divide(Vector4 const& value1, float divider) {
			float num = 1.0F / divider;
			Vector4 vector4;
			vector4.X = value1.X * num;
			vector4.Y = value1.Y * num;
			vector4.Z = value1.Z * num;
			vector4.W = value1.W * num;
			return vector4;
		}

		static constexpr Vector4 Transform(Vector2 const& position, Matrix const& matrix);
		static constexpr Vector4 Transform(Vector3 const& position, Matrix const& matrix);
		static constexpr Vector4 Transform(Vector4 const& vector, Matrix const& matrix);
		static constexpr Vector4 Transform(Vector2 const& value, Quaternion const& rotation);
		static constexpr Vector4 Transform(Vector3 const& position, Quaternion const& rotation);
		static constexpr Vector4 Transform(Vector4 const& vector, Quaternion const& rotation);

		static constexpr void Transform(Vector4* sourceArray, Matrix const& matrix,
			Vector4* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
		static constexpr void Transform(Vector4* sourceArray, Quaternion const& rotation,
			Vector4* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex);
	};

	struct Matrix {
		float M11{ 0 };
		float M12{ 0 };
		float M13{ 0 };
		float M14{ 0 };
		float M21{ 0 };
		float M22{ 0 };
		float M23{ 0 };
		float M24{ 0 };
		float M31{ 0 };
		float M32{ 0 };
		float M33{ 0 };
		float M34{ 0 };
		float M41{ 0 };
		float M42{ 0 };
		float M43{ 0 };
		float M44{ 0 };

		constexpr Matrix() = default;

		constexpr Matrix(float M11, float M12, float M13, float M14, float M21, float M22, float M23, float M24, float M31, float M32, float M33, float M34, float M41, float M42, float M43, float M44)
			: M11(M11), M12(M12), M13(M13), M14(M14), M21(M21), M22(M22), M23(M23), M24(M24), M31(M31), M32(M32), M33(M33), M34(M34), M41(M41), M42(M42), M43(M43), M44(M44) {
		}

		constexpr Matrix operator-() const { return Matrix::Negate(*this); }
		constexpr bool operator==(Matrix const& other) const { return Equals(other); }
		friend constexpr Matrix operator+(Matrix const& value1, Matrix const& value2) { return Matrix::Add(value1, value2); }
		friend constexpr Matrix operator-(Matrix const& value1, Matrix const& value2) { return Matrix::Subtract(value1, value2); }
		friend constexpr Matrix operator*(Matrix const& value1, Matrix const& value2) { return Matrix::Multiply(value1, value2); }
		friend constexpr Matrix operator*(Matrix const& value, float scale) { return Matrix::Multiply(value, scale); }
		friend constexpr Matrix operator*(float scale, Matrix const& value) { return Matrix::Multiply(value, scale); }
		friend constexpr Matrix operator/(Matrix const& value1, Matrix const& value2) { return Matrix::Divide(value1, value2); }
		friend constexpr Matrix operator/(Matrix const& value, float divider) { return Matrix::Divide(value, divider); }


		constexpr Vector3 Up() const {
			Vector3 up;
			up.X = M21;
			up.Y = M22;
			up.Z = M23;
			return up;
		}

		constexpr Vector3 Down() const {
			Vector3 down;
			down.X = -M21;
			down.Y = -M22;
			down.Z = -M23;
			return down;
		}

		constexpr Vector3 Right() const {
			Vector3 right;
			right.X = M11;
			right.Y = M12;
			right.Z = M13;
			return right;
		}

		constexpr Vector3 Left() const {
			Vector3 left;
			left.X = -M11;
			left.Y = -M12;
			left.Z = -M13;
			return left;
		}

		constexpr Vector3 Forward() const {
			Vector3 forward;
			forward.X = -M31;
			forward.Y = -M32;
			forward.Z = -M33;
			return forward;
		}

		constexpr Vector3 Backward() const {
			Vector3 backward;
			backward.X = M31;
			backward.Y = M32;
			backward.Z = M33;
			return backward;
		}

		constexpr Vector3 Translation() const {
			Vector3 translation;
			translation.X = M41;
			translation.Y = M42;
			translation.Z = M43;
			return translation;
		}

		constexpr void Up(Vector3 const& value) {
			M21 = value.X;
			M22 = value.Y;
			M23 = value.Z;
		}

		constexpr void Down(Vector3 const& value) {
			M21 = -value.X;
			M22 = -value.Y;
			M23 = -value.Z;
		}

		constexpr void Right(Vector3 const& value) {
			M11 = value.X;
			M12 = value.Y;
			M13 = value.Z;
		}

		constexpr void Left(Vector3 const& value) {
			M11 = -value.X;
			M12 = -value.Y;
			M13 = -value.Z;
		}

		constexpr void Forward(Vector3 const& value) {
			M31 = -value.X;
			M32 = -value.Y;
			M33 = -value.Z;
		}

		constexpr void Backward(Vector3 const& value) {
			M31 = value.X;
			M32 = value.Y;
			M33 = value.Z;
		}

		constexpr void Translation(Vector3 const& value) {
			M41 = value.X;
			M42 = value.Y;
			M43 = value.Z;
		}

		constexpr bool Equals(Matrix const& other) const {
			return M11 == other.M11
				&& M22 == other.M22
				&& M33 == other.M33
				&& M44 == other.M44
				&& M12 == other.M12
				&& M13 == other.M13
				&& M14 == other.M14
				&& M21 == other.M21
				&& M23 == other.M23
				&& M24 == other.M24
				&& M31 == other.M31
				&& M32 == other.M32
				&& M34 == other.M34
				&& M41 == other.M41
				&& M42 == other.M42
				&& M43 == other.M43;
		}

		constexpr float Determinant() const {
			float m11 = M11;
			float m12 = M12;
			float m13 = M13;
			float m14 = M14;
			float m21 = M21;
			float m22 = M22;
			float m23 = M23;
			float m24 = M24;
			float m31 = M31;
			float m32 = M32;
			float m33 = M33;
			float m34 = M34;
			float m41 = M41;
			float m42 = M42;
			float m43 = M43;
			float m44 = M44;
			float num1 = m33 * m44 - m34 * m43;
			float num2 = m32 * m44 - m34 * m42;
			float num3 = m32 * m43 - m33 * m42;
			float num4 = m31 * m44 - m34 * m41;
			float num5 = m31 * m43 - m33 * m41;
			float num6 = m31 * m42 - m32 * m41;
			return (m11 * (m22 * num1 - m23 * num2 + m24 * num3) - m12 * (m21 * num1 - m23 * num4 + m24 * num5) + m13 * (m21 * num2 - m22 * num4 + m24 * num6) - m14 * (m21 * num3 - m22 * num5 + m23 * num6));
		}

		static constexpr Matrix Identity() {
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		static Matrix CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 const& cameraUpVector, Vector3* const cameraForwardVector = nullptr);

		static Matrix CreateConstrainedBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 rotateAxis, Vector3* const cameraForwardVector, Vector3* const objectForwardVector);

		static constexpr Matrix CreateTranslation(Vector3 const& position) {
			Matrix translation;
			translation.M11 = 1.0f;
			translation.M12 = 0.0f;
			translation.M13 = 0.0f;
			translation.M14 = 0.0f;
			translation.M21 = 0.0f;
			translation.M22 = 1.0f;
			translation.M23 = 0.0f;
			translation.M24 = 0.0f;
			translation.M31 = 0.0f;
			translation.M32 = 0.0f;
			translation.M33 = 1.0f;
			translation.M34 = 0.0f;
			translation.M41 = position.X;
			translation.M42 = position.Y;
			translation.M43 = position.Z;
			translation.M44 = 1.0f;
			return translation;
		}

		static constexpr Matrix CreateTranslation(float xPosition, float yPosition, float zPosition) {
			Matrix translation;
			translation.M11 = 1.0f;
			translation.M12 = 0.0f;
			translation.M13 = 0.0f;
			translation.M14 = 0.0f;
			translation.M21 = 0.0f;
			translation.M22 = 1.0f;
			translation.M23 = 0.0f;
			translation.M24 = 0.0f;
			translation.M31 = 0.0f;
			translation.M32 = 0.0f;
			translation.M33 = 1.0f;
			translation.M34 = 0.0f;
			translation.M41 = xPosition;
			translation.M42 = yPosition;
			translation.M43 = zPosition;
			translation.M44 = 1.0f;
			return translation;
		}

		static constexpr Matrix CreateScale(float xScale, float yScale, float zScale) {
			const auto num1 = xScale;
			const auto num2 = yScale;
			const auto num3 = zScale;

			Matrix scale;
			scale.M11 = num1;
			scale.M12 = 0.0f;
			scale.M13 = 0.0f;
			scale.M14 = 0.0f;
			scale.M21 = 0.0f;
			scale.M22 = num2;
			scale.M23 = 0.0f;
			scale.M24 = 0.0f;
			scale.M31 = 0.0f;
			scale.M32 = 0.0f;
			scale.M33 = num3;
			scale.M34 = 0.0f;
			scale.M41 = 0.0f;
			scale.M42 = 0.0f;
			scale.M43 = 0.0f;
			scale.M44 = 1.0f;
			return scale;
		}

		static constexpr Matrix CreateScale(Vector3 const& scales) {
			const auto x = scales.X;
			const auto y = scales.Y;
			const auto z = scales.Z;

			Matrix scale;
			scale.M11 = x;
			scale.M12 = 0.0f;
			scale.M13 = 0.0f;
			scale.M14 = 0.0f;
			scale.M21 = 0.0f;
			scale.M22 = y;
			scale.M23 = 0.0f;
			scale.M24 = 0.0f;
			scale.M31 = 0.0f;
			scale.M32 = 0.0f;
			scale.M33 = z;
			scale.M34 = 0.0f;
			scale.M41 = 0.0f;
			scale.M42 = 0.0f;
			scale.M43 = 0.0f;
			scale.M44 = 1.0f;
			return scale;
		}

		static constexpr Matrix CreateScale(float scale) {
			const auto num = scale;

			Matrix scale1;
			scale1.M11 = num;
			scale1.M12 = 0.0f;
			scale1.M13 = 0.0f;
			scale1.M14 = 0.0f;
			scale1.M21 = 0.0f;
			scale1.M22 = num;
			scale1.M23 = 0.0f;
			scale1.M24 = 0.0f;
			scale1.M31 = 0.0f;
			scale1.M32 = 0.0f;
			scale1.M33 = num;
			scale1.M34 = 0.0f;
			scale1.M41 = 0.0f;
			scale1.M42 = 0.0f;
			scale1.M43 = 0.0f;
			scale1.M44 = 1.0f;
			return scale1;
		}

		static Matrix CreateRotationX(float radians);
		static Matrix CreateRotationY(float radians);
		static Matrix CreateRotationZ(float radians);
		static Matrix CreateFromAxisAngle(Vector3 const& axis, float angle);
		static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

		static constexpr Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance) {
			const Matrix zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

			if (nearPlaneDistance <= 0.0F)
				return zero;

			if (farPlaneDistance <= 0.0F)
				return zero;

			if (nearPlaneDistance >= farPlaneDistance)
				return zero;

			Matrix perspective;
			perspective.M11 = 2.0f * nearPlaneDistance / width;
			perspective.M12 = perspective.M13 = perspective.M14 = 0.0f;
			perspective.M22 = 2.0f * nearPlaneDistance / height;
			perspective.M21 = perspective.M23 = perspective.M24 = 0.0f;
			perspective.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
			perspective.M31 = perspective.M32 = 0.0f;
			perspective.M34 = -1.0f;
			perspective.M41 = perspective.M42 = perspective.M44 = 0.0f;
			perspective.M43 = nearPlaneDistance * farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
			return perspective;
		}

		static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom,
			float top, float nearPlaneDistance, float farPlaneDistance) {
			const Matrix zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

			if (nearPlaneDistance <= 0.0F)
				return zero;

			if (farPlaneDistance <= 0.0F)
				return zero;

			if (nearPlaneDistance >= farPlaneDistance)
				return zero;

			Matrix perspectiveOffCenter;
			perspectiveOffCenter.M11 = 2.0F * nearPlaneDistance / (right - left);
			perspectiveOffCenter.M12 = perspectiveOffCenter.M13 = perspectiveOffCenter.M14 = 0.0f;
			perspectiveOffCenter.M22 = 2.0F * nearPlaneDistance / (top - bottom);
			perspectiveOffCenter.M21 = perspectiveOffCenter.M23 = perspectiveOffCenter.M24 = 0.0f;
			perspectiveOffCenter.M31 = (left + right) / (right - left);
			perspectiveOffCenter.M32 = (top + bottom) / (top - bottom);
			perspectiveOffCenter.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
			perspectiveOffCenter.M34 = -1.0f;
			perspectiveOffCenter.M43 = nearPlaneDistance * farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
			perspectiveOffCenter.M41 = perspectiveOffCenter.M42 = perspectiveOffCenter.M44 = 0.0f;
			return perspectiveOffCenter;
		}

		static constexpr Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) {
			Matrix orthographic;
			orthographic.M11 = 2.0f / width;
			orthographic.M12 = orthographic.M13 = orthographic.M14 = 0.0f;
			orthographic.M22 = 2.0f / height;
			orthographic.M21 = orthographic.M23 = orthographic.M24 = 0.0f;
			orthographic.M33 = 1.0F / (zNearPlane - zFarPlane);
			orthographic.M31 = orthographic.M32 = orthographic.M34 = 0.0f;
			orthographic.M41 = orthographic.M42 = 0.0f;
			orthographic.M43 = zNearPlane / (zNearPlane - zFarPlane);
			orthographic.M44 = 1.0f;
			return orthographic;
		}

		static constexpr Matrix CreateOrthographicOffCenter(float left, float right, float bottom,
			float top, float zNearPlane, float zFarPlane) {

			Matrix orthographicOffCenter;
			orthographicOffCenter.M11 = 2.0F / (right - left);
			orthographicOffCenter.M12 = orthographicOffCenter.M13 = orthographicOffCenter.M14 = 0.0f;
			orthographicOffCenter.M22 = 2.0F / (top - bottom);
			orthographicOffCenter.M21 = orthographicOffCenter.M23 = orthographicOffCenter.M24 = 0.0f;
			orthographicOffCenter.M33 = 1.0F / (zNearPlane - zFarPlane);
			orthographicOffCenter.M31 = orthographicOffCenter.M32 = orthographicOffCenter.M34 = 0.0f;
			orthographicOffCenter.M41 = ((left + right) / (left - right));
			orthographicOffCenter.M42 = ((top + bottom) / (bottom - top));
			orthographicOffCenter.M43 = zNearPlane / (zNearPlane - zFarPlane);
			orthographicOffCenter.M44 = 1.0f;
			return orthographicOffCenter;
		}

		static Matrix CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector);
		static Matrix CreateWorld(Vector3 position, Vector3 forward, Vector3 up);

		static constexpr Matrix Transpose(Matrix const& matrix) {
			Matrix matrix1;
			matrix1.M11 = matrix.M11;
			matrix1.M12 = matrix.M21;
			matrix1.M13 = matrix.M31;
			matrix1.M14 = matrix.M41;
			matrix1.M21 = matrix.M12;
			matrix1.M22 = matrix.M22;
			matrix1.M23 = matrix.M32;
			matrix1.M24 = matrix.M42;
			matrix1.M31 = matrix.M13;
			matrix1.M32 = matrix.M23;
			matrix1.M33 = matrix.M33;
			matrix1.M34 = matrix.M43;
			matrix1.M41 = matrix.M14;
			matrix1.M42 = matrix.M24;
			matrix1.M43 = matrix.M34;
			matrix1.M44 = matrix.M44;
			return matrix1;
		}

		static constexpr Matrix Invert(Matrix const& matrix) {
			float m11 = matrix.M11;
			float m12 = matrix.M12;
			float m13 = matrix.M13;
			float m14 = matrix.M14;
			float m21 = matrix.M21;
			float m22 = matrix.M22;
			float m23 = matrix.M23;
			float m24 = matrix.M24;
			float m31 = matrix.M31;
			float m32 = matrix.M32;
			float m33 = matrix.M33;
			float m34 = matrix.M34;
			float m41 = matrix.M41;
			float m42 = matrix.M42;
			float m43 = matrix.M43;
			float m44 = matrix.M44;
			float num1 = (m33 * m44 - m34 * m43);
			float num2 = (m32 * m44 - m34 * m42);
			float num3 = (m32 * m43 - m33 * m42);
			float num4 = (m31 * m44 - m34 * m41);
			float num5 = (m31 * m43 - m33 * m41);
			float num6 = (m31 * m42 - m32 * m41);
			float num7 = (m22 * num1 - m23 * num2 + m24 * num3);
			float num8 = -(m21 * num1 - m23 * num4 + m24 * num5);
			float num9 = (m21 * num2 - m22 * num4 + m24 * num6);
			float num10 = -(m21 * num3 - m22 * num5 + m23 * num6);
			float num11 = (1.0F / (m11 * num7 + m12 * num8 + m13 * num9 + m14 * num10));
			Matrix matrix1;
			matrix1.M11 = num7 * num11;
			matrix1.M21 = num8 * num11;
			matrix1.M31 = num9 * num11;
			matrix1.M41 = num10 * num11;
			matrix1.M12 = -(m12 * num1 - m13 * num2 + m14 * num3) * num11;
			matrix1.M22 = (m11 * num1 - m13 * num4 + m14 * num5) * num11;
			matrix1.M32 = -(m11 * num2 - m12 * num4 + m14 * num6) * num11;
			matrix1.M42 = (m11 * num3 - m12 * num5 + m13 * num6) * num11;
			float num12 = (m23 * m44 - m24 * m43);
			float num13 = (m22 * m44 - m24 * m42);
			float num14 = (m22 * m43 - m23 * m42);
			float num15 = (m21 * m44 - m24 * m41);
			float num16 = (m21 * m43 - m23 * m41);
			float num17 = (m21 * m42 - m22 * m41);
			matrix1.M13 = (m12 * num12 - m13 * num13 + m14 * num14) * num11;
			matrix1.M23 = -(m11 * num12 - m13 * num15 + m14 * num16) * num11;
			matrix1.M33 = (m11 * num13 - m12 * num15 + m14 * num17) * num11;
			matrix1.M43 = -(m11 * num14 - m12 * num16 + m13 * num17) * num11;
			float num18 = (m23 * m34 - m24 * m33);
			float num19 = (m22 * m34 - m24 * m32);
			float num20 = (m22 * m33 - m23 * m32);
			float num21 = (m21 * m34 - m24 * m31);
			float num22 = (m21 * m33 - m23 * m31);
			float num23 = (m21 * m32 - m22 * m31);
			matrix1.M14 = -(m12 * num18 - m13 * num19 + m14 * num20) * num11;
			matrix1.M24 = (m11 * num18 - m13 * num21 + m14 * num22) * num11;
			matrix1.M34 = -(m11 * num19 - m12 * num21 + m14 * num23) * num11;
			matrix1.M44 = (m11 * num20 - m12 * num22 + m13 * num23) * num11;
			return matrix1;
		}

		static constexpr Matrix Lerp(Matrix const& matrix1, Matrix const& matrix2, float amount) {
			Matrix matrix;
			matrix.M11 = matrix1.M11 + (matrix2.M11 - matrix1.M11) * amount;
			matrix.M12 = matrix1.M12 + (matrix2.M12 - matrix1.M12) * amount;
			matrix.M13 = matrix1.M13 + (matrix2.M13 - matrix1.M13) * amount;
			matrix.M14 = matrix1.M14 + (matrix2.M14 - matrix1.M14) * amount;
			matrix.M21 = matrix1.M21 + (matrix2.M21 - matrix1.M21) * amount;
			matrix.M22 = matrix1.M22 + (matrix2.M22 - matrix1.M22) * amount;
			matrix.M23 = matrix1.M23 + (matrix2.M23 - matrix1.M23) * amount;
			matrix.M24 = matrix1.M24 + (matrix2.M24 - matrix1.M24) * amount;
			matrix.M31 = matrix1.M31 + (matrix2.M31 - matrix1.M31) * amount;
			matrix.M32 = matrix1.M32 + (matrix2.M32 - matrix1.M32) * amount;
			matrix.M33 = matrix1.M33 + (matrix2.M33 - matrix1.M33) * amount;
			matrix.M34 = matrix1.M34 + (matrix2.M34 - matrix1.M34) * amount;
			matrix.M41 = matrix1.M41 + (matrix2.M41 - matrix1.M41) * amount;
			matrix.M42 = matrix1.M42 + (matrix2.M42 - matrix1.M42) * amount;
			matrix.M43 = matrix1.M43 + (matrix2.M43 - matrix1.M43) * amount;
			matrix.M44 = matrix1.M44 + (matrix2.M44 - matrix1.M44) * amount;
			return matrix;
		}

		static constexpr Matrix Negate(Matrix const& matrix) {
			Matrix matrix1;
			matrix1.M11 = -matrix.M11;
			matrix1.M12 = -matrix.M12;
			matrix1.M13 = -matrix.M13;
			matrix1.M14 = -matrix.M14;
			matrix1.M21 = -matrix.M21;
			matrix1.M22 = -matrix.M22;
			matrix1.M23 = -matrix.M23;
			matrix1.M24 = -matrix.M24;
			matrix1.M31 = -matrix.M31;
			matrix1.M32 = -matrix.M32;
			matrix1.M33 = -matrix.M33;
			matrix1.M34 = -matrix.M34;
			matrix1.M41 = -matrix.M41;
			matrix1.M42 = -matrix.M42;
			matrix1.M43 = -matrix.M43;
			matrix1.M44 = -matrix.M44;
			return matrix1;
		}

		static constexpr Matrix Add(Matrix const& matrix1, Matrix const& matrix2) {
			Matrix matrix;
			matrix.M11 = matrix1.M11 + matrix2.M11;
			matrix.M12 = matrix1.M12 + matrix2.M12;
			matrix.M13 = matrix1.M13 + matrix2.M13;
			matrix.M14 = matrix1.M14 + matrix2.M14;
			matrix.M21 = matrix1.M21 + matrix2.M21;
			matrix.M22 = matrix1.M22 + matrix2.M22;
			matrix.M23 = matrix1.M23 + matrix2.M23;
			matrix.M24 = matrix1.M24 + matrix2.M24;
			matrix.M31 = matrix1.M31 + matrix2.M31;
			matrix.M32 = matrix1.M32 + matrix2.M32;
			matrix.M33 = matrix1.M33 + matrix2.M33;
			matrix.M34 = matrix1.M34 + matrix2.M34;
			matrix.M41 = matrix1.M41 + matrix2.M41;
			matrix.M42 = matrix1.M42 + matrix2.M42;
			matrix.M43 = matrix1.M43 + matrix2.M43;
			matrix.M44 = matrix1.M44 + matrix2.M44;
			return matrix;
		}

		static constexpr Matrix Subtract(Matrix const& matrix1, Matrix const& matrix2) {
			Matrix matrix;
			matrix.M11 = matrix1.M11 - matrix2.M11;
			matrix.M12 = matrix1.M12 - matrix2.M12;
			matrix.M13 = matrix1.M13 - matrix2.M13;
			matrix.M14 = matrix1.M14 - matrix2.M14;
			matrix.M21 = matrix1.M21 - matrix2.M21;
			matrix.M22 = matrix1.M22 - matrix2.M22;
			matrix.M23 = matrix1.M23 - matrix2.M23;
			matrix.M24 = matrix1.M24 - matrix2.M24;
			matrix.M31 = matrix1.M31 - matrix2.M31;
			matrix.M32 = matrix1.M32 - matrix2.M32;
			matrix.M33 = matrix1.M33 - matrix2.M33;
			matrix.M34 = matrix1.M34 - matrix2.M34;
			matrix.M41 = matrix1.M41 - matrix2.M41;
			matrix.M42 = matrix1.M42 - matrix2.M42;
			matrix.M43 = matrix1.M43 - matrix2.M43;
			matrix.M44 = matrix1.M44 - matrix2.M44;
			return matrix;
		}

		static constexpr Matrix Multiply(Matrix const& matrix1, Matrix const& matrix2) {
			Matrix matrix;
			matrix.M11 = matrix1.M11 * matrix2.M11 + matrix1.M12 * matrix2.M21 + matrix1.M13 * matrix2.M31 + matrix1.M14 * matrix2.M41;
			matrix.M12 = matrix1.M11 * matrix2.M12 + matrix1.M12 * matrix2.M22 + matrix1.M13 * matrix2.M32 + matrix1.M14 * matrix2.M42;
			matrix.M13 = matrix1.M11 * matrix2.M13 + matrix1.M12 * matrix2.M23 + matrix1.M13 * matrix2.M33 + matrix1.M14 * matrix2.M43;
			matrix.M14 = matrix1.M11 * matrix2.M14 + matrix1.M12 * matrix2.M24 + matrix1.M13 * matrix2.M34 + matrix1.M14 * matrix2.M44;
			matrix.M21 = matrix1.M21 * matrix2.M11 + matrix1.M22 * matrix2.M21 + matrix1.M23 * matrix2.M31 + matrix1.M24 * matrix2.M41;
			matrix.M22 = matrix1.M21 * matrix2.M12 + matrix1.M22 * matrix2.M22 + matrix1.M23 * matrix2.M32 + matrix1.M24 * matrix2.M42;
			matrix.M23 = matrix1.M21 * matrix2.M13 + matrix1.M22 * matrix2.M23 + matrix1.M23 * matrix2.M33 + matrix1.M24 * matrix2.M43;
			matrix.M24 = matrix1.M21 * matrix2.M14 + matrix1.M22 * matrix2.M24 + matrix1.M23 * matrix2.M34 + matrix1.M24 * matrix2.M44;
			matrix.M31 = matrix1.M31 * matrix2.M11 + matrix1.M32 * matrix2.M21 + matrix1.M33 * matrix2.M31 + matrix1.M34 * matrix2.M41;
			matrix.M32 = matrix1.M31 * matrix2.M12 + matrix1.M32 * matrix2.M22 + matrix1.M33 * matrix2.M32 + matrix1.M34 * matrix2.M42;
			matrix.M33 = matrix1.M31 * matrix2.M13 + matrix1.M32 * matrix2.M23 + matrix1.M33 * matrix2.M33 + matrix1.M34 * matrix2.M43;
			matrix.M34 = matrix1.M31 * matrix2.M14 + matrix1.M32 * matrix2.M24 + matrix1.M33 * matrix2.M34 + matrix1.M34 * matrix2.M44;
			matrix.M41 = matrix1.M41 * matrix2.M11 + matrix1.M42 * matrix2.M21 + matrix1.M43 * matrix2.M31 + matrix1.M44 * matrix2.M41;
			matrix.M42 = matrix1.M41 * matrix2.M12 + matrix1.M42 * matrix2.M22 + matrix1.M43 * matrix2.M32 + matrix1.M44 * matrix2.M42;
			matrix.M43 = matrix1.M41 * matrix2.M13 + matrix1.M42 * matrix2.M23 + matrix1.M43 * matrix2.M33 + matrix1.M44 * matrix2.M43;
			matrix.M44 = matrix1.M41 * matrix2.M14 + matrix1.M42 * matrix2.M24 + matrix1.M43 * matrix2.M34 + matrix1.M44 * matrix2.M44;
			return matrix;
		}

		static constexpr Matrix Multiply(Matrix const& matrix1, float scaleFactor) {
			float num = scaleFactor;
			Matrix matrix;
			matrix.M11 = matrix1.M11 * num;
			matrix.M12 = matrix1.M12 * num;
			matrix.M13 = matrix1.M13 * num;
			matrix.M14 = matrix1.M14 * num;
			matrix.M21 = matrix1.M21 * num;
			matrix.M22 = matrix1.M22 * num;
			matrix.M23 = matrix1.M23 * num;
			matrix.M24 = matrix1.M24 * num;
			matrix.M31 = matrix1.M31 * num;
			matrix.M32 = matrix1.M32 * num;
			matrix.M33 = matrix1.M33 * num;
			matrix.M34 = matrix1.M34 * num;
			matrix.M41 = matrix1.M41 * num;
			matrix.M42 = matrix1.M42 * num;
			matrix.M43 = matrix1.M43 * num;
			matrix.M44 = matrix1.M44 * num;
			return matrix;
		}

		static constexpr Matrix Divide(Matrix const& matrix1, Matrix const& matrix2) {
			Matrix matrix;
			matrix.M11 = matrix1.M11 / matrix2.M11;
			matrix.M12 = matrix1.M12 / matrix2.M12;
			matrix.M13 = matrix1.M13 / matrix2.M13;
			matrix.M14 = matrix1.M14 / matrix2.M14;
			matrix.M21 = matrix1.M21 / matrix2.M21;
			matrix.M22 = matrix1.M22 / matrix2.M22;
			matrix.M23 = matrix1.M23 / matrix2.M23;
			matrix.M24 = matrix1.M24 / matrix2.M24;
			matrix.M31 = matrix1.M31 / matrix2.M31;
			matrix.M32 = matrix1.M32 / matrix2.M32;
			matrix.M33 = matrix1.M33 / matrix2.M33;
			matrix.M34 = matrix1.M34 / matrix2.M34;
			matrix.M41 = matrix1.M41 / matrix2.M41;
			matrix.M42 = matrix1.M42 / matrix2.M42;
			matrix.M43 = matrix1.M43 / matrix2.M43;
			matrix.M44 = matrix1.M44 / matrix2.M44;
			return matrix;
		}

		static constexpr Matrix Divide(Matrix const& matrix1, float divider) {
			float num = 1.0f / divider;
			Matrix matrix;
			matrix.M11 = matrix1.M11 * num;
			matrix.M12 = matrix1.M12 * num;
			matrix.M13 = matrix1.M13 * num;
			matrix.M14 = matrix1.M14 * num;
			matrix.M21 = matrix1.M21 * num;
			matrix.M22 = matrix1.M22 * num;
			matrix.M23 = matrix1.M23 * num;
			matrix.M24 = matrix1.M24 * num;
			matrix.M31 = matrix1.M31 * num;
			matrix.M32 = matrix1.M32 * num;
			matrix.M33 = matrix1.M33 * num;
			matrix.M34 = matrix1.M34 * num;
			matrix.M41 = matrix1.M41 * num;
			matrix.M42 = matrix1.M42 * num;
			matrix.M43 = matrix1.M43 * num;
			matrix.M44 = matrix1.M44 * num;
			return matrix;
		}

		static constexpr Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static constexpr Matrix CreateFromQuaternion(Quaternion const& quaternion);
		static constexpr Matrix CreateShadow(Vector3 const& lightDirection, Plane const& plane);
		static constexpr Matrix Createlection(Plane const& value);
		static Matrix Transform(Matrix const& value, Quaternion const& rotation);
	};

	struct Quaternion {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		constexpr Quaternion() = default;

		constexpr Quaternion(float X, float Y, float Z, float W)
			: X(X), Y(Y), Z(Z), W(W) {}

		constexpr Quaternion(Vector3 const& vectorPart, float scalarPart)
			: X(vectorPart.X), Y(vectorPart.Y), Z(vectorPart.Z), W(scalarPart) {}

		constexpr Quaternion operator-() const { return Quaternion::Negate(*this); }
		constexpr bool operator==(Quaternion const& other) const { return Equals(other); }
		friend constexpr Quaternion operator+(Quaternion const& value1, Quaternion const& value2) { return Quaternion::Add(value1, value2); }
		friend constexpr Quaternion operator-(Quaternion const& value1, Quaternion const& value2) { return Quaternion::Subtract(value1, value2); }
		friend constexpr Quaternion operator*(Quaternion const& value1, Quaternion const& value2) { return Quaternion::Multiply(value1, value2); }
		friend constexpr Quaternion operator*(Quaternion const& value, float scale) { return Quaternion::Multiply(value, scale); }
		friend constexpr Quaternion operator*(float scale, Quaternion const& value) { return Quaternion::Multiply(value, scale); }
		friend constexpr Quaternion operator/(Quaternion const& value1, Quaternion const& value2) { return Quaternion::Divide(value1, value2); }

		constexpr bool Equals(Quaternion const& other) const {
			return X == other.X
				&& Y == other.Y
				&& Z == other.Z
				&& W == other.W;
		}

		constexpr float LengthSquared() const {
			return X * X + Y * Y + Z * Z + W * W;
		}

		float Length() const;
		void Normalize();
		void Conjugate();

		static constexpr Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

		static Quaternion Normalize(Quaternion const& quaternion);

		static constexpr Quaternion Conjugate(Quaternion const& value) {
			Quaternion quaternion;
			quaternion.X = -value.X;
			quaternion.Y = -value.Y;
			quaternion.Z = -value.Z;
			quaternion.W = value.W;
			return quaternion;
		}

		static constexpr Quaternion Inverse(Quaternion const& quaternion) {
			float num = 1.0f / quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z + quaternion.W * quaternion.W;
			Quaternion quaternion1;
			quaternion1.X = -quaternion.X * num;
			quaternion1.Y = -quaternion.Y * num;
			quaternion1.Z = -quaternion.Z * num;
			quaternion1.W = quaternion.W * num;
			return quaternion1;
		}

		static Quaternion CreateFromAxisAngle(Vector3 const& axis, float angle);
		static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static Quaternion CreateFromRotationMatrix(Matrix const& matrix);

		static constexpr float Dot(Quaternion const& quaternion1, Quaternion const& quaternion2) {
			return quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
		}

		static Quaternion Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount);
		static Quaternion Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount);

		static constexpr Quaternion Concatenate(Quaternion const& value1, Quaternion const& value2) {
			const auto x1 = value2.X;
			const auto y1 = value2.Y;
			const auto z1 = value2.Z;
			const auto w1 = value2.W;
			const auto x2 = value1.X;
			const auto y2 = value1.Y;
			const auto z2 = value1.Z;
			const auto w2 = value1.W;
			const auto num1 = (y1 * z2 - z1 * y2);
			const auto num2 = (z1 * x2 - x1 * z2);
			const auto num3 = (x1 * y2 - y1 * x2);
			const auto num4 = (x1 * x2 + y1 * y2 + z1 * z2);
			Quaternion quaternion;
			quaternion.X = (x1 * w2 + x2 * w1) + num1;
			quaternion.Y = (y1 * w2 + y2 * w1) + num2;
			quaternion.Z = (z1 * w2 + z2 * w1) + num3;
			quaternion.W = w1 * w2 - num4;
			return quaternion;
		}

		static constexpr Quaternion Negate(Quaternion const& quaternion) {
			Quaternion quaternion1;
			quaternion1.X = -quaternion.X;
			quaternion1.Y = -quaternion.Y;
			quaternion1.Z = -quaternion.Z;
			quaternion1.W = -quaternion.W;
			return quaternion1;
		}

		static constexpr Quaternion Add(Quaternion const& quaternion1, Quaternion const& quaternion2) {
			Quaternion quaternion;
			quaternion.X = quaternion1.X + quaternion2.X;
			quaternion.Y = quaternion1.Y + quaternion2.Y;
			quaternion.Z = quaternion1.Z + quaternion2.Z;
			quaternion.W = quaternion1.W + quaternion2.W;
			return quaternion;
		}

		static constexpr Quaternion Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2) {
			Quaternion quaternion;
			quaternion.X = quaternion1.X - quaternion2.X;
			quaternion.Y = quaternion1.Y - quaternion2.Y;
			quaternion.Z = quaternion1.Z - quaternion2.Z;
			quaternion.W = quaternion1.W - quaternion2.W;
			return quaternion;
		}

		static constexpr Quaternion Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2) {
			const auto x1 = quaternion1.X;
			const auto y1 = quaternion1.Y;
			const auto z1 = quaternion1.Z;
			const auto w1 = quaternion1.W;
			const auto x2 = quaternion2.X;
			const auto y2 = quaternion2.Y;
			const auto z2 = quaternion2.Z;
			const auto w2 = quaternion2.W;
			const auto num1 = (y1 * z2 - z1 * y2);
			const auto num2 = (z1 * x2 - x1 * z2);
			const auto num3 = (x1 * y2 - y1 * x2);
			const auto num4 = (x1 * x2 + y1 * y2 + z1 * z2);
			Quaternion quaternion;
			quaternion.X = (x1 * w2 + x2 * w1) + num1;
			quaternion.Y = (y1 * w2 + y2 * w1) + num2;
			quaternion.Z = (z1 * w2 + z2 * w1) + num3;
			quaternion.W = w1 * w2 - num4;
			return quaternion;
		}

		static constexpr Quaternion Multiply(Quaternion const& quaternion1, float scaleFactor) {
			Quaternion quaternion;
			quaternion.X = quaternion1.X * scaleFactor;
			quaternion.Y = quaternion1.Y * scaleFactor;
			quaternion.Z = quaternion1.Z * scaleFactor;
			quaternion.W = quaternion1.W * scaleFactor;
			return quaternion;
		}

		static constexpr Quaternion Divide(Quaternion const& quaternion1, Quaternion const& quaternion2) {
			const auto x = quaternion1.X;
			const auto y = quaternion1.Y;
			const auto z = quaternion1.Z;
			const auto w = quaternion1.W;
			const auto num1 = 1.0f / (quaternion2.X * quaternion2.X + quaternion2.Y * quaternion2.Y + quaternion2.Z * quaternion2.Z + quaternion2.W * quaternion2.W);
			const auto num2 = -quaternion2.X * num1;
			const auto num3 = -quaternion2.Y * num1;
			const auto num4 = -quaternion2.Z * num1;
			const auto num5 = quaternion2.W * num1;
			const auto num6 = (y * num4 - z * num3);
			const auto num7 = (z * num2 - x * num4);
			const auto num8 = (x * num3 - y * num2);
			const auto num9 = (x * num2 + y * num3 + z * num4);
			Quaternion quaternion;
			quaternion.X = (x * num5 + num2 * w) + num6;
			quaternion.Y = (y * num5 + num3 * w) + num7;
			quaternion.Z = (z * num5 + num4 * w) + num8;
			quaternion.W = w * num5 - num9;
			return quaternion;
		}
	};

	struct BoundingBox {
		Vector3 Min;
		Vector3 Max;

		constexpr BoundingBox() = default;

		constexpr BoundingBox(Vector3 const& min, Vector3 const& max) :
			Min(min), Max(max) {}

		constexpr bool operator==(BoundingBox const& other) {
			return Equals(other);
		}

		constexpr bool Equals(BoundingBox const& other) const {
			return Min == other.Min && Max == other.Max;
		}

		constexpr void GetCorners(Vector3 corners[8]) const {
			corners[0].X = Min.X;
			corners[0].Y = Max.Y;
			corners[0].Z = Max.Z;
			corners[1].X = Max.X;
			corners[1].Y = Max.Y;
			corners[1].Z = Max.Z;
			corners[2].X = Max.X;
			corners[2].Y = Min.Y;
			corners[2].Z = Max.Z;
			corners[3].X = Min.X;
			corners[3].Y = Min.Y;
			corners[3].Z = Max.Z;
			corners[4].X = Min.X;
			corners[4].Y = Max.Y;
			corners[4].Z = Min.Z;
			corners[5].X = Max.X;
			corners[5].Y = Max.Y;
			corners[5].Z = Min.Z;
			corners[6].X = Max.X;
			corners[6].Y = Min.Y;
			corners[6].Z = Min.Z;
			corners[7].X = Min.X;
			corners[7].Y = Min.Y;
			corners[7].Z = Min.Z;
		}

		constexpr bool Intersects(BoundingBox const& box) const {
			return Max.X >= box.Min.X
				&& Min.X <= box.Max.X
				&& Max.Y >= box.Min.Y
				&& Min.Y <= box.Max.Y
				&& Max.Z >= box.Min.Z
				&& Min.Z <= box.Max.Z;
		}

		constexpr ContainmentType Contains(BoundingBox const& box) const {
			if (Max.X < box.Min.X || Min.X > box.Max.X || Max.Y < box.Min.Y || Min.Y > box.Max.Y || Max.Z < box.Min.Z || Min.Z > box.Max.Z)
				return ContainmentType::Disjoint;

			return Min.X > box.Min.X || box.Max.X > Max.X || Min.Y > box.Min.Y || box.Max.Y > Max.Y || Min.Z > box.Min.Z || box.Max.Z > Max.Z
				? ContainmentType::Intersects : ContainmentType::Contains;
		}

		constexpr ContainmentType Contains(Vector3 const& point) const {
			return Min.X > point.X || point.X > Max.X || Min.Y > point.Y || point.Y > Max.Y || Min.Z > point.Z || point.Z > Max.Z
				? ContainmentType::Disjoint : ContainmentType::Contains;
		}

		void SupportMapping(Vector3 const& v, Vector3& result) const {
			result.X = v.X >= 0.0 ? Max.X : Min.X;
			result.Y = v.Y >= 0.0 ? Max.Y : Min.Y;
			result.Z = v.Z >= 0.0 ? Max.Z : Min.Z;
		}

		static constexpr BoundingBox CreateMerged(BoundingBox const& original, BoundingBox const& additional) {
			Vector3 result1 = Vector3::Min(original.Min, additional.Min);
			Vector3 result2 = Vector3::Max(original.Max, additional.Max);

			BoundingBox result;
			result.Min = result1;
			result.Max = result2;

			return result;
		}

		constexpr bool Intersects(BoundingSphere const& sphere) const;
		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const;
		constexpr ContainmentType Contains(BoundingSphere const& sphere) const;
		static constexpr BoundingBox CreateFromSphere(BoundingSphere const& sphere);
		static constexpr bool Intersects(BoundingFrustum const& frustum);
		static constexpr PlaneIntersectionType Intersects(Plane const& plane);
		static nfloat Intersects(Ray const& ray);

	};

	struct BoundingSphere {
		Vector3 Center;
		float Radius{ 0 };

		constexpr BoundingSphere() = default;

		constexpr BoundingSphere(Vector3 const& center, float radius) :
			Center(center), Radius(radius) {}

		constexpr bool operator==(BoundingSphere const& other) {
			return Equals(other);
		}

		bool constexpr Equals(BoundingSphere const& other) const {
			return Center == other.Center && Radius == other.Radius;
		}

		static BoundingSphere CreateMerged(BoundingSphere const& original, BoundingSphere const& additional);
		static BoundingSphere CreateFromBoundingBox(BoundingBox const& box);
		static BoundingSphere CreateFromPoints(Vector3* points, size_t length, size_t offset = 0);

		bool Intersects(BoundingBox const& box) const {
			const auto result1 = Vector3::Clamp(Center, box.Min, box.Max);
			const auto result2 = Vector3::DistanceSquared(Center, result1);
			return result2 <= Radius * Radius;
		}

		bool Intersects(BoundingSphere const& sphere) const {
			const auto result = Vector3::DistanceSquared(Center, sphere.Center);
			const auto radius1 = Radius;
			const auto radius2 = sphere.Radius;
			return radius1 * radius1 + 2.0F * radius1 * radius2 + radius2 * radius2 > result;
		}

		ContainmentType Contains(BoundingBox const& box) const;

		constexpr ContainmentType Contains(Vector3 point) const {
			return Vector3::DistanceSquared(point, Center) >= Radius * Radius ? ContainmentType::Disjoint : ContainmentType::Contains;
		}

		ContainmentType Contains(BoundingSphere sphere) const {
			const auto result = Vector3::Distance(Center, sphere.Center);
			const auto radius1 = Radius;
			const auto radius2 = sphere.Radius;

			if (radius1 + radius2 < result)
				return ContainmentType::Disjoint;

			return radius1 - radius2 < result ? ContainmentType::Intersects : ContainmentType::Contains;
		}

		void SupportMapping(Vector3 const& v, Vector3& result) const;

		BoundingSphere Transform(Matrix const& matrix) const;

		ContainmentType Contains(BoundingFrustum const& frustum) const;
		bool Intersects(BoundingFrustum const& frustum) const;
		PlaneIntersectionType Intersects(Plane const& plane) const;
		nfloat Intersects(Ray const& ray) const;
		static BoundingSphere CreateFromFrustum(BoundingFrustum const& frustum);
	};

	struct Plane {
		Vector3 Normal;
		float D{ 0 };

		constexpr Plane() = default;

		constexpr Plane(const Vector3& Normal, float D)
			: Normal(Normal), D(D) {}

		constexpr Plane(float a, float b, float c, float d)
			: Normal({ a,b, c }), D(d) { }

		constexpr Plane(Vector4 const& value)
			: Normal({ value.X, value.Y, value.Z }), D(value.W) {}

		Plane(Vector3 const& point1, Vector3 const& point2, Vector3 const& point3);

		constexpr bool operator==(const Plane& other) const {
			return Equals(other);
		}

		constexpr bool Equals(const Plane& other) const {
			return Normal == other.Normal && D == other.D;
		}

		void Normalize();
		static Plane Normalize(Plane const& value);

		static constexpr Plane Transform(Plane const& plane, Matrix const& matrix) {
			const auto result = Matrix::Invert(matrix);
			const auto x = plane.Normal.X;
			const auto y = plane.Normal.Y;
			const auto z = plane.Normal.Z;
			const auto d = plane.D;

			Plane plane1;
			plane1.Normal.X = (x * result.M11 + y * result.M12 + z * result.M13 + d * result.M14);
			plane1.Normal.Y = (x * result.M21 + y * result.M22 + z * result.M23 + d * result.M24);
			plane1.Normal.Z = (x * result.M31 + y * result.M32 + z * result.M33 + d * result.M34);
			plane1.D = (x * result.M41 + y * result.M42 + z * result.M43 + d * result.M44);
			return plane1;
		}

		static Plane Transform(Plane const& plane, Quaternion const& rotation) {
			const auto num1 = rotation.X + rotation.X;
			const auto num2 = rotation.Y + rotation.Y;
			const auto num3 = rotation.Z + rotation.Z;
			const auto num4 = rotation.W * num1;
			const auto num5 = rotation.W * num2;
			const auto num6 = rotation.W * num3;
			const auto num7 = rotation.X * num1;
			const auto num8 = rotation.X * num2;
			const auto num9 = rotation.X * num3;
			const auto num10 = rotation.Y * num2;
			const auto num11 = rotation.Y * num3;
			const auto num12 = rotation.Z * num3;
			const auto num13 = 1.0f - num10 - num12;
			const auto num14 = num8 - num6;
			const auto num15 = num9 + num5;
			const auto num16 = num8 + num6;
			const auto num17 = 1.0f - num7 - num12;
			const auto num18 = num11 - num4;
			const auto num19 = num9 - num5;
			const auto num20 = num11 + num4;
			const auto num21 = 1.0f - num7 - num10;
			const auto x = plane.Normal.X;
			const auto y = plane.Normal.Y;
			const auto z = plane.Normal.Z;

			Plane plane1;
			plane1.Normal.X = (x * num13 + y * num14 + z * num15);
			plane1.Normal.Y = (x * num16 + y * num17 + z * num18);
			plane1.Normal.Z = (x * num19 + y * num20 + z * num21);
			plane1.D = plane.D;

			return plane1;
		}

		constexpr float Dot(Vector4 const& value) const {
			return (Normal.X * value.X + Normal.Y * value.Y + Normal.Z * value.Z + D * value.W);
		}

		constexpr  float DotCoordinate(Vector3 const& value) const {
			return (Normal.X * value.X + Normal.Y * value.Y + Normal.Z * value.Z) + D;
		}

		constexpr float DotNormal(Vector3 const& value) const {
			return (Normal.X * value.X + Normal.Y * value.Y + Normal.Z * value.Z);
		}

		constexpr PlaneIntersectionType Intersects(BoundingBox const& box) {
			Vector3 vector3_1;
			vector3_1.X = Normal.X >= 0.0 ? box.Min.X : box.Max.X;
			vector3_1.Y = Normal.Y >= 0.0 ? box.Min.Y : box.Max.Y;
			vector3_1.Z = Normal.Z >= 0.0 ? box.Min.Z : box.Max.Z;

			Vector3 vector3_2;
			vector3_2.X = Normal.X >= 0.0 ? box.Max.X : box.Min.X;
			vector3_2.Y = Normal.Y >= 0.0 ? box.Max.Y : box.Min.Y;
			vector3_2.Z = Normal.Z >= 0.0 ? box.Max.Z : box.Min.Z;

			if (Normal.X * vector3_1.X + Normal.Y * vector3_1.Y + Normal.Z * vector3_1.Z + D > 0.0)
				return PlaneIntersectionType::Front;

			return Normal.X * vector3_2.X + Normal.Y * vector3_2.Y + Normal.Z * vector3_2.Z + D < 0.0 ? PlaneIntersectionType::Back : PlaneIntersectionType::Intersecting;
		}

		PlaneIntersectionType Intersects(BoundingSphere const& sphere) const {
			const auto num = (sphere.Center.X * Normal.X + sphere.Center.Y * Normal.Y + sphere.Center.Z * Normal.Z) + D;

			if (num > sphere.Radius)
				return PlaneIntersectionType::Front;

			return num < -sphere.Radius ? PlaneIntersectionType::Back : PlaneIntersectionType::Intersecting;
		}

		constexpr PlaneIntersectionType Intersects(BoundingFrustum const& frustum) const;

		constexpr PlaneIntersectionType Intersects(Vector3 const& point) const {
			float distance = DotCoordinate(point);

			if (distance > 0)
				return PlaneIntersectionType::Front;

			if (distance < 0)
				return PlaneIntersectionType::Back;

			return PlaneIntersectionType::Intersecting;
		}

		nfloat Intersects(Ray const& ray) const;

	public:
		static constexpr float ClassifyPoint(Vector3 const& point, Plane const& plane) {
			return point.X * plane.Normal.X + point.Y * plane.Normal.Y + point.Z * plane.Normal.Z + plane.D;
		}

		static float PerpendicularDistance(Vector3 const& point, Plane const& plane);
	};

	struct BoundingFrustum {
		using Matrix_ = dxna::Matrix;

		BoundingFrustum(Matrix_ const& value) : _matrix(value) {
			createCorners();
			createPlanes();
		}

		constexpr bool operator==(const BoundingFrustum& other) const { return Equals(other); }

		constexpr bool Equals(BoundingFrustum const& other) const {
			return _matrix == other._matrix
				&& _corners0 == other._corners0
				&& _corners1 == other._corners1
				&& _corners2 == other._corners2
				&& _corners3 == other._corners3
				&& _corners4 == other._corners4
				&& _corners5 == other._corners5
				&& _corners6 == other._corners6
				&& _corners7 == other._corners7
				&& _planes0 == other._planes0
				&& _planes1 == other._planes1
				&& _planes2 == other._planes2
				&& _planes3 == other._planes3
				&& _planes4 == other._planes4
				&& _planes5 == other._planes5;
		}

		constexpr Matrix_ Matrix() const { return _matrix; }

		void Matrix(Matrix_ const& value) {
			_matrix = value;
			createPlanes();
			createCorners();
		}

		constexpr Plane Near() const { return _planes0; }
		constexpr Plane Far() const { return _planes1; }
		constexpr Plane Left() const { return _planes2; }
		constexpr Plane Right() const { return _planes3; }
		constexpr Plane Top() const { return _planes4; }
		constexpr Plane Bottom() const { return _planes5; }

		constexpr ContainmentType Contains(BoundingBox const& box) const {
			auto intersects = false;

			for (size_t i = 0; i < PlaneCount; ++i)
			{
				const auto plane = getPlane(i);
				const auto planeIntersectionType = box.Intersects(plane);

				switch (planeIntersectionType)
				{
				case PlaneIntersectionType::Front:
					return ContainmentType::Disjoint;
				case PlaneIntersectionType::Intersecting:
					intersects = true;
					break;
				}
			}

			return intersects ? ContainmentType::Intersects : ContainmentType::Contains;
		}

		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const {
			if (*this == frustum)
				return ContainmentType::Contains;

			auto intersects = false;

			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto plane = getPlane(i);
				PlaneIntersectionType planeIntersectionType = frustum.Intersects(plane);

				switch (planeIntersectionType)
				{
				case PlaneIntersectionType::Front:
					return ContainmentType::Disjoint;
				case PlaneIntersectionType::Intersecting:
					intersects = true;
					break;
				}
			}
			return intersects ? ContainmentType::Intersects : ContainmentType::Contains;
		}

		constexpr ContainmentType Contains(BoundingSphere const& sphere) const {
			auto intersects = false;

			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto plane = getPlane(i);
				auto planeIntersectionType = sphere.Intersects(plane);
				switch (planeIntersectionType)
				{
				case PlaneIntersectionType::Front:
					return ContainmentType::Disjoint;
				case PlaneIntersectionType::Intersecting:
					intersects = true;
					break;
				}
			}
			return intersects ? ContainmentType::Intersects : ContainmentType::Contains;
		}

		constexpr ContainmentType Contains(Vector3 const& point) const {
			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto plane = getPlane(i);

				if (Plane::ClassifyPoint(point, plane) > 0.0F) {
					return ContainmentType::Disjoint;
				}
			}

			return ContainmentType::Contains;
		}

		constexpr void GetCorners(Vector3 cornerArray[8]) const {
			for (size_t i = 0; i < CornerCount; ++i) {
				const auto corner = getCorners(i);

				cornerArray[i] = corner;
			}
		}

		constexpr bool Intersects(BoundingBox const& box) const {
			const auto containment = Contains(box);
			return containment != ContainmentType::Disjoint;
		}

		constexpr bool Intersects(BoundingFrustum const& frustum) const {
			return Contains(frustum) != ContainmentType::Disjoint;
		}

		constexpr bool Intersects(BoundingSphere const& sphere) const {
			const auto containment = Contains(sphere);
			return containment != ContainmentType::Disjoint;
		}

		constexpr PlaneIntersectionType Intersects(Plane const& plane) const {
			auto result = plane.Intersects(_corners0);

			for (size_t i = 1; i < CornerCount; i++) {
				const auto corner = getCorners(i);

				if (plane.Intersects(corner) != result)
					result = PlaneIntersectionType::Intersecting;
			}

			return result;
		}

		constexpr nfloat Intersects(Ray const& ray) const;

	public:
		static constexpr int PlaneCount = 6;
		static constexpr int CornerCount = 8;

	private:
		static constexpr Vector3 IntersectionPoint(Plane const& a, Plane const& b, Plane const& c) {
			Vector3 cross = Vector3::Cross(b.Normal, c.Normal);

			float f = Vector3::Dot(a.Normal, cross);
			f *= -1.0f;

			cross = Vector3::Cross(b.Normal, c.Normal);
			const auto v1 = Vector3::Multiply(cross, a.D);

			cross = Vector3::Cross(c.Normal, a.Normal);
			const auto v2 = Vector3::Multiply(cross, b.D);

			cross = Vector3::Cross(a.Normal, b.Normal);
			const auto v3 = Vector3::Multiply(cross, c.D);

			Vector3 result;
			result.X = (v1.X + v2.X + v3.X) / f;
			result.Y = (v1.Y + v2.Y + v3.Y) / f;
			result.Z = (v1.Z + v2.Z + v3.Z) / f;

			return result;
		}

		constexpr void createCorners() {
			_corners0 = IntersectionPoint(_planes0, _planes2, _planes4);
			_corners1 = IntersectionPoint(_planes0, _planes3, _planes4);
			_corners2 = IntersectionPoint(_planes0, _planes3, _planes5);
			_corners3 = IntersectionPoint(_planes0, _planes2, _planes5);
			_corners4 = IntersectionPoint(_planes1, _planes2, _planes4);
			_corners5 = IntersectionPoint(_planes1, _planes3, _planes4);
			_corners6 = IntersectionPoint(_planes1, _planes3, _planes5);
			_corners7 = IntersectionPoint(_planes1, _planes2, _planes5);
		}

		void createPlanes() {
			_planes0 = Plane(-_matrix.M13, -_matrix.M23, -_matrix.M33, -_matrix.M43);
			_planes1 = Plane(_matrix.M13 - _matrix.M14, _matrix.M23 - _matrix.M24, _matrix.M33 - _matrix.M34, _matrix.M43 - _matrix.M44);
			_planes2 = Plane(-_matrix.M14 - _matrix.M11, -_matrix.M24 - _matrix.M21, -_matrix.M34 - _matrix.M31, -_matrix.M44 - _matrix.M41);
			_planes3 = Plane(_matrix.M11 - _matrix.M14, _matrix.M21 - _matrix.M24, _matrix.M31 - _matrix.M34, _matrix.M41 - _matrix.M44);
			_planes4 = Plane(_matrix.M12 - _matrix.M14, _matrix.M22 - _matrix.M24, _matrix.M32 - _matrix.M34, _matrix.M42 - _matrix.M44);
			_planes5 = Plane(-_matrix.M14 - _matrix.M12, -_matrix.M24 - _matrix.M22, -_matrix.M34 - _matrix.M32, -_matrix.M44 - _matrix.M42);

			_planes0.Normalize();
			_planes1.Normalize();
			_planes2.Normalize();
			_planes3.Normalize();
			_planes4.Normalize();
			_planes5.Normalize();
		}

		constexpr Plane getPlane(size_t index) const {
			switch (index)
			{
			case 0:
				return _planes0;
			case 1:
				return _planes1;
			case 2:
				return _planes2;
			case 3:
				return _planes3;
			case 4:
				return _planes4;
			case 5:
				return _planes5;
			default:
				return Plane();
			}
		}

		constexpr Vector3 getCorners(size_t index) const {
			switch (index)
			{
			case 0:
				return _corners0;
			case 1:
				return _corners1;
			case 2:
				return _corners2;
			case 3:
				return _corners3;
			case 4:
				return _corners4;
			case 5:
				return _corners5;
			case 6:
				return _corners6;
			case 7:
				return _corners7;
			default:
				return Vector3();
			}
		}

		Matrix_ _matrix;

		Vector3 _corners0;
		Vector3 _corners1;
		Vector3 _corners2;
		Vector3 _corners3;
		Vector3 _corners4;
		Vector3 _corners5;
		Vector3 _corners6;
		Vector3 _corners7;

		Plane _planes0;
		Plane _planes1;
		Plane _planes2;
		Plane _planes3;
		Plane _planes4;
		Plane _planes5;
	};

	struct Ray {
		Vector3 Position;
		Vector3 Direction;

		constexpr Ray() = default;		

		constexpr Ray(const Vector3& Position, const Vector3& Direction)
			: Position(Position), Direction(Direction) {}

		constexpr bool operator==(Ray const& other) const {
			return Equals(other);
		}

		constexpr bool Equals(Ray const& other) const {
			return Position == other.Position && Direction == other.Direction;
		}

		nfloat Intersects(BoundingBox const& box) const {
			return box.Intersects(*this);
		}

		nfloat Intersects(BoundingFrustum const& frustum) const {
			frustum.Intersects(*this);
		}

		nfloat Intersects(Plane const& plane) {
			plane.Intersects(*this);
		}

		nfloat Intersects(BoundingSphere const& sphere) const {
			sphere.Intersects(*this);
		}
	};
}

namespace dxna {
	constexpr Vector3 dxna::Vector3::Transform(Vector3 const& position, Matrix const& matrix) {
		float num1 = (position.X * matrix.M11 + position.Y * matrix.M21 + position.Z * matrix.M31) + matrix.M41;
		float num2 = (position.X * matrix.M12 + position.Y * matrix.M22 + position.Z * matrix.M32) + matrix.M42;
		float num3 = (position.X * matrix.M13 + position.Y * matrix.M23 + position.Z * matrix.M33) + matrix.M43;
		Vector3 vector3;
		vector3.X = num1;
		vector3.Y = num2;
		vector3.Z = num3;
		return vector3;
	}

	constexpr bool dxna::BoundingBox::Intersects(BoundingSphere const& sphere) const {
		Vector3 result1 = Vector3::Clamp(sphere.Center, Min, Max);
		float result2 = Vector3::DistanceSquared(sphere.Center, result1);
		return result2 <= sphere.Radius * sphere.Radius;
	}
}

#endif
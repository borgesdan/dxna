#ifndef DXNA_STRUCTS_HPP
#define DXNA_STRUCTS_HPP

#include <vector>
#include <memory>
#include "cs/cs.hpp"
#include "enumerations.hpp"
#include "mathhelper.hpp"
#include "utility.hpp"
#include "error.hpp"

namespace dxna {
	struct Matrix;
	struct Quaternion;
	struct Plane;
	struct BoundingSphere;
	struct BoundingFrustum;
	struct Ray;

	struct Point {
		int X{ 0 };
		int Y{ 0 };

		constexpr Point() noexcept = default;
		constexpr Point(int x, int y) noexcept : X(x), Y(y) {}

		static constexpr Point Zero() noexcept { return Point(); }
		
		constexpr bool operator==(Point const& other) const noexcept = default;	

		constexpr size_t GetHashCode() const noexcept {			
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			return seed;
		}
	};

	struct Rectangle {
		int X{ 0 };
		int Y{ 0 };
		int Width{ 0 };
		int Height{ 0 };

		constexpr Rectangle() noexcept = default;

		constexpr Rectangle(int x, int y, int width, int height) noexcept :
			X(x), Y(y), Width(width), Height(height) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			Hash::Combine(seed, Width);
			Hash::Combine(seed, Height);
			return seed;
		}

		static constexpr Rectangle Empty() noexcept { 
			return Rectangle(); 
		}

		constexpr intcs Left() const noexcept { return X; }

		constexpr intcs Right() const noexcept { return X + Width; }

		constexpr intcs Top() const noexcept { return Y; }

		constexpr intcs Bottom() const noexcept { return Y + Height; }

		constexpr void Offset(Point const& amount) noexcept {
			X += amount.X;
			Y += amount.Y;
		}

		constexpr void Offset(int offsetX, int offsetY) noexcept {
			X += offsetX;
			Y += offsetY;
		}

		constexpr void Inflate(int horizontalAmount, int verticalAmount) noexcept {
			X -= horizontalAmount;
			Y -= verticalAmount;
			Width += horizontalAmount * 2;
			Height += verticalAmount * 2;
		}

		constexpr bool Contains(int x, int y) const noexcept {
			return X <= x && x < X + Width && Y <= y && y < Y + Height;
		}

		constexpr bool Contains(Point const& value) const noexcept {
			return X <= value.X && value.X < X + Width && Y <= value.Y && value.Y < Y + Height;
		}

		constexpr bool Contains(Rectangle const& value) const noexcept {
			return X <= value.X && value.X + value.Width <= X + Width && Y <= value.Y && value.Y + value.Height <= Y + Height;
		}

		constexpr bool Intersects(Rectangle const& value) const noexcept {
			return value.X < X + Width && X < value.X + value.Width && value.Y < Y + Height && Y < value.Y + value.Height;
		}		

		static constexpr Rectangle Intersect(Rectangle const& value1, Rectangle const& value2) noexcept {
			const auto num1 = value1.X + value1.Width;
			const auto num2 = value2.X + value2.Width;
			const auto num3 = value1.Y + value1.Height;
			const auto num4 = value2.Y + value2.Height;
			const auto num5 = value1.X > value2.X ? value1.X : value2.X;
			const auto num6 = value1.Y > value2.Y ? value1.Y : value2.Y;
			const auto num7 = num1 < num2 ? num1 : num2;
			const auto num8 = num3 < num4 ? num3 : num4;

			if (num7 > num5 && num8 > num6)
				return Rectangle(num5, num6, num7 - num5, num8 - num6);
			
			return Rectangle::Empty();
		}

		static constexpr Rectangle Union(Rectangle const& value1, Rectangle const& value2) noexcept {
			const auto num1 = value1.X + value1.Width;
			const auto num2 = value2.X + value2.Width;
			const auto num3 = value1.Y + value1.Height;
			const auto num4 = value2.Y + value2.Height;
			const auto num5 = value1.X < value2.X ? value1.X : value2.X;
			const auto num6 = value1.Y < value2.Y ? value1.Y : value2.Y;
			const auto num7 = num1 > num2 ? num1 : num2;
			const auto num8 = num3 > num4 ? num3 : num4;

			return Rectangle(num5, num6, num7 - num5, num8 - num6);
		}

		constexpr bool operator==(Rectangle const& value2) const noexcept = default;
	};

	struct Vector2 {
		float X{ 0 };
		float Y{ 0 };

		constexpr Vector2() noexcept = default;
		constexpr Vector2(float x, float y) noexcept : X(x), Y(y) {}
		constexpr Vector2(float value) noexcept : X(value), Y(value) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			return seed;
		}

		constexpr Vector2 operator-() const noexcept { return Vector2::Negate(*this); }
		constexpr bool operator==(Vector2 const& other) const noexcept = default;
		friend constexpr Vector2 operator+(Vector2 const& value1, Vector2 const& value2) noexcept { return Vector2::Add(value1, value2); }
		friend constexpr Vector2 operator-(Vector2 const& value1, Vector2 const& value2) noexcept { return Vector2::Subtract(value1, value2); }
		friend constexpr Vector2 operator*(Vector2 const& value1, Vector2 const& value2) noexcept { return Vector2::Multiply(value1, value2); }
		friend constexpr Vector2 operator*(Vector2 const& value, float scale) noexcept { return Vector2::Multiply(value, scale); }
		friend constexpr Vector2 operator*(float scale, Vector2 const& value) noexcept { return Vector2::Multiply(value, scale); }
		friend constexpr Vector2 operator/(Vector2 const& value1, Vector2 const& value2) noexcept { return Vector2::Divide(value1, value2); }
		friend constexpr Vector2 operator/(Vector2 const& value, float divider) noexcept { return Vector2::Divide(value, divider); }
		
		constexpr float LengthSquared() const noexcept { return X * X + Y * Y; }

		float Length() const noexcept;
		void Normalize() noexcept;

		static constexpr Vector2 Zero() noexcept { return Vector2(); }
		static constexpr Vector2 One() noexcept { return Vector2(1.0); }
		static constexpr Vector2 UnitX() noexcept { return Vector2(1.0, 0.0); }
		static constexpr Vector2 UnitY() noexcept { return Vector2(0.0, 1.0); }

		static float Distance(Vector2 const& value1, Vector2 const& value2) noexcept;

		static constexpr float DistanceSquared(Vector2 const& value1, Vector2 const& value2) noexcept {
			const auto num1 = value1.X - value2.X;
			const auto num2 = value1.Y - value2.Y;
			return num1 * num1 + num2 * num2;
		}

		static constexpr float Dot(Vector2 const& value1, Vector2 const& value2) noexcept {
			return value1.X * value2.X + value1.Y * value2.Y;
		}

		static constexpr Vector2 Reflect(Vector2 const& vector, Vector2 const& normal) noexcept {
			const auto num = vector.X * normal.X + vector.Y * normal.Y;
			return Vector2(
				vector.X - 2.0F * num * normal.X,
				vector.Y - 2.0F * num * normal.Y);
		}

		static constexpr Vector2 Min(Vector2 const& value1, Vector2 const& value2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X < value2.X ? value1.X : value2.X;
			vector2.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
			return vector2;
		}

		static constexpr Vector2 Max(Vector2 const& value1, Vector2 const& value2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X > value2.X ? value1.X : value2.X;
			vector2.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
			return vector2;
		}

		static constexpr Vector2 Clamp(Vector2 const& value1, Vector2 const& min, Vector2 const& max) noexcept {
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

		static constexpr Vector2 Lerp(Vector2 const& value1, Vector2 const& value2, float amount) noexcept {
			Vector2 vector2;
			vector2.X = value1.X + (value2.X - value1.X) * amount;
			vector2.Y = value1.Y + (value2.Y - value1.Y) * amount;
			return vector2;
		}

		static constexpr Vector2 Barycentric(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3,
			float amount1, float amount2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
			vector2.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
			return vector2;
		}

		static constexpr Vector2 SmoothStep(Vector2 const& value1, Vector2 const& value2, float amount) noexcept {
			amount = amount > 1.0 ? 1.0F : (amount < 0.0 ? 0.0F : amount);
			amount = amount * amount * (3.0F - 2.0F * amount);
			Vector2 vector2;
			vector2.X = value1.X + (value2.X - value1.X) * amount;
			vector2.Y = value1.Y + (value2.Y - value1.Y) * amount;
			return vector2;
		}

		static constexpr Vector2 CatmullRom(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3,
			Vector2 const& value4, float amount) noexcept {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			Vector2 vector2;
			vector2.X = 0.5F * (2.0F * value2.X + (-value1.X + value3.X) * amount + (2.0F * value1.X - 5.0F * value2.X + 4.0F * value3.X - value4.X) * num1 + (-value1.X + 3.0F * value2.X - 3.0F * value3.X + value4.X) * num2);
			vector2.Y = 0.5F * (2.0F * value2.Y + (-value1.Y + value3.Y) * amount + (2.0F * value1.Y - 5.0F * value2.Y + 4.0F * value3.Y - value4.Y) * num1 + (-value1.Y + 3.0F * value2.Y - 3.0F * value3.Y + value4.Y) * num2);
			return vector2;
		}

		static constexpr Vector2 Hermite(Vector2 const& value1, Vector2 const& tangent1, Vector2 const& value2,
			Vector2 const& tangent2, float amount) noexcept {
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

		static Vector2 Normalize(Vector2 const& value) noexcept;

		static constexpr Vector2 Negate(Vector2 const& value) noexcept {
			Vector2 vector2;
			vector2.X = -value.X;
			vector2.Y = -value.Y;
			return vector2;
		}

		static constexpr Vector2 Add(Vector2 const& value1, Vector2 const& value2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X + value2.X;
			vector2.Y = value1.Y + value2.Y;
			return vector2;
		}

		static constexpr Vector2 Subtract(Vector2 const& value1, Vector2 const& value2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X - value2.X;
			vector2.Y = value1.Y - value2.Y;
			return vector2;
		}

		static constexpr Vector2 Multiply(Vector2 const& value1, Vector2 const& value2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X * value2.X;
			vector2.Y = value1.Y * value2.Y;
			return vector2;
		}

		static constexpr Vector2 Multiply(Vector2 const& value1, float scaleFactor) noexcept {
			Vector2 vector2;
			vector2.X = value1.X * scaleFactor;
			vector2.Y = value1.Y * scaleFactor;
			return vector2;
		}

		static constexpr Vector2 Divide(Vector2 const& value1, Vector2 const& value2) noexcept {
			Vector2 vector2;
			vector2.X = value1.X / value2.X;
			vector2.Y = value1.Y / value2.Y;
			return vector2;
		}

		static constexpr Vector2 Divide(Vector2 const& value1, float divider) noexcept {
			const auto num = 1.0F / divider;
			Vector2 vector2;
			vector2.X = value1.X * num;
			vector2.Y = value1.Y * num;
			return vector2;
		}

		static constexpr Vector2 Transform(Vector2 const& position, Matrix const& matrix) noexcept;
		static constexpr Vector2 TransformNormal(Vector2 const& normal, Matrix const& matrix) noexcept;
		static constexpr Vector2 Transform(Vector2 const& value, Quaternion const& rotation) noexcept;

		static constexpr Error Transform(
			Vector2* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Matrix const& matrix,
			Vector2* destinationArray, 
			size_t destinationLength,
			size_t destinationIndex,
			size_t length) noexcept;		

		static constexpr Error Transform(
			Vector2* sourceArray,
			size_t sourceIndex,			
			size_t sourceLength,
			Quaternion const& rotation,
			Vector2* destinationArray,
			size_t destinationIndex,
			size_t destinationLength,
			size_t length) noexcept;
		
		static constexpr Error TransformNormal(
			Vector2* sourceArray,
			size_t sourceIndex,
			size_t sourceLength,
			Matrix const& matrix,
			Vector2* destinationArray,
			size_t destinationIndex,
			size_t destinationLength,
			size_t length) noexcept ;
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

		static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static constexpr Matrix CreateFromQuaternion(Quaternion const& quaternion);
		static Matrix CreateShadow(Vector3 const& lightDirection, Plane const& plane);
		static Matrix CreateReflection(Plane const& value);
		static constexpr Matrix Transform(Matrix const& value, Quaternion const& rotation);
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
		constexpr PlaneIntersectionType Intersects(Plane const& plane) const;
		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const;
		constexpr ContainmentType Contains(BoundingSphere const& sphere) const;
		static constexpr BoundingBox CreateFromSphere(BoundingSphere const& sphere);
		constexpr bool Intersects(BoundingFrustum const& frustum);
		constexpr PlaneIntersectionType Intersects(Plane const& plane);
		nullfloat Intersects(Ray const& ray) const;
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

		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const;
		constexpr bool Intersects(BoundingFrustum const& frustum) const;
		constexpr PlaneIntersectionType Intersects(Plane const& plane) const;
		nullfloat Intersects(Ray const& ray) const;
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

		constexpr PlaneIntersectionType Intersects(BoundingSphere const& sphere) const {
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

		nullfloat Intersects(Ray const& ray) const;

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
				const auto corner = getCorner(i);
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
				const auto corner = getCorner(i);

				if (plane.Intersects(corner) != result)
					result = PlaneIntersectionType::Intersecting;
			}

			return result;
		}

		constexpr nullfloat Intersects(Ray const& ray) const;

	public:
		static constexpr int PlaneCount = 6;
		static constexpr int CornerCount = 8;

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

		constexpr Vector3 getCorner(size_t index) const {
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

		nullfloat Intersects(BoundingBox const& box) const {
			return box.Intersects(*this);
		}

		nullfloat Intersects(BoundingFrustum const& frustum) const {
			frustum.Intersects(*this);
		}

		nullfloat Intersects(Plane const& plane) {
			plane.Intersects(*this);
		}

		nullfloat Intersects(BoundingSphere const& sphere) const {
			sphere.Intersects(*this);
		}
	};

	struct Color {
		constexpr Color() = default;

		constexpr Color(uintcs packedValue) : packedValue(packedValue) {}

		constexpr Color(intcs r, intcs g, intcs b, intcs a = 255) {
			if (((r | g | b | a) & -256) != 0) {
				r = clamp(r);
				g = clamp(g);
				b = clamp(b);
				a = clamp(a);
			}

			g <<= 8;
			b <<= 16;
			a <<= 24;

			packedValue = static_cast<uintcs>(r | g | b | a);
		}

		constexpr Color(float r, float g, float b, float a = 1.0F) {
			r = MathHelper::Clamp(r, 0.0F, 1.0F);
			g = MathHelper::Clamp(r, 0.0F, 1.0F);
			b = MathHelper::Clamp(r, 0.0F, 1.0F);
			a = MathHelper::Clamp(a, 0.0F, 1.0F);

			auto _r = static_cast<intcs>(r * 255);
			auto _g = static_cast<intcs>(g * 255);
			auto _b = static_cast<intcs>(b * 255);
			auto _a = static_cast<intcs>(a * 255);

			if (((_r | _g | _b | _a) & -256) != 0) {
				_r = clamp(_r);
				_g = clamp(_g);
				_b = clamp(_b);
				_a = clamp(_a);
			}

			_g <<= 8;
			_b <<= 16;
			_a <<= 24;

			packedValue = static_cast<uintcs>(_r | _g | _b | _a);
		}

		constexpr uintcs PackedValue() const { return packedValue; }
		constexpr bytecs R() const { return static_cast<bytecs>(packedValue); }
		constexpr bytecs G() const { return static_cast<bytecs>(packedValue >> 8); }
		constexpr bytecs B() const { return static_cast<bytecs>(packedValue >> 16); }
		constexpr bytecs A() const { return static_cast<bytecs>(packedValue >> 24); }

		constexpr void PackedValue(uintcs value) { packedValue = value; }
		constexpr void R(bytecs value) { packedValue = packedValue & 4294967040U | value; }
		constexpr void G(bytecs value) { packedValue = static_cast<uintcs>(static_cast<intcs>(packedValue) & -65281 | (intcs)value << 8); }
		constexpr void B(bytecs value) { packedValue = static_cast<uintcs>(static_cast<intcs>(packedValue) & -16711681 | (intcs)value << 16); }
		constexpr void A(bytecs value) { packedValue = static_cast<uintcs>(static_cast<intcs>(packedValue) & 16777215 | (intcs)value << 24); }

		static constexpr Color Lerp(Color const& value1, Color const& value2, float amount) {
			amount = MathHelper::Lerp(amount, 0.0F, 1.0F);

			const auto r = MathHelper::Lerp(value1.R(), value2.R(), amount);
			const auto g = MathHelper::Lerp(value1.G(), value2.G(), amount);
			const auto b = MathHelper::Lerp(value1.B(), value2.B(), amount);
			const auto a = MathHelper::Lerp(value1.A(), value2.A(), amount);

			return Color(r, g, b, a);
		}

		constexpr bool Equals(Color const& other) const {
			return packedValue == other.packedValue;
		}

		static constexpr Color FromNonPremultiplied(intcs r, intcs g, intcs b, intcs a) {
			r = clamp(r * a / ByteMaxValue);
			g = clamp(g * a / ByteMaxValue);
			b = clamp(b * a / ByteMaxValue);
			a = clamp(a);

			g <<= 8;
			b <<= 16;
			a <<= 24;

			return Color(r | g | b | a);
		}

		static constexpr Color Multiply(Color const& value, float scale) {
			const auto r = value.R() * scale;
			const auto g = value.G() * scale;
			const auto b = value.B() * scale;
			const auto a = value.A() * scale;

			return Color(
				static_cast<intcs>(r),
				static_cast<intcs>(g),
				static_cast<intcs>(b),
				static_cast<intcs>(a));
		}


	public:
		constexpr bool operator==(Color const& other) const {
			return Equals(other);
		}

		constexpr Color operator*(float scale) const {
			return Multiply(*this, scale);
		}

	private:
		static constexpr intcs clamp(intcs value) {
			if (value < 0)
				return 0;

			return value > ByteMaxValue ? ByteMaxValue : value;
		}

		uintcs packedValue{ 0 };
	};

	struct Colors {
		static constexpr Color Transparent{ Color(0U) };
		static constexpr Color AliceBlue{ Color(4294965488U) };
		static constexpr Color AntiqueWhite{ Color(4292340730U) };
		static constexpr Color Aqua{ Color(4294967040U) };
		static constexpr Color Aquamarine{ Color(4292149119U) };
		static constexpr Color Azure{ Color(4294967280U) };
		static constexpr Color Beige{ Color(4292670965U) };
		static constexpr Color Bisque{ Color(4291093759U) };
		static constexpr Color Black{ Color(4278190080U) };
		static constexpr Color BlanchedAlmond{ Color(4291685375U) };
		static constexpr Color Blue{ Color(4294901760U) };
		static constexpr Color BlueViolet{ Color(4293012362U) };
		static constexpr Color Brown{ Color(4280953509U) };
		static constexpr Color BurlyWood{ Color(4287084766U) };
		static constexpr Color CadetBlue{ Color(4288716383U) };
		static constexpr Color Chartreuse{ Color(4278255487U) };
		static constexpr Color Chocolate{ Color(4280183250U) };
		static constexpr Color Coral{ Color(4283465727U) };
		static constexpr Color CornflowerBlue{ Color(4293760356U) };
		static constexpr Color Cornsilk{ Color(4292671743U) };
		static constexpr Color Crimson{ Color(4282127580U) };
		static constexpr Color Cyan{ Color(4294967040U) };
		static constexpr Color DarkBlue{ Color(4287299584U) };
		static constexpr Color DarkCyan{ Color(4287335168U) };
		static constexpr Color DarkGoldenrod{ Color(4278945464U) };
		static constexpr Color DarkGray{ Color(4289309097U) };
		static constexpr Color DarkGreen{ Color(4278215680U) };
		static constexpr Color DarkKhaki{ Color(4285249469U) };
		static constexpr Color DarkMagenta{ Color(4287299723U) };
		static constexpr Color DarkOliveGreen{ Color(4281297749U) };
		static constexpr Color DarkOrange{ Color(4278226175U) };
		static constexpr Color DarkOrchid{ Color(4291572377U) };
		static constexpr Color DarkRed{ Color(4278190219U) };
		static constexpr Color DarkSalmon{ Color(4286224105U) };
		static constexpr Color DarkSeaGreen{ Color(4287347855U) };
		static constexpr Color DarkSlateBlue{ Color(4287315272U) };
		static constexpr Color DarkSlateGray{ Color(4283387695U) };
		static constexpr Color DarkTurquoise{ Color(4291939840U) };
		static constexpr Color DarkViolet{ Color(4292018324U) };
		static constexpr Color DeepPink{ Color(4287829247U) };
		static constexpr Color DeepSkyBlue{ Color(4294950656U) };
		static constexpr Color DimGray{ Color(4285098345U) };
		static constexpr Color DodgerBlue{ Color(4294938654U) };
		static constexpr Color Firebrick{ Color(4280427186U) };
		static constexpr Color FloralWhite{ Color(4293982975U) };
		static constexpr Color ForestGreen{ Color(4280453922U) };
		static constexpr Color Fuchsia{ Color(4294902015U) };
		static constexpr Color Gainsboro{ Color(4292664540U) };
		static constexpr Color GhostWhite{ Color(4294965496U) };
		static constexpr Color Gold{ Color(4278245375U) };
		static constexpr Color Goldenrod{ Color(4280329690U) };
		static constexpr Color Gray{ Color(4286611584U) };
		static constexpr Color Green{ Color(4278222848U) };
		static constexpr Color GreenYellow{ Color(4281335725U) };
		static constexpr Color Honeydew{ Color(4293984240U) };
		static constexpr Color HotPink{ Color(4290013695U) };
		static constexpr Color IndianRed{ Color(4284243149U) };
		static constexpr Color Indigo{ Color(4286709835U) };
		static constexpr Color Ivory{ Color(4293984255U) };
		static constexpr Color Khaki{ Color(4287424240U) };
		static constexpr Color Lavender{ Color(4294633190U) };
		static constexpr Color LavenderBlush{ Color(4294308095U) };
		static constexpr Color LawnGreen{ Color(4278254716U) };
		static constexpr Color LemonChiffon{ Color(4291689215U) };
		static constexpr Color LightBlue{ Color(4293318829U) };
		static constexpr Color LightCoral{ Color(4286611696U) };
		static constexpr Color LightCyan{ Color(4294967264U) };
		static constexpr Color LightGoldenrodYellow{ Color(4292016890U) };
		static constexpr Color LightGreen{ Color(4287688336U) };
		static constexpr Color LightGray{ Color(4292072403U) };
		static constexpr Color LightPink{ Color(4290885375U) };
		static constexpr Color LightSalmon{ Color(4286226687U) };
		static constexpr Color LightSeaGreen{ Color(4289376800U) };
		static constexpr Color LightSkyBlue{ Color(4294626951U) };
		static constexpr Color LightSlateGray{ Color(4288252023U) };
		static constexpr Color LightSteelBlue{ Color(4292789424U) };
		static constexpr Color LightYellow{ Color(4292935679U) };
		static constexpr Color Lime{ Color(4278255360U) };
		static constexpr Color LimeGreen{ Color(4281519410U) };
		static constexpr Color Linen{ Color(4293325050U) };
		static constexpr Color Magenta{ Color(4294902015U) };
		static constexpr Color Maroon{ Color(4278190208U) };
		static constexpr Color MediumAquamarine{ Color(4289383782U) };
		static constexpr Color MediumBlue{ Color(4291624960U) };
		static constexpr Color MediumOrchid{ Color(4292040122U) };
		static constexpr Color MediumPurple{ Color(4292571283U) };
		static constexpr Color MediumSeaGreen{ Color(4285641532U) };
		static constexpr Color MediumSlateBlue{ Color(4293814395U) };
		static constexpr Color MediumSpringGreen{ Color(4288346624U) };
		static constexpr Color MediumTurquoise{ Color(4291613000U) };
		static constexpr Color MediumVioletRed{ Color(4286911943U) };
		static constexpr Color MidnightBlue{ Color(4285536537U) };
		static constexpr Color MintCream{ Color(4294639605U) };
		static constexpr Color MistyRose{ Color(4292994303U) };
		static constexpr Color Moccasin{ Color(4290110719U) };
		static constexpr Color NavajoWhite{ Color(4289584895U) };
		static constexpr Color Navy{ Color(4286578688U) };
		static constexpr Color OldLace{ Color(4293326333U) };
		static constexpr Color Olive{ Color(4278222976U) };
		static constexpr Color OliveDrab{ Color(4280520299U) };
		static constexpr Color Orange{ Color(4278232575U) };
		static constexpr Color OrangeRed{ Color(4278207999U) };
		static constexpr Color Orchid{ Color(4292243674U) };
		static constexpr Color PaleGoldenrod{ Color(4289390830U) };
		static constexpr Color PaleGreen{ Color(4288215960U) };
		static constexpr Color PaleTurquoise{ Color(4293848751U) };
		static constexpr Color PaleVioletRed{ Color(4287852763U) };
		static constexpr Color PapayaWhip{ Color(4292210687U) };
		static constexpr Color PeachPuff{ Color(4290370303U) };
		static constexpr Color Peru{ Color(4282353101U) };
		static constexpr Color Pink{ Color(4291543295U) };
		static constexpr Color Plum{ Color(4292714717U) };
		static constexpr Color PowderBlue{ Color(4293320880U) };
		static constexpr Color Purple{ Color(4286578816U) };
		static constexpr Color Red{ Color(4278190335U) };
		static constexpr Color RosyBrown{ Color(4287598524U) };
		static constexpr Color RoyalBlue{ Color(4292962625U) };
		static constexpr Color SaddleBrown{ Color(4279453067U) };
		static constexpr Color Salmon{ Color(4285694202U) };
		static constexpr Color SandyBrown{ Color(4284523764U) };
		static constexpr Color SeaGreen{ Color(4283927342U) };
		static constexpr Color SeaShell{ Color(4293850623U) };
		static constexpr Color Sienna{ Color(4281160352U) };
		static constexpr Color Silver{ Color(4290822336U) };
		static constexpr Color SkyBlue{ Color(4293643911U) };
		static constexpr Color SlateBlue{ Color(4291648106U) };
		static constexpr Color SlateGray{ Color(4287660144U) };
		static constexpr Color Snow{ Color(4294638335U) };
		static constexpr Color SpringGreen{ Color(4286578432U) };
		static constexpr Color SteelBlue{ Color(4290019910U) };
		static constexpr Color Tan{ Color(4287411410U) };
		static constexpr Color Teal{ Color(4286611456U) };
		static constexpr Color Thistle{ Color(4292394968U) };
		static constexpr Color Tomato{ Color(4282868735U) };
		static constexpr Color Turquoise{ Color(4291878976U) };
		static constexpr Color Violet{ Color(4293821166U) };
		static constexpr Color Wheat{ Color(4289978101U) };
		static constexpr Color White{ Color(UIntMaxValue) };
		static constexpr Color WhiteSmoke{ Color(4294309365U) };
		static constexpr Color Yellow{ Color(4278255615U) };
		static constexpr Color YellowGreen{ Color(4281519514U) };
	};

	struct CurveKey {
		float Position{ 0 };
		float TangentIn{ 0 };
		float TangentOut{ 0 };
		float Value{ 0 };
		CurveContinuity Continuity{ CurveContinuity::Smooth };

		constexpr CurveKey() = default;

		CurveKey(float position, float value, float tangentIn = 0, float tangentOut = 0, CurveContinuity continuity = CurveContinuity::Smooth):
			Position(position), Value(value), TangentIn(tangentIn), TangentOut(tangentOut), Continuity(continuity){}

		constexpr bool operator==(CurveKey const& other) const {
			return Equals(other);
		}

		constexpr bool Equals(const CurveKey& other) const	{
			return Position == other.Position 
				&& TangentIn == other.TangentIn 
				&& TangentOut == other.TangentOut 
				&& Value == other.Value 
				&& Continuity == other.Continuity;
		}
	};	

	struct CurveKeyCollection {
		constexpr CurveKey* operator[](size_t index) {
			if (keys.empty() || index > keys.size())
				return nullptr;

			return &keys[index];
		}

		constexpr cs::Nullable<CurveKey> Get(size_t index) const {
			if (keys.empty() || index > keys.size())
				return cs::Nullable<CurveKey>();

			return keys[index];
		}
		
		constexpr size_t Count() const { return keys.size(); }

		constexpr CurveKey* Last() {
			if (keys.empty())
				return nullptr;

			return &keys[keys.size() - 1];
		}

		constexpr void Add(CurveKey const& item) {
			if (Count() == 0) {
				keys.push_back(item);
			}

			for (size_t i = 0; i < keys.size(); ++i) {
				if (item.Position < keys[i].Position) {
					keys.insert(keys.begin() + i, item);
					return;
				}
			}

			keys.push_back(item);
		}

		constexpr void Clear() {
			keys.clear();
		}
	
	private:
		std::vector<CurveKey> keys;
	};

	struct Curve {
		constexpr Curve() = default;

		constexpr bool IsConstant() const {
			return Keys.Count() <= 1;
		}

		constexpr float Evaluate(float position) {
			if (Keys.Count() == 0)
				return 0.0F;

			if (Keys.Count() == 1)
				return Keys[0]->Value;

			const auto first = Keys[0];
			const auto last = Keys.Last();
			auto cycle = 0;
			auto virtualPos = 0.0F;

			if (position < first->Position) {
				switch (PreLoop)
				{
				case dxna::CurveLoopType::Constant:
					return first->Value;
				
				case dxna::CurveLoopType::Cycle:
					cycle = GetNumberOfCycle(position);
					 virtualPos = position - (cycle * (last->Position - first->Position));
					return GetCurvePosition(virtualPos);
				
				case dxna::CurveLoopType::CycleOffset:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return (GetCurvePosition(virtualPos) + cycle * (last->Value - first->Value));
				
				case dxna::CurveLoopType::Oscillate:
					if (0 == std::fmod(static_cast<float>(cycle), 2.0f))
						virtualPos = position - (cycle * (last->Position - first->Position));
					else
						virtualPos = last->Position - position + first->Position + (cycle * (last->Position - first->Position));					
					
					return GetCurvePosition(virtualPos);
				
				case dxna::CurveLoopType::Linear:
					return first->Value - first->TangentIn * (first->Position - position);
				
				default:
					break;
				}			
			} else if (position > last->Position) {
				auto cycle = 0;
				auto virtualPos = 0.0F;
				
				switch (PostLoop)
				{
				case dxna::CurveLoopType::Constant:
					return last->Value;
				case dxna::CurveLoopType::Cycle:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return GetCurvePosition(virtualPos);

				case dxna::CurveLoopType::CycleOffset:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return (GetCurvePosition(virtualPos) + cycle * (last->Value - first->Value));					
				case dxna::CurveLoopType::Oscillate:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					
					if (0 == std::fmod(static_cast<float>(cycle), 2.0f))
						virtualPos = position - (cycle * (last->Position - first->Position));
					else
						virtualPos = last->Position - position + first->Position + (cycle * (last->Position - first->Position));

					return GetCurvePosition(virtualPos);
				
				case dxna::CurveLoopType::Linear:
					return last->Value + first->TangentOut * (position - last->Position);
				
				default:
					break;
				}
			}
		}
		
		constexpr void ComputeTangents(CurveTangent const& tangentInType, CurveTangent const& tangentOutType) {
			for (size_t i = 0; i < Keys.Count(); ++i) {
				ComputeTangent(i, tangentInType, tangentOutType);
			}
		}

		constexpr void ComputeTangent(size_t keyIndex, CurveTangent tangentInType, CurveTangent tangentOutType) {
			auto key = Keys[keyIndex];

			float p0, p, p1;
			p0 = p = p1 = key->Position;

			float v0, v, v1;
			v0 = v = v1 = key->Value;

			if (keyIndex > 0)
			{
				p0 = Keys[keyIndex - 1]->Position;
				v0 = Keys[keyIndex - 1]->Value;
			}

			if (keyIndex < Keys.Count() - 1)
			{
				p1 = Keys[keyIndex + 1]->Position;
				v1 = Keys[keyIndex + 1]->Value;
			}

			switch (tangentInType)
			{
			case CurveTangent::Flat:
				key->TangentIn = 0;
				break;
			case CurveTangent::Linear:
				key->TangentIn = v - v0;
				break;
			case CurveTangent::Smooth:
				const auto pn = p1 - p0;
				if (std::abs(pn) < std::numeric_limits<float>::epsilon())
					key->TangentIn = 0;
				else
					key->TangentIn = (v1 - v0) * ((p - p0) / pn);
				break;
			}

			switch (tangentOutType)
			{
			case CurveTangent::Flat:
				key->TangentOut = 0;
				break;
			case CurveTangent::Linear:
				key->TangentOut = v1 - v;
				break;
			case CurveTangent::Smooth:
				const auto pn = p1 - p0;
				if (std::abs(pn) < std::numeric_limits<float>::epsilon())
					key->TangentOut = 0;
				else
					key->TangentOut = (v1 - v0) * ((p1 - p) / pn);
				break;
			}
		}

	public:
		CurveLoopType PreLoop;
		CurveLoopType PostLoop;	
		CurveKeyCollection Keys;

	private:
		int GetNumberOfCycle(float position) {
			float cycle = (position - Keys[0]->Position) / (Keys.Last()->Position - Keys[0]->Position);
			
			if (cycle < 0.0f)
				cycle--;

			return static_cast<int>(cycle);
		}

		float GetCurvePosition(float position) {			
			auto prev = Keys[0];			

			for (size_t i = 1; i < Keys.Count(); ++i) {
				const auto next = Keys[i];

				if (next->Position >= position) {
					if (prev->Continuity == CurveContinuity::Step) {
						if (position >= 1.0f) {
							return next->Value;
						}

						return prev->Value;
					}
					const auto t = (position - prev->Position) / (next->Position - prev->Position);
					const auto ts = t * t;
					const auto tss = ts * t;
					
					return (2 * tss - 3 * ts + 1.0f) * prev->Value + (tss - 2 * ts + t) * prev->TangentOut + (3 * ts - 2 * tss) * next->Value + (tss - ts) * next->TangentIn;
				}
				
				prev = next;
			}

			return 0.0f;
		}
	};
}

// ---------------------------------- Vector2 ----------------------------------//
namespace dxna {
	constexpr Vector2 Vector2::Transform(Vector2 const& position, Matrix const& matrix) noexcept {
		const auto num1 = (position.X * matrix.M11 + position.Y * matrix.M21) + matrix.M41;
		const auto num2 = (position.X * matrix.M12 + position.Y * matrix.M22) + matrix.M42;

		return Vector2(num1, num2);
	}

	constexpr Vector2 Vector2::TransformNormal(Vector2 const& normal, Matrix const& matrix) noexcept {
		const auto num1 = (normal.X * matrix.M11 + normal.Y * matrix.M21);
		const auto num2 = (normal.X * matrix.M12 + normal.Y * matrix.M22);

		return Vector2(num1, num2);
	}

	constexpr Vector2 Vector2::Transform(Vector2 const& value, Quaternion const& rotation) noexcept {
		const auto num1 = rotation.X + rotation.X;
		const auto num2 = rotation.Y + rotation.Y;
		const auto num3 = rotation.Z + rotation.Z;
		const auto num4 = rotation.W * num3;
		const auto num5 = rotation.X * num1;
		const auto num6 = rotation.X * num2;
		const auto num7 = rotation.Y * num2;
		const auto num8 = rotation.Z * num3;
		const auto num9 = (value.X * (1.0F - num7 - num8) + value.Y * (num6 - num4));
		const auto num10 = (value.X * (num6 + num4) + value.Y * (1.0F - num5 - num8));

		return Vector2(num9, num10);
	}

	constexpr Error Vector2::Transform(
		Vector2* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Matrix const& matrix,
		Vector2* destinationArray,
		size_t destinationLength,
		size_t destinationIndex,
		size_t length) noexcept {
		if (sourceArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 0);

		if (destinationArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 4);

		if (sourceLength < sourceIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 2);

		if (destinationLength < destinationIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 5);

		for (size_t x = 0; x < length; x++) {
			const auto& position = sourceArray[sourceIndex + x];
			auto destination = destinationArray[destinationIndex + x];
			destination.X = (position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41;
			destination.Y = (position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42;
			destinationArray[destinationIndex + x] = destination;
		}

		return Error::NoError();
	}	

	constexpr Error Vector2::Transform(
		Vector2* sourceArray,
		size_t sourceIndex,
		size_t sourceLength,
		Quaternion const& rotation,
		Vector2* destinationArray,
		size_t destinationIndex,
		size_t destinationLength,
		size_t length) noexcept {

		if (sourceArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 0);

		if (destinationArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 4);

		if (sourceLength < sourceIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 2);

		if (destinationLength < destinationIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 5);

		for (size_t x = 0; x < length; x++) {
			auto& position = sourceArray[sourceIndex + x];
			auto destination = destinationArray[destinationIndex + x];

			Vector2 v = Transform(position, rotation);

			destination.X = v.X;
			destination.Y = v.Y;

			destinationArray[destinationIndex + x] = destination;
		}

		return Error::NoError();
	}	

	constexpr Error Vector2::TransformNormal(
		Vector2* sourceArray,
		size_t sourceIndex,
		size_t sourceLength,
		Matrix const& matrix,
		Vector2* destinationArray,
		size_t destinationIndex,
		size_t destinationLength,
		size_t length) noexcept {

		if (sourceArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 0);

		if (destinationArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 4);

		if (sourceLength < sourceIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 2);

		if (destinationLength < destinationIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 5);

		for (size_t i = 0; i < length; i++) {
			const auto& normal = sourceArray[sourceIndex + i];

			destinationArray[destinationIndex + i] = Vector2(
				(normal.X * matrix.M11) + (normal.Y * matrix.M21),
				(normal.X * matrix.M12) + (normal.Y * matrix.M22));
		}

		return Error::NoError();
	}
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

	constexpr Vector3 Vector3::TransformNormal(Vector3 const& normal, Matrix const& matrix)
	{
		const auto num1 = (normal.X * matrix.M11 + normal.Y * matrix.M21 + normal.Z * matrix.M31);
		const auto num2 = (normal.X * matrix.M12 + normal.Y * matrix.M22 + normal.Z * matrix.M32);
		const auto num3 = (normal.X * matrix.M13 + normal.Y * matrix.M23 + normal.Z * matrix.M33);
		Vector3 vector3;
		vector3.X = num1;
		vector3.Y = num2;
		vector3.Z = num3;
		return vector3;
	}

	constexpr Vector3 Vector3::Transform(Vector3 const& value, Quaternion const& rotation)
	{
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
		const auto num13 = (value.X * (1.0F - num10 - num12) + value.Y * (num8 - num6) + value.Z * (num9 + num5));
		const auto num14 = (value.X * (num8 + num6) + value.Y * (1.0F - num7 - num12) + value.Z * (num11 - num4));
		const auto num15 = (value.X * (num9 - num5) + value.Y * (num11 + num4) + value.Z * (1.0F - num7 - num10));
		Vector3 vector3;
		vector3.X = num13;
		vector3.Y = num14;
		vector3.Z = num15;
		return vector3;
	}

	constexpr void Vector3::Transform(Vector3* sourceArray, Matrix const& matrix, Vector3* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex) {
		if (sourceArray == nullptr)
			return;

		if (destinationArray == nullptr)
			return;

		if (length < sourceIndex + length)
			return;

		if (length < destinationIndex + length)
			return;
		
		for (; length > 0; --length)
		{
			float x = sourceArray[sourceIndex].X;
			float y = sourceArray[sourceIndex].Y;
			float z = sourceArray[sourceIndex].Z;
			destinationArray[destinationIndex].X = (x * matrix.M11 + y * matrix.M21 + z * matrix.M31) + matrix.M41;
			destinationArray[destinationIndex].Y = (x * matrix.M12 + y * matrix.M22 + z * matrix.M32) + matrix.M42;
			destinationArray[destinationIndex].Z = (x * matrix.M13 + y * matrix.M23 + z * matrix.M33) + matrix.M43;
			++sourceIndex;
			++destinationIndex;
		}
	}

	constexpr void Vector3::TransformNormal(Vector3* sourceArray, Matrix const& matrix, Vector3* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex) {
		if (sourceArray == nullptr)
			return;

		if (destinationArray == nullptr)
			return;

		if (length < sourceIndex + length)
			return;

		if (length < destinationIndex + length)
			return;

		for (; length > 0; --length)
		{
			float x = sourceArray[sourceIndex].X;
			float y = sourceArray[sourceIndex].Y;
			float z = sourceArray[sourceIndex].Z;
			destinationArray[destinationIndex].X = (x * matrix.M11 + y * matrix.M21 + z * matrix.M31);
			destinationArray[destinationIndex].Y = (x * matrix.M12 + y * matrix.M22 + z * matrix.M32);
			destinationArray[destinationIndex].Z = (x * matrix.M13 + y * matrix.M23 + z * matrix.M33);
			++sourceIndex;
			++destinationIndex;
		}
	}

	constexpr void Vector3::Transform(Vector3* sourceArray, Quaternion const& rotation, Vector3* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex) {
		if (sourceArray == nullptr)
			return;

		if (destinationArray == nullptr)
			return;

		if (length < sourceIndex + length)
			return;

		if (length < destinationIndex + length)
			return;
		
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

		for (; length > 0; --length)
		{
			float x = sourceArray[sourceIndex].X;
			float y = sourceArray[sourceIndex].Y;
			float z = sourceArray[sourceIndex].Z;
			destinationArray[destinationIndex].X = (x * num13 + y * num14 + z * num15);
			destinationArray[destinationIndex].Y = (x * num16 + y * num17 + z * num18);
			destinationArray[destinationIndex].Z = (x * num19 + y * num20 + z * num21);
			++sourceIndex;
			++destinationIndex;
		}
	}

	constexpr bool dxna::BoundingBox::Intersects(BoundingSphere const& sphere) const {
		Vector3 result1 = Vector3::Clamp(sphere.Center, Min, Max);
		float result2 = Vector3::DistanceSquared(sphere.Center, result1);
		return result2 <= sphere.Radius * sphere.Radius;
	}

	constexpr PlaneIntersectionType BoundingBox::Intersects(Plane const& plane) const
	{
		Vector3 vector3_1;
		vector3_1.X = plane.Normal.X >= 0.0 ? Min.X : Max.X;
		vector3_1.Y = plane.Normal.Y >= 0.0 ? Min.Y : Max.Y;
		vector3_1.Z = plane.Normal.Z >= 0.0 ? Min.Z : Max.Z;
		Vector3 vector3_2;
		vector3_2.X = plane.Normal.X >= 0.0 ? Max.X : Min.X;
		vector3_2.Y = plane.Normal.Y >= 0.0 ? Max.Y : Min.Y;
		vector3_2.Z = plane.Normal.Z >= 0.0 ? Max.Z : Min.Z;
		
		if (plane.Normal.X * vector3_1.X + plane.Normal.Y * vector3_1.Y + plane.Normal.Z * vector3_1.Z + plane.D > 0.0)
			return PlaneIntersectionType::Front;
		
		return plane.Normal.X * vector3_2.X + plane.Normal.Y * vector3_2.Y + plane.Normal.Z * vector3_2.Z + plane.D < 0.0 ? PlaneIntersectionType::Back: PlaneIntersectionType::Intersecting;
	}

	constexpr ContainmentType BoundingBox::Contains(BoundingFrustum const& frustum) const
	{
		if (!frustum.Intersects(*this))
			return ContainmentType::Disjoint;

		for (size_t i = 0; i < frustum.CornerCount; ++i) {
			const auto corner = frustum.getCorner(i);

			if(Contains(corner) == ContainmentType::Disjoint)
				return ContainmentType::Intersects;
		}
		
		return ContainmentType::Contains;
	}

	constexpr ContainmentType BoundingBox::Contains(BoundingSphere const& sphere) const
	{
		Vector3 result1 = Vector3::Clamp(sphere.Center, Min, Max);
		float result2 = Vector3::DistanceSquared(sphere.Center, result1);
		float radius = sphere.Radius;

		if (result2 > radius * radius)
			return ContainmentType::Disjoint;

		return Min.X + radius > sphere.Center.X
			|| sphere.Center.X > Max.X - radius
			|| Max.X - Min.X <= radius
			|| Min.Y + radius > sphere.Center.Y
			|| sphere.Center.Y > Max.Y - radius
			|| Max.Y - Min.Y <= radius 
			|| Min.Z + radius > sphere.Center.Z
			|| sphere.Center.Z > Max.Z - radius
			|| Max.X - Min.X <= radius ? ContainmentType::Intersects : ContainmentType::Contains;
	}

	constexpr BoundingBox BoundingBox::CreateFromSphere(BoundingSphere const& sphere)
	{
		BoundingBox fromSphere;
		fromSphere.Min.X = sphere.Center.X - sphere.Radius;
		fromSphere.Min.Y = sphere.Center.Y - sphere.Radius;
		fromSphere.Min.Z = sphere.Center.Z - sphere.Radius;
		fromSphere.Max.X = sphere.Center.X + sphere.Radius;
		fromSphere.Max.Y = sphere.Center.Y + sphere.Radius;
		fromSphere.Max.Z = sphere.Center.Z + sphere.Radius;
		return fromSphere;
	}

	constexpr bool BoundingBox::Intersects(BoundingFrustum const& frustum)
	{
		return frustum.Intersects(*this);
	}

	constexpr PlaneIntersectionType BoundingBox::Intersects(Plane const& plane)
	{
		Vector3 vector3_1;
		vector3_1.X = plane.Normal.X >= 0.0 ? Min.X : Max.X;
		vector3_1.Y = plane.Normal.Y >= 0.0 ? Min.Y : Max.Y;
		vector3_1.Z = plane.Normal.Z >= 0.0 ? Min.Z : Max.Z;
		
		Vector3 vector3_2;
		vector3_2.X = plane.Normal.X >= 0.0 ? Max.X : Min.X;
		vector3_2.Y = plane.Normal.Y >= 0.0 ? Max.Y : Min.Y;
		vector3_2.Z = plane.Normal.Z >= 0.0 ? Max.Z : Min.Z;
		
		if (plane.Normal.X * vector3_1.X + plane.Normal.Y * vector3_1.Y + plane.Normal.Z * vector3_1.Z + plane.D > 0.0)
			return PlaneIntersectionType::Front;

		return plane.Normal.X * vector3_2.X 
			+ plane.Normal.Y * vector3_2.Y
			+ plane.Normal.Z * vector3_2.Z
			+ plane.D < 0.0 ? PlaneIntersectionType::Back : PlaneIntersectionType::Intersecting;
	}	

	constexpr Vector4 dxna::Vector4::Transform(Vector2 const& position, Matrix const& matrix)
	{
		float num1 = (position.X * matrix.M11 + position.Y * matrix.M21) + matrix.M41;
		float num2 = (position.X * matrix.M12 + position.Y * matrix.M22) + matrix.M42;
		float num3 = (position.X * matrix.M13 + position.Y * matrix.M23) + matrix.M43;
		float num4 = (position.X * matrix.M14 + position.Y * matrix.M24) + matrix.M44;
		Vector4 vector4;
		vector4.X = num1;
		vector4.Y = num2;
		vector4.Z = num3;
		vector4.W = num4;
		return vector4;
	}
	
	constexpr Vector4 Vector4::Transform(Vector3 const& position, Matrix const& matrix) {
		float num1 = (position.X * matrix.M11 + position.Y * matrix.M21 + position.Z * matrix.M31) + matrix.M41;
		float num2 = (position.X * matrix.M12 + position.Y * matrix.M22 + position.Z * matrix.M32) + matrix.M42;
		float num3 = (position.X * matrix.M13 + position.Y * matrix.M23 + position.Z * matrix.M33) + matrix.M43;
		float num4 = (position.X * matrix.M14 + position.Y * matrix.M24 + position.Z * matrix.M34) + matrix.M44;
		Vector4 vector4;
		vector4.X = num1;
		vector4.Y = num2;
		vector4.Z = num3;
		vector4.W = num4;
		return vector4;
	}
	
	constexpr Vector4 Vector4::Transform(Vector4 const& vector, Matrix const& matrix)
	{
		float num1 = (vector.X * matrix.M11 + vector.Y * matrix.M21 + vector.Z * matrix.M31 + vector.W * matrix.M41);
		float num2 = (vector.X * matrix.M12 + vector.Y * matrix.M22 + vector.Z * matrix.M32 + vector.W * matrix.M42);
		float num3 = (vector.X * matrix.M13 + vector.Y * matrix.M23 + vector.Z * matrix.M33 + vector.W * matrix.M43);
		float num4 = (vector.X * matrix.M14 + vector.Y * matrix.M24 + vector.Z * matrix.M34 + vector.W * matrix.M44);
		Vector4 vector4;
		vector4.X = num1;
		vector4.Y = num2;
		vector4.Z = num3;
		vector4.W = num4;
		return vector4;
	}
	
	constexpr Vector4 Vector4::Transform(Vector2 const& value, Quaternion const& rotation)
	{
		float num1 = rotation.X + rotation.X;
		float num2 = rotation.Y + rotation.Y;
		float num3 = rotation.Z + rotation.Z;
		float num4 = rotation.W * num1;
		float num5 = rotation.W * num2;
		float num6 = rotation.W * num3;
		float num7 = rotation.X * num1;
		float num8 = rotation.X * num2;
		float num9 = rotation.X * num3;
		float num10 = rotation.Y * num2;
		float num11 = rotation.Y * num3;
		float num12 = rotation.Z * num3;
		float num13 = (value.X * (1.0F - num10 - num12) + value.Y * (num8 - num6));
		float num14 = (value.X * (num8 + num6) + value.Y * (1.0F - num7 - num12));
		float num15 = (value.X * (num9 - num5) + value.Y * (num11 + num4));
		Vector4 vector4;
		vector4.X = num13;
		vector4.Y = num14;
		vector4.Z = num15;
		vector4.W = 1.0f;
		return vector4;
	}
	
	constexpr Vector4 Vector4::Transform(Vector3 const& value, Quaternion const& rotation) {
		float num1 = rotation.X + rotation.X;
		float num2 = rotation.Y + rotation.Y;
		float num3 = rotation.Z + rotation.Z;
		float num4 = rotation.W * num1;
		float num5 = rotation.W * num2;
		float num6 = rotation.W * num3;
		float num7 = rotation.X * num1;
		float num8 = rotation.X * num2;
		float num9 = rotation.X * num3;
		float num10 = rotation.Y * num2;
		float num11 = rotation.Y * num3;
		float num12 = rotation.Z * num3;
		float num13 = (value.X * (1.0F - num10 - num12) + value.Y * (num8 - num6) + value.Z * (num9 + num5));
		float num14 = (value.X * (num8 + num6) + value.Y * (1.0F - num7 - num12) + value.Z * (num11 - num4));
		float num15 = (value.X * (num9 - num5) + value.Y * (num11 + num4) + value.Z * (1.0F - num7 - num10));
		Vector4 vector4;
		vector4.X = num13;
		vector4.Y = num14;
		vector4.Z = num15;
		vector4.W = 1.0f;
		return vector4;
	}
	
	constexpr Vector4 Vector4::Transform(Vector4 const& value, Quaternion const& rotation)
	{
		float num1 = rotation.X + rotation.X;
		float num2 = rotation.Y + rotation.Y;
		float num3 = rotation.Z + rotation.Z;
		float num4 = rotation.W * num1;
		float num5 = rotation.W * num2;
		float num6 = rotation.W * num3;
		float num7 = rotation.X * num1;
		float num8 = rotation.X * num2;
		float num9 = rotation.X * num3;
		float num10 = rotation.Y * num2;
		float num11 = rotation.Y * num3;
		float num12 = rotation.Z * num3;
		float num13 = (value.X * (1.0F - num10 - num12) + value.Y * (num8 - num6) + value.Z * (num9 + num5));
		float num14 = (value.X * (num8 + num6) + value.Y * (1.0F - num7 - num12) + value.Z * (num11 - num4));
		float num15 = (value.X * (num9 - num5) + value.Y * (num11 + num4) + value.Z * (1.0F - num7 - num10));
		Vector4 vector4;
		vector4.X = num13;
		vector4.Y = num14;
		vector4.Z = num15;
		vector4.W = value.W;
		return vector4;
	}
	
	constexpr void Vector4::Transform(Vector4* sourceArray, Matrix const& matrix, Vector4* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex) {
		if (sourceArray == nullptr)
			return;

		if (destinationArray == nullptr)
			return;

		if (length < sourceIndex + length)
			return;

		if (length < destinationIndex + length)
			return;
		
		for (; length > 0; --length)
		{
			float x = sourceArray[sourceIndex].X;
			float y = sourceArray[sourceIndex].Y;
			float z = sourceArray[sourceIndex].Z;
			float w = sourceArray[sourceIndex].W;
			destinationArray[destinationIndex].X = (x * matrix.M11 + y * matrix.M21 + z * matrix.M31 + w * matrix.M41);
			destinationArray[destinationIndex].Y = (x * matrix.M12 + y * matrix.M22 + z * matrix.M32 + w * matrix.M42);
			destinationArray[destinationIndex].Z = (x * matrix.M13 + y * matrix.M23 + z * matrix.M33 + w * matrix.M43);
			destinationArray[destinationIndex].W = (x * matrix.M14 + y * matrix.M24 + z * matrix.M34 + w * matrix.M44);
			++sourceIndex;
			++destinationIndex;
		}
	}
	
	constexpr void Vector4::Transform(Vector4* sourceArray, Quaternion const& rotation, Vector4* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex){
		if (sourceArray == nullptr)
			return;

		if (destinationArray == nullptr)
			return;

		if (length < sourceIndex + length)
			return;

		if (length < destinationIndex + length)
			return;

		float num1 = rotation.X + rotation.X;
		float num2 = rotation.Y + rotation.Y;
		float num3 = rotation.Z + rotation.Z;
		float num4 = rotation.W * num1;
		float num5 = rotation.W * num2;
		float num6 = rotation.W * num3;
		float num7 = rotation.X * num1;
		float num8 = rotation.X * num2;
		float num9 = rotation.X * num3;
		float num10 = rotation.Y * num2;
		float num11 = rotation.Y * num3;
		float num12 = rotation.Z * num3;
		float num13 = 1.0f - num10 - num12;
		float num14 = num8 - num6;
		float num15 = num9 + num5;
		float num16 = num8 + num6;
		float num17 = 1.0f - num7 - num12;
		float num18 = num11 - num4;
		float num19 = num9 - num5;
		float num20 = num11 + num4;
		float num21 = 1.0f - num7 - num10;
		for (; length > 0; --length)
		{
			float x = sourceArray[sourceIndex].X;
			float y = sourceArray[sourceIndex].Y;
			float z = sourceArray[sourceIndex].Z;
			float w = sourceArray[sourceIndex].W;
			destinationArray[destinationIndex].X = (x * num13 + y * num14 + z * num15);
			destinationArray[destinationIndex].Y = (x * num16 + y * num17 + z * num18);
			destinationArray[destinationIndex].Z = (x * num19 + y * num20 + z * num21);
			destinationArray[destinationIndex].W = w;
			++sourceIndex;
			++destinationIndex;
		}
	}

	constexpr Matrix dxna::Matrix::CreateFromQuaternion(Quaternion const& quaternion)
	{
		float num1 = quaternion.X * quaternion.X;
		float num2 = quaternion.Y * quaternion.Y;
		float num3 = quaternion.Z * quaternion.Z;
		float num4 = quaternion.X * quaternion.Y;
		float num5 = quaternion.Z * quaternion.W;
		float num6 = quaternion.Z * quaternion.X;
		float num7 = quaternion.Y * quaternion.W;
		float num8 = quaternion.Y * quaternion.Z;
		float num9 = quaternion.X * quaternion.W;

		Matrix result;
		result.M11 = (1.0f - 2.0F * (num2 + num3));
		result.M12 = (2.0f * (num4 + num5));
		result.M13 = (2.0f * (num6 - num7));
		result.M14 = 0.0f;
		result.M21 = (2.0f * (num4 - num5));
		result.M22 = (1.0f - 2.0F * (num3 + num1));
		result.M23 = (2.0f * (num8 + num9));
		result.M24 = 0.0f;
		result.M31 = (2.0f * (num6 + num7));
		result.M32 = (2.0f * (num8 - num9));
		result.M33 = (1.0f - 2.0F * (num2 + num1));
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;

		return result;
	}

	constexpr Matrix dxna::Matrix::Transform(Matrix const& value, Quaternion const& rotation)
	{
		float num1 = rotation.X + rotation.X;
		float num2 = rotation.Y + rotation.Y;
		float num3 = rotation.Z + rotation.Z;
		float num4 = rotation.W * num1;
		float num5 = rotation.W * num2;
		float num6 = rotation.W * num3;
		float num7 = rotation.X * num1;
		float num8 = rotation.X * num2;
		float num9 = rotation.X * num3;
		float num10 = rotation.Y * num2;
		float num11 = rotation.Y * num3;
		float num12 = rotation.Z * num3;
		float num13 = 1.0f - num10 - num12;
		float num14 = num8 - num6;
		float num15 = num9 + num5;
		float num16 = num8 + num6;
		float num17 = 1.0f - num7 - num12;
		float num18 = num11 - num4;
		float num19 = num9 - num5;
		float num20 = num11 + num4;
		float num21 = 1.0f - num7 - num10;
		Matrix matrix;
		matrix.M11 = (value.M11 * num13 + value.M12 * num14 + value.M13 * num15);
		matrix.M12 = (value.M11 * num16 + value.M12 * num17 + value.M13 * num18);
		matrix.M13 = (value.M11 * num19 + value.M12 * num20 + value.M13 * num21);
		matrix.M14 = value.M14;
		matrix.M21 = (value.M21 * num13 + value.M22 * num14 + value.M23 * num15);
		matrix.M22 = (value.M21 * num16 + value.M22 * num17 + value.M23 * num18);
		matrix.M23 = (value.M21 * num19 + value.M22 * num20 + value.M23 * num21);
		matrix.M24 = value.M24;
		matrix.M31 = (value.M31 * num13 + value.M32 * num14 + value.M33 * num15);
		matrix.M32 = (value.M31 * num16 + value.M32 * num17 + value.M33 * num18);
		matrix.M33 = (value.M31 * num19 + value.M32 * num20 + value.M33 * num21);
		matrix.M34 = value.M34;
		matrix.M41 = (value.M41 * num13 + value.M42 * num14 + value.M43 * num15);
		matrix.M42 = (value.M41 * num16 + value.M42 * num17 + value.M43 * num18);
		matrix.M43 = (value.M41 * num19 + value.M42 * num20 + value.M43 * num21);
		matrix.M44 = value.M44;
		return matrix;
	}

	constexpr nullfloat BoundingFrustum::Intersects(Ray const& ray) const
	{
		ContainmentType result1 = Contains(ray.Position);
		auto result = nullfloat();

		if (result1 == ContainmentType::Contains) {
			return 0.0f;
		}
		else {
			float num1 = FloatMinValue;
			float num2 = FloatMaxValue;

			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto plane = getPlane(i);

				Vector3 normal = plane.Normal;
				float result2 = Vector3::Dot(ray.Direction, normal);
				float result3 = Vector3::Dot(ray.Position, normal);
				result3 += plane.D;

				if (std::abs(result2) < 9.9999997473787516E-06)
				{
					if (result3 > 0.0)
						return result;
				}
				else
				{
					float num3 = -result3 / result2;
					if (result2 < 0.0)
					{
						if (num3 > num2)
							return result;
						if (num3 > num1)
							num1 = num3;
					}
					else
					{
						if (num3 < num1)
							return result;
						if (num3 < num2)
							num2 = num3;
					}
				}
			}

			float num4 = num1 >= 0.0 ? num1 : num2;

			if (num4 < 0.0)
				return result;

			result = num4;
		}

		return result;
	}

	constexpr ContainmentType dxna::BoundingSphere::Contains(BoundingFrustum const& frustum) const
	{
		if (!frustum.Intersects(*this))
			return ContainmentType::Disjoint;

		float num = Radius * Radius;
		
		for (size_t i = 0; i < frustum.CornerCount; ++i) {
			const auto corner = frustum.getCorner(i);
			
			Vector3 vector3;
			vector3.X = corner.X - Center.X;
			vector3.Y = corner.Y - Center.Y;
			vector3.Z = corner.Z - Center.Z;
			
			if (vector3.LengthSquared() > num)
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}
	
	constexpr bool BoundingSphere::Intersects(BoundingFrustum const& frustum) const {
		return frustum.Intersects(*this);
	}
	
	constexpr PlaneIntersectionType BoundingSphere::Intersects(Plane const& plane) const {
		return plane.Intersects(*this);
	}	

	constexpr PlaneIntersectionType Plane::Intersects(BoundingFrustum const& frustum) const {
		return frustum.Intersects(*this);
	}
}

#endif
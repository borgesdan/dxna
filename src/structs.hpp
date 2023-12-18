#ifndef DXNA_STRUCTS_HPP
#define DXNA_STRUCTS_HPP

#include <vector>
#include <memory>
#include "cs/cs.hpp"
#include "enumerations.hpp"
#include "mathhelper.hpp"
#include "utility.hpp"
#include "error.hpp"
#include "types.hpp"

namespace dxna {
	struct Matrix;
	struct Quaternion;
	struct Plane;
	struct BoundingSphere;
	struct BoundingFrustum;
	struct Ray;

	// Describes a 2D-point.
	struct Point {
		int X{ 0 };
		int Y{ 0 };

		constexpr Point() noexcept = default;
		constexpr Point(int x, int y) noexcept : X(x), Y(y) {}
		constexpr Point(int value) noexcept : X(value), Y(value) {}

		static constexpr Point Zero() noexcept { return Point(); }

		constexpr bool operator==(Point const& other) const noexcept = default;

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			return seed;
		}
	};

	// Describes a 2D-rectangle. 
	struct Rectangle {
		int X{ 0 };
		int Y{ 0 };
		int Width{ 0 };
		int Height{ 0 };

		constexpr Rectangle() noexcept = default;

		constexpr Rectangle(int x, int y, int width, int height) noexcept :
			X(x), Y(y), Width(width), Height(height) {}

		constexpr Rectangle(Point const& location, Point const& size) noexcept :
			X(location.X), Y(location.Y), Width(size.X), Height(size.Y) {}

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

	// Describes a 2D-vector.
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
			Vector2 const* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Matrix const& matrix,
			Vector2* destinationArray,
			size_t destinationLength,
			size_t destinationIndex,
			size_t length);

		static constexpr Error Transform(
			Vector2 const* sourceArray,
			size_t sourceIndex,
			size_t sourceLength,
			Quaternion const& rotation,
			Vector2* destinationArray,
			size_t destinationIndex,
			size_t destinationLength,
			size_t length);
	};

	// Describes a 3D-vector.
	struct Vector3 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };

		constexpr Vector3() noexcept {}
		constexpr Vector3(float x, float y, float z) noexcept : X(x), Y(y), Z(z) {}
		constexpr Vector3(float value) noexcept : X(value), Y(value), Z(value) {}
		constexpr Vector3(Vector2 const& value, float z) noexcept : X(value.X), Y(value.Y), Z(z) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			Hash::Combine(seed, Z);
			return seed;
		}

		constexpr Vector3 operator-() const noexcept { return Vector3::Negate(*this); }
		constexpr bool operator==(Vector3 const& other) const noexcept = default;
		friend constexpr Vector3 operator+(Vector3 const& value1, Vector3 const& value2) noexcept { return Vector3::Add(value1, value2); }
		friend constexpr Vector3 operator-(Vector3 const& value1, Vector3 const& value2) noexcept { return Vector3::Subtract(value1, value2); }
		friend constexpr Vector3 operator*(Vector3 const& value1, Vector3 const& value2) noexcept { return Vector3::Multiply(value1, value2); }
		friend constexpr Vector3 operator*(Vector3 const& value, float scale) noexcept { return Vector3::Multiply(value, scale); }
		friend constexpr Vector3 operator*(float scale, Vector3 const& value) noexcept { return Vector3::Multiply(value, scale); }
		friend constexpr Vector3 operator/(Vector3 const& value1, Vector3 const& value2) noexcept { return Vector3::Divide(value1, value2); }
		friend constexpr Vector3 operator/(Vector3 const& value, float divider) noexcept { return Vector3::Divide(value, divider); }

		constexpr Vector3 operator+=(Vector3 const& other) const { return Vector3::Add(*this, other); }
		constexpr Vector3 operator-=(Vector3 const& other) const { return Vector3::Subtract(*this, other); }
		constexpr Vector3 operator*=(Vector3 const& other) const { return Vector3::Multiply(*this, other); }
		constexpr Vector3 operator/=(Vector3 const& other) const { return Vector3::Divide(*this, other); }


		float Length() const noexcept;
		void Normalize() noexcept;

		constexpr bool Equals(const Vector3& other) const noexcept { return X == other.X && Y == other.Y && Z == other.Z; }
		constexpr float LengthSquared() const noexcept { return (X * X) + (Y * Y) + (Z * Z); }

		static constexpr Vector3 Zero() noexcept { return Vector3(); };
		static constexpr Vector3 One() noexcept { return Vector3(1.F, 1.F, 1.F); }
		static constexpr Vector3 UnitX() noexcept { return Vector3(1.0F, 0.0, 0.0); }
		static constexpr Vector3 UnitY() noexcept { return Vector3(0.0, 1.0F, 0.0); }
		static constexpr Vector3 UnitZ() noexcept { return Vector3(0.0, 0.0, 1.0F); }
		static constexpr Vector3 Up() noexcept { return UnitY(); }
		static constexpr Vector3 Down() noexcept { return -UnitY(); }
		static constexpr Vector3 Right() noexcept { return UnitX(); }
		static constexpr Vector3 Left() noexcept { { return -UnitX(); } }
		static constexpr Vector3 Forward() noexcept { return -UnitZ(); }
		static constexpr Vector3 Backward() noexcept { return UnitZ(); }

		static float Distance(Vector3 const& value1, Vector3 const& value2) noexcept;

		static constexpr float DistanceSquared(Vector3 const& value1, Vector3 const& value2) noexcept {
			const auto num1 = value1.X - value2.X;
			const auto num2 = value1.Y - value2.Y;
			const auto num3 = value1.Z - value2.Z;
			return num1 * num1 + num2 * num2 + num3 * num3;
		}

		static constexpr float Dot(Vector3 const& vector1, Vector3 const& vector2) noexcept {
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z;
		}

		static constexpr Vector3 Cross(Vector3 const& vector1, Vector3 const& vector2) noexcept {
			Vector3 vector3;
			vector3.X = vector1.Y * vector2.Z - vector1.Z * vector2.Y;
			vector3.Y = vector1.Z * vector2.X - vector1.X * vector2.Z;
			vector3.Z = vector1.X * vector2.Y - vector1.Y * vector2.X;
			return vector3;
		}

		static constexpr Vector3 lect(Vector3 const& vector, Vector3 const& normal) noexcept {
			const auto num = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;
			Vector3 vector3;
			vector3.X = vector.X - 2.0F * num * normal.X;
			vector3.Y = vector.Y - 2.0F * num * normal.Y;
			vector3.Z = vector.Z - 2.0F * num * normal.Z;
			return vector3;
		}

		static constexpr Vector3 Min(Vector3 const& value1, Vector3 const& value2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X < value2.X ? value1.X : value2.X;
			vector3.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
			vector3.Z = value1.Z < value2.Z ? value1.Z : value2.Z;
			return vector3;
		}

		static constexpr Vector3 Max(Vector3 const& value1, Vector3 const& value2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X > value2.X ? value1.X : value2.X;
			vector3.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
			vector3.Z = value1.Z > value2.Z ? value1.Z : value2.Z;
			return vector3;
		}

		static constexpr Vector3 Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max) noexcept {
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

		static constexpr Vector3 Lerp(Vector3 const& value1, Vector3 const& value2, float amount) noexcept {
			Vector3 vector3;
			vector3.X = value1.X + (value2.X - value1.X) * amount;
			vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;
			return vector3;
		}

		static constexpr Vector3 Barycentric(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3,
			float amount1, float amount2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
			vector3.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
			vector3.Z = value1.Z + amount1 * (value2.Z - value1.Z) + amount2 * (value3.Z - value1.Z);
			return vector3;
		}

		static constexpr Vector3 SmoothStep(Vector3 const& value1, Vector3 const& value2, float amount) noexcept {
			amount = amount > 1.0F ? 1.0F : (amount < 0.0 ? 0.0F : amount);
			amount = amount * amount * (3.0F - 2.0F * amount);
			Vector3 vector3;
			vector3.X = value1.X + (value2.X - value1.X) * amount;
			vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;
			return vector3;
		}

		static constexpr Vector3 CatmullRom(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3,
			Vector3 const& value4, float amount) noexcept {
			const auto num1 = amount * amount;
			const auto num2 = amount * num1;
			Vector3 vector3;
			vector3.X = (0.5F * (2.0F * value2.X + (-value1.X + value3.X) * amount + (2.0F * value1.X - 5.0F * value2.X + 4.0F * value3.X - value4.X) * num1 + (-value1.X + 3.0F * value2.X - 3.0F * value3.X + value4.X) * num2));
			vector3.Y = (0.5F * (2.0F * value2.Y + (-value1.Y + value3.Y) * amount + (2.0F * value1.Y - 5.0F * value2.Y + 4.0F * value3.Y - value4.Y) * num1 + (-value1.Y + 3.0F * value2.Y - 3.0F * value3.Y + value4.Y) * num2));
			vector3.Z = (0.5F * (2.0F * value2.Z + (-value1.Z + value3.Z) * amount + (2.0F * value1.Z - 5.0F * value2.Z + 4.0F * value3.Z - value4.Z) * num1 + (-value1.Z + 3.0F * value2.Z - 3.0F * value3.Z + value4.Z) * num2));
			return vector3;
		}

		static constexpr Vector3 Hermite(Vector3 const& value1, Vector3 const& tangent1, Vector3 const& value2,
			Vector3 const& tangent2, float amount) noexcept {
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

		static Vector3 Normalize(Vector3 const& value) noexcept;

		static constexpr Vector3 Negate(Vector3 const& value) noexcept {
			Vector3 vector;
			vector.X = -value.X;
			vector.Y = -value.Y;
			vector.Z = -value.Z;
			return vector;
		}

		static constexpr Vector3 Add(Vector3 const& value1, Vector3 const& value2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X + value2.X;
			vector3.Y = value1.Y + value2.Y;
			vector3.Z = value1.Z + value2.Z;
			return vector3;
		}

		static constexpr Vector3 Subtract(Vector3 const& value1, Vector3 const& value2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X - value2.X;
			vector3.Y = value1.Y - value2.Y;
			vector3.Z = value1.Z - value2.Z;
			return vector3;
		}

		static constexpr Vector3 Multiply(Vector3 const& value1, Vector3 const& value2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X * value2.X;
			vector3.Y = value1.Y * value2.Y;
			vector3.Z = value1.Z * value2.Z;
			return vector3;
		}

		static constexpr Vector3 Multiply(Vector3 const& value1, float scaleFactor) noexcept {
			Vector3 vector3;
			vector3.X = value1.X * scaleFactor;
			vector3.Y = value1.Y * scaleFactor;
			vector3.Z = value1.Z * scaleFactor;
			return vector3;
		}

		static constexpr Vector3 Divide(Vector3 const& value1, Vector3 const& value2) noexcept {
			Vector3 vector3;
			vector3.X = value1.X / value2.X;
			vector3.Y = value1.Y / value2.Y;
			vector3.Z = value1.Z / value2.Z;
			return vector3;
		}

		static constexpr Vector3 Divide(Vector3 const& value1, float value2) noexcept {
			float num = 1.0F / value2;
			Vector3 vector3;
			vector3.X = value1.X * num;
			vector3.Y = value1.Y * num;
			vector3.Z = value1.Z * num;
			return vector3;
		}

		static constexpr Vector3 Transform(Vector3 const& position, Matrix const& matrix) noexcept;
		static constexpr Vector3 TransformNormal(Vector3 const& normal, Matrix const& matrix) noexcept;
		static constexpr Vector3 Transform(Vector3 const& value, Quaternion const& rotation) noexcept;

		static constexpr Error Transform(
			Vector3 const* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Matrix const& matrix,
			Vector3* destinationArray,
			size_t destinationLength,
			size_t destinationIndex,
			size_t length) noexcept;

		static constexpr Error Transform(
			Vector3 const* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Quaternion const& rotation,
			Vector3* destinationArray,
			size_t destinationLength,
			size_t destinationIndex,
			size_t length) noexcept;

		static constexpr Error TransformNormal(
			Vector3 const* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Matrix const& matrix,
			Vector3* destinationArray,
			size_t destinationLength,
			size_t destinationIndex,
			size_t length) noexcept;
	};

	// Describes a 4D-vector.
	struct Vector4 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		constexpr Vector4() noexcept = default;
		constexpr Vector4(float value) noexcept : X(value), Y(value), Z(value), W(value) {}
		constexpr Vector4(float x, float y, float z, float w) noexcept : X(x), Y(y), Z(z), W(w) {}
		constexpr Vector4(Vector2 value, float z, float w) noexcept : X(value.X), Y(value.Y), Z(z), W(w) {}
		constexpr Vector4(Vector3 value, float w) noexcept : X(value.X), Y(value.Y), Z(value.Z), W(w) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			Hash::Combine(seed, Z);
			Hash::Combine(seed, W);
			return seed;
		}

		constexpr Vector4 operator-() const noexcept { return Vector4::Negate(*this); }
		constexpr bool operator==(Vector4 const& other) const noexcept = default;
		friend constexpr Vector4 operator+(Vector4 const& value1, Vector4 const& value2) noexcept { return Vector4::Add(value1, value2); }
		friend constexpr Vector4 operator-(Vector4 const& value1, Vector4 const& value2) noexcept { return Vector4::Subtract(value1, value2); }
		friend constexpr Vector4 operator*(Vector4 const& value1, Vector4 const& value2) noexcept { return Vector4::Multiply(value1, value2); }
		friend constexpr Vector4 operator*(Vector4 const& value, float scale) noexcept { return Vector4::Multiply(value, scale); }
		friend constexpr Vector4 operator*(float scale, Vector4 const& value) noexcept { return Vector4::Multiply(value, scale); }
		friend constexpr Vector4 operator/(Vector4 const& value1, Vector4 const& value2) noexcept { return Vector4::Divide(value1, value2); }
		friend constexpr Vector4 operator/(Vector4 const& value, float divider) noexcept { return Vector4::Divide(value, divider); }

		float Length() const noexcept;
		void Normalize() noexcept;

		constexpr float LengthSquared() const noexcept {
			return (X * X) + (Y * Y) + (Z * Z) + (W * W);
		}
		static constexpr Vector4 Zero() noexcept { return Vector4(); }
		static constexpr Vector4 One() noexcept { return Vector4(1); }
		static constexpr Vector4 UnitX() noexcept { return Vector4(1.0F, 0.0F, 0.0F, 0.0F); }
		static constexpr Vector4 UnitY() noexcept { return Vector4(0.0F, 1.0F, 0.0F, 0.0F); }
		static constexpr Vector4 UnitZ() noexcept { return Vector4(0.0F, 0.0F, 1.0F, 0.0F); }
		static constexpr Vector4 UnitW() noexcept { return Vector4(0.0F, 0.0F, 0.0F, 1.0F); }

		static float Distance(Vector4 const& value1, Vector4 const& value2) noexcept;

		static constexpr float DistanceSquared(Vector4 value1, Vector4 value2) noexcept {
			const auto num1 = value1.X - value2.X;
			const auto num2 = value1.Y - value2.Y;
			const auto num3 = value1.Z - value2.Z;
			const auto num4 = value1.W - value2.W;
			return num1 * num1 + num2 * num2 + num3 * num3 + num4 * num4;
		}

		static constexpr float Dot(Vector4 vector1, Vector4 vector2) noexcept {
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z + vector1.W * vector2.W;
		}

		static constexpr Vector4 Min(Vector4 const& value1, Vector4 const& value2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X < value2.X ? value1.X : value2.X;
			vector4.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
			vector4.Z = value1.Z < value2.Z ? value1.Z : value2.Z;
			vector4.W = value1.W < value2.W ? value1.W : value2.W;
			return vector4;
		}

		static constexpr Vector4 Max(Vector4 const& value1, Vector4 const& value2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X > value2.X ? value1.X : value2.X;
			vector4.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
			vector4.Z = value1.Z > value2.Z ? value1.Z : value2.Z;
			vector4.W = value1.W > value2.W ? value1.W : value2.W;
			return vector4;
		}

		static constexpr Vector4 Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max) noexcept {
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

		static constexpr Vector4 Lerp(Vector4 const& value1, Vector4 const& value2, float amount) noexcept {
			Vector4 vector4;
			vector4.X = value1.X + (value2.X - value1.X) * amount;
			vector4.Y = value1.Y + (value2.Y - value1.Y) * amount;
			vector4.Z = value1.Z + (value2.Z - value1.Z) * amount;
			vector4.W = value1.W + (value2.W - value1.W) * amount;
			return vector4;
		}

		static constexpr Vector4 Barycentric(Vector4 const& value1, Vector4 const& value2,
			Vector4 const& value3, float amount1, float amount2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X + amount1 * (value2.X - value1.X) + amount2 * (value3.X - value1.X);
			vector4.Y = value1.Y + amount1 * (value2.Y - value1.Y) + amount2 * (value3.Y - value1.Y);
			vector4.Z = value1.Z + amount1 * (value2.Z - value1.Z) + amount2 * (value3.Z - value1.Z);
			vector4.W = value1.W + amount1 * (value2.W - value1.W) + amount2 * (value3.W - value1.W);
			return vector4;
		}

		static constexpr Vector4 SmoothStep(Vector4 const& value1, Vector4 const& value2, float amount) noexcept {
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
			Vector4 const& value4, float amount) noexcept {
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
			Vector4 const& tangent2, float amount) noexcept {
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

		static Vector4 Normalize(Vector4 const& value) noexcept;

		static constexpr Vector4 Negate(Vector4 const& value) noexcept {
			Vector4 vector4;
			vector4.X = -value.X;
			vector4.Y = -value.Y;
			vector4.Z = -value.Z;
			vector4.W = -value.W;
			return vector4;
		}

		static constexpr Vector4 Add(Vector4 const& value1, Vector4 const& value2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X + value2.X;
			vector4.Y = value1.Y + value2.Y;
			vector4.Z = value1.Z + value2.Z;
			vector4.W = value1.W + value2.W;
			return vector4;
		}

		static constexpr Vector4 Subtract(Vector4 const& value1, Vector4 const& value2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X - value2.X;
			vector4.Y = value1.Y - value2.Y;
			vector4.Z = value1.Z - value2.Z;
			vector4.W = value1.W - value2.W;
			return vector4;
		}

		static constexpr Vector4 Multiply(Vector4 const& value1, Vector4 const& value2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X * value2.X;
			vector4.Y = value1.Y * value2.Y;
			vector4.Z = value1.Z * value2.Z;
			vector4.W = value1.W * value2.W;
			return vector4;
		}

		static constexpr Vector4 Multiply(Vector4 const& value1, float scaleFactor) noexcept {
			Vector4 vector4;
			vector4.X = value1.X * scaleFactor;
			vector4.Y = value1.Y * scaleFactor;
			vector4.Z = value1.Z * scaleFactor;
			vector4.W = value1.W * scaleFactor;
			return vector4;
		}

		static constexpr Vector4 Divide(Vector4 const& value1, Vector4 const& value2) noexcept {
			Vector4 vector4;
			vector4.X = value1.X / value2.X;
			vector4.Y = value1.Y / value2.Y;
			vector4.Z = value1.Z / value2.Z;
			vector4.W = value1.W / value2.W;
			return vector4;
		}

		static constexpr Vector4 Divide(Vector4 const& value1, float divider) noexcept {
			float num = 1.0F / divider;
			Vector4 vector4;
			vector4.X = value1.X * num;
			vector4.Y = value1.Y * num;
			vector4.Z = value1.Z * num;
			vector4.W = value1.W * num;
			return vector4;
		}

		static constexpr Vector4 Transform(Vector2 const& position, Matrix const& matrix) noexcept;
		static constexpr Vector4 Transform(Vector3 const& position, Matrix const& matrix) noexcept;
		static constexpr Vector4 Transform(Vector4 const& vector, Matrix const& matrix) noexcept;
		static constexpr Vector4 Transform(Vector2 const& value, Quaternion const& rotation) noexcept;
		static constexpr Vector4 Transform(Vector3 const& position, Quaternion const& rotation) noexcept;
		static constexpr Vector4 Transform(Vector4 const& vector, Quaternion const& rotation) noexcept;

		static constexpr Error Transform(
			Vector4* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Matrix const& matrix,
			Vector4* destinationArray,
			size_t destinationLength,
			size_t destinationIndex,
			size_t length) noexcept;

		static constexpr Error Transform(
			Vector4* sourceArray,
			size_t sourceLength,
			size_t sourceIndex,
			Quaternion const& rotation,
			Vector4* destinationArray,
			size_t destinationLength,
			size_t destinationIndex,
			size_t length) noexcept;
	};

	// Represents the right-handed 4x4 floating point matrix, which can store translation, scale and rotation information.
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

		constexpr Matrix() noexcept = default;

		constexpr Matrix(
			float M11, float M12, float M13, float M14,
			float M21, float M22, float M23, float M24,
			float M31, float M32, float M33, float M34,
			float M41, float M42, float M43, float M44)
			noexcept :
			M11(M11), M12(M12), M13(M13), M14(M14),
			M21(M21), M22(M22), M23(M23), M24(M24),
			M31(M31), M32(M32), M33(M33), M34(M34),
			M41(M41), M42(M42), M43(M43), M44(M44) {
		}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, M11 + M12 + M13 + M14);
			Hash::Combine(seed, M21 + M22 + M23 + M24);
			Hash::Combine(seed, M31 + M32 + M33 + M34);
			Hash::Combine(seed, M41 + M42 + M43 + M44);

			return seed;
		}

		constexpr Matrix operator-() const noexcept { return Matrix::Negate(*this); }
		constexpr bool operator==(Matrix const& other) const noexcept = default;
		friend constexpr Matrix operator+(Matrix const& value1, Matrix const& value2) noexcept { return Matrix::Add(value1, value2); }
		friend constexpr Matrix operator-(Matrix const& value1, Matrix const& value2) noexcept { return Matrix::Subtract(value1, value2); }
		friend constexpr Matrix operator*(Matrix const& value1, Matrix const& value2) noexcept { return Matrix::Multiply(value1, value2); }
		friend constexpr Matrix operator*(Matrix const& value, float scale) noexcept { return Matrix::Multiply(value, scale); }
		friend constexpr Matrix operator*(float scale, Matrix const& value) noexcept { return Matrix::Multiply(value, scale); }
		friend constexpr Matrix operator/(Matrix const& value1, Matrix const& value2) noexcept { return Matrix::Divide(value1, value2); }
		friend constexpr Matrix operator/(Matrix const& value, float divider) noexcept { return Matrix::Divide(value, divider); }

		constexpr Vector3 Up() const noexcept {
			Vector3 up;
			up.X = M21;
			up.Y = M22;
			up.Z = M23;
			return up;
		}

		constexpr Vector3 Down() const noexcept {
			Vector3 down;
			down.X = -M21;
			down.Y = -M22;
			down.Z = -M23;
			return down;
		}

		constexpr Vector3 Right() const noexcept {
			Vector3 right;
			right.X = M11;
			right.Y = M12;
			right.Z = M13;
			return right;
		}

		constexpr Vector3 Left() const noexcept {
			Vector3 left;
			left.X = -M11;
			left.Y = -M12;
			left.Z = -M13;
			return left;
		}

		constexpr Vector3 Forward() const noexcept {
			Vector3 forward;
			forward.X = -M31;
			forward.Y = -M32;
			forward.Z = -M33;
			return forward;
		}

		constexpr Vector3 Backward() const noexcept {
			Vector3 backward;
			backward.X = M31;
			backward.Y = M32;
			backward.Z = M33;
			return backward;
		}

		constexpr Vector3 Translation() const noexcept {
			Vector3 translation;
			translation.X = M41;
			translation.Y = M42;
			translation.Z = M43;
			return translation;
		}

		constexpr void Up(Vector3 const& value) noexcept {
			M21 = value.X;
			M22 = value.Y;
			M23 = value.Z;
		}

		constexpr void Down(Vector3 const& value) noexcept {
			M21 = -value.X;
			M22 = -value.Y;
			M23 = -value.Z;
		}

		constexpr void Right(Vector3 const& value) noexcept {
			M11 = value.X;
			M12 = value.Y;
			M13 = value.Z;
		}

		constexpr void Left(Vector3 const& value) noexcept {
			M11 = -value.X;
			M12 = -value.Y;
			M13 = -value.Z;
		}

		constexpr void Forward(Vector3 const& value) noexcept {
			M31 = -value.X;
			M32 = -value.Y;
			M33 = -value.Z;
		}

		constexpr void Backward(Vector3 const& value) noexcept {
			M31 = value.X;
			M32 = value.Y;
			M33 = value.Z;
		}

		constexpr void Translation(Vector3 const& value) noexcept {
			M41 = value.X;
			M42 = value.Y;
			M43 = value.Z;
		}

		constexpr float Determinant() const noexcept {
			const auto m11 = M11;
			const auto m12 = M12;
			const auto m13 = M13;
			const auto m14 = M14;
			const auto m21 = M21;
			const auto m22 = M22;
			const auto m23 = M23;
			const auto m24 = M24;
			const auto m31 = M31;
			const auto m32 = M32;
			const auto m33 = M33;
			const auto m34 = M34;
			const auto m41 = M41;
			const auto m42 = M42;
			const auto m43 = M43;
			const auto m44 = M44;
			const auto num1 = m33 * m44 - m34 * m43;
			const auto num2 = m32 * m44 - m34 * m42;
			const auto num3 = m32 * m43 - m33 * m42;
			const auto num4 = m31 * m44 - m34 * m41;
			const auto num5 = m31 * m43 - m33 * m41;
			const auto num6 = m31 * m42 - m32 * m41;
			return (m11 * (m22 * num1 - m23 * num2 + m24 * num3)
				- m12 * (m21 * num1 - m23 * num4 + m24 * num5)
				+ m13 * (m21 * num2 - m22 * num4 + m24 * num6)
				- m14 * (m21 * num3 - m22 * num5 + m23 * num6));
		}

		static constexpr Matrix Identity() noexcept {
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		static Matrix CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 const& cameraUpVector, Vector3* const cameraForwardVector = nullptr) noexcept;

		static Matrix CreateConstrainedBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 rotateAxis, Vector3* const cameraForwardVector, Vector3* const objectForwardVector) noexcept;

		static constexpr Matrix CreateTranslation(Vector3 const& position) noexcept {
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

		static constexpr Matrix CreateTranslation(float xPosition, float yPosition, float zPosition) noexcept {
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

		static constexpr Matrix CreateScale(float xScale, float yScale, float zScale) noexcept {
			Matrix scale;
			scale.M11 = xScale;
			scale.M12 = 0.0f;
			scale.M13 = 0.0f;
			scale.M14 = 0.0f;
			scale.M21 = 0.0f;
			scale.M22 = yScale;
			scale.M23 = 0.0f;
			scale.M24 = 0.0f;
			scale.M31 = 0.0f;
			scale.M32 = 0.0f;
			scale.M33 = zScale;
			scale.M34 = 0.0f;
			scale.M41 = 0.0f;
			scale.M42 = 0.0f;
			scale.M43 = 0.0f;
			scale.M44 = 1.0f;
			return scale;
		}

		static constexpr Matrix CreateScale(Vector3 const& scales) noexcept {
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

		static constexpr Matrix CreateScale(float scale) noexcept {
			Matrix scale1;
			scale1.M11 = scale;
			scale1.M12 = 0.0f;
			scale1.M13 = 0.0f;
			scale1.M14 = 0.0f;
			scale1.M21 = 0.0f;
			scale1.M22 = scale;
			scale1.M23 = 0.0f;
			scale1.M24 = 0.0f;
			scale1.M31 = 0.0f;
			scale1.M32 = 0.0f;
			scale1.M33 = scale;
			scale1.M34 = 0.0f;
			scale1.M41 = 0.0f;
			scale1.M42 = 0.0f;
			scale1.M43 = 0.0f;
			scale1.M44 = 1.0f;
			return scale1;
		}

		static Matrix CreateRotationX(float radians) noexcept;
		static Matrix CreateRotationY(float radians) noexcept;
		static Matrix CreateRotationZ(float radians) noexcept;
		static Matrix CreateFromAxisAngle(Vector3 const& axis, float angle) noexcept;
		static Error CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, Matrix& result) noexcept;

		static constexpr Error CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance, Matrix& result) noexcept {
			if (nearPlaneDistance <= 0.0F)
				return Error(ErrorCode::ARGUMENT_LESS_OR_EQUAL_ZERO, 2);

			if (farPlaneDistance <= 0.0F)
				return Error(ErrorCode::ARGUMENT_LESS_OR_EQUAL_ZERO, 3);

			if (nearPlaneDistance >= farPlaneDistance)
				return Error(ErrorCode::ARGUMENT_GREATER_OR_EQUAL_OTHER, 2);

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

			result = perspective;
			return Error::NoError();
		}

		static Error CreatePerspectiveOffCenter(float left, float right, float bottom,
			float top, float nearPlaneDistance, float farPlaneDistance, Matrix& result) noexcept {
			const Matrix zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

			if (nearPlaneDistance <= 0.0F)
				return Error(ErrorCode::ARGUMENT_LESS_OR_EQUAL_ZERO, 2);

			if (farPlaneDistance <= 0.0F)
				return Error(ErrorCode::ARGUMENT_LESS_OR_EQUAL_ZERO, 3);

			if (nearPlaneDistance >= farPlaneDistance)
				return Error(ErrorCode::ARGUMENT_GREATER_OR_EQUAL_OTHER, 2);

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

			result = perspectiveOffCenter;
			return Error::NoError();
		}

		static constexpr Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) noexcept {
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
			float top, float zNearPlane, float zFarPlane) noexcept {

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

		static Matrix CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector) noexcept;
		static Matrix CreateWorld(Vector3 position, Vector3 forward, Vector3 up) noexcept;

		static constexpr Matrix Transpose(Matrix const& matrix) noexcept {
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

		static constexpr Matrix Invert(Matrix const& matrix) noexcept {
			const auto m11 = matrix.M11;
			const auto m12 = matrix.M12;
			const auto m13 = matrix.M13;
			const auto m14 = matrix.M14;
			const auto m21 = matrix.M21;
			const auto m22 = matrix.M22;
			const auto m23 = matrix.M23;
			const auto m24 = matrix.M24;
			const auto m31 = matrix.M31;
			const auto m32 = matrix.M32;
			const auto m33 = matrix.M33;
			const auto m34 = matrix.M34;
			const auto m41 = matrix.M41;
			const auto m42 = matrix.M42;
			const auto m43 = matrix.M43;
			const auto m44 = matrix.M44;
			const auto num1 = (m33 * m44 - m34 * m43);
			const auto num2 = (m32 * m44 - m34 * m42);
			const auto num3 = (m32 * m43 - m33 * m42);
			const auto num4 = (m31 * m44 - m34 * m41);
			const auto num5 = (m31 * m43 - m33 * m41);
			const auto num6 = (m31 * m42 - m32 * m41);
			const auto num7 = (m22 * num1 - m23 * num2 + m24 * num3);
			const auto num8 = -(m21 * num1 - m23 * num4 + m24 * num5);
			const auto num9 = (m21 * num2 - m22 * num4 + m24 * num6);
			const auto num10 = -(m21 * num3 - m22 * num5 + m23 * num6);
			const auto num11 = (1.0F / (m11 * num7 + m12 * num8 + m13 * num9 + m14 * num10));
			Matrix matrix1;
			matrix1.M11 = num7 * num11;
			matrix1.M21 = num8 * num11;
			matrix1.M31 = num9 * num11;
			matrix1.M41 = num10 * num11;
			matrix1.M12 = -(m12 * num1 - m13 * num2 + m14 * num3) * num11;
			matrix1.M22 = (m11 * num1 - m13 * num4 + m14 * num5) * num11;
			matrix1.M32 = -(m11 * num2 - m12 * num4 + m14 * num6) * num11;
			matrix1.M42 = (m11 * num3 - m12 * num5 + m13 * num6) * num11;
			const auto num12 = (m23 * m44 - m24 * m43);
			const auto num13 = (m22 * m44 - m24 * m42);
			const auto num14 = (m22 * m43 - m23 * m42);
			const auto num15 = (m21 * m44 - m24 * m41);
			const auto num16 = (m21 * m43 - m23 * m41);
			const auto num17 = (m21 * m42 - m22 * m41);
			matrix1.M13 = (m12 * num12 - m13 * num13 + m14 * num14) * num11;
			matrix1.M23 = -(m11 * num12 - m13 * num15 + m14 * num16) * num11;
			matrix1.M33 = (m11 * num13 - m12 * num15 + m14 * num17) * num11;
			matrix1.M43 = -(m11 * num14 - m12 * num16 + m13 * num17) * num11;
			const auto num18 = (m23 * m34 - m24 * m33);
			const auto num19 = (m22 * m34 - m24 * m32);
			const auto num20 = (m22 * m33 - m23 * m32);
			const auto num21 = (m21 * m34 - m24 * m31);
			const auto num22 = (m21 * m33 - m23 * m31);
			const auto num23 = (m21 * m32 - m22 * m31);
			matrix1.M14 = -(m12 * num18 - m13 * num19 + m14 * num20) * num11;
			matrix1.M24 = (m11 * num18 - m13 * num21 + m14 * num22) * num11;
			matrix1.M34 = -(m11 * num19 - m12 * num21 + m14 * num23) * num11;
			matrix1.M44 = (m11 * num20 - m12 * num22 + m13 * num23) * num11;
			return matrix1;
		}

		static constexpr Matrix Lerp(Matrix const& matrix1, Matrix const& matrix2, float amount) noexcept {
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

		static constexpr Matrix Negate(Matrix const& matrix) noexcept {
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

		static constexpr Matrix Add(Matrix const& matrix1, Matrix const& matrix2) noexcept {
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

		static constexpr Matrix Subtract(Matrix const& matrix1, Matrix const& matrix2) noexcept {
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

		static constexpr Matrix Multiply(Matrix const& matrix1, Matrix const& matrix2) noexcept {
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

		static constexpr Matrix Multiply(Matrix const& matrix1, float scaleFactor) noexcept {
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

		static constexpr Matrix Divide(Matrix const& matrix1, Matrix const& matrix2) noexcept {
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

		static constexpr Matrix Divide(Matrix const& matrix1, float divider)  noexcept {
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

		static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;
		static constexpr Matrix CreateFromQuaternion(Quaternion const& quaternion) noexcept;
		static Matrix CreateShadow(Vector3 const& lightDirection, Plane const& plane) noexcept;
		static Matrix CreateReflection(Plane const& value) noexcept;
		static constexpr Matrix Transform(Matrix const& value, Quaternion const& rotation) noexcept;
	};

	// An efficient mathematical representation for three dimensional rotations.
	struct Quaternion {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		constexpr Quaternion() noexcept = default;

		constexpr Quaternion(float X, float Y, float Z, float W) noexcept : X(X), Y(Y), Z(Z), W(W) {}

		constexpr Quaternion(Vector3 const& vectorPart, float scalarPart) noexcept
			: X(vectorPart.X), Y(vectorPart.Y), Z(vectorPart.Z), W(scalarPart) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, X);
			Hash::Combine(seed, Y);
			Hash::Combine(seed, Z);
			Hash::Combine(seed, W);
			return seed;
		}

		constexpr Quaternion operator-() const noexcept { return Quaternion::Negate(*this); }
		constexpr bool operator==(Quaternion const& other) const noexcept = default;
		friend constexpr Quaternion operator+(Quaternion const& value1, Quaternion const& value2) noexcept { return Quaternion::Add(value1, value2); }
		friend constexpr Quaternion operator-(Quaternion const& value1, Quaternion const& value2) noexcept { return Quaternion::Subtract(value1, value2); }
		friend constexpr Quaternion operator*(Quaternion const& value1, Quaternion const& value2) noexcept { return Quaternion::Multiply(value1, value2); }
		friend constexpr Quaternion operator*(Quaternion const& value, float scale) noexcept { return Quaternion::Multiply(value, scale); }
		friend constexpr Quaternion operator*(float scale, Quaternion const& value) noexcept { return Quaternion::Multiply(value, scale); }
		friend constexpr Quaternion operator/(Quaternion const& value1, Quaternion const& value2) noexcept { return Quaternion::Divide(value1, value2); }

		constexpr float LengthSquared() const noexcept { return X * X + Y * Y + Z * Z + W * W; }

		float Length() const noexcept;
		void Normalize() noexcept;
		void Conjugate() noexcept;

		static constexpr Quaternion Identity() noexcept { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

		static Quaternion Normalize(Quaternion const& quaternion) noexcept;

		static constexpr Quaternion Conjugate(Quaternion const& value) noexcept {
			Quaternion quaternion;
			quaternion.X = -value.X;
			quaternion.Y = -value.Y;
			quaternion.Z = -value.Z;
			quaternion.W = value.W;
			return quaternion;
		}

		static constexpr Quaternion Inverse(Quaternion const& quaternion) noexcept {
			float num = 1.0f / quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z + quaternion.W * quaternion.W;
			Quaternion quaternion1;
			quaternion1.X = -quaternion.X * num;
			quaternion1.Y = -quaternion.Y * num;
			quaternion1.Z = -quaternion.Z * num;
			quaternion1.W = quaternion.W * num;
			return quaternion1;
		}

		static Quaternion CreateFromAxisAngle(Vector3 const& axis, float angle) noexcept;
		static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;
		static Quaternion CreateFromRotationMatrix(Matrix const& matrix) noexcept;

		static constexpr float Dot(Quaternion const& quaternion1, Quaternion const& quaternion2) noexcept {
			return quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
		}

		static Quaternion Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount) noexcept;
		static Quaternion Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount) noexcept;

		static constexpr Quaternion Concatenate(Quaternion const& value1, Quaternion const& value2) noexcept {
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

		static constexpr Quaternion Negate(Quaternion const& quaternion) noexcept {
			Quaternion quaternion1;
			quaternion1.X = -quaternion.X;
			quaternion1.Y = -quaternion.Y;
			quaternion1.Z = -quaternion.Z;
			quaternion1.W = -quaternion.W;
			return quaternion1;
		}

		static constexpr Quaternion Add(Quaternion const& quaternion1, Quaternion const& quaternion2) noexcept {
			Quaternion quaternion;
			quaternion.X = quaternion1.X + quaternion2.X;
			quaternion.Y = quaternion1.Y + quaternion2.Y;
			quaternion.Z = quaternion1.Z + quaternion2.Z;
			quaternion.W = quaternion1.W + quaternion2.W;
			return quaternion;
		}

		static constexpr Quaternion Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2) noexcept {
			Quaternion quaternion;
			quaternion.X = quaternion1.X - quaternion2.X;
			quaternion.Y = quaternion1.Y - quaternion2.Y;
			quaternion.Z = quaternion1.Z - quaternion2.Z;
			quaternion.W = quaternion1.W - quaternion2.W;
			return quaternion;
		}

		static constexpr Quaternion Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2) noexcept {
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

		static constexpr Quaternion Multiply(Quaternion const& quaternion1, float scaleFactor) noexcept {
			Quaternion quaternion;
			quaternion.X = quaternion1.X * scaleFactor;
			quaternion.Y = quaternion1.Y * scaleFactor;
			quaternion.Z = quaternion1.Z * scaleFactor;
			quaternion.W = quaternion1.W * scaleFactor;
			return quaternion;
		}

		static constexpr Quaternion Divide(Quaternion const& quaternion1, Quaternion const& quaternion2) noexcept {
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

	// Represents an axis-aligned bounding box (AABB) in 3D space.
	struct BoundingBox {
		Vector3 Min;
		Vector3 Max;

		static constexpr int CornerCount = 8;

		constexpr BoundingBox() noexcept = default;

		constexpr BoundingBox(Vector3 const& min, Vector3 const& max) noexcept :
			Min(min), Max(max) {}

		constexpr size_t GetHashCode() const noexcept {
			return Min.GetHashCode() + Max.GetHashCode();
		}

		constexpr bool operator==(BoundingBox const& other) const noexcept {
			return Min == other.Min && Max == other.Max;
		}

		constexpr bool Intersects(BoundingBox const& box) const noexcept {
			if ((Max.X >= box.Min.X) && (Min.X <= box.Max.X)) {
				if ((Max.Y < box.Min.Y) || (Min.Y > box.Max.Y))
					return false;

				return (Max.Z >= box.Min.Z) && (Min.Z <= box.Max.Z);
			}

			return false;
		}

		constexpr ContainmentType Contains(BoundingBox const& box) const noexcept {
			if (Max.X < box.Min.X
				|| Min.X > box.Max.X
				|| Max.Y < box.Min.Y
				|| Min.Y > box.Max.Y
				|| Max.Z < box.Min.Z
				|| Min.Z > box.Max.Z)
				return ContainmentType::Disjoint;

			return box.Min.X >= Min.X
				&& box.Max.X <= Max.X
				&& box.Min.Y >= Min.Y
				&& box.Max.Y <= Max.Y
				&& box.Min.Z >= Min.Z
				&& box.Max.Z <= Max.Z
				? ContainmentType::Contains : ContainmentType::Intersects;
		}

		constexpr ContainmentType Contains(Vector3 const& point) const noexcept {
			return Min.X > point.X
				|| point.X > Max.X
				|| Min.Y > point.Y
				|| point.Y > Max.Y
				|| Min.Z > point.Z
				|| point.Z > Max.Z
				? ContainmentType::Disjoint : ContainmentType::Contains;
		}

		static constexpr BoundingBox CreateMerged(BoundingBox const& original, BoundingBox const& additional) noexcept {
			BoundingBox result;
			result.Min.X = std::min(original.Min.X, additional.Min.X);
			result.Min.Y = std::min(original.Min.Y, additional.Min.Y);
			result.Min.Z = std::min(original.Min.Z, additional.Min.Z);
			result.Max.X = std::max(original.Max.X, additional.Max.X);
			result.Max.Y = std::max(original.Max.Y, additional.Max.Y);
			result.Max.Z = std::max(original.Max.Z, additional.Max.Z);

			return result;
		}

		constexpr bool Intersects(BoundingSphere const& sphere) const noexcept;
		constexpr PlaneIntersectionType Intersects(Plane const& plane) const noexcept;
		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const;
		constexpr ContainmentType Contains(BoundingSphere const& sphere) const noexcept;
		static constexpr BoundingBox CreateFromSphere(BoundingSphere const& sphere) noexcept;
		constexpr bool Intersects(BoundingFrustum const& frustum) const noexcept;
		nullfloat Intersects(Ray const& ray) const noexcept;
	};

	// Describes a sphere in 3D-space for bounding operations.
	struct BoundingSphere {
		Vector3 Center;
		float Radius{ 0 };

		constexpr BoundingSphere() noexcept = default;

		constexpr BoundingSphere(Vector3 const& center, float radius) noexcept :
			Center(center), Radius(radius) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, Radius);
			return Center.GetHashCode() + seed;
		}

		constexpr bool operator==(BoundingSphere const& other) noexcept {
			return Center == other.Center && Radius == other.Radius;
		}

		static BoundingSphere CreateMerged(BoundingSphere const& original, BoundingSphere const& additional) noexcept;
		static BoundingSphere CreateFromBoundingBox(BoundingBox const& box) noexcept;
		static BoundingSphere CreateFromPoints(Vector3* points, size_t length, size_t offset = 0) noexcept;

		bool Intersects(BoundingBox const& box) const noexcept {
			const auto result1 = Vector3::Clamp(Center, box.Min, box.Max);
			const auto result2 = Vector3::DistanceSquared(Center, result1);
			return result2 <= Radius * Radius;
		}

		bool Intersects(BoundingSphere const& sphere) const noexcept {
			const auto result = Vector3::DistanceSquared(Center, sphere.Center);
			const auto radius1 = Radius;
			const auto radius2 = sphere.Radius;
			return radius1 * radius1 + 2.0F * radius1 * radius2 + radius2 * radius2 > result;
		}

		ContainmentType Contains(BoundingBox const& box) const noexcept;

		constexpr ContainmentType Contains(Vector3 point) const {
			return Vector3::DistanceSquared(point, Center) >= Radius * Radius ? ContainmentType::Disjoint : ContainmentType::Contains;
		}

		ContainmentType Contains(BoundingSphere sphere) const noexcept {
			const auto result = Vector3::Distance(Center, sphere.Center);
			const auto radius1 = Radius;
			const auto radius2 = sphere.Radius;

			if (radius1 + radius2 < result)
				return ContainmentType::Disjoint;

			return radius1 - radius2 < result ? ContainmentType::Intersects : ContainmentType::Contains;
		}

		BoundingSphere Transform(Matrix const& matrix) const noexcept;

		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const noexcept;
		constexpr bool Intersects(BoundingFrustum const& frustum) const noexcept;
		constexpr PlaneIntersectionType Intersects(Plane const& plane) const noexcept;
		nullfloat Intersects(Ray const& ray) const noexcept;
		static BoundingSphere CreateFromFrustum(BoundingFrustum const& frustum) noexcept;
	};

	// A plane in 3d space, 
	// represented by its normal away from the origin and its distance from the origin, D.
	struct Plane {
		Vector3 Normal;
		float D{ 0 };

		constexpr Plane() noexcept = default;
		constexpr Plane(const Vector3& Normal, float D) noexcept : Normal(Normal), D(D) {}
		constexpr Plane(float a, float b, float c, float d) noexcept : Normal({ a,b, c }), D(d) { }
		constexpr Plane(Vector4 const& value) noexcept : Normal({ value.X, value.Y, value.Z }), D(value.W) {}

		Plane(Vector3 const& point1, Vector3 const& point2, Vector3 const& point3) noexcept;

		constexpr bool operator==(const Plane& other) const noexcept {
			return Normal == other.Normal && D == other.D;
		}

		void Normalize() noexcept;
		static Plane Normalize(Plane const& value) noexcept;

		static constexpr Plane Transform(Plane const& plane, Matrix const& matrix) noexcept {
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

		static Plane Transform(Plane const& plane, Quaternion const& rotation) noexcept {
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

		constexpr float Dot(Vector4 const& value) const noexcept {
			return (Normal.X * value.X + Normal.Y * value.Y + Normal.Z * value.Z + D * value.W);
		}

		constexpr  float DotCoordinate(Vector3 const& value) const noexcept {
			return (Normal.X * value.X + Normal.Y * value.Y + Normal.Z * value.Z) + D;
		}

		constexpr float DotNormal(Vector3 const& value) const noexcept {
			return (Normal.X * value.X + Normal.Y * value.Y + Normal.Z * value.Z);
		}

		constexpr PlaneIntersectionType Intersects(BoundingBox const& box) noexcept {
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

		constexpr PlaneIntersectionType Intersects(BoundingSphere const& sphere) const noexcept {
			const auto num = (sphere.Center.X * Normal.X + sphere.Center.Y * Normal.Y + sphere.Center.Z * Normal.Z) + D;

			if (num > sphere.Radius)
				return PlaneIntersectionType::Front;

			return num < -sphere.Radius ? PlaneIntersectionType::Back : PlaneIntersectionType::Intersecting;
		}

		constexpr PlaneIntersectionType Intersects(BoundingFrustum const& frustum) const noexcept;

		constexpr PlaneIntersectionType Intersects(Vector3 const& point) const noexcept {
			float distance = DotCoordinate(point);

			if (distance > 0)
				return PlaneIntersectionType::Front;

			if (distance < 0)
				return PlaneIntersectionType::Back;

			return PlaneIntersectionType::Intersecting;
		}

		nullfloat Intersects(Ray const& ray) const;

	public:
		static constexpr float ClassifyPoint(Vector3 const& point, Plane const& plane) noexcept {
			return point.X * plane.Normal.X + point.Y * plane.Normal.Y + point.Z * plane.Normal.Z + plane.D;
		}

		static float PerpendicularDistance(Vector3 const& point, Plane const& plane) noexcept;
	};

	// Defines a viewing frustum for intersection operations.
	struct BoundingFrustum {
		using Matrix_ = dxna::Matrix;

		BoundingFrustum(Matrix_ const& value) noexcept : _matrix(value) {
			createCorners();
			createPlanes();
		}

		constexpr bool operator==(const BoundingFrustum& other) const noexcept {
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

		constexpr Matrix_ Matrix() const noexcept { return _matrix; }

		void Matrix(Matrix_ const& value) noexcept {
			_matrix = value;
			createPlanes();
			createCorners();
		}

		constexpr Plane Near() const noexcept { return _planes0; }
		constexpr Plane Far() const noexcept { return _planes1; }
		constexpr Plane Left() const noexcept { return _planes2; }
		constexpr Plane Right() const noexcept { return _planes3; }
		constexpr Plane Top() const noexcept { return _planes4; }
		constexpr Plane Bottom() const noexcept { return _planes5; }

		constexpr ContainmentType Contains(BoundingBox const& box) const noexcept {
			auto intersects = false;

			for (size_t i = 0; i < PlaneCount; ++i)
			{
				const auto& plane = GetPlane(i);
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

		constexpr ContainmentType Contains(BoundingFrustum const& frustum) const noexcept {
			if (*this == frustum)
				return ContainmentType::Contains;

			auto intersects = false;

			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto& plane = GetPlane(i);
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

		constexpr ContainmentType Contains(BoundingSphere const& sphere) const noexcept {
			auto intersects = false;

			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto& plane = GetPlane(i);
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

		constexpr ContainmentType Contains(Vector3 const& point) const noexcept {
			for (size_t i = 0; i < PlaneCount; ++i) {
				const auto& plane = GetPlane(i);

				if (Plane::ClassifyPoint(point, plane) > 0.0F) {
					return ContainmentType::Disjoint;
				}
			}

			return ContainmentType::Contains;
		}

		constexpr bool Intersects(BoundingBox const& box) const noexcept {
			const auto containment = Contains(box);
			return containment != ContainmentType::Disjoint;
		}

		constexpr bool Intersects(BoundingFrustum const& frustum) const noexcept {
			return Contains(frustum) != ContainmentType::Disjoint;
		}

		constexpr bool Intersects(BoundingSphere const& sphere) const noexcept {
			const auto containment = Contains(sphere);
			return containment != ContainmentType::Disjoint;
		}

		constexpr PlaneIntersectionType Intersects(Plane const& plane) const noexcept {
			auto result = plane.Intersects(_corners0);

			for (size_t i = 1; i < CornerCount; i++) {
				const auto& corner = GetCorner(i);

				if (plane.Intersects(corner) != result)
					result = PlaneIntersectionType::Intersecting;
			}

			return result;
		}

		constexpr nullfloat Intersects(Ray const& ray) const noexcept;

	public:
		static constexpr int PlaneCount = 6;
		static constexpr int CornerCount = 8;

		constexpr const Plane& GetPlane(size_t index) const noexcept {
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
				auto p = Plane();
				return p;
			}
		}

		constexpr const Vector3& GetCorner(size_t index) const noexcept {
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
		static constexpr Vector3 IntersectionPoint(Plane const& a, Plane const& b, Plane const& c) noexcept {
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

		constexpr void createCorners() noexcept {
			_corners0 = IntersectionPoint(_planes0, _planes2, _planes4);
			_corners1 = IntersectionPoint(_planes0, _planes3, _planes4);
			_corners2 = IntersectionPoint(_planes0, _planes3, _planes5);
			_corners3 = IntersectionPoint(_planes0, _planes2, _planes5);
			_corners4 = IntersectionPoint(_planes1, _planes2, _planes4);
			_corners5 = IntersectionPoint(_planes1, _planes3, _planes4);
			_corners6 = IntersectionPoint(_planes1, _planes3, _planes5);
			_corners7 = IntersectionPoint(_planes1, _planes2, _planes5);
		}

		void createPlanes() noexcept {
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

	private:
		Matrix_ _matrix;

	public:
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
}

// ----------------------------- Vector2 ---------------------------------------//
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
		Vector2 const* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Matrix const& matrix,
		Vector2* destinationArray,
		size_t destinationLength,
		size_t destinationIndex,
		size_t length) {
		if (sourceArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 0);

		if (destinationArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 4);

		if (sourceLength < sourceIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 2);

		if (destinationLength < destinationIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 5);

		for (size_t i = 0; i < length; ++i) {
			const auto& value = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] = Transform(value, matrix);
		}

		return Error::NoError();
	}

	constexpr Error Vector2::Transform(
		Vector2 const* sourceArray,
		size_t sourceIndex,
		size_t sourceLength,
		Quaternion const& rotation,
		Vector2* destinationArray,
		size_t destinationIndex,
		size_t destinationLength,
		size_t length) {

		if (sourceArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 0);

		if (destinationArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 4);

		if (sourceLength < sourceIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 2);

		if (destinationLength < destinationIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 5);

		for (size_t i = 0; i < length; i++)
		{
			const auto& value = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] = Transform(value, rotation);
		}

		return Error::NoError();
	}
}

// ----------------------------- Vector3 ---------------------------------------//
namespace dxna {
	constexpr Vector3 dxna::Vector3::Transform(Vector3 const& position, Matrix const& matrix) noexcept {
		float num1 = (position.X * matrix.M11 + position.Y * matrix.M21 + position.Z * matrix.M31) + matrix.M41;
		float num2 = (position.X * matrix.M12 + position.Y * matrix.M22 + position.Z * matrix.M32) + matrix.M42;
		float num3 = (position.X * matrix.M13 + position.Y * matrix.M23 + position.Z * matrix.M33) + matrix.M43;
		Vector3 vector3;
		vector3.X = num1;
		vector3.Y = num2;
		vector3.Z = num3;
		return vector3;
	}

	constexpr Vector3 Vector3::TransformNormal(Vector3 const& normal, Matrix const& matrix) noexcept {
		const auto num1 = (normal.X * matrix.M11 + normal.Y * matrix.M21 + normal.Z * matrix.M31);
		const auto num2 = (normal.X * matrix.M12 + normal.Y * matrix.M22 + normal.Z * matrix.M32);
		const auto num3 = (normal.X * matrix.M13 + normal.Y * matrix.M23 + normal.Z * matrix.M33);
		Vector3 vector3;
		vector3.X = num1;
		vector3.Y = num2;
		vector3.Z = num3;
		return vector3;
	}

	constexpr Vector3 Vector3::Transform(Vector3 const& value, Quaternion const& rotation) noexcept {
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

	constexpr Error Vector3::Transform(
		Vector3 const* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Matrix const& matrix,
		Vector3* destinationArray,
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

		for (size_t i = 0; i < length; i++)
		{
			const auto& position = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] = Vector3(
				(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41,
				(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42,
				(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43);
		}

		return Error::NoError();
	}

	constexpr Error Vector3::TransformNormal(
		Vector3 const* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Matrix const& matrix,
		Vector3* destinationArray,
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

		for (size_t x = 0; x < length; x++)
		{
			const auto& normal = sourceArray[sourceIndex + x];

			destinationArray[destinationIndex + x] =
				Vector3(
					(normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31),
					(normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32),
					(normal.X * matrix.M13) + (normal.Y * matrix.M23) + (normal.Z * matrix.M33));
		}

		return Error::NoError();
	}

	constexpr Error Vector3::Transform(
		Vector3 const* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Quaternion const& rotation,
		Vector3* destinationArray,
		size_t destinationLength,
		size_t destinationIndex,
		size_t length)  noexcept {

		if (sourceArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 0);

		if (destinationArray == nullptr)
			return Error(ErrorCode::ARGUMENT_IS_NULL, 4);

		if (sourceLength < sourceIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 2);

		if (destinationLength < destinationIndex + length)
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 5);

		for (size_t i = 0; i < length; i++)
		{
			const auto& position = sourceArray[sourceIndex + i];

			const auto x = 2 * (rotation.Y * position.Z - rotation.Z * position.Y);
			const auto y = 2 * (rotation.Z * position.X - rotation.X * position.Z);
			const auto z = 2 * (rotation.X * position.Y - rotation.Y * position.X);

			destinationArray[destinationIndex + i] =
				Vector3(
					position.X + x * rotation.W + (rotation.Y * z - rotation.Z * y),
					position.Y + y * rotation.W + (rotation.Z * x - rotation.X * z),
					position.Z + z * rotation.W + (rotation.X * y - rotation.Y * x));
		}

		return Error::NoError();
	}
}

// ----------------------------- Vector4 ---------------------------------------//
namespace dxna {
	constexpr Vector4 dxna::Vector4::Transform(Vector2 const& position, Matrix const& matrix) noexcept
	{
		const auto num1 = (position.X * matrix.M11 + position.Y * matrix.M21) + matrix.M41;
		const auto num2 = (position.X * matrix.M12 + position.Y * matrix.M22) + matrix.M42;
		const auto num3 = (position.X * matrix.M13 + position.Y * matrix.M23) + matrix.M43;
		const auto num4 = (position.X * matrix.M14 + position.Y * matrix.M24) + matrix.M44;
		Vector4 vector4;
		vector4.X = num1;
		vector4.Y = num2;
		vector4.Z = num3;
		vector4.W = num4;
		return vector4;
	}

	constexpr Vector4 Vector4::Transform(Vector3 const& position, Matrix const& matrix) noexcept {
		const auto num1 = (position.X * matrix.M11 + position.Y * matrix.M21 + position.Z * matrix.M31) + matrix.M41;
		const auto num2 = (position.X * matrix.M12 + position.Y * matrix.M22 + position.Z * matrix.M32) + matrix.M42;
		const auto num3 = (position.X * matrix.M13 + position.Y * matrix.M23 + position.Z * matrix.M33) + matrix.M43;
		const auto num4 = (position.X * matrix.M14 + position.Y * matrix.M24 + position.Z * matrix.M34) + matrix.M44;
		Vector4 vector4;
		vector4.X = num1;
		vector4.Y = num2;
		vector4.Z = num3;
		vector4.W = num4;
		return vector4;
	}

	constexpr Vector4 Vector4::Transform(Vector4 const& vector, Matrix const& matrix) noexcept
	{
		const auto num1 = (vector.X * matrix.M11 + vector.Y * matrix.M21 + vector.Z * matrix.M31 + vector.W * matrix.M41);
		const auto num2 = (vector.X * matrix.M12 + vector.Y * matrix.M22 + vector.Z * matrix.M32 + vector.W * matrix.M42);
		const auto num3 = (vector.X * matrix.M13 + vector.Y * matrix.M23 + vector.Z * matrix.M33 + vector.W * matrix.M43);
		const auto num4 = (vector.X * matrix.M14 + vector.Y * matrix.M24 + vector.Z * matrix.M34 + vector.W * matrix.M44);
		Vector4 vector4;
		vector4.X = num1;
		vector4.Y = num2;
		vector4.Z = num3;
		vector4.W = num4;
		return vector4;
	}

	constexpr Vector4 Vector4::Transform(Vector2 const& value, Quaternion const& rotation) noexcept
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
		const auto num13 = (value.X * (1.0F - num10 - num12) + value.Y * (num8 - num6));
		const auto num14 = (value.X * (num8 + num6) + value.Y * (1.0F - num7 - num12));
		const auto num15 = (value.X * (num9 - num5) + value.Y * (num11 + num4));
		Vector4 vector4;
		vector4.X = num13;
		vector4.Y = num14;
		vector4.Z = num15;
		vector4.W = 1.0f;
		return vector4;
	}

	constexpr Vector4 Vector4::Transform(Vector3 const& value, Quaternion const& rotation) noexcept {
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
		Vector4 vector4;
		vector4.X = num13;
		vector4.Y = num14;
		vector4.Z = num15;
		vector4.W = 1.0f;
		return vector4;
	}

	constexpr Vector4 Vector4::Transform(Vector4 const& value, Quaternion const& rotation) noexcept
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
		Vector4 vector4;
		vector4.X = num13;
		vector4.Y = num14;
		vector4.Z = num15;
		vector4.W = value.W;
		return vector4;
	}

	constexpr Error Vector4::Transform(
		Vector4* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Matrix const& matrix,
		Vector4* destinationArray,
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
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 6);

		for (size_t i = 0; i < length; ++i) {
			const auto& value = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] = Transform(value, matrix);
		}

		return Error::NoError();
	}

	constexpr Error Vector4::Transform(Vector4* sourceArray,
		size_t sourceLength,
		size_t sourceIndex,
		Quaternion const& rotation,
		Vector4* destinationArray,
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
			return Error(ErrorCode::ARGUMENT_OUT_OF_RANGE, 6);

		for (size_t i = 0; i < length; ++i) {
			const auto& value = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] = Transform(value, rotation);
		}

		return Error::NoError();
	}
}

// ------------------------------ Matrix ---------------------------------------//
namespace dxna {
	constexpr Matrix dxna::Matrix::CreateFromQuaternion(Quaternion const& quaternion) noexcept
	{
		const auto num1 = quaternion.X * quaternion.X;
		const auto num2 = quaternion.Y * quaternion.Y;
		const auto num3 = quaternion.Z * quaternion.Z;
		const auto num4 = quaternion.X * quaternion.Y;
		const auto num5 = quaternion.Z * quaternion.W;
		const auto num6 = quaternion.Z * quaternion.X;
		const auto num7 = quaternion.Y * quaternion.W;
		const auto num8 = quaternion.Y * quaternion.Z;
		const auto num9 = quaternion.X * quaternion.W;

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

	constexpr Matrix dxna::Matrix::Transform(Matrix const& value, Quaternion const& rotation) noexcept
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
		const auto num13 = 1.0f - num10 - num12;
		const auto num14 = num8 - num6;
		const auto num15 = num9 + num5;
		const auto num16 = num8 + num6;
		const auto num17 = 1.0f - num7 - num12;
		const auto num18 = num11 - num4;
		const auto num19 = num9 - num5;
		const auto num20 = num11 + num4;
		const auto num21 = 1.0f - num7 - num10;
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
}

// --------------------------- BoundingBox -------------------------------------//
namespace dxna {
	constexpr bool dxna::BoundingBox::Intersects(BoundingSphere const& sphere) const noexcept {
		auto squareDistance = 0.0f;
		const auto point = sphere.Center;

		if (point.X < Min.X)
			squareDistance += (Min.X - point.X) * (Min.X - point.X);
		if (point.X > Max.X)
			squareDistance += (point.X - Max.X) * (point.X - Max.X);
		if (point.Y < Min.Y)
			squareDistance += (Min.Y - point.Y) * (Min.Y - point.Y);
		if (point.Y > Max.Y)
			squareDistance += (point.Y - Max.Y) * (point.Y - Max.Y);
		if (point.Z < Min.Z)
			squareDistance += (Min.Z - point.Z) * (Min.Z - point.Z);
		if (point.Z > Max.Z)
			squareDistance += (point.Z - Max.Z) * (point.Z - Max.Z);

		return squareDistance <= sphere.Radius * sphere.Radius;
	}

	constexpr PlaneIntersectionType BoundingBox::Intersects(Plane const& plane) const noexcept {
		Vector3 vector3_1;
		vector3_1.X = plane.Normal.X >= 0.0 ? Min.X : Max.X;
		vector3_1.Y = plane.Normal.Y >= 0.0 ? Min.Y : Max.Y;
		vector3_1.Z = plane.Normal.Z >= 0.0 ? Min.Z : Max.Z;
		Vector3 vector3_2;
		vector3_2.X = plane.Normal.X >= 0.0 ? Max.X : Min.X;
		vector3_2.Y = plane.Normal.Y >= 0.0 ? Max.Y : Min.Y;
		vector3_2.Z = plane.Normal.Z >= 0.0 ? Max.Z : Min.Z;

		if (plane.Normal.X * vector3_1.X
			+ plane.Normal.Y * vector3_1.Y
			+ plane.Normal.Z * vector3_1.Z
			+ plane.D > 0.0)
			return PlaneIntersectionType::Front;

		return plane.Normal.X * vector3_2.X
			+ plane.Normal.Y * vector3_2.Y
			+ plane.Normal.Z * vector3_2.Z
			+ plane.D < 0.0
			? PlaneIntersectionType::Back
			: PlaneIntersectionType::Intersecting;
	}

	constexpr ContainmentType BoundingBox::Contains(BoundingFrustum const& frustum) const
	{
		if (!frustum.Intersects(*this))
			return ContainmentType::Disjoint;

		for (size_t i = 0; i < frustum.CornerCount; ++i) {
			const auto& corner = frustum.GetCorner(i);

			if (Contains(corner) == ContainmentType::Disjoint)
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}

	constexpr ContainmentType BoundingBox::Contains(BoundingSphere const& sphere) const noexcept {
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
			|| Max.X - Min.X <= radius
			? ContainmentType::Intersects
			: ContainmentType::Contains;
	}

	constexpr BoundingBox BoundingBox::CreateFromSphere(BoundingSphere const& sphere) noexcept {
		BoundingBox fromSphere;
		fromSphere.Min.X = sphere.Center.X - sphere.Radius;
		fromSphere.Min.Y = sphere.Center.Y - sphere.Radius;
		fromSphere.Min.Z = sphere.Center.Z - sphere.Radius;
		fromSphere.Max.X = sphere.Center.X + sphere.Radius;
		fromSphere.Max.Y = sphere.Center.Y + sphere.Radius;
		fromSphere.Max.Z = sphere.Center.Z + sphere.Radius;
		return fromSphere;
	}

	constexpr bool BoundingBox::Intersects(BoundingFrustum const& frustum) const noexcept
	{
		return frustum.Intersects(*this);
	}
}

// ------------------------- BoundingSphere ------------------------------------//
namespace dxna {
	constexpr ContainmentType dxna::BoundingSphere::Contains(BoundingFrustum const& frustum) const noexcept
	{
		if (!frustum.Intersects(*this))
			return ContainmentType::Disjoint;

		float num = Radius * Radius;

		for (size_t i = 0; i < frustum.CornerCount; ++i) {
			const auto& corner = frustum.GetCorner(i);

			Vector3 vector3;
			vector3.X = corner.X - Center.X;
			vector3.Y = corner.Y - Center.Y;
			vector3.Z = corner.Z - Center.Z;

			if (vector3.LengthSquared() > num)
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}

	constexpr bool BoundingSphere::Intersects(BoundingFrustum const& frustum) const noexcept {
		return frustum.Intersects(*this);
	}

	constexpr PlaneIntersectionType BoundingSphere::Intersects(Plane const& plane) const noexcept {
		return plane.Intersects(*this);
	}
}

namespace dxna {

	constexpr nullfloat BoundingFrustum::Intersects(Ray const& ray) const noexcept
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
				const auto& plane = GetPlane(i);

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



	constexpr PlaneIntersectionType Plane::Intersects(BoundingFrustum const& frustum) const noexcept {
		return frustum.Intersects(*this);
	}
}

#endif
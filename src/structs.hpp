#ifndef DXNA_STRUCTS_HPP
#define DXNA_STRUCTS_HPP

#include "cs/cstypes.hpp"

namespace dxna {
	struct Matrix;
	struct Quaternion;

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

		constexpr Vector2 operator-() const { return Negate(*this); }
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

	struct Vector3 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };

		constexpr Vector3() {}
		constexpr Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
		constexpr Vector3(float value) : X(value), Y(value), Z(value) {}
		constexpr Vector3(Vector2 const& value, float z) : X(value.X), Y(value.Y), Z(z) {}

		constexpr Vector3 operator-() const { return Negate(*this); }
		constexpr bool operator==(Vector3 const& other) const { return Equals(other); }
		friend constexpr Vector3 operator+(Vector3 const& value1, Vector3 const& value2) { return Vector3::Add(value1, value2); }
		friend constexpr Vector3 operator-(Vector3 const& value1, Vector3 const& value2) { return Vector3::Subtract(value1, value2); }
		friend constexpr Vector3 operator*(Vector3 const& value1, Vector3 const& value2) { return Vector3::Multiply(value1, value2); }
		friend constexpr Vector3 operator*(Vector3 const& value, float scale) { return Vector3::Multiply(value, scale); }
		friend constexpr Vector3 operator*(float scale, Vector3 const& value) { return Vector3::Multiply(value, scale); }
		friend constexpr Vector3 operator/(Vector3 const& value1, Vector3 const& value2) { return Vector3::Divide(value1, value2); }
		friend constexpr Vector3 operator/(Vector3 const& value, float divider) { return Vector3::Divide(value, divider); }


		float Length() const;
		void Normalize();

		constexpr bool Equals(const Vector3& other) const {	return X == other.X && Y == other.Y && Z == other.Z; }
		constexpr float LengthSquared() const { return (X * X) + (Y * Y) + (Z * Z);	}

		static constexpr Vector3 Zero() { return Vector3(); };
		static constexpr Vector3 One() { return Vector3(1.F, 1.F, 1.F); }
		static constexpr Vector3 UnitX() { return Vector3(1.0F, 0.0, 0.0); }
		static constexpr Vector3 UnitY() { return Vector3(0.0, 1.0F, 0.0); }
		static constexpr Vector3 UnitZ() { return Vector3(0.0, 0.0, 1.0F); }
		static constexpr Vector3 Up() { return UnitY(); }
		static constexpr Vector3 Down() { return -UnitY(); }
		static constexpr Vector3 Right() { return UnitX(); }
		static constexpr Vector3 Left(){ { return -UnitX(); } }
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

		static constexpr Vector3 Reflect(Vector3 const& vector, Vector3 const& normal) {
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
			vector3.X = value1.X >  value2.X ? value1.X : value2.X;
			vector3.Y = value1.Y >  value2.Y ? value1.Y : value2.Y;
			vector3.Z = value1.Z >  value2.Z ? value1.Z : value2.Z;
			return vector3;
		}

		static constexpr Vector3 Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max) {
			const auto x = value1.X;
			const auto num1 = x > max.X ? max.X : x;
			const auto num2 = num1 < min.X ? min.X : num1;
			const auto y = value1.Y;
			const auto num3 = y >  max.Y ? max.Y : y;
			const auto num4 = num3 < min.Y ? min.Y : num3;
			const auto z = value1.Z;
			const auto num5 = z >  max.Z ? max.Z : z;
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

		static Vector3 Transform(Vector3 const& position, Matrix const& matrix);
		static Vector3 TransformNormal(Vector3 const& normal, Matrix const& matrix);
		static Vector3 Transform(Vector3 const& value, Quaternion const& rotation);
		static void Transform(Vector3* sourceArray, Matrix const& matrix,
			Vector3* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
		static void TransformNormal(Vector3* sourceArray, Matrix const& matrix,
			Vector3* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
		static void Transform(Vector3* sourceArray, Quaternion const& rotation,
			Vector3* destinationArray, size_t length, size_t sourceIndex = 0, size_t destinationIndex = 0);
	};

	struct Vector4 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		constexpr Vector4() = default;
		constexpr Vector4(float value):
			X(value), Y(value), Z(value), W(value) {}
		constexpr Vector4(float x, float y, float z, float w) :
			X(x), Y(y), Z(z), W(w){}
		constexpr Vector4(Vector2 value, float z, float w) :
			X(value.X), Y(value.Y), Z(z), W(w) {}
		constexpr Vector4(Vector3 value, float w) :
			X(value.X), Y(value.Y), Z(value.Z), W(w) {}

		constexpr Vector4 operator-() const { return Negate(*this); }
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
			vector4.X = value1.X >  value2.X ? value1.X : value2.X;
			vector4.Y = value1.Y >  value2.Y ? value1.Y : value2.Y;
			vector4.Z = value1.Z >  value2.Z ? value1.Z : value2.Z;
			vector4.W = value1.W > value2.W ? value1.W : value2.W;
			return vector4;
		}

		static constexpr Vector4 Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max) {
			const auto x = value1.X;
			const auto num1 = x > max.X ? max.X : x;
			const auto num2 = num1 < min.X ? min.X : num1;
			const auto y = value1.Y;
			const auto num3 = y >  max.Y ? max.Y : y;
			const auto num4 = num3 < min.Y ? min.Y : num3;
			const auto z = value1.Z;
			const auto num5 = z >  max.Z ? max.Z : z;
			const auto num6 = num5 < min.Z ? min.Z : num5;
			const auto w = value1.W;
			const auto num7 = w >  max.W ? max.W : w;
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
			vector4.X = (float)(value1.X * num3 + value2.X * num4 + tangent1.X * num5 + tangent2.X * num6);
			vector4.Y = (float)(value1.Y * num3 + value2.Y * num4 + tangent1.Y * num5 + tangent2.Y * num6);
			vector4.Z = (float)(value1.Z * num3 + value2.Z * num4 + tangent1.Z * num5 + tangent2.Z * num6);
			vector4.W = (float)(value1.W * num3 + value2.W * num4 + tangent1.W * num5 + tangent2.W * num6);
			return vector4;
		}

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

		static Vector4 Transform(Vector2 const& position, Matrix const& matrix);
		static Vector4 Transform(Vector3 const& position, Matrix const& matrix);
		static Vector4 Transform(Vector4 const& vector, Matrix const& matrix);
		static Vector4 Transform(Vector2 const& value, Quaternion const& rotation);
		static Vector4 Transform(Vector3 const& position, Quaternion const& rotation);
		static Vector4 Transform(Vector4 const& vector, Quaternion const& rotation);

		static void Transform(Vector4* sourceArray, Matrix const& matrix,
			Vector4* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex);
		static void Transform(Vector4* sourceArray, Quaternion const& rotation,
			Vector4* destinationArray, size_t length, size_t sourceIndex, size_t destinationIndex);		
	};
}

#endif
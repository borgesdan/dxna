#include "structs.hpp"
#include <cmath>
#include <vector>

namespace dxna {
	float Vector2::Length() const { return std::sqrt(LengthSquared()); }

	void Vector2::Normalize() {
		const auto num = 1.0F / Length();
		X *= num;
		Y *= num;
	}

	Vector2 Vector2::Normalize(Vector2 const& value) {
		float num = 1.0F / std::sqrt(value.Length());
		Vector2 vector;
		vector.X *= num;
		vector.Y *= num;

		return vector;
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

	Vector3 Vector3::Normalize(Vector3 const& value) {
		float num = 1.0F / std::sqrt(value.Length());
		Vector3 vector;
		vector.X *= num;
		vector.Y *= num;
		vector.Z *= num;

		return vector;
	}

	float Vector3::Distance(Vector3 const& value1, Vector3 const& value2) {
		const auto num1 = value1.X - value2.X;
		const auto num2 = value1.Y - value2.Y;
		const auto num3 = value1.Z - value2.Z;
		return std::sqrt(num1 * num1 + num2 * num2 + num3 * num3);
	}

	float Vector4::Length() const {
		return std::sqrt(LengthSquared());
	}

	float Vector4::Distance(Vector4 const& value1, Vector4 const& value2) {
		const auto num1 = value1.X - value2.X;
		const auto num2 = value1.Y - value2.Y;
		const auto num3 = value1.Z - value2.Z;
		const auto num4 = value1.W - value2.W;
		return std::sqrt(num1 * num1 + num2 * num2 + num3 * num3 + num4 * num4);
	}

	void Vector4::Normalize() {
		float num = 1.0F / std::sqrt(Length());
		X *= num;
		Y *= num;
		Z *= num;
		W *= num;
	}

	Vector4 Vector4::Normalize(Vector4 const& value) {
		float num = 1.0F / std::sqrt(value.Length());
		Vector4 vector;
		vector.X *= num;
		vector.Y *= num;
		vector.Z *= num;
		vector.W *= num;

		return vector;
	}

	Matrix Matrix::CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
		Vector3 const& cameraUpVector, Vector3* const cameraForwardVector) {
		Vector3 result1;
		result1.X = objectPosition.X - cameraPosition.X;
		result1.Y = objectPosition.Y - cameraPosition.Y;
		result1.Z = objectPosition.Z - cameraPosition.Z;

		const auto d = result1.LengthSquared();

		if (d < 9.9999997473787516E-05) 
			result1 = cameraForwardVector != nullptr ? -(*cameraForwardVector) : Vector3::Forward();			
		else
			result1 = Vector3::Multiply(result1, 1.0F / std::sqrt(d));
		Vector3 result2 = Vector3::Cross(cameraUpVector, result1);
		result2.Normalize();

		Vector3 result3 = Vector3::Cross(result1, result2);

		Matrix billboard;
		billboard.M11 = result2.X;
		billboard.M12 = result2.Y;
		billboard.M13 = result2.Z;
		billboard.M14 = 0.0f;
		billboard.M21 = result3.X;
		billboard.M22 = result3.Y;
		billboard.M23 = result3.Z;
		billboard.M24 = 0.0f;
		billboard.M31 = result1.X;
		billboard.M32 = result1.Y;
		billboard.M33 = result1.Z;
		billboard.M34 = 0.0f;
		billboard.M41 = objectPosition.X;
		billboard.M42 = objectPosition.Y;
		billboard.M43 = objectPosition.Z;
		billboard.M44 = 1.0f;

		return billboard;
	}

	Matrix Matrix::CreateConstrainedBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
		Vector3 rotateAxis, Vector3* const cameraForwardVector, Vector3* const objectForwardVector) {
		Vector3 result1;
		result1.X = objectPosition.X - cameraPosition.X;
		result1.Y = objectPosition.Y - cameraPosition.Y;
		result1.Z = objectPosition.Z - cameraPosition.Z;

		float d = result1.LengthSquared();

		if (d < 9.9999997473787516E-05)
			result1 = cameraForwardVector ? -(*cameraForwardVector) : Vector3::Forward();
		else
			result1 = Vector3::Multiply(result1, 1.0f / std::sqrt(d));

		Vector3 vector2 = rotateAxis;
		auto result2 = Vector3::Dot(rotateAxis, result1);

		Vector3 result3;
		Vector3 result4;

		if (std::abs(result2) > 0.998254656791687) {
			if (objectForwardVector) {
				result3 = *objectForwardVector;
				result2 = Vector3::Dot(rotateAxis, result3);

				if (std::abs(result2) > 0.998254656791687)
					result3 = std::abs((rotateAxis.X * Vector3::Forward().X + rotateAxis.Y * Vector3::Forward().Y + rotateAxis.Z * Vector3::Forward().Z)) > 0.998254656791687 ? Vector3::Right() : Vector3::Forward();
			}
			else
				result3 = std::abs(rotateAxis.X * Vector3::Forward().X + rotateAxis.Y * Vector3::Forward().Y + rotateAxis.Z * Vector3::Forward().Z) > 0.998254656791687 ? Vector3::Right() : Vector3::Forward();

			result4 = Vector3::Cross(rotateAxis, result3);
			result4.Normalize();

			result3 = Vector3::Cross(result4, rotateAxis);
			result3.Normalize();
		}
		else
		{
			result4 = Vector3::Cross(rotateAxis, result1);
			result4.Normalize();

			result3 = Vector3::Cross(result4, vector2);
			result3.Normalize();
		}

		Matrix constrainedBillboard;
		constrainedBillboard.M11 = result4.X;
		constrainedBillboard.M12 = result4.Y;
		constrainedBillboard.M13 = result4.Z;
		constrainedBillboard.M14 = 0.0f;
		constrainedBillboard.M21 = vector2.X;
		constrainedBillboard.M22 = vector2.Y;
		constrainedBillboard.M23 = vector2.Z;
		constrainedBillboard.M24 = 0.0f;
		constrainedBillboard.M31 = result3.X;
		constrainedBillboard.M32 = result3.Y;
		constrainedBillboard.M33 = result3.Z;
		constrainedBillboard.M34 = 0.0f;
		constrainedBillboard.M41 = objectPosition.X;
		constrainedBillboard.M42 = objectPosition.Y;
		constrainedBillboard.M43 = objectPosition.Z;
		constrainedBillboard.M44 = 1.0f;
		return constrainedBillboard;
	}

	Matrix Matrix::CreateRotationX(float radians) {
		const auto num1 = std::cos(radians);
		const auto num2 = std::sin(radians);
		Matrix rotationX;
		rotationX.M11 = 1.0f;
		rotationX.M12 = 0.0f;
		rotationX.M13 = 0.0f;
		rotationX.M14 = 0.0f;
		rotationX.M21 = 0.0f;
		rotationX.M22 = num1;
		rotationX.M23 = num2;
		rotationX.M24 = 0.0f;
		rotationX.M31 = 0.0f;
		rotationX.M32 = -num2;
		rotationX.M33 = num1;
		rotationX.M34 = 0.0f;
		rotationX.M41 = 0.0f;
		rotationX.M42 = 0.0f;
		rotationX.M43 = 0.0f;
		rotationX.M44 = 1.0f;
		return rotationX;
	}

	Matrix Matrix::CreateRotationY(float radians) {
		const auto num1 = std::cos(radians);
		const auto num2 = std::sin(radians);
		Matrix rotationY;
		rotationY.M11 = num1;
		rotationY.M12 = 0.0f;
		rotationY.M13 = -num2;
		rotationY.M14 = 0.0f;
		rotationY.M21 = 0.0f;
		rotationY.M22 = 1.0f;
		rotationY.M23 = 0.0f;
		rotationY.M24 = 0.0f;
		rotationY.M31 = num2;
		rotationY.M32 = 0.0f;
		rotationY.M33 = num1;
		rotationY.M34 = 0.0f;
		rotationY.M41 = 0.0f;
		rotationY.M42 = 0.0f;
		rotationY.M43 = 0.0f;
		rotationY.M44 = 1.0f;
		return rotationY;
	}

	Matrix Matrix::CreateRotationZ(float radians) {
		const auto num1 = std::cos(radians);
		const auto num2 = std::sin(radians);
		Matrix rotationZ;
		rotationZ.M11 = num1;
		rotationZ.M12 = num2;
		rotationZ.M13 = 0.0f;
		rotationZ.M14 = 0.0f;
		rotationZ.M21 = -num2;
		rotationZ.M22 = num1;
		rotationZ.M23 = 0.0f;
		rotationZ.M24 = 0.0f;
		rotationZ.M31 = 0.0f;
		rotationZ.M32 = 0.0f;
		rotationZ.M33 = 1.0f;
		rotationZ.M34 = 0.0f;
		rotationZ.M41 = 0.0f;
		rotationZ.M42 = 0.0f;
		rotationZ.M43 = 0.0f;
		rotationZ.M44 = 1.0f;
		return rotationZ;
	}

	Matrix Matrix::CreateFromAxisAngle(Vector3 const& axis, float angle) {
		float x = axis.X;
		float y = axis.Y;
		float z = axis.Z;
		float num1 = std::sin(angle);
		float num2 = std::cos(angle);
		float num3 = x * x;
		float num4 = y * y;
		float num5 = z * z;
		float num6 = x * y;
		float num7 = x * z;
		float num8 = y * z;

		Matrix fromAxisAngle;
		fromAxisAngle.M11 = num3 + num2 * (1.0f - num3);
		fromAxisAngle.M12 = (num6 - num2 * num6 + num1 * z);
		fromAxisAngle.M13 = (num7 - num2 * num7 - num1 * y);
		fromAxisAngle.M14 = 0.0f;
		fromAxisAngle.M21 = (num6 - num2 * num6 - num1 * z);
		fromAxisAngle.M22 = num4 + num2 * (1.0f - num4);
		fromAxisAngle.M23 = (num8 - num2 * num8 + num1 * x);
		fromAxisAngle.M24 = 0.0f;
		fromAxisAngle.M31 = (num7 - num2 * num7 + num1 * y);
		fromAxisAngle.M32 = (num8 - num2 * num8 - num1 * x);
		fromAxisAngle.M33 = num5 + num2 * (1.0f - num5);
		fromAxisAngle.M34 = 0.0f;
		fromAxisAngle.M41 = 0.0f;
		fromAxisAngle.M42 = 0.0f;
		fromAxisAngle.M43 = 0.0f;
		fromAxisAngle.M44 = 1.0f;
		return fromAxisAngle;
	}

	Matrix Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) {
		const Matrix zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		if (fieldOfView <= 0.0F || fieldOfView >= 3.1415927410125732)
			return zero;

		if (nearPlaneDistance <= 0.0F)
			return zero;

		if (farPlaneDistance <= 0.0F)
			return zero;

		if (nearPlaneDistance >= farPlaneDistance)
			return zero;

		const auto num1 = 1.0F / std::tan(fieldOfView * 0.5F);
		const auto num2 = num1 / aspectRatio;
		Matrix perspectiveFieldOfView;
		perspectiveFieldOfView.M11 = num2;
		perspectiveFieldOfView.M12 = perspectiveFieldOfView.M13 = perspectiveFieldOfView.M14 = 0.0f;
		perspectiveFieldOfView.M22 = num1;
		perspectiveFieldOfView.M21 = perspectiveFieldOfView.M23 = perspectiveFieldOfView.M24 = 0.0f;
		perspectiveFieldOfView.M31 = perspectiveFieldOfView.M32 = 0.0f;
		perspectiveFieldOfView.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		perspectiveFieldOfView.M34 = -1.0f;
		perspectiveFieldOfView.M41 = perspectiveFieldOfView.M42 = perspectiveFieldOfView.M44 = 0.0f;
		perspectiveFieldOfView.M43 = (nearPlaneDistance * farPlaneDistance / (nearPlaneDistance - farPlaneDistance));
		return perspectiveFieldOfView;
	}

	Matrix Matrix::CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector) {
		Vector3 vector3_1 = Vector3::Normalize(cameraPosition - cameraTarget);
		Vector3 vector3_2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector3_1));
		Vector3 vector1 = Vector3::Cross(vector3_1, vector3_2);

		Matrix lookAt;
		lookAt.M11 = vector3_2.X;
		lookAt.M12 = vector1.X;
		lookAt.M13 = vector3_1.X;
		lookAt.M14 = 0.0f;
		lookAt.M21 = vector3_2.Y;
		lookAt.M22 = vector1.Y;
		lookAt.M23 = vector3_1.Y;
		lookAt.M24 = 0.0f;
		lookAt.M31 = vector3_2.Z;
		lookAt.M32 = vector1.Z;
		lookAt.M33 = vector3_1.Z;
		lookAt.M34 = 0.0f;
		lookAt.M41 = -Vector3::Dot(vector3_2, cameraPosition);
		lookAt.M42 = -Vector3::Dot(vector1, cameraPosition);
		lookAt.M43 = -Vector3::Dot(vector3_1, cameraPosition);
		lookAt.M44 = 1.0f;
		return lookAt;
	}

	Matrix Matrix::CreateWorld(Vector3 position, Vector3 forward, Vector3 up) {
		Vector3 vector3_1 = Vector3::Normalize(-forward);
		Vector3 vector2 = Vector3::Normalize(Vector3::Cross(up, vector3_1));
		Vector3 vector3_2 = Vector3::Cross(vector3_1, vector2);

		Matrix world;
		world.M11 = vector2.X;
		world.M12 = vector2.Y;
		world.M13 = vector2.Z;
		world.M14 = 0.0f;
		world.M21 = vector3_2.X;
		world.M22 = vector3_2.Y;
		world.M23 = vector3_2.Z;
		world.M24 = 0.0f;
		world.M31 = vector3_1.X;
		world.M32 = vector3_1.Y;
		world.M33 = vector3_1.Z;
		world.M34 = 0.0f;
		world.M41 = position.X;
		world.M42 = position.Y;
		world.M43 = position.Z;
		world.M44 = 1.0f;
		return world;
	}

	Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		const auto result = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
		return CreateFromQuaternion(result);
	}

	float Quaternion::Length() const {
		return std::sqrt(LengthSquared());
	}
	
	void Quaternion::Normalize() {
		float num = 1.0F / Length();
		X *= num;
		Y *= num;
		Z *= num;
		W *= num;
	}

	void Quaternion::Conjugate() {
		X = -X;
		Y = -Y;
		Z = -Z;
	}

	Quaternion Quaternion::Normalize(Quaternion const& quaternion) {
		float num = 1.0f / quaternion.Length();
		Quaternion quaternion1;
		quaternion1.X = quaternion.X * num;
		quaternion1.Y = quaternion.Y * num;
		quaternion1.Z = quaternion.Z * num;
		quaternion1.W = quaternion.W * num;
		return quaternion1;
	}

	Quaternion Quaternion::CreateFromAxisAngle(Vector3 const& axis, float angle) {
		float num1 = angle * 0.5f;
		float num2 = std::sin(num1);
		float num3 = std::cos(num1);

		Quaternion fromAxisAngle;
		fromAxisAngle.X = axis.X * num2;
		fromAxisAngle.Y = axis.Y * num2;
		fromAxisAngle.Z = axis.Z * num2;
		fromAxisAngle.W = num3;
		return fromAxisAngle;
	}

	Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll) {
		float num1 = roll * 0.5f;
		float num2 = std::sin(num1);
		float num3 = std::cos(num1);
		float num4 = pitch * 0.5f;
		float num5 = std::sin(num4);
		float num6 = std::cos(num4);
		float num7 = yaw * 0.5f;
		float num8 = std::sin(num7);
		float num9 = std::cos(num7);

		Quaternion fromYawPitchRoll;
		fromYawPitchRoll.X = (num9 * num5 * num3 + num8 * num6 * num2);
		fromYawPitchRoll.Y = (num8 * num6 * num3 - num9 * num5 * num2);
		fromYawPitchRoll.Z = (num9 * num6 * num2 - num8 * num5 * num3);
		fromYawPitchRoll.W = (num9 * num6 * num3 + num8 * num5 * num2);
		return fromYawPitchRoll;
	}

	Quaternion Quaternion::CreateFromRotationMatrix(Matrix const& matrix) {
		float num1 = matrix.M11 + matrix.M22 + matrix.M33;
		Quaternion fromRotationMatrix;

		if (num1 > 0.0) {
			float num2 = std::sqrt(num1 + 1.0F);
			fromRotationMatrix.W = num2 * 0.5f;
			float num3 = 0.5f / num2;
			fromRotationMatrix.X = (matrix.M23 - matrix.M32) * num3;
			fromRotationMatrix.Y = (matrix.M31 - matrix.M13) * num3;
			fromRotationMatrix.Z = (matrix.M12 - matrix.M21) * num3;
		}
		else if (matrix.M11 >= matrix.M22 && matrix.M11 >= matrix.M33) {
			float num4 = std::sqrt(1.0F + matrix.M11 - matrix.M22 - matrix.M33);
			float num5 = 0.5f / num4;
			fromRotationMatrix.X = 0.5f * num4;
			fromRotationMatrix.Y = (matrix.M12 + matrix.M21) * num5;
			fromRotationMatrix.Z = (matrix.M13 + matrix.M31) * num5;
			fromRotationMatrix.W = (matrix.M23 - matrix.M32) * num5;
		}
		else if (matrix.M22 > matrix.M33) {
			float num6 = std::sqrt(1.0F + matrix.M22 - matrix.M11 - matrix.M33);
			float num7 = 0.5f / num6;
			fromRotationMatrix.X = (matrix.M21 + matrix.M12) * num7;
			fromRotationMatrix.Y = 0.5f * num6;
			fromRotationMatrix.Z = (matrix.M32 + matrix.M23) * num7;
			fromRotationMatrix.W = (matrix.M31 - matrix.M13) * num7;
		}
		else {
			float num8 = std::sqrt(1.0F + matrix.M33 - matrix.M11 - matrix.M22);
			float num9 = 0.5f / num8;
			fromRotationMatrix.X = (matrix.M31 + matrix.M13) * num9;
			fromRotationMatrix.Y = (matrix.M32 + matrix.M23) * num9;
			fromRotationMatrix.Z = 0.5f * num8;
			fromRotationMatrix.W = (matrix.M12 - matrix.M21) * num9;
		}
		return fromRotationMatrix;
	}

	Quaternion Quaternion::Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount) {
		float num1 = amount;
		float d = quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
		bool flag = false;
		
		if (d < 0.0) {
			flag = true;
			d = -d;
		}

		float num2;
		float num3;

		if (d > 0.99999898672103882) {
			num2 = 1.0f - num1;
			num3 = flag ? -num1 : num1;
		}
		else {
			float a = std::acos(d);
			float num4 = (1.0F /std::sin(a));
			num2 = std::sin((1.0F - num1) * a) * num4;
			num3 = flag ? -std::sin(num1 * a) * num4 : std::sin(num1 * a) * num4;
		}

		Quaternion quaternion;
		quaternion.X = (num2 * quaternion1.X + num3 * quaternion2.X);
		quaternion.Y = (num2 * quaternion1.Y + num3 * quaternion2.Y);
		quaternion.Z = (num2 * quaternion1.Z + num3 * quaternion2.Z);
		quaternion.W = (num2 * quaternion1.W + num3 * quaternion2.W);

		return quaternion;
	}

	Quaternion Quaternion::Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount) {
		float num1 = amount;
		float num2 = 1.0f - num1;
		Quaternion quaternion;
		
		if (quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W >= 0.0) {
			quaternion.X = (num2 * quaternion1.X + num1 * quaternion2.X);
			quaternion.Y = (num2 * quaternion1.Y + num1 * quaternion2.Y);
			quaternion.Z = (num2 * quaternion1.Z + num1 * quaternion2.Z);
			quaternion.W = (num2 * quaternion1.W + num1 * quaternion2.W);
		}
		else {
			quaternion.X = (num2 * quaternion1.X - num1 * quaternion2.X);
			quaternion.Y = (num2 * quaternion1.Y - num1 * quaternion2.Y);
			quaternion.Z = (num2 * quaternion1.Z - num1 * quaternion2.Z);
			quaternion.W = (num2 * quaternion1.W - num1 * quaternion2.W);
		}

		float num3 = 1.0f / std::sqrt(quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z + quaternion.W * quaternion.W);
		quaternion.X *= num3;
		quaternion.Y *= num3;
		quaternion.Z *= num3;
		quaternion.W *= num3;
		return quaternion;
	}
	
	BoundingSphere BoundingSphere::CreateMerged(BoundingSphere const& original, BoundingSphere const& additional) {
		Vector3 result = Vector3::Subtract(additional.Center, original.Center);
		float num1 = result.Length();
		float radius1 = original.Radius;
		float radius2 = additional.Radius;

		if (radius1 + radius2 >= num1) {
			if (radius1 - radius2 >= num1)
				return original;
			if (radius2 - radius1 >= num1)
				return additional;
		}

		Vector3 vector3 = result * (1.0f / num1);
		float num2 = MathHelper::Min(-radius1, num1 - radius2);
		float num3 = (MathHelper::Max(radius1, num1 + radius2) - num2) * 0.5F;

		BoundingSphere merged;
		merged.Center = original.Center + vector3 * (num3 + num2);
		merged.Radius = num3;
		return merged;
	}

	BoundingSphere BoundingSphere::CreateFromBoundingBox(BoundingBox const& box) {
		BoundingSphere fromBoundingBox;
		fromBoundingBox.Center = Vector3::Lerp(box.Min, box.Max, 0.5f);
		float result = Vector3::Distance(box.Min, box.Max);
		fromBoundingBox.Radius = result * 0.5f;
		return fromBoundingBox;
	}
	
	BoundingSphere BoundingSphere::CreateFromPoints(Vector3* points, size_t length, size_t offset) {
		Vector3 current;
		Vector3 vector3_1 = current = points[offset];
		Vector3 vector3_2 = current;
		Vector3 vector3_3 = current;
		Vector3 vector3_4 = current;
		Vector3 vector3_5 = current;
		Vector3 vector3_6 = current;

		for (size_t i = 0 + offset; i < length; ++i) {
			const auto point = &points[i];

			if (point->X < vector3_6.X)
				vector3_6 = *point;
			if (point->X > vector3_5.X)
				vector3_5 = *point;
			if (point->Y < vector3_4.Y)
				vector3_4 = *point;
			if (point->Y > vector3_3.Y)
				vector3_3 = *point;
			if (point->Z < vector3_2.Z)
				vector3_2 = *point;
			if (point->Z > vector3_1.Z)
				vector3_1 = *point;
		}

		float result1 = Vector3::Distance(vector3_5, vector3_6);
		float result2 = Vector3::Distance(vector3_3, vector3_4);
		float result3 = Vector3::Distance(vector3_1, vector3_2);

		Vector3 result4;
		float num1;

		if (result1 > result2) {
			if (result1 > result3) {
				result4 = Vector3::Lerp(vector3_5, vector3_6, 0.5f);
				num1 = result1 * 0.5f;
			}
			else {
				result4 = Vector3::Lerp(vector3_1, vector3_2, 0.5f);
				num1 = result3 * 0.5f;
			}
		}
		else if (result2 > result3) {
			result4 = Vector3::Lerp(vector3_3, vector3_4, 0.5f);
			num1 = result2 * 0.5f;
		}
		else {
			result4 = Vector3::Lerp(vector3_1, vector3_2, 0.5f);
			num1 = result3 * 0.5f;
		}

		for (size_t i = 0; i < length; ++i) {
			const auto point = &points[i];

			Vector3 vector3_7;
			vector3_7.X = point->X - result4.X;
			vector3_7.Y = point->Y - result4.Y;
			vector3_7.Z = point->Z - result4.Z;

			float num2 = vector3_7.Length();

			if (num2 > num1) {
				num1 = ((num1 + num2) * 0.5F);
				result4 += (1.0F - num1 / num2) * vector3_7;
			}
		}

		BoundingSphere fromPoints;
		fromPoints.Center = result4;
		fromPoints.Radius = num1;
		return fromPoints;
	}

	ContainmentType BoundingSphere::Contains(BoundingBox const& box) const {
		if (!box.Intersects(*this))
			return ContainmentType::Disjoint;

		float num = Radius * Radius;

		Vector3 vector3;
		vector3.X = Center.X - box.Min.X;
		vector3.Y = Center.Y - box.Max.Y;
		vector3.Z = Center.Z - box.Max.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Max.X;
		vector3.Y = Center.Y - box.Max.Y;
		vector3.Z = Center.Z - box.Max.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Max.X;
		vector3.Y = Center.Y - box.Min.Y;
		vector3.Z = Center.Z - box.Max.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Min.X;
		vector3.Y = Center.Y - box.Min.Y;
		vector3.Z = Center.Z - box.Max.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Min.X;
		vector3.Y = Center.Y - box.Max.Y;
		vector3.Z = Center.Z - box.Min.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Max.X;
		vector3.Y = Center.Y - box.Max.Y;
		vector3.Z = Center.Z - box.Min.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Max.X;
		vector3.Y = Center.Y - box.Min.Y;
		vector3.Z = Center.Z - box.Min.Z;

		if (vector3.LengthSquared() > num)
			return ContainmentType::Intersects;

		vector3.X = Center.X - box.Min.X;
		vector3.Y = Center.Y - box.Min.Y;
		vector3.Z = Center.Z - box.Min.Z;

		return vector3.LengthSquared() > num ? ContainmentType::Intersects : ContainmentType::Contains;
	}

	void BoundingSphere::SupportMapping(Vector3 const& v, Vector3& result) const {
		float num = Radius / v.Length();
		result.X = Center.X + v.X * num;
		result.Y = Center.Y + v.Y * num;
		result.Z = Center.Z + v.Z * num;
	}

	BoundingSphere BoundingSphere::Transform(Matrix const& matrix) const {
		BoundingSphere boundingSphere;
		boundingSphere.Center = Vector3::Transform(Center, matrix);
		float d = MathHelper::Max((matrix.M11 * matrix.M11 + matrix.M12 * matrix.M12 + matrix.M13 * matrix.M13), MathHelper::Max((matrix.M21 * matrix.M21 + matrix.M22 * matrix.M22 + matrix.M23 * matrix.M23), (matrix.M31 * matrix.M31 + matrix.M32 * matrix.M32 + matrix.M33 * matrix.M33)));
		boundingSphere.Radius = Radius * std::sqrt(d);
		return boundingSphere;
	}

	Plane::Plane(Vector3 const& point1, Vector3 const& point2, Vector3 const& point3) {
		float num1 = point2.X - point1.X;
		float num2 = point2.Y - point1.Y;
		float num3 = point2.Z - point1.Z;
		float num4 = point3.X - point1.X;
		float num5 = point3.Y - point1.Y;
		float num6 = point3.Z - point1.Z;
		float num7 = (num2 * num6 - num3 * num5);
		float num8 = (num3 * num4 - num1 * num6);
		float num9 = (num1 * num5 - num2 * num4);
		float num10 = 1.0f / std::sqrt(num7 * num7 + num8 * num8 + num9 * num9);
		Normal.X = num7 * num10;
		Normal.Y = num8 * num10;
		Normal.Z = num9 * num10;
		D = -(Normal.X * point1.X + Normal.Y * point1.Y + Normal.Z * point1.Z);
	}

	void Plane::Normalize()	{
		float d = (Normal.X * Normal.X + Normal.Y * Normal.Y + Normal.Z * Normal.Z);
		if (std::abs(d - 1.0f) < 1.1920928955078125E-07)
			return;
		float num = 1.0f / std::sqrt(d);
		Normal.X *= num;
		Normal.Y *= num;
		Normal.Z *= num;
		D *= num;
	}

	Plane Plane::Normalize(Plane const& value) {
		float d = (value.Normal.X * value.Normal.X + value.Normal.Y * value.Normal.Y + value.Normal.Z * value.Normal.Z);
		
		if (std::abs(d - 1.0f) < 1.1920928955078125E-07) {
			Plane plane;
			plane.Normal = value.Normal;
			plane.D = value.D;
			return plane;
		}

		float num = 1.0f / std::sqrt(d);
		Plane plane1;
		plane1.Normal.X = value.Normal.X * num;
		plane1.Normal.Y = value.Normal.Y * num;
		plane1.Normal.Z = value.Normal.Z * num;
		plane1.D = value.D * num;
		return plane1;
	}

	nullfloat Plane::Intersects(Ray const& ray) const
	{
		float num1 = (Normal.X * ray.Direction.X + Normal.Y * ray.Direction.Y + Normal.Z * ray.Direction.Z);

		if (std::abs(num1) < 9.9999997473787516E-06)
			return nullfloat();

		float num2 = (Normal.X * ray.Position.X + Normal.Y * ray.Position.Y + Normal.Z * ray.Position.Z);
		float num3 = (-D - num2) / num1;

		if (num3 < 0.0F) {
			if (num3 < -9.9999997473787516E-06)
				return nullfloat();

			num3 = 0.0f;
		}
		return num3;
	}

	float Plane::PerpendicularDistance(Vector3 const& point, Plane const& plane) {
		return std::abs((plane.Normal.X * point.X + plane.Normal.Y * point.Y + plane.Normal.Z * point.Z)
			/ std::sqrt(plane.Normal.X * plane.Normal.X + plane.Normal.Y * plane.Normal.Y + plane.Normal.Z * plane.Normal.Z));
	}

	Matrix Matrix::CreateShadow(Vector3 const& lightDirection, Plane const& plane)
	{
		Plane result = Plane::Normalize(plane);
		float num1 = (result.Normal.X * lightDirection.X + result.Normal.Y * lightDirection.Y + result.Normal.Z * lightDirection.Z);
		float num2 = -result.Normal.X;
		float num3 = -result.Normal.Y;
		float num4 = -result.Normal.Z;
		float num5 = -result.D;

		Matrix shadow;
		shadow.M11 = num2 * lightDirection.X + num1;
		shadow.M21 = num3 * lightDirection.X;
		shadow.M31 = num4 * lightDirection.X;
		shadow.M41 = num5 * lightDirection.X;
		shadow.M12 = num2 * lightDirection.Y;
		shadow.M22 = num3 * lightDirection.Y + num1;
		shadow.M32 = num4 * lightDirection.Y;
		shadow.M42 = num5 * lightDirection.Y;
		shadow.M13 = num2 * lightDirection.Z;
		shadow.M23 = num3 * lightDirection.Z;
		shadow.M33 = num4 * lightDirection.Z + num1;
		shadow.M43 = num5 * lightDirection.Z;
		shadow.M14 = 0.0f;
		shadow.M24 = 0.0f;
		shadow.M34 = 0.0f;
		shadow.M44 = num1;
		return shadow;
	}
	
	Matrix Matrix::CreateReflection(Plane const& original)
	{
		auto value = original;

		value.Normalize();
		float x = value.Normal.X;
		float y = value.Normal.Y;
		float z = value.Normal.Z;
		float num1 = -2.f * x;
		float num2 = -2.f * y;
		float num3 = -2.f * z;
		Matrix reflection;
		reflection.M11 = (num1 * x + 1.0F);
		reflection.M12 = num2 * x;
		reflection.M13 = num3 * x;
		reflection.M14 = 0.0f;
		reflection.M21 = num1 * y;
		reflection.M22 = (num2 * y + 1.0F);
		reflection.M23 = num3 * y;
		reflection.M24 = 0.0f;
		reflection.M31 = num1 * z;
		reflection.M32 = num2 * z;
		reflection.M33 = (num3 * z + 1.0F);
		reflection.M34 = 0.0f;
		reflection.M41 = num1 * value.D;
		reflection.M42 = num2 * value.D;
		reflection.M43 = num3 * value.D;
		reflection.M44 = 1.f;
		return reflection;
	}

	nullfloat dxna::BoundingBox::Intersects(Ray const& ray) const
	{
		float num1 = 0.0f;
		float num2 = FloatMaxValue;
		
		if (std::abs(ray.Direction.X) < 9.9999999747524271E-07)	{
			if (ray.Position.X < Min.X || ray.Position.X > Max.X)
				return nullfloat();
		}
		else {
			float num3 = 1.0f / ray.Direction.X;
			float num4 = (Min.X - ray.Position.X) * num3;
			float num5 = (Max.X - ray.Position.X) * num3;
			
			if (num4 > num5) {
				float num6 = num4;
				num4 = num5;
				num5 = num6;
			}
			
			num1 = MathHelper::Max(num4, num1);
			num2 = MathHelper::Min(num5, num2);

			if (num1 > num2)
				return nullfloat();
		}
		
		if (std::abs(ray.Direction.Y) < 9.9999999747524271E-07)
		{
			if (ray.Position.Y < Min.Y || ray.Position.Y > Max.Y)
				return nullfloat();
		}
		else {
			float num7 = 1.0f / ray.Direction.Y;
			float num8 = (Min.Y - ray.Position.Y) * num7;
			float num9 = (Max.Y - ray.Position.Y) * num7;
			if (num8 > num9)
			{
				float num10 = num8;
				num8 = num9;
				num9 = num10;
			}
			
			num1 = MathHelper::Max(num8, num1);
			num2 = MathHelper::Min(num9, num2);
			
			if (num1 > num2)
				return nullfloat();
		}

		if (std::abs(ray.Direction.Z) < 9.9999999747524271E-07) 	{
			if (ray.Position.Z < Min.Z || ray.Position.Z > Max.Z)
				return nullfloat();
		}
		else
		{
			float num11 = 1.0f / ray.Direction.Z;
			float num12 = (Min.Z - ray.Position.Z) * num11;
			float num13 = (Max.Z - ray.Position.Z) * num11;
			
			if (num12 > num13)
			{
				float num14 = num12;
				num12 = num13;
				num13 = num14;
			}

			num1 = MathHelper::Max(num12, num1);
			float num15 = MathHelper::Min(num13, num2);

			if (num1 > num15)
				return nullfloat();
		}
		return num1;
	}

	nullfloat BoundingSphere::Intersects(Ray const& ray) const {
		float num1 = Center.X - ray.Position.X;
		float num2 = Center.Y - ray.Position.Y;
		float num3 = Center.Z - ray.Position.Z;
		float num4 = (num1 * num1 + num2 * num2 + num3 * num3);
		float num5 = Radius * Radius;

		if (num4 <= num5)
			return 0.0f;

		float num6 = (num1 * ray.Direction.X + num2 * ray.Direction.Y + num3 * ray.Direction.Z);

		if (num6 < 0.0)
			return nullfloat();

		float num7 = num4 - num6 * num6;
		
		if (num7 >  num5)
			return nullfloat();

		float num8 = std::sqrt(num5 - num7);

		return num6 - num8;
	}

	BoundingSphere dxna::BoundingSphere::CreateFromFrustum(BoundingFrustum const& frustum) {
		std::vector<Vector3> points(frustum.CornerCount);

		return CreateFromPoints(points.data(), points.size(), 0);
	}
}
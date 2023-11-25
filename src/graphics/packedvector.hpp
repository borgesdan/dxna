#ifndef DXNA_GRAPHICS_PACKEDVECTOR_HPP
#define DXNA_GRAPHICS_PACKEDVECTOR_HPP

#include "../structs.hpp"
#include "../cs/cs.hpp"
#include "../mathhelper.hpp"

namespace dxna::graphics {
	class IPackedVector {
	public:
		virtual void PackFromVector4(Vector4 const& vector) = 0;
		virtual Vector4 ToVector4() const = 0;
	};

	struct HalfTypeHelper {
		static constexpr ushortcs Convert(float f) noexcept
		{
			const auto value = *(intcs*)&f;
			return Convert(value);
		}

		static constexpr ushortcs Convert(intcs i) noexcept {
			auto s = (i >> 16) & 0x00008000;
			auto e = ((i >> 23) & 0x000000ff) - (127 - 15);
			auto m = i & 0x007fffff;

			if (e <= 0) {
				if (e < -10) {
					return (ushortcs)s;
				}

				m = m | 0x00800000;

				auto t = 14 - e;
				auto a = (1 << (t - 1)) - 1;
				auto b = (m >> t) & 1;

				m = (m + a + b) >> t;

				return (ushortcs)(s | m);
			}
			else if (e == 0xff - (127 - 15))
			{
				if (m == 0)	{
					return (ushortcs)(s | 0x7c00);
				}
				else {
					m >>= 13;
					return (ushortcs)(s | 0x7c00 | m | ((m == 0) ? 1 : 0));
				}
			}
			else {
				m = m + 0x00000fff + ((m >> 13) & 1);

				if ((m & 0x00800000) != 0) {
					m = 0;
					e += 1;
				}

				if (e > 30) {
					return (ushortcs)(s | 0x7c00);
				}

				return (ushortcs)(s | (e << 10) | (m >> 13));
			}
		}

		static constexpr float Convert(ushortcs value) noexcept
		{
			uintcs rst;
			uintcs mantissa = (uintcs)(value & 1023);
			uintcs exp = 0xfffffff2;

			if ((value & -33792) == 0)
			{
				if (mantissa != 0)
				{
					while ((mantissa & 1024) == 0)
					{
						exp--;
						mantissa = mantissa << 1;
					}
					mantissa &= 0xfffffbff;
					rst = ((uintcs)((((uintcs)value & 0x8000) << 16) | ((exp + 127) << 23))) | (mantissa << 13);
				}
				else
				{
					rst = (uintcs)((value & 0x8000) << 16);
				}
			}
			else
			{
				rst = (uintcs)(((((uintcs)value & 0x8000) << 16) | ((((((uintcs)value >> 10) & 0x1f) - 15) + 127) << 23)) | (mantissa << 13));
			}
			
			return *(float*)&rst;
		}

	private:
		constexpr HalfTypeHelper() = default;
		constexpr HalfTypeHelper(HalfTypeHelper&&) = default;
		constexpr HalfTypeHelper(const HalfTypeHelper&) = default;
	};

	struct Alpha8 : public IPackedVector {

		constexpr Alpha8() noexcept = default;

		Alpha8(float alpha) noexcept :
			PackedValue(Pack(alpha)) {
		}

		constexpr float ToAlpha() const noexcept {
			return static_cast<float>(PackedValue) / 255.0f;
		}

		void PackFromVector4(Vector4 const& vector) noexcept override {
			PackedValue = Pack(vector.W);
		}

		Vector4 ToVector4() const noexcept {
			return Vector4(0.0f, 0.0f, 0.0f, static_cast<float>(PackedValue) / 255.0f);
		}

		static bytecs Pack(float alpha) noexcept {
			return static_cast<bytecs>(std::round(MathHelper::Clamp(alpha, 0, 1) * 255.0f));
		}

		bytecs PackedValue{ 0 };
	};

	struct Bgr565 : public IPackedVector {
		constexpr Bgr565() noexcept = default;

		Bgr565(float x, float y, float z) noexcept :
			PackedValue(Pack(x, y, z)) {}

		Bgr565(Vector3 const& value) noexcept :
			PackedValue(Pack(value.X, value.Y, value.Z)) {}

		constexpr void PackFromVector4(Vector4 const& vector) noexcept override {
			PackedValue = (ushortcs)(
				((intcs)(vector.X * 31.0f) & 0x1F) << 11 |
				((intcs)(vector.Y * 63.0f) & 0x3F) << 5 |
				((intcs)(vector.Z * 31.0f) & 0x1F));
		}

		constexpr Vector4 ToVector4() const noexcept {
			return Vector4(ToVector3(), 1.0f);
		}

		constexpr Vector3 ToVector3() const noexcept {
			return Vector3(
				static_cast<float>(((PackedValue >> 11) & 0x1F) * (1.0f / 31.0f)),
				static_cast<float>(((PackedValue >> 5) & 0x3F) * (1.0f / 63.0f)),
				static_cast<float>((PackedValue & 0x1F) * (1.0f / 31.0f))
			);
		}

		static ushortcs Pack(float x, float y, float z) noexcept {
			const auto val1 = MathHelper::Clamp(x, 0, 1) * 31.0f;
			const auto val2 = MathHelper::Clamp(y, 0, 1) * 63.0f;
			const auto val3 = MathHelper::Clamp(z, 0, 1) * 31.0f;

			const auto val4 = ((intcs)std::round(val1) & 0x1F) << 11;
			const auto val5 = ((intcs)std::round(val2) & 0x3F) << 5;
			const auto val6 = (intcs)std::round(val3) & 0x1F;

			return static_cast<ushortcs>(val4 | val5 | val6);
		}

		ushortcs PackedValue{ 0 };
	};

	struct Bgra4444 : public IPackedVector {
		constexpr Bgra4444() noexcept = default;

		Bgra4444(float x, float y, float z, float w) noexcept :
			PackedValue(Pack(x, y, z, w)) {
		}

		Bgra4444(Vector4 const& vector) noexcept :
			PackedValue(Pack(vector.X, vector.Y, vector.Z, vector.W)) {
		}

		void PackFromVector4(Vector4 const& vector) noexcept override {
			PackedValue = Pack(vector.X, vector.Y, vector.Z, vector.W);
		}

		constexpr Vector4 ToVector4() const noexcept override {
			const auto maxVal = 1.0f / 15.0f;

			return Vector4(
				((PackedValue >> 8) & 0x0F) * maxVal,
				((PackedValue >> 4) & 0x0F) * maxVal,
				(PackedValue & 0x0F) * maxVal,
				((PackedValue >> 12) & 0x0F) * maxVal);
		}

		static ushortcs Pack(float x, float y, float z, float w) noexcept {
			const auto val1 = MathHelper::Clamp(w, 0, 1) * 15.0f;
			const auto val2 = MathHelper::Clamp(x, 0, 1) * 15.0f;
			const auto val3 = MathHelper::Clamp(y, 0, 1) * 15.0f;
			const auto val4 = MathHelper::Clamp(z, 0, 1) * 15.0f;

			const auto val5 = ((intcs)std::round(val1) & 0x0F) << 12;
			const auto val6 = ((intcs)std::round(val2) & 0x0F) << 8;
			const auto val7 = ((intcs)std::round(val3) & 0x0F) << 4;
			const auto val8 = ((intcs)std::round(val4) & 0x0F);

			return static_cast<ushortcs>(val5 | val6 | val7 | val8);
		}

		ushortcs PackedValue{ 0 };
	};

	struct Bgra5551 : public IPackedVector {
		constexpr Bgra5551() noexcept = default;

		Bgra5551(float x, float y, float z, float w) noexcept :
			PackedValue(Pack(x, y, z, w)) {
		}

		Bgra5551(Vector4 const& vector) noexcept :
			PackedValue(Pack(vector.X, vector.Y, vector.Z, vector.W)) {
		}

		void PackFromVector4(Vector4 const& vector) noexcept {
			PackedValue = Pack(vector.X, vector.Y, vector.Z, vector.W);
		}

		constexpr Vector4 ToVector4() const noexcept {
			return Vector4(
				static_cast<float>(((PackedValue >> 10) & 0x1F) / 31.0f),
				static_cast<float>(((PackedValue >> 5) & 0x1F) / 31.0f),
				static_cast<float>(((PackedValue >> 0) & 0x1F) / 31.0f),
				static_cast<float>((PackedValue >> 15) & 0x01)
			);
		}

		static ushortcs Pack(float x, float y, float z, float w) noexcept {
			const auto val1 = MathHelper::Clamp(x, 0, 1) * 31.0f;
			const auto val2 = MathHelper::Clamp(y, 0, 1) * 31.0f;
			const auto val3 = MathHelper::Clamp(z, 0, 1) * 31.0f;
			const auto val4 = MathHelper::Clamp(w, 0, 1);

			const auto res1 = ((intcs)std::round(val1) & 0x1F) << 10;
			const auto res2 = ((intcs)std::round(val2) & 0x1F) << 5;
			const auto res3 = ((intcs)std::round(val3) & 0x1F) << 0;
			const auto res4 = (((intcs)std::round(val4) & 0x1) << 15);

			return (ushortcs)(res1 | res2 | res3 | res4);
		}

		ushortcs PackedValue{ 0 };
	};	

	struct HalfSingle : public IPackedVector {

		constexpr HalfSingle() noexcept = default;

		constexpr HalfSingle(float single) noexcept :
			PackedValue(HalfTypeHelper::Convert(single)) {
		}		

		constexpr Vector4 ToVector4() const noexcept {
			return Vector4(ToSingle(), 0.0f, 0.0f, 1.0f);
		}

		constexpr float ToSingle() const noexcept {
			return HalfTypeHelper::Convert(PackedValue);
		}		

		constexpr void PackFromVector4(Vector4 const& vector) noexcept {
			PackedValue = HalfTypeHelper::Convert(vector.X);
		}

		ushortcs PackedValue{ 0 };
	};

	struct HalfVector2 : public IPackedVector {

		constexpr HalfVector2() noexcept = default;

		HalfVector2(Vector2 const& vector) noexcept :
			PackedValue(Pack(vector.X, vector.Y)) {
		}

		HalfVector2(float x, float y) noexcept :
			PackedValue(Pack(x, y)) {
		}

		void PackFromVector4(Vector4 const& vector) noexcept {
			PackedValue = Pack(vector.X, vector.Y);
		}

		constexpr Vector4 ToVector4() const noexcept {
			Vector2 vector = ToVector2();
			return Vector4(vector.X, vector.Y, 0.0f, 1.0f);
		}

		constexpr Vector2 ToVector2() const noexcept {
			Vector2 vector;
			vector.X = HalfTypeHelper::Convert((ushortcs)PackedValue);
			vector.Y = HalfTypeHelper::Convert((ushortcs)(PackedValue >> 0x10));
			return vector;
		}

		constexpr static uintcs Pack(float vectorX, float vectorY) noexcept {
			const auto num2 = HalfTypeHelper::Convert(vectorX);
			const auto num = static_cast<uintcs>(HalfTypeHelper::Convert(vectorY) << 0x10);
			
			return (num2 | num);
		}

		uintcs PackedValue{ 0 };
	};

	struct HalfVector4 : public IPackedVector {

		constexpr HalfVector4() noexcept = default;		

		HalfVector4(float x, float y, float z, float w) noexcept :
			PackedValue(Pack({ x, y, z, w })) {
		}

		void PackFromVector4(Vector4 const& vector) noexcept {
			PackedValue = Pack(vector);
		}

		constexpr Vector4 ToVector4() const noexcept {
			return Vector4(
				HalfTypeHelper::Convert((ushortcs)PackedValue),
				HalfTypeHelper::Convert((ushortcs)(PackedValue >> 0x10)),
				HalfTypeHelper::Convert((ushortcs)(PackedValue >> 0x20)),
				HalfTypeHelper::Convert((ushortcs)(PackedValue >> 0x30)));
		}		

		constexpr static uintcs Pack(Vector4 const& vector) noexcept {
			const auto num4 = (ulongcs)HalfTypeHelper::Convert(vector.X);
			const auto num3 = ((ulongcs)HalfTypeHelper::Convert(vector.Y) << 0x10);
			const auto num2 = ((ulongcs)HalfTypeHelper::Convert(vector.Z) << 0x20);
			const auto num1 = ((ulongcs)HalfTypeHelper::Convert(vector.W) << 0x30);
			
			return num4 | num3 | num2 | num1;
		}

		uintcs PackedValue{ 0 };
	};

	struct NormalizedByte2 : public IPackedVector {

		constexpr NormalizedByte2() noexcept = default;

		NormalizedByte2(Vector2 const& vector) noexcept :
			PackedValue(Pack(vector.X, vector.Y)) {
		}

		NormalizedByte2(float x, float y) noexcept :
			PackedValue(Pack(x, y)) {
		}	

		void PackFromVector4(Vector4 const& vector) noexcept {
			PackedValue = Pack(vector.X, vector.Y);
		}

		constexpr Vector4 ToVector4() const noexcept {
			return Vector4(ToVector2(), 0.0f, 1.0f);
		}

		constexpr Vector2 ToVector2() const noexcept {
			return Vector2(
				((sbytecs)((PackedValue >> 0) & 0xFF)) / 127.0f,
				((sbytecs)((PackedValue >> 8) & 0xFF)) / 127.0f);
		}

		static uintcs Pack(float x, float y) noexcept {
			const auto byte2 = (((ushortcs)std::round(MathHelper::Clamp(x, -1.0f, 1.0f) * 127.0f)) & 0xFF) << 0;
			const auto byte1 = (((ushortcs)std::round(MathHelper::Clamp(y, -1.0f, 1.0f) * 127.0f)) & 0xFF) << 8;

			return (ushortcs)(byte2 | byte1);
		}

		ushortcs PackedValue{ 0 };
	};
}

#endif
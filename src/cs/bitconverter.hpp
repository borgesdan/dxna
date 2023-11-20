#ifndef DXNA_CS_BITCONVERTER_HPP
#define DXNA_CS_BITCONVERTER_HPP

#include "cstypes.hpp"
#include <string>

namespace cs {
	struct BitConveter {
		static constexpr bool IsLittleEndian() {
			const int value{ 0x01 };
			const void* address{ static_cast<const void*>(&value) };
			const unsigned char* least_significant_address{ static_cast<const unsigned char*>(address) };

			return (*least_significant_address == 0x01);
		}

		//Returns the specified Boolean value as a byte array.
		static bytecs* GetBytes(bool value) {
			return new bytecs[]{ value ? static_cast<bytecs>(1) : static_cast<bytecs>(0) };
		}

		//Returns the specified Unicode character value as an array of bytes.
		static bytecs* GetBytes(charcs value) {
			return GetBytes(static_cast<shortcs>(value));
		}

		//Returns the specified 16-bit unsigned integer value as an array of bytes.
		static bytecs* GetBytes(ushortcs value) {
			return GetBytes(static_cast<shortcs>(value));
		}

		//Returns the specified 32-bit unsigned integer value as an array of bytes.
		static bytecs* GetBytes(uintcs value) {
			return GetBytes(static_cast<intcs>(value));
		}

		//Returns the specified 64-bit unsigned integer value as an array of bytes.
		static bytecs* GetBytes(ulongcs value) {
			return GetBytes(static_cast<longcs>(value));
		}

		//Returns the specified single-precision floating point value as an array of bytes.
		static bytecs* GetBytes(float value) {
			return GetBytes(*(intcs*)&value);
		}

		//Returns the specified double-precision floating point value as an array of bytes.
		static bytecs* GetBytes(double value) {
			return GetBytes(*(longcs*)&value);
		}

		//Returns the specified 16-bit signed integer value as an array of bytes.
		static bytecs* GetBytes(shortcs value) {
			auto bytes = new bytecs[2];
			auto numPtr = &bytes[0];
			*(short*)numPtr = value;

			return bytes;
		}

		//Returns the specified 32-bit signed integer value as an array of bytes.
		static bytecs* GetBytes(intcs value) {
			auto bytes = new bytecs[4];
			auto numPtr = &bytes[0];
			*(intcs*)numPtr = value;

			return bytes;
		}

		//Returns the specified 64-bit signed integer value as an array of bytes.
		static bytecs* GetBytes(longcs value) {
			auto bytes = new bytecs[8];
			auto numPtr = &bytes[0];
			*(longcs*)numPtr = value;

			return bytes;
		}

		//Returns a Unicode character converted from two bytes at a specified position in a byte array.
		static charcs ToChar(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 2)
				return 0;

			return static_cast<charcs>(ToInt16(value, valueLength, startIndex));
		}

		//Returns a 16-bit signed integer converted from two bytes at a specified position in a byte array.
		static shortcs ToInt16(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 2)
				return 0;

			auto numPtr = &value[startIndex];

			if (startIndex % 2 == 0)
				return *(shortcs*)numPtr;

			return IsLittleEndian() ? (shortcs)((intcs)*numPtr | (intcs)numPtr[1] << 8) : (shortcs)((intcs)*numPtr << 8 | (intcs)numPtr[1]);
		}

		//Returns a 32-bit signed integer converted from two bytes at a specified position in a byte array.
		static intcs ToInt32(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 4)
				return 0;

			auto numPtr = &value[startIndex];

			if (startIndex % 4 == 0)
				return *(intcs*)numPtr;

			return IsLittleEndian() ? (intcs)*numPtr | (intcs)numPtr[1] << 8 | (intcs)numPtr[2] << 16 | (intcs)numPtr[3] << 24 : (intcs)*numPtr << 24 | (intcs)numPtr[1] << 16 | (intcs)numPtr[2] << 8 | (intcs)numPtr[3];
		}

		//Returns a 64-bit signed integer converted from eight bytes at a specified position in a byte array.
		static longcs ToInt64(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 8)
				return 0;

			auto numPtr = &value[startIndex];

			if (startIndex % 8 == 0)
				return *(long*)numPtr;

			if (IsLittleEndian())
				return (longcs)(uintcs)((intcs)*numPtr | (intcs)numPtr[1] << 8 | (intcs)numPtr[2] << 16 | (intcs)numPtr[3] << 24) | (longcs)((intcs)numPtr[4] | (intcs)numPtr[5] << 8 | (intcs)numPtr[6] << 16 | (intcs)numPtr[7] << 24) << 32;

			auto num = (intcs)*numPtr << 24 | (intcs)numPtr[1] << 16 | (intcs)numPtr[2] << 8 | (intcs)numPtr[3];
			return (longcs)((uintcs)((intcs)numPtr[4] << 24 | (intcs)numPtr[5] << 16 | (intcs)numPtr[6] << 8) | (uintcs)numPtr[7]) | (longcs)num << 32;
		}

		//Returns a 16-bit unsigned integer converted from two bytes at a specified position in a byte array.
		static ushortcs ToUInt16(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 2)
				return 0;

			return (ushortcs)ToInt16(value, valueLength, startIndex);
		}

		//Returns a 32-bit unsigned integer converted from four bytes at a specified position in a byte array.
		static uintcs ToUInt32(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 4)
				return 0;

			return (uintcs)ToInt32(value, valueLength, startIndex);
		}

		//Returns a 64-bit unsigned integer converted from eight bytes at a specified position in a byte array.
		static ulongcs ToUInt64(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 8)
				return 0;

			return (ulongcs)ToInt64(value, valueLength, startIndex);
		}

		//Returns a single-precision floating point number converted from four bytes at a specified position in a byte array.
		static float ToSingle(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 4)
				return 0;

			const auto result = ToInt32(value, valueLength, startIndex);
			return *(float*)&result;
		}

		//Returns a double-precision floating point number converted from eight bytes at a specified position in a byte array.
		static double ToDouble(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex >= valueLength || startIndex > valueLength - 8)
				return 0;

			const auto result = ToInt64(value, valueLength, startIndex);
			return *(double*)&result;
		}

		
		static constexpr char GetHexValue(intcs i) {
			return i < 10 ? (charcs)(i + 48) : (charcs)(i - 10 + 65);
		}

		//Converts the numeric value of each element of a specified subarray of bytes to its equivalent hexadecimal string representation.
		static std::string ToString(bytecs* value, size_t valueLength, intcs startIndex, intcs length) {
			if (value == nullptr || startIndex < 0 || startIndex >= valueLength && startIndex > 0
				|| length <= 0 || startIndex > valueLength - length || length > 715827882)
				return std::string();

			auto length1 = length * 3;
			auto chArray = new char[length1];
			auto num1 = startIndex;

			for (size_t index = 0; index < length1; index += 3)
			{
				auto num2 = value[num1++];
				chArray[index] = GetHexValue((intcs)num2 / 16);
				chArray[index + 1] = GetHexValue((intcs)num2 % 16);
				chArray[index + 2] = '-';
			}

			return std::string(chArray, length1 - 1);
		}

		//Returns a Boolean value converted from the byte at a specified position in a byte array.
		static bool ToBoolean(bytecs* value, size_t valueLength, intcs startIndex) {
			if (value == nullptr || startIndex < 0 || startIndex > valueLength - 1)
				return false;

			return value[startIndex] != (bytecs)0;
		}

		//Converts the specified double-precision floating point number to a 64-bit signed integer.
		static constexpr longcs DoubleToInt64Bits(double value) {
			return *(long*)&value;
		}

		//Converts the specified 64-bit signed integer to a double-precision floating point number.
		static constexpr double Int64BitsToDouble(longcs value) {
			return *(double*)&value;
		}
		
	private:
		//Esconde construtores para transformar a classe em estática.
		constexpr BitConveter() = default;
		constexpr BitConveter(BitConveter&&) = default;
		constexpr BitConveter(const BitConveter&) = default;
	};
}

#endif
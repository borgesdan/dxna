#ifndef DXNA_HELPERS_HPP
#define DXNA_HELPERS_HPP

namespace dxna {
	enum class Endianness {
		Little, Big
	};

	struct Enviroment {
		// https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program

		static constexpr Endianness GetEndianness() {
			const int value{ 0x01 };
			const void* address{ static_cast<const void*>(&value) };
			const unsigned char* least_significant_address{ static_cast<const unsigned char*>(address) };

			return (*least_significant_address == 0x01) ? Endianness::Little : Endianness::Big;
		}

		static constexpr bool IsLittleEndian() { return GetEndianness() == Endianness::Little; }
		static constexpr bool IsBigEndian() { return GetEndianness() == Endianness::Big; }
	};
}

#endif
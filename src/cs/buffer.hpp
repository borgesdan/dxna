#ifndef DXNA_CS_BUFFER_HPP
#define DXNA_CS_BUFFER_HPP

#include "cstypes.hpp"

namespace cs {
	class Buffer {
	public:
		template <typename T>
		static void BlockCopy(T const* src, rsize_t srcOffset, T* dst, rsize_t dstOffset, rsize_t byteCount) {
			memmove_s(dst + dstOffset, byteCount, src + srcOffset, byteCount);
		}

	private:
		//Esconde construtores para transformar a classe em estática.
		constexpr Buffer() = default;
		constexpr Buffer(Buffer&&) = default;
		constexpr Buffer(const Buffer&) = default;
	};
}

#endif
#ifndef DXNA_CS_ARRAY_HPP
#define DXNA_CS_ARRAY_HPP

namespace cs {
	struct Array {
		template <typename T, typename TValue>
		static void Clear(T* array, size_t index, size_t length, TValue clearValue) {
			for (size_t i = index; i < length; ++i) {
				array[i] = clearValue;
			}
		}
	};
}

#endif
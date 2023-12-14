#ifndef DXNA_UTILITY_HPP
#define DXNA_UTILITY_HPP

//
// https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
// https://en.cppreference.com/w/cpp/utility/hash
//

namespace dxna {
	struct Hash {
		template <class T>
		static constexpr void Combine(std::size_t& seed, const T& v) {
			std::hash<T> hasher;
			seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
	};
}



#endif
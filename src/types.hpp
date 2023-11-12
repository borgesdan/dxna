#ifndef DXNA_TYPES_HPP
#define DXNA_TYPES_HPP

#include <vector>
#include <memory>
#include <utility>

namespace dxna {
	template <typename T>
	using vectorptr = std::shared_ptr<std::vector<T>>;

	template <class _Ty, class... _Types>
	vectorptr<_Ty> NewVector(_Types&&... _Args) {
		return std::make_shared<std::vector<_Ty>>(std::forward<_Types>(_Args)...);
	}
}

#endif
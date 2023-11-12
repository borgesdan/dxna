#ifndef DXNA_TYPES_HPP
#define DXNA_TYPES_HPP

#include <vector>
#include <memory>
#include <utility>

namespace dxna {
	//Define um ponteiro para um vetor de um tipo definido.
	template <typename T>
	using vectorptr = std::shared_ptr<std::vector<T>>;

	//Inicializa um ponteiro para um tipo definido.
	template <class _Ty, class... _Types>
	std::shared_ptr<_Ty> New(_Types&&... _Args) {
		return std::make_shared<_Ty>(std::forward<_Types>(_Args)...);
	}

	//Inicializa um vetor para ponteiros de um tipo definido.
	template <class _Ty>
	std::vector<std::shared_ptr<_Ty>> NewArray(size_t count) {
		return std::vector<std::shared_ptr<_Ty>>(count);
	}

	//Inicializa um novo ponteiro para um vetor
	template <class _Ty, class... _Types>
	vectorptr<_Ty> NewVector(_Types&&... _Args) {
		return std::make_shared<std::vector<_Ty>>(std::forward<_Types>(_Args)...);
	}
}

#endif
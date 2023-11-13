#ifndef DXNA_TYPES_HPP
#define DXNA_TYPES_HPP

#include <vector>
#include <memory>
#include <utility>
#include <any>

namespace dxna {
	//Define um ponteiro para um vetor de um tipo definido.
	template <typename T>
	using vectorptr = std::shared_ptr<std::vector<T>>;

	//Define um pontiero para um tipo aceito em std::any
	using anyptr = std::shared_ptr<std::any>;

	//Inicializa um ponteiro para um tipo definido.
	template <class _Ty, class... _Types>
	std::shared_ptr<_Ty> New(_Types&&... _Args) {
		return std::make_shared<_Ty>(std::forward<_Types>(_Args)...);
	}	

	//Inicializa um novo ponteiro para um vetor
	template <class _Ty, class... _Types>
	vectorptr<_Ty> NewVectorPtr(_Types&&... _Args) {
		return std::make_shared<std::vector<_Ty>>(std::forward<_Types>(_Args)...);
	}
}

#endif
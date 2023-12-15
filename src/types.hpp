#ifndef DXNA_TYPES_HPP
#define DXNA_TYPES_HPP

#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <any>

namespace dxna {
	//Define um ponteiro para um vetor.
	template <typename T>
	using vectorptr = std::shared_ptr<std::vector<T>>;	

	//Define um ponteiro para um mapa.
	template <typename T1, typename T2>
	using mapptr = std::shared_ptr<std::map<T1, T2>>;

	//Define um pontiero para um tipo aceito em std::any
	using anyptr = std::shared_ptr<std::any>;

	//Converte um objeto any para um tipo definido.
	template <class T>
	T AnyTo(std::any const& a) {
		return std::any_cast<T>(a);
	}

	//Inicializa um ponteiro para um tipo definido.
	template <class _Ty, class... _Types>
	std::shared_ptr<_Ty> New(_Types&&... _Args) {
		return std::make_shared<_Ty>(std::forward<_Types>(_Args)...);
	}	

	//Inicializa um novo ponteiro para um vetor
	template <class _Ty, class... _Types>
	vectorptr<_Ty> NewVector(_Types&&... _Args) {
		return std::make_shared<std::vector<_Ty>>(std::forward<_Types>(_Args)...);
	}	
}

#endif
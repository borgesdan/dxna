#ifndef DXNA_ERROR_HPP
#define DXNA_ERROR_HPP

#include "errorcode.hpp"

namespace dxna {
	
	//Representa uma estrutura de dados que armazena uma flag de erro
	//e um valor de index do argumento de função ou outro valor convencionado.
	struct Error {	
		constexpr Error(ErrorCode const& error) noexcept : Flag(error) {}

		constexpr Error(ErrorCode const& error, int argIndex) noexcept : 
			Flag(error), Index(argIndex) {}

		static constexpr Error NoError() noexcept {	return Error(ErrorCode::NONE); }		

		constexpr bool operator==(const Error& other) const noexcept {
			return Index == other.Index && Flag == other.Flag;
		}

		constexpr bool operator==(const ErrorCode& other) const noexcept {
			return Flag == other;
		}

		constexpr bool HasError() const noexcept {
			return Flag != ErrorCode::NONE;
		}

		int Index { -1 };
		ErrorCode Flag{ ErrorCode::NONE };
	};
}

#endif
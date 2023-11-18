#ifndef DXNA_CS_NULLABLE_HPP
#define DXNA_CS_NULLABLE_HPP

#include "cstypes.hpp"

namespace cs {
	template <typename T>
	struct Nullable {
		constexpr Nullable() = default;
		constexpr Nullable(T const& value) : value(value), hasValue(true) {}

		constexpr bool HasValue() const {
			return hasValue;
		}

		constexpr T Value() const {
			return value;
		}		

		constexpr operator T() const {
			return value;
		}

	private:
		bool hasValue{ false };
		T value{ T() };
	};
}

using nullfloat		= cs::Nullable<float>;
using nulldouble	= cs::Nullable<double>;
using nullsbytecs	= cs::Nullable<sbytecs>;
using nullbytecs	= cs::Nullable<bytecs>;
using nullshortcs	= cs::Nullable<shortcs>;
using nullushortcs	= cs::Nullable<ushortcs>;
using nullintcs		= cs::Nullable<intcs>;
using nulluintcs	= cs::Nullable<uintcs>;
using nulllongcs	= cs::Nullable<longcs>;
using nullulongcs	= cs::Nullable<ulongcs>;
using nullbool		= cs::Nullable<bool>;
using nullcharcs	= cs::Nullable<charcs>;

#endif
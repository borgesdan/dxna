#ifndef CS_NULLABLE_HPP
#define CS_NULLABLE_HPP

namespace cs {
	template <typename T>
	struct Nullable {
		constexpr Nullable() = default;
		constexpr Nullable(T value) : value(value), hasValue(true) {}

		constexpr bool HasValue() const {
			return hasValue;
		}

		constexpr T Value() {
			return value;
		}		

	private:
		bool hasValue{ false };
		T value{ T() };
	};
}

using nfloat	= cs::Nullable<float>;
using ndouble	= cs::Nullable<double>;
using nsbytecs	= cs::Nullable<sbytecs>;
using nbytecs	= cs::Nullable<bytecs>;
using nshortcs	= cs::Nullable<shortcs>;
using nushortcs = cs::Nullable<ushortcs>;
using nintcs	= cs::Nullable<intcs>;
using nuintcs	= cs::Nullable<uintcs>;
using nlongcs	= cs::Nullable<longcs>;
using nulongcs	= cs::Nullable<ulongcs>;

#endif
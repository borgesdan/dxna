#ifndef CS_CSTYPES_HPP
#define CS_CSTYPES_HPP

#include <cstdint>
#include <limits>

namespace cs {
    using sbytecs     = int8_t;
    using bytecs      = uint8_t;
    using shortcs     = int16_t;
    using ushortcs    = uint16_t;
    using intcs       = int32_t;
    using uintcs      = uint32_t;
    using longcs      = int64_t;
    using ulongcs     = uint64_t;

    static constexpr sbytecs    MaxSbyte    = std::numeric_limits<sbytecs>::max();
    static constexpr sbytecs    MinSbyte    = std::numeric_limits<sbytecs>::min();
    static constexpr bytecs     MaxByte     = std::numeric_limits<bytecs>::max();
    static constexpr bytecs     MinByte     = std::numeric_limits<bytecs>::min();
    static constexpr shortcs    MaxShort    = std::numeric_limits<shortcs>::max();
    static constexpr shortcs    MinShort    = std::numeric_limits<shortcs>::min();
    static constexpr ushortcs   MaxUshort   = std::numeric_limits<ushortcs>::max();
    static constexpr ushortcs   MinUshort   = std::numeric_limits<ushortcs>::min();
    static constexpr intcs      MaxInt      = std::numeric_limits<intcs>::max();
    static constexpr intcs      MinInt      = std::numeric_limits<intcs>::min();
    static constexpr uintcs     MaxUint     = std::numeric_limits<uintcs>::max();
    static constexpr uintcs     MinUint     = std::numeric_limits<uintcs>::min();
    static constexpr longcs     MaxLong     = std::numeric_limits<longcs>::max();
    static constexpr longcs     MinLong     = std::numeric_limits<longcs>::min();
    static constexpr ulongcs    MaxUlong    = std::numeric_limits<ulongcs>::max();
    static constexpr ulongcs    MinUlong    = std::numeric_limits<ulongcs>::min();
    static constexpr float      MaxFloat    = std::numeric_limits<float>::max();
    static constexpr float      MinFloat    = std::numeric_limits<float>::min();
    static constexpr double     MaxDouble   = std::numeric_limits<double>::max();
    static constexpr double     MinDouble   = std::numeric_limits<double>::min();
}

#endif
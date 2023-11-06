#ifndef DXNA_CS_CSTYPES_HPP
#define DXNA_CS_CSTYPES_HPP

#include <cstdint>
#include <limits>

using sbytecs	= int8_t;
using bytecs	= uint8_t;
using shortcs	= int16_t;
using ushortcs	= uint16_t;
using intcs		= int32_t;
using uintcs	= uint32_t;
using longcs	= int64_t;
using ulongcs	= uint64_t;
using charcs	= char16_t;

static constexpr sbytecs    SByteMaxValue	= std::numeric_limits<sbytecs>::max();
static constexpr sbytecs    SbyteMinValue	= std::numeric_limits<sbytecs>::min();
static constexpr bytecs     ByteMaxValue	= std::numeric_limits<bytecs>::max();
static constexpr bytecs     ByteMinValue	= std::numeric_limits<bytecs>::min();
static constexpr shortcs    ShortMaxValue	= std::numeric_limits<shortcs>::max();
static constexpr shortcs    ShortMinValue	= std::numeric_limits<shortcs>::min();
static constexpr ushortcs   UShortMaxValue	= std::numeric_limits<ushortcs>::max();
static constexpr ushortcs   UShortMinValue	= std::numeric_limits<ushortcs>::min();
static constexpr intcs      IntMaxValue		= std::numeric_limits<intcs>::max();
static constexpr intcs      IntMinValue		= std::numeric_limits<intcs>::min();
static constexpr uintcs     UIntMaxValue	= std::numeric_limits<uintcs>::max();
static constexpr uintcs     UIntMinValue	= std::numeric_limits<uintcs>::min();
static constexpr longcs     LongMaxValue	= std::numeric_limits<longcs>::max();
static constexpr longcs     LongMinValue	= std::numeric_limits<longcs>::min();
static constexpr ulongcs    ULongMaxValue	= std::numeric_limits<ulongcs>::max();
static constexpr ulongcs    ULongMinValue	= std::numeric_limits<ulongcs>::min();
static constexpr ulongcs    CharMaxValue	= std::numeric_limits<charcs>::max();
static constexpr ulongcs    CharMinValue	= std::numeric_limits<charcs>::min();
static constexpr float      FloatMaxValue	= std::numeric_limits<float>::max();
static constexpr float      FloatMinValue	= std::numeric_limits<float>::min();
static constexpr double     DoubleMaxValue	= std::numeric_limits<double>::max();
static constexpr double     DoubleMinValue	= std::numeric_limits<double>::min();

#endif
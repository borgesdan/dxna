#include "texture.hpp"

namespace dxna::graphics {
	intcs Texture::_lastSortingKey = 0;
	
	vectorptr<Color> Texture2D::GetColorData() {
		const auto colorDataLength = width * height;
		auto colorData = NewVector<Color>(colorDataLength);

		switch (Format) {
		case SurfaceFormat::Single: {
			auto floatData = NewVector<float>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, floatData, 0, floatData->size());

			if (err != ValidadeDataError::ER_NONE) return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
			{
				const auto brightness = floatData->at(i);
				colorData->at(i) = Color(brightness, brightness, brightness);
			}
			break;
		}
		case SurfaceFormat::Color: {
			const auto err = GetData(0, 0, nullptr, colorData, 0, colorData->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			break;
		}
		case SurfaceFormat::Alpha8: {
			auto alpha8Data = NewVector<Alpha8>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, alpha8Data, 0, alpha8Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (int i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(alpha8Data->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::Bgr565: {
			auto bgr565Data = NewVector<Bgr565>(colorDataLength);

			const auto err = GetData(0, 0, nullptr, bgr565Data, 0, bgr565Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(bgr565Data->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::Bgra4444: {
			auto bgra4444Data = NewVector<Bgra4444>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, bgra4444Data, 0, bgra4444Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(bgra4444Data->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::Bgra5551: {
			auto bgra5551Data = NewVector<Bgra5551>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, bgra5551Data, 0, bgra5551Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(bgra5551Data->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::HalfSingle: {
			auto halfSingleData = NewVector<HalfSingle>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, halfSingleData, 0, halfSingleData->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(halfSingleData->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::HalfVector2: {
			auto halfVector2Data = NewVector<HalfVector2>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, halfVector2Data, 0, halfVector2Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(halfVector2Data->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::HalfVector4: {
			auto halfVector4Data = NewVector<HalfVector4>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, halfVector4Data, 0, halfVector4Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(halfVector4Data->at(i).ToVector4());

			break;
		}
		case SurfaceFormat::NormalizedByte2: {
			auto normalizedByte2Data = NewVector<NormalizedByte2>(colorDataLength);
			const auto err = GetData(0, 0, nullptr, normalizedByte2Data, 0, normalizedByte2Data->size());

			if (err != ValidadeDataError::ER_NONE)	return nullptr;

			for (size_t i = 0; i < colorDataLength; ++i)
				colorData->at(i) = Color(normalizedByte2Data->at(i).ToVector4());

			break;
		}
		}

		return colorData;
	}
}
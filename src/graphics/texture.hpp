#ifndef DXNA_GRAPHICS_TEXTURE_HPP
#define DXNA_GRAPHICS_TEXTURE_HPP

#include "graphicsresource.hpp"
#include <cmath>

namespace dxna::graphics {
	class Texture : public GraphicsResource {
	public:
		constexpr intcs GetSortingKey() const noexcept {
			return _sortingKey;
		}

		static constexpr intcs CalculateMipLevels(intcs width, intcs height = 0, intcs depth = 0) noexcept {
			auto levels = 1;
			auto size = std::max(std::max(width, height), depth);

			while (size > 1) {
				size = size / 2;
				levels++;
			}

			return levels;
		}

		static constexpr void GetSizeForLevel(intcs width, intcs height, intcs level, intcs& w, intcs& h) noexcept {
			w = width;
			h = height;

			while (level > 0) {
				--level;
				w /= 2;
				h /= 2;
			}

			if (w == 0)
				w = 1;

			if (h == 0)
				h = 1;
		}

		static constexpr void GetSizeForLevel(intcs width, intcs height, intcs depth, intcs level, intcs& w, intcs& h, intcs& d) noexcept {
			w = width;
			h = height;
			d = depth;

			while (level > 0) {
				--level;
				w /= 2;
				h /= 2;
				d /= 2;
			}

			if (w == 0)
				w = 1;
			if (h == 0)
				h = 1;
			if (d == 0)
				d = 1;
		}

		constexpr intcs GetPitch(intcs width) noexcept {

			int pitch;

			switch (Format)
			{
			case SurfaceFormat::Dxt1:
			case SurfaceFormat::Dxt1SRgb:
			case SurfaceFormat::Dxt1a:
			case SurfaceFormat::RgbPvrtc2Bpp:
			case SurfaceFormat::RgbaPvrtc2Bpp:
			case SurfaceFormat::RgbEtc1:
			case SurfaceFormat::Rgb8Etc2:
			case SurfaceFormat::Srgb8Etc2:
			case SurfaceFormat::Rgb8A1Etc2:
			case SurfaceFormat::Srgb8A1Etc2:
			case SurfaceFormat::Dxt3:
			case SurfaceFormat::Dxt3SRgb:
			case SurfaceFormat::Dxt5:
			case SurfaceFormat::Dxt5SRgb:
			case SurfaceFormat::RgbPvrtc4Bpp:
			case SurfaceFormat::RgbaPvrtc4Bpp:
				pitch = ((width + 3) / 4) * GetSize(Format);
				break;

			default:
				pitch = width * GetSize(Format);
				break;
			};

			return pitch;
		}

		virtual void GraphicsDeviceResetting() {

		}

	public:
		SurfaceFormat Format{ 0 };
		intcs LevelCount{ 0 };

	private:
		intcs _sortingKey{ ++_lastSortingKey };
		static intcs _lastSortingKey;
		void PlatformGraphicsDeviceResetting();
	};	

	class Texture2D : public Texture {
	public:
		enum class SurfaceType
		{
			Texture,
			RenderTarget,
			SwapChainRenderTarget,
		};		

		Texture2D(
			GraphicsDevicePtr const& graphicsDevice,
			intcs width,
			intcs height,
			bool mipmap = false,
			SurfaceFormat const& format = SurfaceFormat::Color,
			SurfaceType const& type = SurfaceType::Texture,
			bool shared = false,
			intcs arraySize = 1) :
			width(width), height(height),
			_texelWidth(1.0F / static_cast<float>(width)),
			_texelHeight(1.0F / static_cast<float>(height)) {
			
			//TODO: Exceptions
			Device(graphicsDevice);
			Format = format;
			LevelCount = mipmap ? CalculateMipLevels(width, height) : 1;
			ArraySize = arraySize;
		}

		constexpr float TexelWidth() const noexcept { return _texelWidth; }
		constexpr float TexelHeight() const noexcept { return _texelHeight; }

		constexpr Rectangle Bounds() const noexcept {
			return Rectangle(0, 0, width, height);
		}

		constexpr intcs Width() const noexcept { return width; }
		constexpr intcs Height() const noexcept { return height; }

		//Erros informados na função SetData
		enum ValidadeDataError {
			ER_NONE,
			//Level must be smaller than the number of levels in this texture.
			ER_ARG_LEVEL_SMALLER_THAN_LEVELCOUNT,
			//ArraySlice must be smaller than the ArraySize of this texture and larger than 0.
			ER_ARG_ARRAYSIZE_SMALLER_THAN_ARRAYSLICE,
			//Rectangle must be inside the texture bounds
			ER_INVALID_RECTANGLE,
			//Data is null.
			ER_ARG_DATA_NULLPTR,
			//StartIndex must be at least zero and smaller than data.Length.
			ER_ARG_STARTINDEX_SMALLER_THAN_DATALENGTH,
			//The data array is too small.
			ER_ARG_DATA_TOO_SMALL,
			//ElementCount is not the right size
			ER_ARG_ELEMENTCOUNT_IS_NOT_RIGHT_SIZE,
			//Type T is of an invalid size for the format of this texture.
			ER_T_INVALID_SIZE_TEXTURE,
		};

		//SetData retorna um código de erro caso algum argumento com valor errado
		//ou retorna NONE caso sucesso.
		template <typename T>
		ValidadeDataError SetData(intcs level, intcs arraySlice, Rectangle* rect, vectorptr<T> data, intcs startIndex, intcs elementCount) {
			Rectangle checkedRect;
			const auto err = ValidateParams(level, arraySlice, rect, data->data(), data->size(), startIndex, elementCount, checkedRect);

			if (err != ValidadeDataError::ER_NONE)
				return err;

			PlatformSetData(level, arraySlice, checkedRect, data->data(), data->size(), startIndex, elementCount);

			return ValidadeDataError::ER_NONE;
		}

		template <typename T>
		ValidadeDataError GetData(intcs level, intcs arraySlice, Rectangle* rect, vectorptr<T> data, intcs startIndex, intcs elementCount) {
			Rectangle checkedRect;
			const auto err = ValidateParams(level, arraySlice, rect, data->data(), data->size(), startIndex, elementCount, checkedRect);

			if (err != ValidadeDataError::ER_NONE)
				return err;

			PlatformGetData(level, arraySlice, checkedRect, data->data(), data->size(), startIndex, elementCount);

			return ValidadeDataError::ER_NONE;
		}

		vectorptr<Color> GetColorData();

	public:
		intcs width{ 0 };
		intcs height{ 0 };
		intcs ArraySize{ 0 };

	private:
		float _texelWidth{ 0 };
		float _texelHeight{ 0 };

		void PlatformConstruct(intcs width, intcs height, bool mipmap, SurfaceFormat format, SurfaceType type, intcs shared) {
			//TODO: remover
		}

		//Para validação de parametros:
		//'level' deve ser maior que 0 e menor ou igual a IntMaxValue;
		//'arraySlice' deve ser maior que 0 e menor ou igual a IntMaxValue;
		//'startIndex' deve ser maior que 0 e menor ou igual a IntMaxValue;
		//'elementCount' deve ser maior que 0 e menor ou igual a IntMaxValue;
		//'rect' pode ser nulo;
		template <typename T>
		ValidadeDataError ValidateParams(size_t level, size_t arraySlice, Rectangle* rect, T* data, size_t dataLength,
			size_t startIndex, size_t elementCount, Rectangle& checkedRect) {
			const auto textureBounds = Rectangle(0, 0, std::max(width >> level, 1), std::max(height >> level, 1));
			checkedRect = rect != nullptr ? *rect : textureBounds;

			if (level > IntMaxValue)
				level = IntMaxValue;
			if (arraySlice > IntMaxValue)
				arraySlice = IntMaxValue;
			if (startIndex > IntMaxValue)
				startIndex = IntMaxValue;
			if (elementCount > IntMaxValue)
				elementCount = IntMaxValue;

			if (level >= LevelCount)
				return ValidadeDataError::ER_ARG_LEVEL_SMALLER_THAN_LEVELCOUNT;

			//TODO
			//if (arraySlice > 0 && !GraphicsDevice.GraphicsCapabilities.SupportsTextureArrays)
			//	throw new ArgumentException("Texture arrays are not supported on this graphics device", "arraySlice");

			if (arraySlice >= ArraySize)
				return ValidadeDataError::ER_ARG_ARRAYSIZE_SMALLER_THAN_ARRAYSLICE;

			if (!textureBounds.Contains(checkedRect)
				|| checkedRect.Width <= 0 || checkedRect.Height <= 0)
				return ValidadeDataError::ER_INVALID_RECTANGLE;

			if (data == nullptr)
				return ValidadeDataError::ER_ARG_DATA_NULLPTR;

			const auto tSize = sizeof(T);
			const auto fSize = GetSize(Format);

			if (tSize > fSize || fSize % tSize != 0)
				return ValidadeDataError::ER_T_INVALID_SIZE_TEXTURE;

			if (startIndex >= dataLength)
				return ValidadeDataError::ER_ARG_STARTINDEX_SMALLER_THAN_DATALENGTH;

			if (dataLength < startIndex + elementCount)
				return ValidadeDataError::ER_ARG_DATA_TOO_SMALL;

			intcs dataByteSize = 0;

			if (IsCompressedFormat(Format)) {
				intcs blockWidth, blockHeight;
				GetBlockSize(Format, blockWidth, blockHeight);

				const auto blockWidthMinusOne = blockWidth - 1;
				const auto blockHeightMinusOne = blockHeight - 1;

				const auto roundedWidth =
					(checkedRect.Width + blockWidthMinusOne) & ~blockWidthMinusOne;
				const auto roundedHeight =
					(checkedRect.Height + blockHeightMinusOne) & ~blockHeightMinusOne;

				//TODO: #if OPENGL
				checkedRect = Rectangle(checkedRect.X & ~blockWidthMinusOne, checkedRect.Y & ~blockHeightMinusOne, roundedWidth, roundedHeight);

				if (Format == SurfaceFormat::RgbPvrtc2Bpp || Format == SurfaceFormat::RgbaPvrtc2Bpp) {
					dataByteSize = (std::max(checkedRect.Width, 16) * std::max(checkedRect.Height, 8) * 2 + 7) / 8;
				}
				else if (Format == SurfaceFormat::RgbPvrtc4Bpp || Format == SurfaceFormat::RgbaPvrtc4Bpp) {
					dataByteSize = (std::max(checkedRect.Width, 8) * std::max(checkedRect.Height, 8) * 4 + 7) / 8;
				}
				else {
					dataByteSize = roundedWidth * roundedHeight * fSize / (blockWidth * blockHeight);
				}
			}
			else {
				dataByteSize = checkedRect.Width * checkedRect.Height * fSize;
			}

			if (elementCount * tSize != dataByteSize)
				return ValidadeDataError::ER_ARG_ELEMENTCOUNT_IS_NOT_RIGHT_SIZE;

			return ValidadeDataError::ER_NONE;
		}

		template <typename T>
		void PlatformSetData(intcs level, intcs arraySlice, Rectangle const& rect, T* data,
			size_t dataLength, intcs startIndex, intcs elementCount) {
			//TODO: remover
		}

		template <typename T>
		void PlatformGetData(intcs level, intcs arraySlice, Rectangle const& rect, T* data,
			size_t dataLength, intcs startIndex, intcs elementCount) {
			//TODO: remover
		}
	};
}

#endif
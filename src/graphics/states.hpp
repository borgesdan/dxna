#ifndef DXNA_GRAPHICS_BLENDSTATE_HPP
#define DXNA_GRAPHICS_BLENDSTATE_HPP

#include "graphicsresource.hpp"
#include "enumerations.hpp"
#include <string>
#include "../structs.hpp"


namespace dxna::graphics {
	struct SamplerState : public GraphicsResource {
		constexpr SamplerState() = default;

		constexpr SamplerState(std::string const& name, TextureFilter const& filter, TextureAddressMode const& addressMode) {
			Name = name;
			Filter = filter;
			AddressU = addressMode;
			AddressV = addressMode;
			AddressW = addressMode;
		}

		bool BindToGraphicsDevice(GraphicsDevice_* device) {
			const auto currentDevice = GraphicsDevice();

			if (currentDevice != nullptr && currentDevice != device)
				return;

			GraphicsDevice(device);
		}

		static SamplerState AnisotropicClamp() {
			return SamplerState("SamplerState.AnisotropicClamp", TextureFilter::Anisotropic, TextureAddressMode::Clamp);
		}

		static SamplerState AnisotropicWrap() {
			return SamplerState("SamplerState.AnisotropicWrap", TextureFilter::Anisotropic, TextureAddressMode::Wrap);
		}

		static SamplerState LinearClamp() {
			return SamplerState("SamplerState.LinearClamp", TextureFilter::Linear, TextureAddressMode::Clamp);
		}

		static SamplerState LinearWrap() {
			return SamplerState("SamplerState.LinearWrap", TextureFilter::Linear, TextureAddressMode::Wrap);
		}

		static SamplerState PointClamp() {
			return SamplerState("SamplerState.PointClamp", TextureFilter::Point, TextureAddressMode::Clamp);
		}

		static SamplerState PointWrap() {
			return SamplerState("SamplerState.PointWrap", TextureFilter::Point, TextureAddressMode::Wrap);
		}

		TextureAddressMode AddressU{ TextureAddressMode::Wrap };
		TextureAddressMode AddressV{ TextureAddressMode::Wrap };
		TextureAddressMode AddressW{ TextureAddressMode::Wrap };
		Color BorderColor{ Colors::White };
		TextureFilter Filter{ TextureFilter::Linear };
		int MaxAnisotropy{ 4 };
		int MaxMipLevel{ 0 };
		float MipMapLevelOfDetailBias{ 0.0F };
		TextureFilterMode FilterMode{ TextureFilterMode::Default };
		CompareFunction ComparisonFunction{ CompareFunction::Never };
	};

	class BlendState {
		using WriteChannel = dxna::graphics::ColorWriteChannels;
	public:
		BlendState();

	public:
		Blend ColorSourceBlend() const;
		Blend ColorDestinationBlend() const;
		BlendFunction ColorBlendFunction() const;
		Blend AlphaSourceBlend() const;
		Blend AlphaDestinationBlend() const;
		BlendFunction AlphaBlendFunction() const;
		WriteChannel ColorWriteChannels() const;
		WriteChannel ColorWriteChannels1() const;
		WriteChannel ColorWriteChannels2() const;
		WriteChannel ColorWriteChannels3() const;
		Color BlendFactor() const;
		int MultiSampleMask() const;
		void Apply(GraphicsDevice& device);

		void ColorSourceBlend(Blend const& value);
		void ColorDestinationBlend(Blend const& value);
		void ColorBlendFunction(BlendFunction const& value);
		void AlphaSourceBlend(Blend const& value);
		void AlphaDestinationBlend(Blend const& value);
		void AlphaBlendFunction(BlendFunction const& value);
		void ColorWriteChannels(WriteChannel const& value);
		void ColorWriteChannels1(WriteChannel const& value);
		void ColorWriteChannels2(WriteChannel const& value);
		void ColorWriteChannels3(WriteChannel const& value);
		void BlendFactor(Color const& value);
		void MultiSampleMask(int const& value);

	public:
		static const BlendState Opaque();
		static const BlendState AlphaBlend();
		static const BlendState Additive();
		static const BlendState NonPremultiplied();

	private:
		BlendState(Blend source, Blend destination, std::string const& name);
	};
}

#endif
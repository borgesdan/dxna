#ifndef DXNA_GRAPHICS_BLENDSTATE_HPP
#define DXNA_GRAPHICS_BLENDSTATE_HPP

#include "graphicsresource.hpp"
#include <string>
#include <vector>

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
				return false;

			GraphicsDevice(device);

			return true;
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

	struct BlendState;
	using ColorWriteChannels_ = dxna::graphics::ColorWriteChannels;

	struct TargetBlendState {
		constexpr TargetBlendState(BlendState const* parent) {
			Parent = parent;
		}

		const BlendState* Parent;
		BlendFunction AlphaBlendFunction{ BlendFunction::Add };
		Blend AlphaDestinationBlend{ Blend::Zero };
		Blend AlphaSourceBlend{ Blend::One };
		BlendFunction ColorBlendFunction{ BlendFunction::Add };
		Blend ColorDestinationBlend{ Blend::Zero };
		Blend ColorSourceBlend{ Blend::One };
		ColorWriteChannels_ ColorWriteChannels{ ColorWriteChannels_::All };
	};

	using TargetBlendState_ = dxna::graphics::TargetBlendState;

	struct BlendState : public GraphicsResource {
		constexpr BlendState() = default;

		BlendState(std::string const& name, Blend const& source, Blend const& destination) {
			Name = name;
			ColorSourceBlend(source);
			AlphaSourceBlend(source);
			ColorDestinationBlend(destination);
			AlphaDestinationBlend(destination);
		}

		bool BindToGraphicsDevice(GraphicsDevice_* device) {
			const auto currentDevice = GraphicsDevice();

			if (currentDevice != nullptr && currentDevice != device)
				return false;

			GraphicsDevice(device);

			return true;
		}

		BlendFunction AlphaBlendFunction() const { return TargetBlendState[0].AlphaBlendFunction; }

		void AlphaBlendFunction(BlendFunction const& value) { TargetBlendState[0].AlphaBlendFunction = value; }

		Blend AlphaDestinationBlend() const { return TargetBlendState[0].AlphaDestinationBlend; }

		void AlphaDestinationBlend(Blend const& value) { TargetBlendState[0].AlphaDestinationBlend = value; }

		Blend AlphaSourceBlend() const { return TargetBlendState[0].AlphaSourceBlend; }

		void AlphaSourceBlend(Blend const& value) { TargetBlendState[0].AlphaSourceBlend = value; }

		BlendFunction ColorBlendFunction() const { return TargetBlendState[0].ColorBlendFunction; }

		void ColorBlendFunction(BlendFunction const& value) { TargetBlendState[0].ColorBlendFunction = value; }

		Blend ColorDestinationBlend() const { return TargetBlendState[0].ColorDestinationBlend; }

		void ColorDestinationBlend(Blend const& value) { TargetBlendState[0].ColorDestinationBlend = value; }

		Blend ColorSourceBlend() const { return TargetBlendState[0].ColorSourceBlend; }

		void ColorSourceBlend(Blend const& value) { TargetBlendState[0].ColorSourceBlend = value; }

		ColorWriteChannels_ ColorWriteChannels() const { return TargetBlendState[0].ColorWriteChannels; }

		void ColorWriteChannels(ColorWriteChannels_ const& value) { TargetBlendState[0].ColorWriteChannels = value; }

		ColorWriteChannels_ ColorWriteChannels1() const { return TargetBlendState[1].ColorWriteChannels; }

		void ColorWriteChannels1(ColorWriteChannels_ const& value) { TargetBlendState[1].ColorWriteChannels = value; }

		ColorWriteChannels_ ColorWriteChannels2() const { return TargetBlendState[2].ColorWriteChannels; }

		void ColorWriteChannels2(ColorWriteChannels_ const& value) { TargetBlendState[2].ColorWriteChannels = value; }

		ColorWriteChannels_ ColorWriteChannels3() const { return TargetBlendState[3].ColorWriteChannels; }

		void ColorWriteChannels3(ColorWriteChannels_ const& value) { TargetBlendState[3].ColorWriteChannels = value; }

		static BlendState Additive() { return BlendState("BlendState.Additive", Blend::SourceAlpha, Blend::One); }
		static BlendState AlphaBlend() { return BlendState("BlendState.AlphaBlend", Blend::One, Blend::InverseSourceAlpha); }
		static BlendState NonPremultiplied() { return BlendState("BlendState.NonPremultiplied", Blend::SourceAlpha, Blend::InverseSourceAlpha); }
		static BlendState Opaque() { return BlendState("BlendState.Opaque", Blend::One, Blend::Zero); }

	public:
		Color BlendFactor{ Colors::White };
		intcs MultiSampleMask{ MaxInt };
		bool IndependentBlendEnable{ false };

		std::vector<TargetBlendState_> TargetBlendState{
			TargetBlendState_(this),
			TargetBlendState_(this),
			TargetBlendState_(this),
			TargetBlendState_(this),
		};
	};

	struct DepthStencilState : public GraphicsResource {

		constexpr DepthStencilState() = default;

		constexpr DepthStencilState(std::string const& name, bool depthBufferEnable, bool depthBufferWriteEnable) {
			Name = name;
			DepthBufferEnable = depthBufferEnable;
			DepthBufferWriteEnable = depthBufferWriteEnable;			
		}

		bool BindToGraphicsDevice(GraphicsDevice_* device) {
			const auto currentDevice = GraphicsDevice();

			if (currentDevice != nullptr && currentDevice != device)
				return false;

			GraphicsDevice(device);

			return true;
		}

		static DepthStencilState Default() { return DepthStencilState("DepthStencilState.Default", true, true); }
		static DepthStencilState DepthRead() { return DepthStencilState("DepthStencilState.DepthRead", true, false); }
		static DepthStencilState None() { return DepthStencilState("DepthStencilState.None", false, false); }

		bool DepthBufferEnable{ true };
		bool DepthBufferWriteEnable{ true };
		CompareFunction DepthBufferFunction{ CompareFunction::LessEqual };
		bool StencilEnable{ true };
		CompareFunction StencilFunction{ CompareFunction::Always };
		StencilOperation StencilPass{ StencilOperation::Keep };
		StencilOperation StencilFail{ StencilOperation::Keep };
		StencilOperation StencilDepthBufferFail{ StencilOperation::Keep };
		bool TwoSidedStencilMode{ false };
		CompareFunction CounterClockwiseStencilFunction{ CompareFunction::Always };
		StencilOperation CounterClockwiseStencilFail{ StencilOperation::Keep };
		StencilOperation CounterClockwiseStencilPass{ StencilOperation::Keep };
		StencilOperation CounterClockwiseStencilDepthBufferFail{ StencilOperation::Keep };
		intcs StencilMask{ MaxInt };
		intcs StencilWriteMask{ MaxInt };
		intcs ReferenceStencil{ 0 };
	};
}

#endif
#ifndef DXNA_GRAPHICS_BLENDSTATE_HPP
#define DXNA_GRAPHICS_BLENDSTATE_HPP

#include "enumerations.hpp"
#include <string>
#include "../structs.hpp"

namespace dxna::graphics {
	class GraphicsDevice;

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
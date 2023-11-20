#ifndef DXNA_GRAPHICS_GRAPHICSDEVICE_HPP
#define DXNA_GRAPHICS_GRAPHICSDEVICE_HPP

#include <memory>
#include "forward.hpp"
#include "viewport.hpp"
#include "../structs.hpp"

namespace dxna::graphics {
	class GraphicsDevice {
	public:
		bool UseHalfPixelOffset = false;

	private:
		static Color _discardColor;

		Viewport _viewport;
		Color _blendFactor = Colors::White;
		
		BlendStatePtr _blendState;
		BlendStatePtr _actualBlendState;
		BlendStatePtr _blendStateAdditive;
		BlendStatePtr _blendStateAlphaBlend;
		BlendStatePtr _blendStateNonPremultiplied;
		BlendStatePtr _blendStateOpaque;

		DepthStencilStatePtr _depthStencilState;
		DepthStencilStatePtr _actualDepthStencilState;
		DepthStencilStatePtr _depthStencilStateDefault;
		DepthStencilStatePtr _depthStencilStateDepthRead;
		DepthStencilStatePtr _depthStencilStateNone;

		RasterizerStatePtr _rasterizerState;
		RasterizerStatePtr _actualRasterizerState;
		RasterizerStatePtr _rasterizerStateCullClockwise;
		RasterizerStatePtr _rasterizerStateCullCounterClockwise;
		RasterizerStatePtr _rasterizerStateCullNone;

		Rectangle _scissorRectangle;
	};
}

#endif
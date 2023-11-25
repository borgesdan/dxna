#ifndef DXNA_GRAPHICS_GRAPHICSDEVICE_HPP
#define DXNA_GRAPHICS_GRAPHICSDEVICE_HPP

#include <memory>
#include "forward.hpp"
#include "viewport.hpp"
#include "../structs.hpp"
#include "vertex.hpp"

namespace dxna::graphics {
	class GraphicsDevice {
	public:
		bool UseHalfPixelOffset = false;

	private:
		static Color _discardColor;

		Viewport _viewport;
		Color _blendFactor = Colors::White;
		
		BlendStatePtr _blendState = nullptr;
		BlendStatePtr _actualBlendState = nullptr;
		BlendStatePtr _blendStateAdditive = nullptr;
		BlendStatePtr _blendStateAlphaBlend = nullptr;
		BlendStatePtr _blendStateNonPremultiplied = nullptr;
		BlendStatePtr _blendStateOpaque = nullptr;

		DepthStencilStatePtr _depthStencilState = nullptr;
		DepthStencilStatePtr _actualDepthStencilState = nullptr;
		DepthStencilStatePtr _depthStencilStateDefault = nullptr;
		DepthStencilStatePtr _depthStencilStateDepthRead = nullptr;
		DepthStencilStatePtr _depthStencilStateNone = nullptr;

		RasterizerStatePtr _rasterizerState = nullptr;
		RasterizerStatePtr _actualRasterizerState = nullptr;
		RasterizerStatePtr _rasterizerStateCullClockwise = nullptr;
		RasterizerStatePtr _rasterizerStateCullCounterClockwise = nullptr;
		RasterizerStatePtr _rasterizerStateCullNone = nullptr;

		Rectangle _scissorRectangle{};
		VertexBufferBindingsPtr _vertexBuffers = nullptr;
		IndexBufferPtr _indexBuffer = nullptr;
		
	};
}

#endif
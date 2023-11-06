#ifndef DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP
#define DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP

#include <string>
#include "../cs/cstypes.hpp"
#include "enumerations.hpp"
#include "../structs.hpp"

namespace dxna::graphics {
	class GraphicsDevice;
	using GraphicsDevice_ = dxna::graphics::GraphicsDevice;

	class GraphicsResource {	
	public:	
		constexpr GraphicsResource() = default;

		virtual ~GraphicsResource(){}		

		constexpr GraphicsDevice_* GraphicsDevice() { 
			return graphicsDevice; 
		}
		
		void GraphicsDevice(GraphicsDevice_* value) {
			if (!value || graphicsDevice == value)
				return;			

			//TODO
			graphicsDevice = value;
		}

	protected:
		virtual void GraphicsDeviceResetting() {}
	
	public:
		std::string Name;

	private:
		GraphicsDevice_ * graphicsDevice;
	};
}

#endif
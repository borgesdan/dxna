#ifndef DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP
#define DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP

#include <string>
#include "../cs/cstypes.hpp"
#include "enumerations.hpp"
#include "../structs.hpp"
#include <memory>
#include "forward.hpp"

namespace dxna::graphics {	

	class GraphicsResource {	
	public:	
		constexpr GraphicsResource() = default;

		virtual ~GraphicsResource(){}		

		GraphicsDevicePtr Device() const { 
			return graphicsDevice; 
		}
		
		void Device(GraphicsDevicePtr const& value) {
			if (!value || graphicsDevice == value)
				return;			

			//TODO
			graphicsDevice = value;
		}

	protected:
		virtual void GraphicsDeviceReseting() {}
	
	public:
		std::string Name;

	private:
		GraphicsDevicePtr graphicsDevice;
	};	
}

#endif
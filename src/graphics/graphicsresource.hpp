#ifndef DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP
#define DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP

#include <string>
#include <memory>
#include <vector>
#include "../structs.hpp"
#include "../types.hpp"
#include "../cs/cs.hpp"
#include "enumerations.hpp"
#include "forward.hpp"
#include <cassert>
#include "packedvector.hpp"

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
		virtual void GraphicsDeviceResetting() {}
	
	public:
		std::string Name;

	private:
		GraphicsDevicePtr graphicsDevice;
	};	
}

#endif
#ifndef DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP
#define DXNA_GRAPHICS_GRAPHICSRESOURCE_HPP

#include <string>
#include "../cs/cstypes.hpp"

namespace dxna::graphics {
	class GraphicsDevice;

	class GraphicsResource {
	public:
		GraphicsResource() = default;		
		virtual ~GraphicsResource() = default;

		std::string Name() const;
		void Name(std::string const& name);

		GraphicsDevice* Device() { return _parent; }

	protected:
		GraphicsDevice* _parent;

	private:
		std::string _localName;
		ulongcs _internalHandle{ 0 };
	};
}

#endif
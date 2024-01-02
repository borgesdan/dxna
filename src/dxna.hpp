#ifndef DXNA_DXNA_HPP
#define DXNA_DXNA_HPP

#include "structs.hpp"
#include "static.hpp"

#include "graphics/adapter.hpp"

namespace dxna {
	inline void RegisterDefaultStaticCtors() {
		StaticManager::RegisterCtors(dxna::graphics::GraphicsAdapter::GraphicsAdapter_ctor);
	}
}

#endif
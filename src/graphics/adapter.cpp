#include "adapter.hpp"

namespace dxna::graphics {
	vectorptr<GraphicsAdapterPtr> GraphicsAdapter::_adapters = NewVector<GraphicsAdapterPtr>();
}
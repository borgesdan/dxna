#include "effect.hpp"

namespace dxna::graphics {
	ConstantBuffer::ConstantBuffer(GraphicsDevice_* device, intcs const& sizeInBytes, std::vector<intcs> const& parameterIndexes, std::vector<intcs> const& parameterOffsets, std::string const& name) {
		this->GraphicsDevice(device);

		_buffer = std::vector<bytecs>(sizeInBytes);
		_parameters = parameterIndexes;
		_offsets = parameterOffsets;
		_name = name;

		PlatformInitialize();
	}
}
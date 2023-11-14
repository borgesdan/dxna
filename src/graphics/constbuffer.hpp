#ifndef DXNA_GRAPHICS_CONSTBUFFER_HPP
#define DXNA_GRAPHICS_CONSTBUFFER_HPP

#include "graphicsresource.hpp"

namespace dxna::graphics {
	class ConstantBuffer : public GraphicsResource {
	public:
		ConstantBuffer(GraphicsDevicePtr const& device, intcs sizeInBytes,
			vectorptr<intcs> const& parametersIndexes,
			vectorptr<intcs> const& parameterOffsets):
			_parameters(parametersIndexes), _offsets(parameterOffsets)
		{
			_buffer = NewVectorPtr<bytecs>(sizeInBytes);
			Device(device);	
			
			PlatformInitialize();
		}

		void PlatformInitialize() {
			//TODO: implementar
		}

		void Clear() {
			PlatformClear();
		}

		void PlatformClear() {
			//TODO: implementar
		}

	private:
		void SetData(intcs offset, intcs rows, intcs columns, anyptr const& data, bool isarray = true);
		intcs SetParameter(intcs offset, EffectParameter& param);
		void Update(EffectParameterCollection& parameters);

	private:
		vectorptr<bytecs> _buffer;
		vectorptr<intcs> _parameters;
		vectorptr<intcs> _offsets;		
		ulongcs _stateKey;		
	};
}

#endif
#ifndef DXNA_GRAPHICS_CONSTBUFFER_HPP
#define DXNA_GRAPHICS_CONSTBUFFER_HPP

#include "graphicsresource.hpp"

namespace dxna::graphics {
	class ConstantBuffer : public GraphicsResource {
	public:
		ConstantBuffer() = default;

		ConstantBuffer(GraphicsDevicePtr const& device, intcs sizeInBytes,
			vectorptr<intcs> const& parametersIndexes,
			vectorptr<intcs> const& parameterOffsets,
			std::string name) :
			_parameters(parametersIndexes), _offsets(parameterOffsets), _name(name)	{
			_buffer = NewVector<bytecs>(sizeInBytes);
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

		bool operator==(const ConstantBuffer& other) const {
			return _buffer == other._buffer
				&& _parameters == other._parameters
				&& _offsets == other._offsets
				&& _stateKey == other._stateKey;
		}

		bool IsEmpty() const {
			return _buffer == nullptr || _buffer->empty();
		}

		void PlatformApply(GraphicsDevice& device, ShaderStage state, int slot) {
			//TODO
		}

	private:
		void SetData(intcs offset, intcs rows, intcs columns, anyptr const& data, bool isarray = true);
		intcs SetParameter(intcs offset, EffectParameter& param);
		void Update(EffectParameterCollection& parameters);

	private:
		vectorptr<bytecs> _buffer = nullptr;
		vectorptr<intcs> _parameters = nullptr;
		vectorptr<intcs> _offsets = nullptr;
		ulongcs _stateKey{ 0 };
		std::string _name;
	};

	class ConstantBufferCollection {
	public:
		ConstantBufferCollection(ShaderStage stage, size_t maxBuffers) :
			_stage(stage), _maxbuffers(maxBuffers),
			_buffers(NewVector<ConstantBufferPtr>(maxBuffers)) {
		}

		ConstantBufferPtr At(size_t index) { 
			if(_isclear)
				_buffers->resize(_maxbuffers);

			return _buffers->at(index); 
		}

		ConstantBufferPtr operator[](size_t index) { 
			if (_isclear)
				_buffers->resize(_maxbuffers);

			return _buffers->at(index); 
		}

		void Clear();

		//TODO #if WEB / OPENGL
		void SetConstantBuffers(GraphicsDevice& device);

	private:
		vectorptr<ConstantBufferPtr> _buffers = nullptr;
		ShaderStage _stage{ ShaderStage::Vertex };
		size_t _maxbuffers{ 0 };
		bool _isclear{ false };
	};
}

#endif
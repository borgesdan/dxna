#include "constbuffer.hpp"
#include "../cs/buffer.hpp"
#include "effect.hpp"

using namespace cs;

namespace dxna::graphics {
	void ConstantBuffer::SetData(intcs offset, intcs rows, intcs columns, anyptr const& data, bool isarray)	{
		const auto elementSize = 4;
		const auto rowSize = elementSize * 4;

		if (rows == 1 && columns == 1) {
			if (isarray) {
				auto source = AnyTo<vectorptr<bytecs>>(data);

				Buffer::BlockCopy(source->data(), 0, _buffer->data(), offset, elementSize);
			}
		}
		else if (rows == 1 || (rows == 4 && columns == 4)) {
			auto source = AnyTo<vectorptr<bytecs>>(data);
			auto len = rows * columns * elementSize;

			if (_buffer->size() - offset > len)
				len = _buffer->size() - offset;

			Buffer::BlockCopy(source->data(), 0, _buffer->data(), offset, rows * columns * elementSize);
		}
		else {
			auto source = AnyTo<vectorptr<bytecs>>(data);
			auto stride = (columns * elementSize);
			
			for (size_t y = 0; y < rows; ++y)
				Buffer::BlockCopy(source->data(), stride * y, _buffer->data(), offset + (rowSize * y), stride);
		}
	}

	intcs ConstantBuffer::SetParameter(intcs offset, EffectParameter& param) {
		const auto elementSize = 4;
		const auto rowSize = elementSize * 4;

		auto rowsUsed = 0;
		auto elements = param.Elements;

		if (elements->Count() > 0) {
			for (size_t i = 0; i < elements->Count(); i++)
			{
				const auto rowsUsedSubParam = SetParameter(offset,*elements->At(i));
				offset += rowsUsedSubParam * rowSize;
				rowsUsed += rowsUsedSubParam;
			}
		}
		else if (param.Data != nullptr) {
			switch (param.ParameterType)
			{
			case EffectParameterType::Single:
			case EffectParameterType::Int32:
			case EffectParameterType::Bool:
				
				if (param.ParameterClass == EffectParameterClass::Matrix) {
					rowsUsed = param.ColumnCount;
					SetData(offset, param.ColumnCount, param.RowCount, param.Data);
				}
				else {
					rowsUsed = param.RowCount;
					SetData(offset, param.RowCount, param.ColumnCount, param.Data);
				}
				break;
			default:
				return -1;
			}
		}

		return rowsUsed;
	}

	void ConstantBuffer::Update(EffectParameterCollection& parameters) {
		if (_stateKey > EffectParameter::NextStateKey)
			_stateKey = 0;

		for (size_t p = 0; p < _parameters->size(); ++p)
		{
			auto index = _parameters->at(p);
			auto param = parameters[index];

			if (param->StateKey < _stateKey)
				continue;

			auto offset = _offsets->at(p);			

			SetParameter(offset, *param);
		}

		_stateKey = EffectParameter::NextStateKey;
	}
	
	void ConstantBufferCollection::Clear() {
		_buffers->clear();
		_isclear = true;
	}

	void ConstantBufferCollection::SetConstantBuffers(GraphicsDevice& device) {
		if (_isclear)
			return;
		
		for (size_t i = 0; i < _buffers->size(); i++) {
			auto buffer = _buffers->at(i);

			if (!buffer->IsEmpty()) {
				buffer->PlatformApply(device, _stage, i);
			}
		}
	}
}
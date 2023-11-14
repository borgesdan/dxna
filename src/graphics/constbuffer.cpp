#include "constbuffer.hpp"

namespace dxna::graphics {
	void ConstantBuffer::SetData(intcs offset, intcs rows, intcs columns, anyptr const& data, bool isarray)	{
		const auto elementSize = 4;
		const auto rowSize = elementSize * 4;

		if (rows == 1 && columns == 1) {
			if (isarray) {
				auto source = AnyTo<vectorptr<bytecs>>(data);

				for (size_t i = 0; i < elementSize; ++i) {
					_buffer->at(offset + i) = source->at(i);
				}
			}
		}
		else if (rows == 1 || (rows == 4 && columns == 4)) {
			auto source = AnyTo<vectorptr<bytecs>>(data);
			auto len = rows * columns * elementSize;

			if (_buffer->size() - offset > len)
				len = _buffer->size() - offset;

			const auto count = rows * columns * elementSize;
			for (size_t i = 0; i < count; ++i) {
				_buffer->at(offset + i) = source->at(i);
			}
		}
		else {
			auto source = AnyTo<vectorptr<bytecs>>(data);
			auto stride = (columns * elementSize);

			for (size_t y = 0; y < rows; ++y) {
				for (size_t i = 0; i < stride; ++i) {
					_buffer->at(offset + (rowSize * y) + i) = source->at((stride * y) + i);
				}
			}
		}
	}
}
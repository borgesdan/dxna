#include "stream.hpp"

namespace cs {
	void MemoryStream::WriteTo(Stream* stream) const {
		if (stream == nullptr)
			return;

		if (!_isOpen)
			return;

		stream->Write(_buffer.data(),
			static_cast<intcs>(_buffer.size()),
			static_cast<intcs>(_origin),
			static_cast<intcs>(_length - _origin));
	}
}
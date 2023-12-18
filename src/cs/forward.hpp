#ifndef DXNA_CS_FORWARD_HPP
#define DXNA_CS_FORWARD_HPP

#include <memory>

namespace cs {
	class Stream;
	class MemoryStream;
	class BinaryReader;
	class Encoding;
	class Decoder;
	class DefaultDecoder;

	using StreamPtr = std::shared_ptr<Stream>;
	using MemoryStreamPtr = std::shared_ptr<MemoryStream>;
	using BinaryReaderPtr = std::shared_ptr<BinaryReader>;
	using EncodingPtr = std::shared_ptr<Encoding>;
	using DecoderPtr = std::shared_ptr<Decoder>;
	using DefaultDecoderPtr = std::shared_ptr<DefaultDecoder>;
}

#endif
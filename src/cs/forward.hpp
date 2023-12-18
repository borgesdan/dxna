#ifndef DXNA_CS_FORWARD_HPP
#define DXNA_CS_FORWARD_HPP

#include <memory>

namespace cs {
	class Stream;
	class MemoryStream;

	using StreamPtr = std::shared_ptr<Stream>;
	using MemoryStreamPtr = std::shared_ptr<MemoryStream>;
}

#endif
#ifndef DXNA_CS_ENCODING_HPP
#define DXNA_CS_ENCODING_HPP

#include "cstypes.hpp"
#include "forward.hpp"

namespace cs {

	class Encoding {
	public:
		virtual DecoderPtr GetDecoder() {
			auto def = std::make_shared<DefaultDecoder>(this);
			auto redef = dynamic_pointer_cast<Decoder>(def);

			return redef;
		}

		virtual intcs GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex) = 0;
	};

	class Decoder {
	public:
		virtual intcs GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex) = 0;
	};

	class DefaultDecoder : public Decoder {
	public:
		DefaultDecoder(Encoding* encoding) {
			m_encoding = encoding;
			m_hasInitializedEncoding = true;
		}

		virtual intcs GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex) override {

		}

	private:
		Encoding* m_encoding = nullptr;
		bool m_hasInitializedEncoding{ false };
	};

	class UTF8Encoding : public Encoding {

	};
}

#endif
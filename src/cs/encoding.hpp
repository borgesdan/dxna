#ifndef DXNA_CS_ENCODING_HPP
#define DXNA_CS_ENCODING_HPP

#include "cstypes.hpp"
#include "forward.hpp"
#include "../types.hpp"
#include "../error.hpp"

namespace cs {
	class Encoding {
	public:		
		virtual DecoderPtr GetDecoder() {
			auto def = std::make_shared<DefaultDecoder>(this);
			auto redef = dynamic_pointer_cast<Decoder>(def);

			return redef;
		}

		virtual dxna::Error GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex,
			intcs& result) = 0;

	protected:
		Encoding(intcs codePage = 0) {
			m_codePage = codePage >= 0 ? codePage : 0;
		}

	private:
		intcs m_codePage{ 0 };
		bool m_isReadOnly = true;
	};

	class Decoder {
	public:
		virtual dxna::Error GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex,
			intcs& result) = 0;
	};

	class DefaultDecoder : public Decoder {
	public:
		DefaultDecoder(Encoding* encoding) {
			m_encoding = encoding;
			m_hasInitializedEncoding = true;
		}

		virtual dxna::Error GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex,
			intcs& result) override {
			return dxna::Error::NoError();
		}

	private:
		Encoding* m_encoding = nullptr;
		bool m_hasInitializedEncoding{ false };
	};

	class UTF8Decoder : public Decoder {
	public:
		UTF8Decoder(Encoding* encoding) :m_encoding(encoding) {
		}

		virtual dxna::Error GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex,
			intcs& result) override {
			m_encoding->GetChars(bytes, bytesLength, byteIndex, byteCount, chars, charsLength, charIndex, result);
		}

	private:
		Encoding* m_encoding;
	};

	class UTF8Encoding : public Encoding {
	public:
		virtual dxna::Error GetChars(
			bytecs* bytes,
			size_t bytesLength,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			size_t charsLength,
			intcs charIndex,
			intcs& result) override {

			using dxerr = dxna::Error;
			using dxcode = dxna::ErrorCode;

			//if (chars.Length == 0) chars = new char[1];
			if (bytesLength == 0 || charsLength == 0) {
				result = 0;
				return dxerr::NoError();;
			}

			if (bytes == nullptr)
				return dxerr(dxcode::ARGUMENT_IS_NULL, 0);
			
			if (chars == nullptr)
				return dxerr(dxcode::ARGUMENT_IS_NULL, 4);

			if (byteIndex < 0)
				return dxerr(dxcode::ARGUMENT_OUT_OF_RANGE, 2);

			if (byteCount < 0)
				return dxerr(dxcode::ARGUMENT_OUT_OF_RANGE, 3);

			if (charIndex < 0 || charIndex > charsLength)
				return dxerr(dxcode::ARGUMENT_OUT_OF_RANGE, 6);

			const auto charCount = charsLength - charIndex;			

			auto res = internalGetChars(bytes, byteIndex, byteCount, chars, charIndex, result);

			return dxerr::NoError();
		}

	private:
		dxna::Error internalGetChars(
			bytecs* bytes,
			intcs byteIndex,
			intcs byteCount,
			charcs* chars,
			intcs charIndex,
			intcs& result) {

			return dxna::Error::NoError();
		}
	};
}

#endif